FROM gcc:latest

LABEL maintainer="Anthony Farquharson (scooterdelta@gmail.com)"

RUN apt-get update \
    && apt-get install -y libboost-dev libsfml-dev libboost-test-dev \
    && curl https://cmake.org/files/v3.11/cmake-3.11.3-Linux-x86_64.sh -o /tmp/curl-install.sh \
    && chmod u+x /tmp/curl-install.sh \
    && mkdir /usr/bin/cmake \
    && /tmp/curl-install.sh --skip-license --prefix=/usr/bin/cmake \
    && rm /tmp/curl-install.sh

ENV PATH="/usr/bin/cmake/bin:${PATH}"
