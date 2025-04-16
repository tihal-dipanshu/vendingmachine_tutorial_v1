FROM yg397/thrift-microservice-deps:xenial

ARG NUM_CPUS=4

# Install Python 3.6
RUN apt-get update && \
    apt-get install -y software-properties-common && \
    add-apt-repository ppa:deadsnakes/ppa && \
    apt-get update && \
    apt-get install -y python3.6 python3.6-dev python3-pip

COPY ./ /vending-machine-microservices
RUN cd /vending-machine-microservices \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && make -j${NUM_CPUS} \
    && make install

WORKDIR /vending-machine-microservices
