# THIS FILE WAS AUTO-GENERATED
#
#  $ lcitool manifest ci/manifest.yml
#
# https://gitlab.com/libvirt/libvirt-ci

function install_buildenv() {
    apk update
    apk upgrade
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
        samurai
    rm -f /usr/lib*/python3*/EXTERNALLY-MANAGED
    apk list --installed | sort > /packages.txt
    mkdir -p /usr/libexec/ccache-wrappers
    ln -s /usr/bin/ccache /usr/libexec/ccache-wrappers/cc
    ln -s /usr/bin/ccache /usr/libexec/ccache-wrappers/gcc
}

export CCACHE_WRAPPERSDIR="/usr/libexec/ccache-wrappers"
export LANG="en_US.UTF-8"
export MAKE="/usr/bin/make"
export NINJA="/usr/bin/ninja"
export PYTHON="/usr/bin/python3"
