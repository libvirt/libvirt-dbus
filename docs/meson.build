prog_pod2man = find_program('pod2man')

configure_file(
    command: [prog_pod2man.path(), '-s 8', '@INPUT@', '@OUTPUT@'],
    input: 'libvirt-dbus.pod',
    output: 'libvirt-dbus.8',
    install_dir: join_paths (get_option('mandir'), 'man8'),
)
