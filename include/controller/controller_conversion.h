#pragma once
#include <ViGEm/Common.h>
#include <cmath>
#define map(val, before_max, after_max) (unsigned char)lround(((double)(val * after_max) / before_max))

class controller_conversion {
public:
	static XUSB_REPORT data_to_report(unsigned char* data);
};