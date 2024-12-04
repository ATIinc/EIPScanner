FROM gcc:8 AS prepare_testing

RUN apt-get update && apt-get install -y git cmake

RUN mkdir /git
WORKDIR /git

RUN git clone https://github.com/google/googletest.git \
    && cd /git/googletest \
    && git checkout release-1.8.1 \
    && cmake . \
    && cmake --build . --target install \
    && rm /git/googletest -rf

RUN apt install -y libgmock-dev

FROM prepare_testing AS build_devcontainer

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    # [Optional] Add sudo support. Omit if you don't need to install software after connecting.
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

USER ${USERNAME}

WORKDIR /workspaces/devcontainer


# Create a new stage target that installs the EIPScanner library
FROM prepare_testing AS install_library

COPY / /code

RUN mkdir -p /code/build \
    && cd /code/build \
    && cmake -DTEST_ENABLED=OFF -DEXAMPLE_ENABLED=OFF -DENABLE_VENDOR_SRC=OFF .. \
    && cmake --build . --target install -j 2

WORKDIR /code