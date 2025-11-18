#include <matter_data_model.h>

#include <app/PluginApplicationCallbacks.h>
#include <app/util/endpoint-config-defines.h>
#include <app/util/att-storage.h>
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app-common/zap-generated/callback.h>

using namespace chip::app::Clusters;

#define STORAGE_MASK                ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
#define WRITABLE_MASK               ZAP_ATTRIBUTE_MASK(WRITABLE)
#define SINGLETON_MASK              ZAP_ATTRIBUTE_MASK(SINGLETON)
#define NULLABLE_MASK               ZAP_ATTRIBUTE_MASK(NULLABLE)
#define TOKENIZE_MASK               ZAP_ATTRIBUTE_MASK(TOKENIZE)

#define WRITABLE_STORAGE            (STORAGE_MASK | WRITABLE_MASK)
#define SINGLETON_STORAGE           (STORAGE_MASK | SINGLETON_MASK)
#define NULLABLE_STORAGE            (STORAGE_MASK | NULLABLE_MASK)
#define TOKENIZE_COMBO              (STORAGE_MASK | TOKENIZE_MASK | SINGLETON_MASK | WRITABLE_MASK)

namespace Presets {
namespace Clusters {

// Attribute default values that are non trivial
EmberAfAttributeMinMaxValue onoffStartUpOnOffMinMaxValue = {(uint16_t)0xFF, (uint16_t)0x0, (uint16_t)0x2};
EmberAfAttributeMinMaxValue levelcontrolOptionsMinMaxValue = {(uint16_t)0x0, (uint16_t)0x0, (uint16_t)0x3};
uint8_t generalcommissioningBreadCrumbValue[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void matter_cluster_descriptor_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x0000001D;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Attributes
    AttributeConfig descDeviceTypeList(0x00000000, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig descServerList(0x00000001, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig descClientList(0x00000002, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig descPartsList(0x00000003, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(descDeviceTypeList);
    clusterConfig->attributeConfigs.push_back(descServerList);
    clusterConfig->attributeConfigs.push_back(descClientList);
    clusterConfig->attributeConfigs.push_back(descPartsList);

    // Global Attributes
    AttributeConfig descFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(0), 4, STORAGE_MASK);
    AttributeConfig descClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(descFeatureMap);
    clusterConfig->attributeConfigs.push_back(descClusterRevision);
}

void matter_cluster_access_control_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x0000001F;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Attributes
    AttributeConfig aclACL(0x00000000, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, WRITABLE_STORAGE);
    AttributeConfig aclExtension(0x00000001, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, WRITABLE_STORAGE);
    AttributeConfig aclSubjectsPerAccessControlEntry(0x00000002, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 2, STORAGE_MASK);
    AttributeConfig aclTargetsPerAccessControlEntry(0x00000003, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 2, STORAGE_MASK);
    AttributeConfig aclAccessControlEntriesPerFabric(0x00000004, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(aclACL);
    clusterConfig->attributeConfigs.push_back(aclExtension);
    clusterConfig->attributeConfigs.push_back(aclSubjectsPerAccessControlEntry);
    clusterConfig->attributeConfigs.push_back(aclTargetsPerAccessControlEntry);
    clusterConfig->attributeConfigs.push_back(aclAccessControlEntriesPerFabric);

    // Global Attributes
    AttributeConfig aclFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(0), 4, STORAGE_MASK);
    AttributeConfig aclClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(1), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(aclFeatureMap);
    clusterConfig->attributeConfigs.push_back(aclClusterRevision);

    // Events
    EventConfig aclAccessControlEntryChanged(0x00000000);
    EventConfig aclAccessControlExtensionChanged(0x00000001);

    clusterConfig->eventConfigs.push_back(aclAccessControlEntryChanged);
    clusterConfig->eventConfigs.push_back(aclAccessControlExtensionChanged);
}

void matter_cluster_basic_information_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x00000028;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Attributes
    AttributeConfig binfoDataModelRevision(0x00000000, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 2, SINGLETON_STORAGE);
    AttributeConfig binfoVendorName(0x00000001, ZAP_TYPE(CHAR_STRING), ZAP_EMPTY_DEFAULT(), 33, SINGLETON_STORAGE);
    AttributeConfig binfoVendorId(0x00000002, ZAP_TYPE(VENDOR_ID), ZAP_EMPTY_DEFAULT(), 2, SINGLETON_STORAGE);
    AttributeConfig binfoProductName(0x00000003, ZAP_TYPE(CHAR_STRING), ZAP_EMPTY_DEFAULT(), 33, SINGLETON_STORAGE);
    AttributeConfig binfoProductId(0x00000004, ZAP_TYPE(VENDOR_ID), ZAP_EMPTY_DEFAULT(), 2, SINGLETON_STORAGE);
    AttributeConfig binfoNodeLabel(0x00000005, ZAP_TYPE(CHAR_STRING), ZAP_EMPTY_DEFAULT(), 33, TOKENIZE_COMBO);
    AttributeConfig binfoLocation(0x00000006, ZAP_TYPE(CHAR_STRING), ZAP_EMPTY_DEFAULT(), 3, SINGLETON_STORAGE | ZAP_ATTRIBUTE_MASK(WRITABLE));
    AttributeConfig binfoHardwareVersion(0x00000007, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 2, SINGLETON_STORAGE);
    AttributeConfig binfoHardwareVersionString(0x00000008, ZAP_TYPE(CHAR_STRING), ZAP_EMPTY_DEFAULT(), 65, SINGLETON_STORAGE);
    AttributeConfig binfoSoftwareVersion(0x00000009, ZAP_TYPE(INT32U), ZAP_EMPTY_DEFAULT(), 4, SINGLETON_STORAGE);
    AttributeConfig binfoSoftwareVersionString(0x0000000A, ZAP_TYPE(CHAR_STRING), ZAP_EMPTY_DEFAULT(), 65, SINGLETON_STORAGE);
    AttributeConfig binfoManufacturingDate(0x0000000B, ZAP_TYPE(CHAR_STRING), ZAP_EMPTY_DEFAULT(), 17, SINGLETON_STORAGE);
    AttributeConfig binfoPartNumber(0x0000000C, ZAP_TYPE(CHAR_STRING), ZAP_EMPTY_DEFAULT(), 33, SINGLETON_STORAGE);
    AttributeConfig binfoProductUrl(0x0000000D, ZAP_TYPE(LONG_CHAR_STRING), ZAP_EMPTY_DEFAULT(), 258, SINGLETON_STORAGE);
    AttributeConfig binfoProductLabel(0x0000000E, ZAP_TYPE(CHAR_STRING), ZAP_EMPTY_DEFAULT(), 65, SINGLETON_STORAGE);
    AttributeConfig binfoSerialNumber(0x0000000F, ZAP_TYPE(CHAR_STRING), ZAP_EMPTY_DEFAULT(), 33, SINGLETON_STORAGE);
    AttributeConfig binfoLocalConfigDisabled(0x00000010, ZAP_TYPE(BOOLEAN), ZAP_EMPTY_DEFAULT(), 1, TOKENIZE_COMBO);
    AttributeConfig binfoUniqueId(0x00000012, ZAP_TYPE(CHAR_STRING), ZAP_EMPTY_DEFAULT(), 33, SINGLETON_STORAGE);
    AttributeConfig binfoCapabilityMinima(0x00000013, ZAP_TYPE(STRUCT), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(binfoDataModelRevision);
    clusterConfig->attributeConfigs.push_back(binfoVendorName);
    clusterConfig->attributeConfigs.push_back(binfoVendorId);
    clusterConfig->attributeConfigs.push_back(binfoProductName);
    clusterConfig->attributeConfigs.push_back(binfoProductId);
    clusterConfig->attributeConfigs.push_back(binfoNodeLabel);
    clusterConfig->attributeConfigs.push_back(binfoLocation);
    clusterConfig->attributeConfigs.push_back(binfoHardwareVersion);
    clusterConfig->attributeConfigs.push_back(binfoHardwareVersionString);
    clusterConfig->attributeConfigs.push_back(binfoSoftwareVersion);
    clusterConfig->attributeConfigs.push_back(binfoSoftwareVersionString);
    clusterConfig->attributeConfigs.push_back(binfoManufacturingDate);
    clusterConfig->attributeConfigs.push_back(binfoPartNumber);
    clusterConfig->attributeConfigs.push_back(binfoProductUrl);
    clusterConfig->attributeConfigs.push_back(binfoProductLabel);
    clusterConfig->attributeConfigs.push_back(binfoSerialNumber);
    clusterConfig->attributeConfigs.push_back(binfoLocalConfigDisabled);
    clusterConfig->attributeConfigs.push_back(binfoUniqueId);
    clusterConfig->attributeConfigs.push_back(binfoCapabilityMinima);

    // Global Attributes
    AttributeConfig binfoFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(0), 4, STORAGE_MASK);
    AttributeConfig binfoClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(3), 2, SINGLETON_STORAGE);

    clusterConfig->attributeConfigs.push_back(binfoFeatureMap);
    clusterConfig->attributeConfigs.push_back(binfoClusterRevision);

    // Event
    EventConfig binfoStartUp(0x00000000);
    EventConfig binfoShutDown(0x00000001);
    EventConfig binfoLeave(0x00000002);

    clusterConfig->eventConfigs.push_back(binfoStartUp);
    clusterConfig->eventConfigs.push_back(binfoShutDown);
    clusterConfig->eventConfigs.push_back(binfoLeave);
}

void matter_cluster_ota_requestor_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x0000002A;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Attributes
    AttributeConfig otarDefaultOtaProviders(0x00000000, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, WRITABLE_STORAGE);
    AttributeConfig otarUpdatePossible(0x00000001, ZAP_TYPE(BOOLEAN), ZAP_SIMPLE_DEFAULT(1), 1, STORAGE_MASK);
    AttributeConfig otarUpdateState(0x00000002, ZAP_TYPE(ENUM8), ZAP_SIMPLE_DEFAULT(0), 1, STORAGE_MASK);
    AttributeConfig otarUpdateStateProgress(0x00000003, ZAP_TYPE(INT8U), ZAP_SIMPLE_DEFAULT(0), 1, NULLABLE_STORAGE);

    clusterConfig->attributeConfigs.push_back(otarDefaultOtaProviders);
    clusterConfig->attributeConfigs.push_back(otarUpdatePossible);
    clusterConfig->attributeConfigs.push_back(otarUpdateState);
    clusterConfig->attributeConfigs.push_back(otarUpdateStateProgress);

    // Global Attributes
    AttributeConfig otarFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(0), 4, STORAGE_MASK);
    AttributeConfig otarClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(1), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(otarFeatureMap);
    clusterConfig->attributeConfigs.push_back(otarClusterRevision);

    // Accepted Command List
    CommandConfig otarAnnounceOtaProvider(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig otarEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(otarAnnounceOtaProvider);
    clusterConfig->commandConfigs.push_back(otarEndOfAcceptedCommandList);

    // Events
    EventConfig otarStateTransition(0x00000000);
    EventConfig otarVersionApplied(0x00000001);
    EventConfig otarDownloadError(0x00000002);

    clusterConfig->eventConfigs.push_back(otarStateTransition);
    clusterConfig->eventConfigs.push_back(otarVersionApplied);
    clusterConfig->eventConfigs.push_back(otarDownloadError);
}

void matter_cluster_general_commissioning_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x00000030;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Attributes
    AttributeConfig cgenBreadcrumb(0x00000000, ZAP_TYPE(INT64U), uint32_t(0), 8, WRITABLE_STORAGE);
    AttributeConfig cgenBasicCommissioningInfo(0x00000001, ZAP_TYPE(STRUCT), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig cgenRegulatoryConfig(0x00000002, ZAP_TYPE(ENUM8), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);
    AttributeConfig cgenLocationCapability(0x00000003, ZAP_TYPE(ENUM8), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);
    AttributeConfig cgenSupportsConcurrentConnection(0x00000004, ZAP_TYPE(BOOLEAN), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(cgenBreadcrumb);
    clusterConfig->attributeConfigs.push_back(cgenBasicCommissioningInfo);
    clusterConfig->attributeConfigs.push_back(cgenRegulatoryConfig);
    clusterConfig->attributeConfigs.push_back(cgenLocationCapability);
    clusterConfig->attributeConfigs.push_back(cgenSupportsConcurrentConnection);

    // Global Attributes
    AttributeConfig cgenFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(0), 4, STORAGE_MASK);
    AttributeConfig cgenClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(1), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(cgenFeatureMap);
    clusterConfig->attributeConfigs.push_back(cgenClusterRevision);

    // Accepted Command Lists
    CommandConfig cgenArmFailSafe(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig cgenSetRegulatoryConfig(0x00000002, COMMAND_MASK_ACCEPTED);
    CommandConfig cgenCommissioningComplete(0x00000004, COMMAND_MASK_ACCEPTED);
    CommandConfig cgenEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(cgenArmFailSafe);
    clusterConfig->commandConfigs.push_back(cgenSetRegulatoryConfig);
    clusterConfig->commandConfigs.push_back(cgenCommissioningComplete);
    clusterConfig->commandConfigs.push_back(cgenEndOfAcceptedCommandList);

    // Generated Command Lists
    CommandConfig cgenArmFailSafeResponse(0x00000001, COMMAND_MASK_GENERATED);
    CommandConfig cgenSetRegulatoryConfigResponse(0x00000003, COMMAND_MASK_GENERATED);
    CommandConfig cgenCommissioningCompleteResponse(0x00000005, COMMAND_MASK_GENERATED);
    CommandConfig cgenEndOfGeneratedCommandList(chip::kInvalidCommandId, COMMAND_MASK_GENERATED);

    clusterConfig->commandConfigs.push_back(cgenArmFailSafeResponse);
    clusterConfig->commandConfigs.push_back(cgenSetRegulatoryConfigResponse);
    clusterConfig->commandConfigs.push_back(cgenCommissioningCompleteResponse);
    clusterConfig->commandConfigs.push_back(cgenEndOfGeneratedCommandList);
}

void matter_cluster_network_commissioning_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x00000031;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Attributes
    AttributeConfig cnetMaxNetworks(0x00000000, ZAP_TYPE(INT8U), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);
    AttributeConfig cnetNetworks(0x00000001, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig cnetScanMaxTimeSeconds(0x00000002, ZAP_TYPE(INT8U), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);
    AttributeConfig cnetConnectMaxTimeSeconds(0x00000003, ZAP_TYPE(INT8U), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);
    AttributeConfig cnetInterfaceEnabled(0x00000004, ZAP_TYPE(BOOLEAN), ZAP_EMPTY_DEFAULT(), 1, WRITABLE_STORAGE);
    AttributeConfig cnetLastNetworkingStatus(0x00000005, ZAP_TYPE(ENUM8), ZAP_EMPTY_DEFAULT(), 1, NULLABLE_STORAGE);
    AttributeConfig cnetLastNetworkId(0x00000006, ZAP_TYPE(OCTET_STRING), ZAP_EMPTY_DEFAULT(), 33, NULLABLE_STORAGE);
    AttributeConfig cnetLastConnectErrorValue(0x00000007, ZAP_TYPE(INT32S), ZAP_EMPTY_DEFAULT(), 4, NULLABLE_STORAGE);

    clusterConfig->attributeConfigs.push_back(cnetMaxNetworks);
    clusterConfig->attributeConfigs.push_back(cnetNetworks);
    clusterConfig->attributeConfigs.push_back(cnetScanMaxTimeSeconds);
    clusterConfig->attributeConfigs.push_back(cnetConnectMaxTimeSeconds);
    clusterConfig->attributeConfigs.push_back(cnetInterfaceEnabled);
    clusterConfig->attributeConfigs.push_back(cnetLastNetworkingStatus);
    clusterConfig->attributeConfigs.push_back(cnetLastNetworkId);
    clusterConfig->attributeConfigs.push_back(cnetLastConnectErrorValue);

    // Global Attributes
    AttributeConfig cnetFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(1), 4, STORAGE_MASK);
    AttributeConfig cnetClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(1), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(cnetFeatureMap);
    clusterConfig->attributeConfigs.push_back(cnetClusterRevision);

    // Accepted Command Lists
    CommandConfig cnetScanNetworks(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig cnetAddOrUpdateWiFiNetwork(0x00000002, COMMAND_MASK_ACCEPTED);
    CommandConfig cnetRemoveNetwork(0x00000004, COMMAND_MASK_ACCEPTED);
    CommandConfig cnetConnectNetwork(0x00000006, COMMAND_MASK_ACCEPTED);
    CommandConfig cnetReorderNetwork(0x00000008, COMMAND_MASK_ACCEPTED);
    CommandConfig cnetEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(cnetScanNetworks);
    clusterConfig->commandConfigs.push_back(cnetAddOrUpdateWiFiNetwork);
    clusterConfig->commandConfigs.push_back(cnetRemoveNetwork);
    clusterConfig->commandConfigs.push_back(cnetConnectNetwork);
    clusterConfig->commandConfigs.push_back(cnetReorderNetwork);
    clusterConfig->commandConfigs.push_back(cnetEndOfAcceptedCommandList);

    // Generated Command Lists
    CommandConfig cnetScanNetworksResponse(0x00000001, COMMAND_MASK_GENERATED);
    CommandConfig cnetNetworkConfigResponse(0x00000005, COMMAND_MASK_GENERATED);
    CommandConfig cnetConnectNetworkResponse(0x00000007, COMMAND_MASK_GENERATED);
    CommandConfig cnetEndOfGeneratedCommandList(chip::kInvalidCommandId, COMMAND_MASK_GENERATED);

    clusterConfig->commandConfigs.push_back(cnetScanNetworksResponse);
    clusterConfig->commandConfigs.push_back(cnetNetworkConfigResponse);
    clusterConfig->commandConfigs.push_back(cnetConnectNetworkResponse);
    clusterConfig->commandConfigs.push_back(cnetEndOfGeneratedCommandList);
}

void matter_cluster_diagnostic_logs_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x00000032;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Global Attributes
    AttributeConfig diaglogFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(0), 4, STORAGE_MASK);
    AttributeConfig diaglogClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(1), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(diaglogFeatureMap);
    clusterConfig->attributeConfigs.push_back(diaglogClusterRevision);

    // Accepted Command Lists
    CommandConfig diaglogRetrieveLogsRequest(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig diaglogEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(diaglogRetrieveLogsRequest);
    clusterConfig->commandConfigs.push_back(diaglogEndOfAcceptedCommandList);

    // Generated Command Lists
    CommandConfig diaglogRetrieveLogsResponse(0x00000001, COMMAND_MASK_GENERATED);
    CommandConfig diaglogEndOfGeneratedCommandList(chip::kInvalidCommandId, COMMAND_MASK_GENERATED);

    clusterConfig->commandConfigs.push_back(diaglogRetrieveLogsResponse);
    clusterConfig->commandConfigs.push_back(diaglogEndOfGeneratedCommandList);
}

void matter_cluster_general_diagnostics_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x00000033;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Attributes
    AttributeConfig dggenNetworkInterfaces(0x00000000, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig dggenRebootCount(0x00000001, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 2, STORAGE_MASK);
    AttributeConfig dggenUpTime(0x00000002, ZAP_TYPE(INT64U), ZAP_EMPTY_DEFAULT(), 8, STORAGE_MASK);
    AttributeConfig dggenTotalOperationalHours(0x00000003, ZAP_TYPE(INT32U), ZAP_EMPTY_DEFAULT(), 4, STORAGE_MASK);
    AttributeConfig dggenBootReason(0x00000004, ZAP_TYPE(ENUM8), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);
    AttributeConfig dggenActiveHardwareFaults(0x00000005, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig dggenActiveRadioFaults(0x00000006, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig dggenActiveNetworkFaults(0x00000007, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig dggenTestEventTriggersEnabled(0x00000008, ZAP_TYPE(BOOLEAN), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(dggenNetworkInterfaces);
    clusterConfig->attributeConfigs.push_back(dggenRebootCount);
    clusterConfig->attributeConfigs.push_back(dggenUpTime);
    clusterConfig->attributeConfigs.push_back(dggenTotalOperationalHours);
    clusterConfig->attributeConfigs.push_back(dggenBootReason);
    clusterConfig->attributeConfigs.push_back(dggenActiveHardwareFaults);
    clusterConfig->attributeConfigs.push_back(dggenActiveRadioFaults);
    clusterConfig->attributeConfigs.push_back(dggenActiveNetworkFaults);
    clusterConfig->attributeConfigs.push_back(dggenTestEventTriggersEnabled);

    // Global Attributes
    AttributeConfig dggenFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(0), 4, STORAGE_MASK);
    AttributeConfig dggenClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(1), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(dggenFeatureMap);
    clusterConfig->attributeConfigs.push_back(dggenClusterRevision);

    // Accepted Command Lists
    CommandConfig dggenTestEventTrigger(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig dggenTimeSnapshot(0x00000001, COMMAND_MASK_ACCEPTED);
    CommandConfig dggenEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(dggenTestEventTrigger);
    clusterConfig->commandConfigs.push_back(dggenTimeSnapshot);
    clusterConfig->commandConfigs.push_back(dggenEndOfAcceptedCommandList);

    // Generated Command Lists
    CommandConfig dggenTimeSnapshotResponse(0x00000002, COMMAND_MASK_GENERATED);
    CommandConfig dggenEndOfGeneratedCommandList(chip::kInvalidCommandId, COMMAND_MASK_GENERATED);

    clusterConfig->commandConfigs.push_back(dggenTimeSnapshotResponse);
    clusterConfig->commandConfigs.push_back(dggenEndOfGeneratedCommandList);

    // Events
    EventConfig dggenHardwareFaultChange(0x00000000);
    EventConfig dggenRadioFaultChange(0x00000001);
    EventConfig dggenNetworkFaultChange(0x00000002);
    EventConfig dggenBootReasonEvent(0x00000003);

    clusterConfig->eventConfigs.push_back(dggenHardwareFaultChange);
    clusterConfig->eventConfigs.push_back(dggenRadioFaultChange);
    clusterConfig->eventConfigs.push_back(dggenNetworkFaultChange);
    clusterConfig->eventConfigs.push_back(dggenBootReasonEvent);
}

void matter_cluster_software_diagnostics_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x00000034;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Attributes
    AttributeConfig dgswThreadMetrics(0x00000000, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig dgswCurrentHeapFree(0x00000001, ZAP_TYPE(INT64U), ZAP_EMPTY_DEFAULT(), 8, STORAGE_MASK);
    AttributeConfig dgswCurrentHeapUsed(0x00000002, ZAP_TYPE(INT64U), ZAP_EMPTY_DEFAULT(), 8, STORAGE_MASK);
    AttributeConfig dgswCurrentHeapHighWatermark(0x00000003, ZAP_TYPE(INT64U), ZAP_EMPTY_DEFAULT(), 8, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(dgswThreadMetrics);
    clusterConfig->attributeConfigs.push_back(dgswCurrentHeapFree);
    clusterConfig->attributeConfigs.push_back(dgswCurrentHeapUsed);
    clusterConfig->attributeConfigs.push_back(dgswCurrentHeapHighWatermark);

    // Global Attributes
    AttributeConfig dgswFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(1), 4, STORAGE_MASK);
    AttributeConfig dgswClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(1), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(dgswFeatureMap);
    clusterConfig->attributeConfigs.push_back(dgswClusterRevision);

    // Accepted Command Lists
    CommandConfig dgswResetWatermarks(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig dgswEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(dgswResetWatermarks);
    clusterConfig->commandConfigs.push_back(dgswEndOfAcceptedCommandList);

    // Generated Command Lists
    CommandConfig dgswEndOfGeneratedCommandList(chip::kInvalidCommandId, COMMAND_MASK_GENERATED);

    clusterConfig->commandConfigs.push_back(dgswEndOfGeneratedCommandList);
}

void matter_cluster_wifi_network_diagnostics_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x00000036;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Attributes
    AttributeConfig dgwifiBssid(0x00000000, ZAP_TYPE(OCTET_STRING), ZAP_EMPTY_DEFAULT(), 7, NULLABLE_STORAGE);
    AttributeConfig dgwifiSecurityType(0x00000001, ZAP_TYPE(ENUM8), ZAP_EMPTY_DEFAULT(), 1, NULLABLE_STORAGE);
    AttributeConfig dgwifiWiFiVersion(0x00000002, ZAP_TYPE(ENUM8), ZAP_EMPTY_DEFAULT(), 1, NULLABLE_STORAGE);
    AttributeConfig dgwifiChannelNumber(0x00000003, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 2, NULLABLE_STORAGE);
    AttributeConfig dgwifiRssi(0x00000004, ZAP_TYPE(INT8S), ZAP_EMPTY_DEFAULT(), 1, NULLABLE_STORAGE);

    clusterConfig->attributeConfigs.push_back(dgwifiBssid);
    clusterConfig->attributeConfigs.push_back(dgwifiSecurityType);
    clusterConfig->attributeConfigs.push_back(dgwifiWiFiVersion);
    clusterConfig->attributeConfigs.push_back(dgwifiChannelNumber);
    clusterConfig->attributeConfigs.push_back(dgwifiRssi);

    // Global Attributes
    AttributeConfig dgwifiFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(3), 4, STORAGE_MASK);
    AttributeConfig dgwifiClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(1), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(dgwifiFeatureMap);
    clusterConfig->attributeConfigs.push_back(dgwifiClusterRevision);

    // Accepted Command Lists
    CommandConfig dgwifiResetCounts(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig dgwifiEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(dgwifiResetCounts);
    clusterConfig->commandConfigs.push_back(dgwifiEndOfAcceptedCommandList);

    // Generated Command Lists
    CommandConfig dgwifiEndOfGeneratedCommandList(chip::kInvalidCommandId, COMMAND_MASK_GENERATED);

    clusterConfig->commandConfigs.push_back(dgwifiEndOfGeneratedCommandList);

    // Events
    EventConfig dgwifiDisconnection(0x00000000);
    EventConfig dgwifiAssociationFailure(0x00000001);
    EventConfig dgwifiConnectionStatus(0x00000002);

    clusterConfig->eventConfigs.push_back(dgwifiDisconnection);
    clusterConfig->eventConfigs.push_back(dgwifiAssociationFailure);
    clusterConfig->eventConfigs.push_back(dgwifiConnectionStatus);
}

void matter_cluster_administrator_commissioning_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x0000003C;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Attributes
    AttributeConfig cadminWindowStatus(0x00000000, ZAP_TYPE(ENUM8), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);
    AttributeConfig cadminAdminFabricIndex(0x00000001, ZAP_TYPE(FABRIC_IDX), ZAP_EMPTY_DEFAULT(), 1, NULLABLE_STORAGE);
    AttributeConfig cadminAdminVendorId(0x00000002, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 1, NULLABLE_STORAGE);

    clusterConfig->attributeConfigs.push_back(cadminWindowStatus);
    clusterConfig->attributeConfigs.push_back(cadminAdminFabricIndex);
    clusterConfig->attributeConfigs.push_back(cadminAdminVendorId);

    // Global Attributes
    AttributeConfig cadminAdminFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(0), 4, STORAGE_MASK);
    AttributeConfig cadminAdminClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(1), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(cadminAdminFeatureMap);
    clusterConfig->attributeConfigs.push_back(cadminAdminClusterRevision);

    // Accepted Command Lists
    CommandConfig cadminOpenCommissioningWindow(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig cadminOpenBasicCommissioningWindow(0x00000001, COMMAND_MASK_ACCEPTED);
    CommandConfig cadminRevokeCommissioning(0x00000002, COMMAND_MASK_ACCEPTED);
    CommandConfig cadminEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(cadminOpenCommissioningWindow);
    clusterConfig->commandConfigs.push_back(cadminOpenBasicCommissioningWindow);
    clusterConfig->commandConfigs.push_back(cadminRevokeCommissioning);
    clusterConfig->commandConfigs.push_back(cadminEndOfAcceptedCommandList);

    // Generated Command Lists
    CommandConfig cadminEndOfGeneratedCommandList(chip::kInvalidCommandId, COMMAND_MASK_GENERATED);

    clusterConfig->commandConfigs.push_back(cadminEndOfGeneratedCommandList);
}

void matter_cluster_operational_credentials_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x0000003E;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Attributes
    AttributeConfig opcredsNocs(0x00000000, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig opcredsFabrics(0x00000001, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig opcredsSupportedFabrics(0x00000002, ZAP_TYPE(INT8U), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);
    AttributeConfig opcredsCommissionedFabrics(0x00000003, ZAP_TYPE(INT8U), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);
    AttributeConfig opcredsTrustedRootCertificates(0x00000004, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig opcredsCurrentFabricIndex(0x00000005, ZAP_TYPE(INT8U), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(opcredsNocs);
    clusterConfig->attributeConfigs.push_back(opcredsFabrics);
    clusterConfig->attributeConfigs.push_back(opcredsSupportedFabrics);
    clusterConfig->attributeConfigs.push_back(opcredsCommissionedFabrics);
    clusterConfig->attributeConfigs.push_back(opcredsTrustedRootCertificates);
    clusterConfig->attributeConfigs.push_back(opcredsCurrentFabricIndex);

    // Global Attributes
    AttributeConfig opcredsFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(0), 4, STORAGE_MASK);
    AttributeConfig opcredsClusterRevision(0x0000FFFD, ZAP_TYPE(INT8U), ZAP_SIMPLE_DEFAULT(1), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(opcredsFeatureMap);
    clusterConfig->attributeConfigs.push_back(opcredsClusterRevision);

    // Accepted Command Lists
    CommandConfig opcredsAttestationRequest(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig opcredsCertificateChainRequest(0x00000002, COMMAND_MASK_ACCEPTED);
    CommandConfig opcredsCSRRequest(0x00000004, COMMAND_MASK_ACCEPTED);
    CommandConfig opcredsAddNOC(0x00000006, COMMAND_MASK_ACCEPTED);
    CommandConfig opcredsUpdateNOC(0x00000007, COMMAND_MASK_ACCEPTED);
    CommandConfig opcredsRemoveFabric(0x0000000A, COMMAND_MASK_ACCEPTED);
    CommandConfig opcredsAddTrustedRootCertificate(0x0000000B, COMMAND_MASK_ACCEPTED);
    CommandConfig opcredsEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(opcredsAttestationRequest);
    clusterConfig->commandConfigs.push_back(opcredsCertificateChainRequest);
    clusterConfig->commandConfigs.push_back(opcredsCSRRequest);
    clusterConfig->commandConfigs.push_back(opcredsAddNOC);
    clusterConfig->commandConfigs.push_back(opcredsUpdateNOC);
    clusterConfig->commandConfigs.push_back(opcredsRemoveFabric);
    clusterConfig->commandConfigs.push_back(opcredsAddTrustedRootCertificate);
    clusterConfig->commandConfigs.push_back(opcredsEndOfAcceptedCommandList);

    // Generated Command Lists
    CommandConfig opcredsAttestationResponse(0x00000001, COMMAND_MASK_GENERATED);
    CommandConfig opcredsCertificateChainResponse(0x00000003, COMMAND_MASK_GENERATED);
    CommandConfig opcredsCSRResponse(0x00000005, COMMAND_MASK_GENERATED);
    CommandConfig opcredsNOCResponse(0x00000008, COMMAND_MASK_GENERATED);
    CommandConfig opcredsEndOfGeneratedCommandList(chip::kInvalidCommandId, COMMAND_MASK_GENERATED);

    clusterConfig->commandConfigs.push_back(opcredsAttestationResponse);
    clusterConfig->commandConfigs.push_back(opcredsCertificateChainResponse);
    clusterConfig->commandConfigs.push_back(opcredsCSRResponse);
    clusterConfig->commandConfigs.push_back(opcredsNOCResponse);
    clusterConfig->commandConfigs.push_back(opcredsEndOfGeneratedCommandList);
}

void matter_cluster_group_key_management_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x0000003F;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Attributes
    AttributeConfig gkmGroupKeyMap(0x00000000, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, WRITABLE_STORAGE);
    AttributeConfig gkmGroupTable(0x00000001, ZAP_TYPE(ARRAY), ZAP_EMPTY_DEFAULT(), 0, STORAGE_MASK);
    AttributeConfig gkmMaxGroupsPerFabric(0x00000002, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 2, STORAGE_MASK);
    AttributeConfig gkmMaxGroupKeysPerFabric(0x00000003, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(gkmGroupKeyMap);
    clusterConfig->attributeConfigs.push_back(gkmGroupTable);
    clusterConfig->attributeConfigs.push_back(gkmMaxGroupsPerFabric);
    clusterConfig->attributeConfigs.push_back(gkmMaxGroupKeysPerFabric);

    // Global Attributes
    AttributeConfig gkmFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(0), 4, STORAGE_MASK);
    AttributeConfig gkmClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(1), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(gkmFeatureMap);
    clusterConfig->attributeConfigs.push_back(gkmClusterRevision);

    // Accepted Command Lists
    CommandConfig gkmKeySetWrite(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig gkmKeySetRead(0x00000001, COMMAND_MASK_ACCEPTED);
    CommandConfig gkmKeySetRemove(0x00000003, COMMAND_MASK_ACCEPTED);
    CommandConfig gkmKeySetReadAllIndices(0x00000004, COMMAND_MASK_ACCEPTED);
    CommandConfig gkmEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(gkmKeySetWrite);
    clusterConfig->commandConfigs.push_back(gkmKeySetRead);
    clusterConfig->commandConfigs.push_back(gkmKeySetRemove);
    clusterConfig->commandConfigs.push_back(gkmKeySetReadAllIndices);
    clusterConfig->commandConfigs.push_back(gkmEndOfAcceptedCommandList);

    // Generated Command Lists
    CommandConfig gkmKeySetReadResponse(0x00000002, COMMAND_MASK_GENERATED);
    CommandConfig gkmKeySetReadAllIndicesResponse(0x00000005, COMMAND_MASK_GENERATED);
    CommandConfig gkmEndOfGeneratedCommandList(chip::kInvalidCommandId, COMMAND_MASK_GENERATED);

    clusterConfig->commandConfigs.push_back(gkmKeySetReadResponse);
    clusterConfig->commandConfigs.push_back(gkmKeySetReadAllIndicesResponse);
    clusterConfig->commandConfigs.push_back(gkmEndOfGeneratedCommandList);
}

void matter_cluster_identify_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x00000003;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER) | ZAP_CLUSTER_MASK(INIT_FUNCTION) | ZAP_CLUSTER_MASK(ATTRIBUTE_CHANGED_FUNCTION);

    // Attributes
    AttributeConfig iIdentifyTime(0x00000000, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(0x0000), 2, WRITABLE_STORAGE);
    AttributeConfig iIdentifyType(0x00000001, ZAP_TYPE(ENUM8), ZAP_SIMPLE_DEFAULT(0x0), 1, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(iIdentifyTime);
    clusterConfig->attributeConfigs.push_back(iIdentifyType);

    // Global Attributes
    AttributeConfig iFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(0), 4, STORAGE_MASK);
    AttributeConfig iClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(4), 2, STORAGE_MASK);
    clusterConfig->attributeConfigs.push_back(iFeatureMap);
    clusterConfig->attributeConfigs.push_back(iClusterRevision);

    // Accepted Command Lists
    CommandConfig iIdentify(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig iTriggerEffect(0x00000040, COMMAND_MASK_ACCEPTED);
    CommandConfig iEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(iIdentify);
    clusterConfig->commandConfigs.push_back(iTriggerEffect);
    clusterConfig->commandConfigs.push_back(iEndOfAcceptedCommandList);

    // Functions
    clusterConfig->functionConfigs.push_back((EmberAfGenericClusterFunction) emberAfIdentifyClusterServerInitCallback);
    clusterConfig->functionConfigs.push_back((EmberAfGenericClusterFunction) MatterIdentifyClusterServerAttributeChangedCallback);
}

void matter_cluster_groups_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x00000004;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER) | ZAP_CLUSTER_MASK(INIT_FUNCTION);

    // Attributes
    AttributeConfig gNameSupport(0x00000000, ZAP_TYPE(BITMAP8), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(gNameSupport);

    // Global Attributes
    AttributeConfig gFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(0), 4, STORAGE_MASK);
    AttributeConfig gClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(4), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(gFeatureMap);
    clusterConfig->attributeConfigs.push_back(gClusterRevision);

    // Accepted Command Lists
    CommandConfig gAddGroup(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig gViewGroup(0x00000001, COMMAND_MASK_ACCEPTED);
    CommandConfig gGetGroupMembership(0x00000002, COMMAND_MASK_ACCEPTED);
    CommandConfig gRemoveGroup(0x00000003, COMMAND_MASK_ACCEPTED);
    CommandConfig gRemoveAllGroups(0x00000004, COMMAND_MASK_ACCEPTED);
    CommandConfig gAddGroupIfIdentifying(0x00000005, COMMAND_MASK_ACCEPTED);
    CommandConfig gEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(gAddGroup);
    clusterConfig->commandConfigs.push_back(gViewGroup);
    clusterConfig->commandConfigs.push_back(gGetGroupMembership);
    clusterConfig->commandConfigs.push_back(gRemoveGroup);
    clusterConfig->commandConfigs.push_back(gRemoveAllGroups);
    clusterConfig->commandConfigs.push_back(gAddGroupIfIdentifying);
    clusterConfig->commandConfigs.push_back(gEndOfAcceptedCommandList);

    // Generated Command Lists
    CommandConfig gAddGroupResponse(0x00000000, COMMAND_MASK_GENERATED);
    CommandConfig gViewGroupResponse(0x00000001, COMMAND_MASK_GENERATED);
    CommandConfig gGetGroupMembershipResponse(0x00000002, COMMAND_MASK_GENERATED);
    CommandConfig gRemoveGroupResponse(0x00000003, COMMAND_MASK_GENERATED);
    CommandConfig gEndOfGeneratedCommandList(chip::kInvalidCommandId, COMMAND_MASK_GENERATED);

    clusterConfig->commandConfigs.push_back(gAddGroupResponse);
    clusterConfig->commandConfigs.push_back(gViewGroupResponse);
    clusterConfig->commandConfigs.push_back(gGetGroupMembershipResponse);
    clusterConfig->commandConfigs.push_back(gRemoveGroupResponse);
    clusterConfig->commandConfigs.push_back(gEndOfGeneratedCommandList);

    // Functions
    clusterConfig->functionConfigs.push_back((EmberAfGenericClusterFunction) emberAfGroupsClusterServerInitCallback);
}

void matter_cluster_onoff_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x00000006;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER) | ZAP_CLUSTER_MASK(INIT_FUNCTION) | ZAP_CLUSTER_MASK(SHUTDOWN_FUNCTION);

    // Attributes
    AttributeConfig ooOnOff(0x00000000, ZAP_TYPE(BOOLEAN), ZAP_SIMPLE_DEFAULT(0x00), 1, STORAGE_MASK | ZAP_ATTRIBUTE_MASK(TOKENIZE));
    AttributeConfig ooGlobalSceneControl(0x00004000, ZAP_TYPE(BOOLEAN), ZAP_SIMPLE_DEFAULT(0x01), 1, STORAGE_MASK);
    AttributeConfig ooOnTime(0x00004001, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(0x0000), 2, WRITABLE_STORAGE);
    AttributeConfig ooOffWaitTime(0x00004002, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(0x0000), 2, WRITABLE_STORAGE);
    AttributeConfig ooStartUpOnOff(0x00004003, ZAP_TYPE(ENUM8), &onoffStartUpOnOffMinMaxValue, 1, STORAGE_MASK | ZAP_ATTRIBUTE_MASK(TOKENIZE) | ZAP_ATTRIBUTE_MASK(WRITABLE) | ZAP_ATTRIBUTE_MASK(NULLABLE));

    clusterConfig->attributeConfigs.push_back(ooOnOff);
    clusterConfig->attributeConfigs.push_back(ooGlobalSceneControl);
    clusterConfig->attributeConfigs.push_back(ooOnTime);
    clusterConfig->attributeConfigs.push_back(ooOffWaitTime);
    clusterConfig->attributeConfigs.push_back(ooStartUpOnOff);

    // Global Attributes
    AttributeConfig ooFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(1), 4, STORAGE_MASK);
    AttributeConfig ooClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(4), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(ooFeatureMap);
    clusterConfig->attributeConfigs.push_back(ooClusterRevision);

    // Accepted Command Lists
    CommandConfig ooOff(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig ooOn(0x00000001, COMMAND_MASK_ACCEPTED);
    CommandConfig ooToggle(0x00000002, COMMAND_MASK_ACCEPTED);
    CommandConfig ooOffWithEffect(0x00000040, COMMAND_MASK_ACCEPTED);
    CommandConfig ooOnWithRecallGlobalScene(0x00000041, COMMAND_MASK_ACCEPTED);
    CommandConfig ooOnWithTimedOff(0x00000042, COMMAND_MASK_ACCEPTED);
    CommandConfig ooEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(ooOff);
    clusterConfig->commandConfigs.push_back(ooOn);
    clusterConfig->commandConfigs.push_back(ooToggle);
    clusterConfig->commandConfigs.push_back(ooOffWithEffect);
    clusterConfig->commandConfigs.push_back(ooOnWithRecallGlobalScene);
    clusterConfig->commandConfigs.push_back(ooOnWithTimedOff);
    clusterConfig->commandConfigs.push_back(ooEndOfAcceptedCommandList);

    // Generated Command Lists
    CommandConfig ooMoveToLevel(0x00000000, COMMAND_MASK_GENERATED);
    CommandConfig ooMove(0x00000001, COMMAND_MASK_GENERATED);
    CommandConfig ooStep(0x00000002, COMMAND_MASK_GENERATED);
    CommandConfig ooStop(0x00000003, COMMAND_MASK_GENERATED);
    CommandConfig ooMoveToLevelWithOnOff(0x00000004, COMMAND_MASK_GENERATED);
    CommandConfig ooMoveWithOnOff(0x00000005, COMMAND_MASK_GENERATED);
    CommandConfig ooStepWithOnOff(0x00000006, COMMAND_MASK_GENERATED);
    CommandConfig ooStopWithOnOff(0x00000007, COMMAND_MASK_GENERATED);
    CommandConfig ooEndOfGeneratedCommandList(chip::kInvalidCommandId, COMMAND_MASK_GENERATED);

    clusterConfig->commandConfigs.push_back(ooMoveToLevel);
    clusterConfig->commandConfigs.push_back(ooMove);
    clusterConfig->commandConfigs.push_back(ooStep);
    clusterConfig->commandConfigs.push_back(ooStop);
    clusterConfig->commandConfigs.push_back(ooMoveToLevelWithOnOff);
    clusterConfig->commandConfigs.push_back(ooStepWithOnOff);
    clusterConfig->commandConfigs.push_back(ooStopWithOnOff);
    clusterConfig->commandConfigs.push_back(ooEndOfGeneratedCommandList);

    // Functions
    clusterConfig->functionConfigs.push_back((EmberAfGenericClusterFunction) emberAfOnOffClusterServerInitCallback);
    clusterConfig->functionConfigs.push_back((EmberAfGenericClusterFunction) MatterOnOffClusterServerShutdownCallback);
}

void matter_cluster_level_control_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x00000008;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER) | ZAP_CLUSTER_MASK(INIT_FUNCTION) | ZAP_CLUSTER_MASK(SHUTDOWN_FUNCTION);

    // Attributes
    AttributeConfig lvlCurrentLevel(0x00000000, ZAP_TYPE(INT8U), ZAP_SIMPLE_DEFAULT(0x01), 1, STORAGE_MASK | ZAP_ATTRIBUTE_MASK(TOKENIZE) | ZAP_ATTRIBUTE_MASK(NULLABLE));
    AttributeConfig lvlRemainingTime(0x00000001, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(0x0000), 2, STORAGE_MASK);
    AttributeConfig lvlMinLevel(0x00000002, ZAP_TYPE(INT8U), ZAP_SIMPLE_DEFAULT(0x01), 1, STORAGE_MASK);
    AttributeConfig lvlMaxLevel(0x00000003, ZAP_TYPE(INT8U), ZAP_SIMPLE_DEFAULT(0xFE), 1, STORAGE_MASK);
    AttributeConfig lvlCurrentFrequency(0x00000004, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(0x0000), 2, STORAGE_MASK);
    AttributeConfig lvlMinFrequency(0x00000005, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(0x0000), 2, STORAGE_MASK);
    AttributeConfig lvlMaxFrequency(0x00000006, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(0x0000), 2, STORAGE_MASK);
    AttributeConfig lvlOptions(0x0000000F, ZAP_TYPE(BITMAP8), &levelcontrolOptionsMinMaxValue, 1, STORAGE_MASK | ZAP_ATTRIBUTE_MASK(MIN_MAX) | ZAP_ATTRIBUTE_MASK(WRITABLE));
    AttributeConfig lvlOnOffTransitionTime(0x00000010, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(0x0000), 2, WRITABLE_STORAGE);
    AttributeConfig lvlOnLevel(0x00000011, ZAP_TYPE(INT8U), ZAP_SIMPLE_DEFAULT(0xFF), 1, WRITABLE_STORAGE | ZAP_ATTRIBUTE_MASK(NULLABLE));
    AttributeConfig lvlOnTransitionTime(0x00000012, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 2, WRITABLE_STORAGE | ZAP_ATTRIBUTE_MASK(NULLABLE));
    AttributeConfig lvlOffTransitionTime(0x00000013, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 2, WRITABLE_STORAGE | ZAP_ATTRIBUTE_MASK(NULLABLE));
    AttributeConfig lvlDefaultMoveRate(0x00000014, ZAP_TYPE(INT8U), ZAP_SIMPLE_DEFAULT(50), 1, WRITABLE_STORAGE | ZAP_ATTRIBUTE_MASK(NULLABLE));
    AttributeConfig lvlStartUpCurrentLevel(0x00004000, ZAP_TYPE(INT8U), ZAP_SIMPLE_DEFAULT(255), 1, STORAGE_MASK | ZAP_ATTRIBUTE_MASK(TOKENIZE) | ZAP_ATTRIBUTE_MASK(WRITABLE) | ZAP_ATTRIBUTE_MASK(NULLABLE));

    clusterConfig->attributeConfigs.push_back(lvlCurrentLevel);
    clusterConfig->attributeConfigs.push_back(lvlRemainingTime);
    clusterConfig->attributeConfigs.push_back(lvlMinLevel);
    clusterConfig->attributeConfigs.push_back(lvlMaxLevel);
    clusterConfig->attributeConfigs.push_back(lvlCurrentFrequency);
    clusterConfig->attributeConfigs.push_back(lvlMinFrequency);
    clusterConfig->attributeConfigs.push_back(lvlMaxFrequency);
    clusterConfig->attributeConfigs.push_back(lvlOptions);
    clusterConfig->attributeConfigs.push_back(lvlOnOffTransitionTime);
    clusterConfig->attributeConfigs.push_back(lvlOnLevel);
    clusterConfig->attributeConfigs.push_back(lvlOnTransitionTime);
    clusterConfig->attributeConfigs.push_back(lvlOffTransitionTime);
    clusterConfig->attributeConfigs.push_back(lvlDefaultMoveRate);
    clusterConfig->attributeConfigs.push_back(lvlStartUpCurrentLevel);

    // Global Attributes
    AttributeConfig lvlFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(3), 4, STORAGE_MASK);
    AttributeConfig lvlClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(5), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(lvlFeatureMap);
    clusterConfig->attributeConfigs.push_back(lvlClusterRevision);

    // Accepted Command Lists
    CommandConfig lvlMoveToLevel(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig lvlMove(0x00000001, COMMAND_MASK_ACCEPTED);
    CommandConfig lvlStep(0x00000002, COMMAND_MASK_ACCEPTED);
    CommandConfig lvlStop(0x00000003, COMMAND_MASK_ACCEPTED);
    CommandConfig lvlMoveToLevelWithOnOff(0x00000004, COMMAND_MASK_ACCEPTED);
    CommandConfig lvlMoveWithOnOff(0x00000005, COMMAND_MASK_ACCEPTED);
    CommandConfig lvlStepWithOnOff(0x00000006, COMMAND_MASK_ACCEPTED);
    CommandConfig lvlStopWithOnOff(0x00000007, COMMAND_MASK_ACCEPTED);
    CommandConfig lvlEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(lvlMoveToLevel);
    clusterConfig->commandConfigs.push_back(lvlMove);
    clusterConfig->commandConfigs.push_back(lvlStep);
    clusterConfig->commandConfigs.push_back(lvlStop);
    clusterConfig->commandConfigs.push_back(lvlMoveToLevelWithOnOff);
    clusterConfig->commandConfigs.push_back(lvlMoveWithOnOff);
    clusterConfig->commandConfigs.push_back(lvlStepWithOnOff);
    clusterConfig->commandConfigs.push_back(lvlStopWithOnOff);
    clusterConfig->commandConfigs.push_back(lvlEndOfAcceptedCommandList);

    // Generated Command Lists
    CommandConfig lvlEndOfGeneratedCommandList(chip::kInvalidCommandId, COMMAND_MASK_GENERATED);

    clusterConfig->commandConfigs.push_back(lvlEndOfGeneratedCommandList);

    // Functions
    clusterConfig->functionConfigs.push_back((EmberAfGenericClusterFunction) emberAfLevelControlClusterServerInitCallback);
    clusterConfig->functionConfigs.push_back((EmberAfGenericClusterFunction) MatterLevelControlClusterServerShutdownCallback);
}

void matter_cluster_scenes_server(ClusterConfig *clusterConfig)
{
    clusterConfig->clusterId = 0x00000005;
    clusterConfig->mask = ZAP_CLUSTER_MASK(SERVER);

    // Attributes
    AttributeConfig sSceneCount(0x00000000, ZAP_TYPE(INT8U), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);
    AttributeConfig sCurrentScene(0x00000001, ZAP_TYPE(INT8U), ZAP_SIMPLE_DEFAULT(0x00), 1, STORAGE_MASK);
    AttributeConfig sCurrentGroup(0x00000002, ZAP_TYPE(GROUP_ID), ZAP_SIMPLE_DEFAULT(0x0000), 2, STORAGE_MASK);
    AttributeConfig sSceneValid(0x00000003, ZAP_TYPE(BOOLEAN), ZAP_SIMPLE_DEFAULT(0x00), 1, STORAGE_MASK);
    AttributeConfig sNameSupport(0x00000004, ZAP_TYPE(BITMAP8), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);
    AttributeConfig sLastConfiguredBy(0x00000005, ZAP_TYPE(NODE_ID), uint32_t(0), 8, NULLABLE_STORAGE);
    AttributeConfig sSceneTableSize(0x00000006, ZAP_TYPE(INT16U), ZAP_EMPTY_DEFAULT(), 2, STORAGE_MASK);
    AttributeConfig sRemainingCapacity(0x00000007, ZAP_TYPE(INT8U), ZAP_EMPTY_DEFAULT(), 1, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(sSceneCount);
    clusterConfig->attributeConfigs.push_back(sCurrentScene);
    clusterConfig->attributeConfigs.push_back(sCurrentGroup);
    clusterConfig->attributeConfigs.push_back(sSceneValid);
    clusterConfig->attributeConfigs.push_back(sNameSupport);
    clusterConfig->attributeConfigs.push_back(sLastConfiguredBy);
    clusterConfig->attributeConfigs.push_back(sSceneTableSize);
    clusterConfig->attributeConfigs.push_back(sRemainingCapacity);

    // Global Attributes
    AttributeConfig sFeatureMap(0x0000FFFC, ZAP_TYPE(BITMAP32), ZAP_SIMPLE_DEFAULT(0), 4, STORAGE_MASK);
    AttributeConfig sClusterRevision(0x0000FFFD, ZAP_TYPE(INT16U), ZAP_SIMPLE_DEFAULT(5), 2, STORAGE_MASK);

    clusterConfig->attributeConfigs.push_back(sFeatureMap);
    clusterConfig->attributeConfigs.push_back(sClusterRevision);

    // Accepted Command Lists
    CommandConfig sAddScene(0x00000000, COMMAND_MASK_ACCEPTED);
    CommandConfig sViewScene(0x00000001, COMMAND_MASK_ACCEPTED);
    CommandConfig sRemoveScene(0x00000002, COMMAND_MASK_ACCEPTED);
    CommandConfig sRemoveAllScenes(0x00000003, COMMAND_MASK_ACCEPTED);
    CommandConfig sStoreScene(0x00000004, COMMAND_MASK_ACCEPTED);
    CommandConfig sRecallScene(0x00000005, COMMAND_MASK_ACCEPTED);
    CommandConfig sGetSceneMembership(0x00000006, COMMAND_MASK_ACCEPTED);
    CommandConfig sEndOfAcceptedCommandList(chip::kInvalidCommandId, COMMAND_MASK_ACCEPTED);

    clusterConfig->commandConfigs.push_back(sAddScene);
    clusterConfig->commandConfigs.push_back(sViewScene);
    clusterConfig->commandConfigs.push_back(sRemoveScene);
    clusterConfig->commandConfigs.push_back(sRemoveAllScenes);
    clusterConfig->commandConfigs.push_back(sStoreScene);
    clusterConfig->commandConfigs.push_back(sRecallScene);
    clusterConfig->commandConfigs.push_back(sGetSceneMembership);
    clusterConfig->commandConfigs.push_back(sEndOfAcceptedCommandList);

    // Generated Command Lists
    CommandConfig sAddSceneResponse(0x00000000, COMMAND_MASK_GENERATED);
    CommandConfig sViewSceneResponse(0x00000001, COMMAND_MASK_GENERATED);
    CommandConfig sRemoveSceneResponse(0x00000002, COMMAND_MASK_GENERATED);
    CommandConfig sRemoveAllScenesResponse(0x00000003, COMMAND_MASK_GENERATED);
    CommandConfig sStoreSceneResponse(0x00000004, COMMAND_MASK_GENERATED);
    CommandConfig sGetSceneMembershipResponse(0x00000006, COMMAND_MASK_GENERATED);
    CommandConfig sEndOfGeneratedCommandList(chip::kInvalidCommandId, COMMAND_MASK_GENERATED);

    clusterConfig->commandConfigs.push_back(sAddSceneResponse);
    clusterConfig->commandConfigs.push_back(sViewSceneResponse);
    clusterConfig->commandConfigs.push_back(sRemoveSceneResponse);
    clusterConfig->commandConfigs.push_back(sRemoveAllScenesResponse);
    clusterConfig->commandConfigs.push_back(sStoreSceneResponse);
    clusterConfig->commandConfigs.push_back(sGetSceneMembershipResponse);
    clusterConfig->commandConfigs.push_back(sEndOfGeneratedCommandList);
}

} // Clusters

namespace Endpoints {

void matter_root_node_preset(EndpointConfig *rootNodeEndpointConfig)
{
    ClusterConfig descServerCluster;
    ClusterConfig aclServerCluster;
    ClusterConfig binfoServerCluster;
    ClusterConfig otarServerCluster;
    ClusterConfig cgenServerCluster;
    ClusterConfig cnetServerCluster;
    ClusterConfig dggenServerCluster;
    ClusterConfig dgswServerCluster;
    ClusterConfig dgwifiServerCluster;
    ClusterConfig cadminServerCluster;
    ClusterConfig opcreadsServerCluster;
    ClusterConfig gkmServerCluster;

    Presets::Clusters::matter_cluster_descriptor_server(&descServerCluster);
    Presets::Clusters::matter_cluster_access_control_server(&aclServerCluster);
    Presets::Clusters::matter_cluster_basic_information_server(&binfoServerCluster);
    Presets::Clusters::matter_cluster_ota_requestor_server(&otarServerCluster);
    Presets::Clusters::matter_cluster_general_commissioning_server(&cgenServerCluster);
    Presets::Clusters::matter_cluster_network_commissioning_server(&cnetServerCluster);
    Presets::Clusters::matter_cluster_general_diagnostics_server(&dggenServerCluster);
    Presets::Clusters::matter_cluster_software_diagnostics_server(&dgswServerCluster);
    Presets::Clusters::matter_cluster_wifi_network_diagnostics_server(&dgwifiServerCluster);
    Presets::Clusters::matter_cluster_administrator_commissioning_server(&cadminServerCluster);
    Presets::Clusters::matter_cluster_operational_credentials_server(&opcreadsServerCluster);
    Presets::Clusters::matter_cluster_group_key_management_server(&gkmServerCluster);

    rootNodeEndpointConfig->clusterConfigs.push_back(descServerCluster);
    rootNodeEndpointConfig->clusterConfigs.push_back(aclServerCluster);
    rootNodeEndpointConfig->clusterConfigs.push_back(binfoServerCluster);
    rootNodeEndpointConfig->clusterConfigs.push_back(otarServerCluster);
    rootNodeEndpointConfig->clusterConfigs.push_back(cgenServerCluster);
    rootNodeEndpointConfig->clusterConfigs.push_back(cnetServerCluster);
    rootNodeEndpointConfig->clusterConfigs.push_back(dggenServerCluster);
    rootNodeEndpointConfig->clusterConfigs.push_back(dgswServerCluster);
    rootNodeEndpointConfig->clusterConfigs.push_back(dgwifiServerCluster);
    rootNodeEndpointConfig->clusterConfigs.push_back(cadminServerCluster);
    rootNodeEndpointConfig->clusterConfigs.push_back(opcreadsServerCluster);
    rootNodeEndpointConfig->clusterConfigs.push_back(gkmServerCluster);
}

void matter_dimmable_light_preset(EndpointConfig *dimmableLightEndpointConfig)
{
    ClusterConfig descServerCluster;
    ClusterConfig iServerCluster;
    ClusterConfig gServerCluster;
    ClusterConfig sServerCluster;
    ClusterConfig ooServerCluster;
    ClusterConfig lvlServerCluster;

    Presets::Clusters::matter_cluster_descriptor_server(&descServerCluster);
    Presets::Clusters::matter_cluster_identify_server(&iServerCluster);
    Presets::Clusters::matter_cluster_groups_server(&gServerCluster);
    Presets::Clusters::matter_cluster_scenes_server(&sServerCluster);
    Presets::Clusters::matter_cluster_onoff_server(&ooServerCluster);
    Presets::Clusters::matter_cluster_level_control_server(&lvlServerCluster);

    dimmableLightEndpointConfig->clusterConfigs.push_back(descServerCluster);
    dimmableLightEndpointConfig->clusterConfigs.push_back(iServerCluster);
    dimmableLightEndpointConfig->clusterConfigs.push_back(gServerCluster);
    dimmableLightEndpointConfig->clusterConfigs.push_back(sServerCluster);
    dimmableLightEndpointConfig->clusterConfigs.push_back(ooServerCluster);
    dimmableLightEndpointConfig->clusterConfigs.push_back(lvlServerCluster);
}

void matter_aggregator_preset(EndpointConfig *aggregatorEndpointConfig)
{
    ClusterConfig descServerCluster;

    Presets::Clusters::matter_cluster_descriptor_server(&descServerCluster);

    aggregatorEndpointConfig->clusterConfigs.push_back(descServerCluster);
}

} // Endpoints

} // Presetst
