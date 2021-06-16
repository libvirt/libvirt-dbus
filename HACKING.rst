================================
Tips for hacking on libvirt-dbus
================================

Here is where to get code:

::

   $ git clone https://libvirt.org/git/libvirt-dbus.git

Alternatively you can use one of the mirrors:

https://github.com/libvirt/libvirt-dbus
https://gitlab.com/libvirt/libvirt-dbus


Running from git repository
===========================

* The first step is to run meson to create build directory:

  ::

     meson build

  Now you can compile libvirt-dbus:

  ::

     ninja -C build


* Before posting a patch, you should run tests:

  ::

     ninja -C build test

  The test tool requires these packages:

  ::

    python3, python3-pytest, python3-dbus, flake8, dbus-daemon

  It is possible to run only specific test using:

  ::

     meson test -C build $test-name

  or a group of tests:

  ::

     meson test -C build --suite $label

  For more information see https://mesonbuild.com/Unit-tests.html#testing-tool.


* To run libvirt-dbus directly from the build dir without installing it
  use the run script:

  ::

     ./run ./src/libvirt-dbus


Downstream package maintainers
==============================

* It is possible to run the test suite directly for installed libvirt-dbus
  by using the following commands:

  ::

     cd tests && TEST_INSTALLED=1 pytest

  This is intended only for downstream testing process integration.


Coding style rules
==================

* Opening & closing braces for functions should be at start of line:

  ::

     int
     foo(int bar)
     {
         ...
     }

  Not

  ::

     int
     foo(int bar) {
         ...
     }


* Opening brace for if/while/for loops should be at the end of line:

  ::

     if (foo) {
         bar;
         wizz;
     }

  Not

  ::

     if (foo)
     {
         bar;
         wizz;
     }

  Rationale: putting every if/while/for opening brace on a new line
  expands function length too much.


* If a brace needs to be used for one clause in an if/else statement,
  it should be used for both clauses, even if the other clauses are
  only single statements. eg:

  ::

     if (foo) {
         bar;
         wizz;
     } else {
         eek;
     }

  Not

  ::

     if (foo) {
         bar;
         wizz;
     } else
         eek;


* Function parameter attribute annotations should follow the parameter
  name, eg:

  ::

     int
     foo(int bar G_GNUC_UNUSED)
     {
     }

  Not

  ::

     int
     foo(G_GNUC_UNUSED int bar)
     {
     }

  Rationale: Adding / removing G_GNUC_UNUSED  should not cause the
  rest of the line to move around since that obscures diffs.


* There should be no space between function names & open brackets eg:

  ::

     int
     foo(int bar)
     {
     }

  Not

  ::

     int
     foo (int bar)
     {
     }


* To keep lines under 80 characters (where practical), multiple parameters
  should be on new lines. Do not attempt to line up parameters vertically eg:

  ::

     int
     foo(int bar,
         unsigned long wizz)
     {
     }

  Not

  ::

     int
     foo(int bar, unsigned long wizz)
     {
     }

  Not

  ::

     int
     foo(int           bar,
         unsigned long wizz)
     {
     }

  Rationale: attempting vertical alignment causes bigger diffs when
  modifying code if type names change causing whitespace re-alignment.
