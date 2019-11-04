#include "domainsnapshot.h"
#include "domain.h"
#include "util.h"

#include <libvirt/libvirt.h>

static virDomainSnapshotPtr
virtDBusDomainSnapshotGetVirDomainSnapshot(virtDBusConnect *connect,
                                           const gchar *objectPath,
                                           GError **error)
{
    virDomainSnapshotPtr domSnap;

    if (!virtDBusConnectOpen(connect, error))
        return NULL;

    domSnap = virtDBusUtilVirDomainSnapshotFromBusPath(connect->connection,
                                                       objectPath,
                                                       connect->domainSnapshotPath);
    if (!domSnap) {
        virtDBusUtilSetLastVirtError(error);
        return NULL;
    }

    return domSnap;
}

static void
virtDBusDomainSnapshotDelete(GVariant *inArgs,
                             GUnixFDList *inFDs G_GNUC_UNUSED,
                             const gchar *objectPath,
                             gpointer userData,
                             GVariant **outArgs G_GNUC_UNUSED,
                             GUnixFDList **outFDs G_GNUC_UNUSED,
                             GError **error)
{
    virtDBusConnect *connect = userData;
    g_autoptr(virDomainSnapshot) domainSnapshot = NULL;
    guint flags;

    g_variant_get(inArgs, "(u)", &flags);

    domainSnapshot = virtDBusDomainSnapshotGetVirDomainSnapshot(connect,
                                                                objectPath,
                                                                error);
    if (!domainSnapshot)
        return;

    if (virDomainSnapshotDelete(domainSnapshot, flags) < 0)
        return virtDBusUtilSetLastVirtError(error);
}

static void
virtDBusDomainSnapshotGetParent(GVariant *inArgs,
                                GUnixFDList *inFDs G_GNUC_UNUSED,
                                const gchar *objectPath,
                                gpointer userData,
                                GVariant **outArgs G_GNUC_UNUSED,
                                GUnixFDList **outFDs G_GNUC_UNUSED,
                                GError **error)
{
    virtDBusConnect *connect = userData;
    g_autoptr(virDomainSnapshot) domainSnapshot = NULL;
    g_autoptr(virDomainSnapshot) parent = NULL;
    guint flags;
    g_autoptr(virDomain) domain = NULL;
    g_autofree gchar *parentPath = NULL;

    g_variant_get(inArgs, "(u)", &flags);

    domainSnapshot = virtDBusDomainSnapshotGetVirDomainSnapshot(connect,
                                                                objectPath,
                                                                error);
    if (!domainSnapshot)
        return;

    parent = virDomainSnapshotGetParent(domainSnapshot, flags);
    if (!parent)
        return virtDBusUtilSetLastVirtError(error);

    domain = virDomainSnapshotGetDomain(domainSnapshot);
    parentPath = virtDBusUtilBusPathForVirDomainSnapshot(domain,
                                                         parent,
                                                         connect->domainSnapshotPath);

    *outArgs = g_variant_new("(o)", parentPath);
}

static void
virtDBusDomainSnapshotGetXMLDesc(GVariant *inArgs,
                                 GUnixFDList *inFDs G_GNUC_UNUSED,
                                 const gchar *objectPath,
                                 gpointer userData,
                                 GVariant **outArgs G_GNUC_UNUSED,
                                 GUnixFDList **outFDs G_GNUC_UNUSED,
                                 GError **error)
{
    virtDBusConnect *connect = userData;
    g_autoptr(virDomainSnapshot) domainSnapshot = NULL;
    guint flags;
    g_autofree gchar *xml = NULL;

    g_variant_get(inArgs, "(u)", &flags);

    domainSnapshot = virtDBusDomainSnapshotGetVirDomainSnapshot(connect,
                                                                objectPath,
                                                                error);
    if (!domainSnapshot)
        return;

    xml = virDomainSnapshotGetXMLDesc(domainSnapshot, flags);
    if (!xml)
        return virtDBusUtilSetLastVirtError(error);

    *outArgs = g_variant_new("(s)", xml);
}

static void
virtDBusDomainSnapshotIsCurrent(GVariant *inArgs,
                                GUnixFDList *inFDs G_GNUC_UNUSED,
                                const gchar *objectPath,
                                gpointer userData,
                                GVariant **outArgs G_GNUC_UNUSED,
                                GUnixFDList **outFDs G_GNUC_UNUSED,
                                GError **error)
{
    virtDBusConnect *connect = userData;
    g_autoptr(virDomainSnapshot) domainSnapshot = NULL;
    guint flags;
    gint isCurrent;

    g_variant_get(inArgs, "(u)", &flags);

    domainSnapshot = virtDBusDomainSnapshotGetVirDomainSnapshot(connect,
                                                                objectPath,
                                                                error);
    if (!domainSnapshot)
        return;

    isCurrent = virDomainSnapshotIsCurrent(domainSnapshot, flags);
    if (isCurrent < 0)
        return virtDBusUtilSetLastVirtError(error);

    *outArgs = g_variant_new("(b)", !!isCurrent);
}

static void
virtDBusDomainSnapshotListAllChildren(GVariant *inArgs,
                                      GUnixFDList *inFDs G_GNUC_UNUSED,
                                      const gchar *objectPath,
                                      gpointer userData,
                                      GVariant **outArgs G_GNUC_UNUSED,
                                      GUnixFDList **outFDs G_GNUC_UNUSED,
                                      GError **error)
{
    virtDBusConnect *connect = userData;
    g_autoptr(virDomainSnapshot) domainSnapshot = NULL;
    g_autoptr(virDomainSnapshotPtr) snaps = NULL;
    guint flags;
    GVariantBuilder builder;
    GVariant *gdomainSnapshots;
    g_autoptr(virDomain) domain = NULL;

    g_variant_get(inArgs, "(u)", &flags);

    domainSnapshot = virtDBusDomainSnapshotGetVirDomainSnapshot(connect,
                                                                objectPath,
                                                                error);
    if (!domainSnapshot)
        return;

    if (virDomainSnapshotListAllChildren(domainSnapshot, &snaps, flags) < 0)
        return virtDBusUtilSetLastVirtError(error);

    g_variant_builder_init(&builder, G_VARIANT_TYPE("ao"));

    domain = virDomainSnapshotGetDomain(domainSnapshot);
    for (gint i = 0; snaps[i]; i++) {
        g_autofree gchar *path = NULL;
        path = virtDBusUtilBusPathForVirDomainSnapshot(domain,
                                                       snaps[i],
                                                       connect->domainSnapshotPath);

        g_variant_builder_add(&builder, "o", path);
    }

    gdomainSnapshots = g_variant_builder_end(&builder);
    *outArgs = g_variant_new_tuple(&gdomainSnapshots, 1);
}

static void
virtDBusDomainSnapshotRevert(GVariant *inArgs,
                             GUnixFDList *inFDs G_GNUC_UNUSED,
                             const gchar *objectPath,
                             gpointer userData,
                             GVariant **outArgs G_GNUC_UNUSED,
                             GUnixFDList **outFDs G_GNUC_UNUSED,
                             GError **error)
{
    virtDBusConnect *connect = userData;
    g_autoptr(virDomainSnapshot) domainSnapshot = NULL;
    guint flags;

    g_variant_get(inArgs, "(u)", &flags);

    domainSnapshot = virtDBusDomainSnapshotGetVirDomainSnapshot(connect,
                                                                objectPath,
                                                                error);
    if (!domainSnapshot)
        return;

    if (virDomainRevertToSnapshot(domainSnapshot, flags) < 0)
        return virtDBusUtilSetLastVirtError(error);
}

static virtDBusGDBusPropertyTable virtDBusDomainSnapshotPropertyTable[] = {
    { 0 }
};

static virtDBusGDBusMethodTable virtDBusDomainSnapshotMethodTable[] = {
    { "Delete", virtDBusDomainSnapshotDelete },
    { "GetParent", virtDBusDomainSnapshotGetParent },
    { "GetXMLDesc", virtDBusDomainSnapshotGetXMLDesc },
    { "IsCurrent", virtDBusDomainSnapshotIsCurrent },
    { "ListChildren", virtDBusDomainSnapshotListAllChildren },
    { "Revert", virtDBusDomainSnapshotRevert },
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
