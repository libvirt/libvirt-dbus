FROM registry.centos.org/centos:8

RUN dnf install -y centos-release-stream && \
    dnf install 'dnf-command(config-manager)' -y && \
    dnf config-manager --set-enabled -y Stream-PowerTools && \
    dnf install -y centos-release-advanced-virtualization && \
    dnf install -y epel-release && \
    dnf update -y && \
    dnf install -y \
        autoconf \
        automake \
        ca-certificates \
        ccache \
        dbus \
        gcc \
        gettext \
        gettext-devel \
        git \
        glib2-devel \
        glibc-devel \
        glibc-langpack-en \
        gnutls-devel \
        gobject-introspection-devel \
        gtk-doc \
        libnl3-devel \
        libtirpc-devel \
        libtool \
        libxml2 \
        libxml2-devel \
        libxslt \
        make \
        ninja-build \
        perl \
        pkgconfig \
        python3 \
        python3-dbus \
        python3-docutils \
        python3-flake8 \
        python3-gobject \
        python3-pip \
        python3-pytest \
        python3-setuptools \
        python3-wheel \
        rpcgen \
        rpm-build \
        vala && \
    dnf autoremove -y && \
    dnf clean all -y && \
    mkdir -p /usr/libexec/ccache-wrappers && \
    ln -s /usr/bin/ccache /usr/libexec/ccache-wrappers/cc && \
    ln -s /usr/bin/ccache /usr/libexec/ccache-wrappers/$(basename /usr/bin/gcc)

RUN pip3 install \
         meson==0.54.0

ENV LANG "en_US.UTF-8"
ENV MAKE "/usr/bin/make"
ENV NINJA "/usr/bin/ninja"
ENV PYTHON "/usr/bin/python3"
ENV CCACHE_WRAPPERSDIR "/usr/libexec/ccache-wrappers"
