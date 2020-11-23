FROM registry.fedoraproject.org/fedora:33

RUN dnf update -y && \
    dnf install -y \
        ca-certificates \
        ccache \
        dbus-daemon \
        gcc \
        git \
        glib2-devel \
        glibc-langpack-en \
        libvirt-devel \
        libvirt-gobject-devel \
        make \
        meson \
        ninja-build \
        pkgconfig \
        python3 \
        python3-dbus \
        python3-docutils \
        python3-flake8 \
        python3-gobject \
        python3-pytest \
        rpm-build && \
    dnf autoremove -y && \
    dnf clean all -y && \
    mkdir -p /usr/libexec/ccache-wrappers && \
    ln -s /usr/bin/ccache /usr/libexec/ccache-wrappers/cc && \
    ln -s /usr/bin/ccache /usr/libexec/ccache-wrappers/$(basename /usr/bin/gcc)

ENV LANG "en_US.UTF-8"
ENV MAKE "/usr/bin/make"
ENV NINJA "/usr/bin/ninja"
ENV PYTHON "/usr/bin/python3"
ENV CCACHE_WRAPPERSDIR "/usr/libexec/ccache-wrappers"
