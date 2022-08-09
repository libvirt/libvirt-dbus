============
libvirt-dbus
============

Libvirt provides a portable, long term stable C API for managing the
virtualization technologies provided by many operating systems. It
includes support for QEMU, KVM, Xen, LXC, bhyve, Virtuozzo, VMware
vCenter and ESX, VMware Desktop, Hyper-V, VirtualBox and the POWER
Hypervisor.

libvirt-dbus wraps libvirt API to provide a high-level object-oriented
API better suited for dbus-based applications.

libvirt-dbus is Free Software and licenced under LGPLv2+.

* https://www.libvirt.org/dbus.html

The latest official releases can be found at:

* https://libvirt.org/sources/dbus


Dependencies / supported platforms
==================================

The packages required to build libvirt-dbus are

* libvirt
* libvirt-glib
* glib2


Installation
============

libvirt-dbus uses Meson build system, so the build & install
process is fairly simple. For example, to install as root user:

::

   # meson build --prefix=/usr --sysconfdir=/etc --localstatedir=/var
   # ninja -C build install

or to install as unprivileged user:

::

   $ meson build --prefix=$HOME/usr
   $ ninja -C build install


Patches submissions
===================

Patch submissions are welcomed from any interested contributor. Please
send them to the main libvir-list mailing list

* libvir-list@redhat.com

Questions about usage / deployment can be send to the end users mailing
list

* libvirt-users@redhat.com

For further information about mailing lists & contacting the developers,
please consult

https://libvirt.org/contact.html
