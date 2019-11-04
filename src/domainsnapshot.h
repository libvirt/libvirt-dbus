#pragma once

#include "connect.h"

#define VIRT_DBUS_DOMAIN_SNAPSHOT_INTERFACE "org.libvirt.DomainSnapshot"

void
virtDBusDomainSnapshotRegister(virtDBusConnect *connect,
                               GError **error);
