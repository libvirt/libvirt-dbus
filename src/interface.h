#pragma once

#include "connect.h"

#define VIRT_DBUS_INTERFACE_INTERFACE "org.libvirt.Interface"

void
virtDBusInterfaceRegister(virtDBusConnect *connect,
                          GError **error);
