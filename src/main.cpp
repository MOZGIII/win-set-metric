#include <cstdio>
#include <cwchar>

#include "IfTable2Wrapper.h"
#include "IpInterfaceHelper.h"
#include "MultibyteString.h"

void print_info(const MIB_IF_ROW2 & IF_ROW2, const MIB_IPINTERFACE_ROW & IPINTERFACE_ROW)
{
	{
		MultibyteString str(IF_ROW2.Alias);
		wprintf(L"Name: %S\n", str);
	}

	{
		MultibyteString str(IF_ROW2.Description);
		wprintf(L"Description: %S\n", str);
	}

	wprintf(L"Metric: %d\n", IPINTERFACE_ROW.Metric);
}

void show_interfaces_info(void)
{
	IfTable2Wrapper IfTable2;

	for (ULONG i = 0; i < IfTable2.NumEntries(); i++)
	{
		MIB_IPINTERFACE_ROW ipinterface;
		if (FillIpInterfaceEntry(IfTable2[i], AF_INET, &ipinterface) != NO_ERROR) continue;
		print_info(IfTable2[i], ipinterface);
		wprintf(L"\n");
	}
}

bool get_interface_metric(WCHAR * interface_name)
{
	IfTable2Wrapper IfTable2;

	int count = 0;
	for (ULONG i = 0; i < IfTable2.NumEntries(); i++)
	{
		if (wcscmp(IfTable2[i].Alias, interface_name) != 0) continue;
		MIB_IPINTERFACE_ROW ipinterface;
		if (FillIpInterfaceEntry(IfTable2[i], AF_INET, &ipinterface) != NO_ERROR) continue;
		print_info(IfTable2[i], ipinterface);
		wprintf(L"\n");
		count++;
	}

	if (count == 0)
	{
		wprintf(L"No interfaces with such name!\n", count);
	}
	return count > 0;
}

bool set_interface_metric(WCHAR * interface_name, int metric)
{
	IfTable2Wrapper IfTable2;

	int count = 0;
	for (ULONG i = 0; i < IfTable2.NumEntries(); i++)
	{
		if (wcscmp(IfTable2[i].Alias, interface_name) != 0) continue;
		MIB_IPINTERFACE_ROW ipinterface;
		if (FillIpInterfaceEntry(IfTable2[i], AF_INET, &ipinterface) != NO_ERROR) continue;
		AssignMetric(&ipinterface, metric);
		SetIpInterfaceEntryWrapper(&ipinterface);
		count++;
	}

	if (count == 0)
	{
		wprintf(L"No interfaces with such name!\n", count);
	}
	else
	{
		wprintf(L"Metric set on %d interface(s)!\n", count);
	}
	return count > 0;
}

int wmain(int argc, WCHAR *argv[])
{
	switch (argc)
	{
	case 1:
		show_interfaces_info();
		return 0;
		break;
	case 2:
		return get_interface_metric(argv[1]) ? 0 : 1;
		break;
	case 3:
		int metric;
		if (wcscmp(argv[1], L"auto") == 0)
		{
			metric = METRIC_AUTO;
		}
		else
		{
			metric = wcstol(argv[2], NULL, 0);
			if (!IsMetricValid(metric))
			{
				wprintf(L"Error: metric must be between 1 and 9999\n");
				return 1;
			}
		}
		return set_interface_metric(argv[1], metric) ? 0 : 1;
		break;
	default:
		wprintf(L"Usage: %s [interface_name [new_metric_value]]\n", argv[0]);
		return 1;
	}
}
