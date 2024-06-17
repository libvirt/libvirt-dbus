# THIS FILE WAS AUTO-GENERATED
#
#  $ lcitool manifest ci/manifest.yml
#
# https://gitlab.com/libvirt/libvirt-ci

FROM docker.io/library/alpine:edge

RUN apk update && \
    apk upgrade && \
    apk add \
        ca-certificates \
        ccache \
        dbus \
        gcc \
        git \
        glib-dev \
        libvirt-dev \
        libvirt-glib-dev \
        make \
        meson \
        musl-dev \
        pkgconf \
        py3-dbus \
        py3-docutils \
        py3-flake8 \
        py3-gobject3 \
        py3-pytest \
        python3 \
        samurai && \
    rm -f /usr/lib*/python3*/EXTERNALLY-MANAGED && \
    apk list --installed | sort > /packages.txt && \
    mkdir -p /usr/libexec/ccache-wrappers && \
    ln -s /usr/bin/ccache /usr/libexec/ccache-wrappers/cc && \
    ln -s /usr/bin/ccache /usr/libexec/ccache-wrappers/gcc

ENV CCACHE_WRAPPERSDIR "/usr/libexec/ccache-wrappers"
ENV LANG "en_US.UTF-8"
ENV MAKE "/usr/bin/make"
ENV NINJA "/usr/bin/ninja"
ENV PYTHON "/usr/bin/python3"
