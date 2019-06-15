configure_file(
    configuration: conf,
    input: 'org.libvirt.service.in',
    output: 'org.libvirt.service',
    install_dir: dbus_system_services_dir,
)
configure_file(
    configuration: conf,
    input: 'org.libvirt.conf.in',
    output: 'org.libvirt.conf',
    install_dir: dbus_system_policies_dir,
)
configure_file(
    configuration: conf,
    input: 'libvirt-dbus.rules.in',
    output: 'libvirt-dbus.rules',
    install_dir: polkit_rules_dir,
)
