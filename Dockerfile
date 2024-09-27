FROM gcc:8

RUN apt-get update && apt-get install -y git cmake

RUN mkdir /git
WORKDIR /git

RUN git clone https://github.com/google/googletest.git \
    && cd /git/googletest \
    && git checkout release-1.8.1 \
    && cmake . \
    && cmake --build . --target install \
    && rm /git/googletest -rf

COPY / /code

WORKDIR /code/build

RUN cmake -DTEST_ENABLED=OFF -DEXAMPLE_ENABLED=OFF -DENABLE_VENDOR_SRC=OFF ..
RUN cmake --build . --target install -j 2

CMD ["/bin/bash"]