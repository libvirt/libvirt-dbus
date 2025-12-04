# THIS FILE WAS AUTO-GENERATED
#
#  $ lcitool manifest ci/manifest.yml
#
# https://gitlab.com/libvirt/libvirt-ci

function install_buildenv() {
    dnf update -y
    dnf install 'dnf-command(config-manager)' -y
    dnf config-manager --set-enabled -y crb
    dnf install -y epel-release
    dnf install almalinux-release-devel -y
    dnf config-manager --set-enabled -y devel
    dnf install -y \
        ca-certificates \
        ccache \
        dbus-daemon \
        gcc \
        git \
        glib2-devel \
        glibc-devel \
        glibc-langpack-en \
        libvirt-devel \
        libvirt-glib-devel \
        make \
        meson \
        ninja-build \
        pkgconfig \
        python3 \
        python3-dbus \
        python3-docutils \
        python3-gobject \
        python3-pip \
        python3-pytest \
        python3-setuptools \
        python3-wheel \
        rpm-build \
        systemd-rpm-macros
    rm -f /usr/lib*/python3*/EXTERNALLY-MANAGED
    rpm -qa | sort > /packages.txt
    mkdir -p /usr/libexec/ccache-wrappers
    ln -s /usr/bin/ccache /usr/libexec/ccache-wrappers/cc
    ln -s /usr/bin/ccache /usr/libexec/ccache-wrappers/gcc
    /usr/bin/pip3 install flake8
}

export CCACHE_WRAPPERSDIR="/usr/libexec/ccache-wrappers"
export LANG="en_US.UTF-8"
export MAKE="/usr/bin/make"
export NINJA="/usr/bin/ninja"
export PYTHON="/usr/bin/python3"
