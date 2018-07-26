#!/usr/bin/env python3

import dbus
import libvirttest
import pytest


@pytest.mark.usefixtures("interface_create")
class TestInterface(libvirttest.BaseTestClass):
    """ Tests for methods and properties of the Interface interface
    """

    def test_interface_undefine(self, interface_create):
        _, interface_obj = interface_create
        interface_obj.Destroy(0)
        interface_obj.Undefine()

    def test_interface_destroy(self, interface_create):
        _, interface_obj = interface_create
        interface_obj.Destroy(0)

    def test_interface_create(self, interface_create):
        _, interface_obj = interface_create
        interface_obj.Destroy(0)
        interface_obj.Create(0)

    def test_interface_get_xml_description(self, interface_create):
        _, interface_obj = interface_create
        assert isinstance(interface_obj.GetXMLDesc(0), dbus.String)

    def test_interface_properties_type(self, interface_create):
        """ Ensure correct return type for Interface properties
        """
        test_interface_path, _ = interface_create
        obj = self.bus.get_object('org.libvirt', test_interface_path)
        props = obj.GetAll('org.libvirt.Interface', dbus_interface=dbus.PROPERTIES_IFACE)
        assert isinstance(props['Name'], dbus.String)
        assert isinstance(props['MAC'], dbus.String)
        assert isinstance(props['Active'], dbus.Boolean)


if __name__ == '__main__':
    libvirttest.run()
