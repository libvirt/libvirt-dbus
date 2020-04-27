prog_rst2man = find_program('rst2man', 'rst2man.py', 'rst2man-3')

configure_file(
    command: [prog_rst2man.path(), '@INPUT@', '@OUTPUT@'],
    input: 'libvirt-dbus.rst',
    output: 'libvirt-dbus.8',
    install_dir: join_paths (get_option('mandir'), 'man8'),
)
