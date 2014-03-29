#pragma once

#include "windows-api-headers.h"

#define METRIC_AUTO 0

DWORD FillIpInterfaceEntry(const MIB_IF_ROW2 & if_row2, ADDRESS_FAMILY Family, PMIB_IPINTERFACE_ROW ipinterface_row);
DWORD SetIpInterfaceEntryWrapper(PMIB_IPINTERFACE_ROW Row);

bool IsMetricValid(int metric);
void AssignMetric(PMIB_IPINTERFACE_ROW ipinterface, int metric);
