# --------- build ----------- #
FROM ubuntu AS buildlibrary
COPY ./Library ./Library
COPY ./Web ./Web
COPY ./oatpp ./oatpp

WORKDIR "./Library"

RUN apt-get update && apt-get -y install cmake protobuf-compiler g++
RUN mkdir buildllib

WORKDIR "./buildlib"

RUN cmake ..
RUN make install


WORKDIR "../../oatpp"
RUN mkdir buildoat
WORKDIR "./buildoat"
RUN cmake ..
RUN make install

WORKDIR "../../Web"

RUN mkdir buildweb
WORKDIR "./buildweb"

RUN cmake ..
RUN make

WORKDIR "../../"

# ---------- run ------------ #
FROM ubuntu:latest

WORKDIR /service

COPY --from=buildlibrary ./Library/buildlib/libbfinder.so.0.0.1 .
COPY --from=buildlibrary ./Web/buildweb/Web .

VOLUME /dataset

EXPOSE 8000

ENV DATASET_PATH "/dataset"
ENV LD_LIBRARY_PATH=.
CMD  ["./Web"]