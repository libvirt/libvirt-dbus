============
libvirt-dbus
============

----------------------------------
D-Bus daemon exporting libvirt API
----------------------------------

:Manual section: 8

SYNOPSIS
========

``libvirt-dbus`` [*OPTION*]...

DESCRIPTION
===========

libvirt-dbus wraps libvirt API to provide a high-level object-oriented
API better suited for dbus-based applications.

Normally libvirt-dbus is started by D-Bus daemon on demand.

OPTIONS
=======

**-h --help**

  Display command line help usage then exit.

**--system**

  Connect to the system bus.

**--session**

  Connect to the session bus.

**-t --threads** *NUM*

  Configure maximal number of worker threads.

BUGS
====

Please report all bugs you discover.  This should be done via either:

a) the mailing list

  https://libvirt.org/contact.html

b) the bug tracker

  https://libvirt.org/bugs.html

Alternatively, you may report bugs to your software distribution / vendor.

AUTHORS
=======

Please refer to the AUTHORS file distributed with libvirt-dbus.

LICENSE
=======

libvirt-dbus is Free Software and licenced under LGPLv2+.

SEE ALSO
========

https://libvirt.org/dbus.html, https://libvirt.org/
