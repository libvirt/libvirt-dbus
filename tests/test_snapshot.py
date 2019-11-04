#!/usr/bin/env python3

import dbus
import libvirttest
import pytest

EXCEPTION_NO_PARENT = 'does not have a parent'


@pytest.mark.usefixtures("snapshot_create")
class TestSnapshot(libvirttest.BaseTestClass):
    """ Tests for methods and properties of the Snapshot snapshot
    """

    def test_snapshot_delete(self, snapshot_create):
        snapshot_obj = snapshot_create
        snapshot_obj.Delete(0)

    def test_snapshot_get_parent(self, snapshot_create):
        snapshot_obj = snapshot_create
        try:
            snapshot_obj.GetParent(0)
        except dbus.exceptions.DBusException as e:
            if not any(EXCEPTION_NO_PARENT in arg for arg in e.args):
                raise e

    def test_snapshot_get_xml(self, snapshot_create):
        snapshot_obj = snapshot_create
        assert isinstance(snapshot_obj.GetXMLDesc(0), dbus.String)

    def test_snapshot_get_is_current(self, snapshot_create):
        snapshot_obj = snapshot_create
        assert isinstance(snapshot_obj.IsCurrent(0), dbus.Boolean)

    def test_snapshot_list_children(self, snapshot_create):
        snapshot_obj = snapshot_create
        assert isinstance(snapshot_obj.ListChildren(0), dbus.Array)

    def test_snapshot_revert(self, snapshot_create):
        snapshot_obj = snapshot_create
        snapshot_obj.Revert(0)


if __name__ == '__main__':
    libvirttest.run()
