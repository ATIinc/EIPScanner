FROM gcc:8 as prepareTesting

RUN apt-get update && apt-get install -y git cmake

RUN mkdir /git
WORKDIR /git

RUN git clone https://github.com/google/googletest.git \
    && cd /git/googletest \
    && git checkout release-1.8.1 \
    && cmake . \
    && cmake --build . --target install \
    && rm /git/googletest -rf

# Create a new stage target that installs the EIPScanner library
FROM prepareTesting as installLibrary

COPY / /code

RUN mkdir -p /code/build \
    && cd /code/build \
    && cmake -DTEST_ENABLED=OFF -DEXAMPLE_ENABLED=OFF -DENABLE_VENDOR_SRC=OFF .. \
    && cmake --build . --target install -j 2

WORKDIR /code