if init_script == 'systemd'
    configure_file(
        configuration: conf,
        input: 'libvirt-dbus.service.in',
        output: 'libvirt-dbus.service',
        install_dir: systemd_system_unit_dir,
    )
    dbus_service_in = 'org.libvirt-systemd.service.in'
else
    dbus_service_in = 'org.libvirt.service.in'
endif

configure_file(
    configuration: conf,
    input: dbus_service_in,
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
