#pragma once

#include "connect.h"
#include <libvirt/libvirt.h>

#define VIRT_DBUS_NETWORK_INTERFACE "org.libvirt.Network"

void
virtDBusNetworkRegister(virtDBusConnect *connect,
                        GError **error);

void
virtDBusNetworkDHCPLeaseListFree(virNetworkDHCPLeasePtr *leases);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(virNetworkDHCPLeasePtr, virtDBusNetworkDHCPLeaseListFree);
