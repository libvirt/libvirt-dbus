#!/usr/bin/python3

import dbus
import libvirttest

class TestInterface(libvirttest.BaseTestClass):
    """ Tests for methods and properties of the Interface interface
    """

    def test_interface_undefine(self):
        _,interface_obj = self.interface_create()
        interface_obj.Destroy(0)
        interface_obj.Undefine()

    def test_interface_destroy(self):
        _,interface_obj = self.interface_create()
        interface_obj.Destroy(0)

    def test_interface_create(self):
        _,interface_obj = self.interface_create()
        interface_obj.Destroy(0)
        interface_obj.Create(0)

    def test_interface_get_xml_description(self):
        _,interface_obj = self.interface_create()
        assert isinstance(interface_obj.GetXMLDesc(0), dbus.String)

if __name__ == '__main__':
    libvirttest.run()
