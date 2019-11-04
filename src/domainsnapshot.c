#include "domainsnapshot.h"
#include "util.h"

#include <libvirt/libvirt.h>

static virtDBusGDBusPropertyTable virtDBusDomainSnapshotPropertyTable[] = {
    { 0 }
};

static virtDBusGDBusMethodTable virtDBusDomainSnapshotMethodTable[] = {
    { 0 }
};

static gchar **
virtDBusDomainSnapshotEnumerate(gpointer userData)
{
    virtDBusConnect *connect = userData;
    g_autoptr(virDomainPtr) domains = NULL;
    gint numDoms = 0;
    GPtrArray *list = NULL;

    if (!virtDBusConnectOpen(connect, NULL))
        return NULL;

    numDoms = virConnectListAllDomains(connect->connection, &domains, 0);
    if (numDoms <= 0)
        return NULL;

    list = g_ptr_array_new();

    for (gint i = 0; i < numDoms; i++) {
        g_autoptr(virDomainSnapshotPtr) domainSnapshots = NULL;
        gint numSnaps;

        numSnaps = virDomainListAllSnapshots(domains[i], &domainSnapshots, 0);
        if (numSnaps <= 0)
            continue;

        for (gint j = 0; j < numSnaps; j++) {
            gchar *snapPath = virtDBusUtilBusPathForVirDomainSnapshot(domains[i],
                                                                      domainSnapshots[j],
                                                                      connect->domainSnapshotPath);
            g_ptr_array_add(list, snapPath);
        }
    }

    if (list->len > 0)
        g_ptr_array_add(list, NULL);

    return (gchar **)g_ptr_array_free(list, FALSE);
}

static GDBusInterfaceInfo *interfaceInfo = NULL;

void
virtDBusDomainSnapshotRegister(virtDBusConnect *connect,
                               GError **error)
{
    connect->domainSnapshotPath = g_strdup_printf("%s/domainsnapshot", connect->connectPath);

    if (!interfaceInfo) {
        interfaceInfo = virtDBusGDBusLoadIntrospectData(VIRT_DBUS_DOMAIN_SNAPSHOT_INTERFACE,
                                                        error);
        if (!interfaceInfo)
            return;
    }

    virtDBusGDBusRegisterSubtree(connect->bus,
                                 connect->domainSnapshotPath,
                                 interfaceInfo,
                                 virtDBusDomainSnapshotEnumerate,
                                 virtDBusDomainSnapshotMethodTable,
                                 virtDBusDomainSnapshotPropertyTable,
                                 connect);
}
