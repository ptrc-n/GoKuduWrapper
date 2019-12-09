
#
# Builds an image used for testing a go wrapper around kudus c++ client api
#
FROM apache/kudu:latest-xenial as kudu-go-test

USER root

RUN apt-get update
RUN apt-get install -y ca-certificates wget build-essential
RUN rm -rf /var/lib/apt/lists/*

# install kudu client lib
COPY --from=apache/kudu:build-latest-xenial \
    /usr/local/lib/libkudu* \
    /usr/local/lib/
COPY --from=apache/kudu:build-latest-xenial \
    /usr/local/include/kudu \
    /usr/local/include/kudu
# as docker does not preserve symlinks but copies files instead
RUN rm /usr/local/lib/libkudu_client.so \ 
    && rm /usr/local/lib/libkudu_client.so.0 \
    && ln -s /usr/local/lib/libkudu_client.so.0.1.0 /usr/local/lib/libkudu_client.so.0 \
    && ln -s /usr/local/lib/libkudu_client.so.0 /usr/local/lib/libkudu_client.so \
    && ldconfig
# install golang
RUN mkdir -p /tmp/golang \
    && cd /tmp/golang \
    && wget https://dl.google.com/go/go1.13.linux-amd64.tar.gz \
    && tar -xzf go1.13.linux-amd64.tar.gz \
    && mv go /usr/local/ \
    && echo 'export PATH=$PATH:/usr/local/go/bin' >> /etc/profile.d/golang.sh && . /etc/profile \
    && cd / && rm -rf /tmp/golang
RUN echo 'export PATH=$PATH:/opt/kudu/bin' >> /etc/profile.d/kudu.sh && . /etc/profile

# copy project and prepare entrypoint
RUN mkdir -p /root/go/src/gokudugo
COPY . /root/go/src/gokudugo/

LABEL descriptoion="Image contains Apache Kudu binaries and c++ client libs as well as a golang wrapper around these"
LABEL maintainer = "ptrc-n"

WORKDIR /root/go/src/gokudugo
ENTRYPOINT ["/root/go/src/gokudugo/container/go-kudu-wrapper-entry.sh"]

