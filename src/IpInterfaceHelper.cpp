#include "IpInterfaceHelper.h"

DWORD FillIpInterfaceEntry(const MIB_IF_ROW2 & if_row2, ADDRESS_FAMILY Family, PMIB_IPINTERFACE_ROW ipinterface_row)
{
	InitializeIpInterfaceEntry(ipinterface_row);
	
	ipinterface_row->Family = Family;
	ipinterface_row->InterfaceLuid = if_row2.InterfaceLuid;
	ipinterface_row->InterfaceIndex = if_row2.InterfaceIndex;

	return GetIpInterfaceEntry(ipinterface_row);
}

DWORD SetIpInterfaceEntryWrapper(PMIB_IPINTERFACE_ROW Row)
{
	// For IPv4
	if (Row->Family == AF_INET)
	{
		// Force set SitePrefixLength to 0 
		// as required by MSDN
		Row->SitePrefixLength = 0;
	}
	return SetIpInterfaceEntry(Row);
}

bool IsMetricValid(int metric)
{
	if (metric <= 0 || metric > 9999) return false;
	return true;
}

void AssignMetric(PMIB_IPINTERFACE_ROW ipinterface, int metric)
{
	if (metric == METRIC_AUTO)
	{
		ipinterface->UseAutomaticMetric = true;
	}
	else if (IsMetricValid(metric))
	{
		ipinterface->UseAutomaticMetric = false;
		ipinterface->Metric = metric;
	}
	else
	{
		throw("Invalid metric value!");
	}
}
