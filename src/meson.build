lib_util = static_library(
    'libutil',
    [
        'util.c',
    ],
    dependencies: [
        dep_gio_unix,
        dep_glib,
        dep_libvirt,
        dep_libvirt_glib
    ],
)

exe_libvirt_dbus = executable(
    'libvirt-dbus',
    [
        'connect.c',
        'domain.c',
        'domainsnapshot.c',
        'events.c',
        'gdbus.c',
        'interface.c',
        'main.c',
        'network.c',
        'nodedev.c',
        'nwfilter.c',
        'secret.c',
        'storagepool.c',
        'storagevol.c',
    ],
    dependencies: [
        dep_gio_unix,
        dep_glib,
        dep_libvirt,
        dep_libvirt_glib
    ],
    link_with: [
        lib_util,
    ],
    install: true,
    install_dir: get_option('sbindir'),
)
