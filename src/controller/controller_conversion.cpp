#include <controller/controller_offsets.h>
#include <controller/controller_conversion.h>
#include <cstdio>

XUSB_REPORT controller_conversion::data_to_report(unsigned char* data) {
	XUSB_REPORT report;
    report.wButtons = 0;
    if(data[0] & 0b1) report.wButtons |= XUSB_GAMEPAD_A;
    if((data[0] >> GB_OFF_B) & 0b1) report.wButtons |= XUSB_GAMEPAD_B;
    if((data[0] >> GB_OFF_X) & 0b1) report.wButtons |= XUSB_GAMEPAD_X;
    if((data[0] >> GB_OFF_Y) & 0b1) report.wButtons |= XUSB_GAMEPAD_Y;
    if((data[0] >> GB_OFF_SEL) & 0b1) report.wButtons |= XUSB_GAMEPAD_BACK;
    if((data[0] >> GB_OFF_START) & 0b1) report.wButtons |= XUSB_GAMEPAD_START;
    if((data[0] >> GB_OFF_S1_Z) & 0b1) report.wButtons |= XUSB_GAMEPAD_LEFT_THUMB;
    if(data[1] & 0b1) report.wButtons |= XUSB_GAMEPAD_RIGHT_THUMB;
    if((data[1] >> GB_OFF_LB) & 0b1) report.wButtons |= XUSB_GAMEPAD_LEFT_SHOULDER;
    if((data[1] >> GB_OFF_RB) & 0b1) report.wButtons |= XUSB_GAMEPAD_RIGHT_SHOULDER;
    if((data[1] >> GB_OFF_UP) & 0b1) report.wButtons |= XUSB_GAMEPAD_DPAD_UP;
    if((data[1] >> GB_OFF_DOWN) & 0b1) report.wButtons |= XUSB_GAMEPAD_DPAD_DOWN;
    if((data[1] >> GB_OFF_LEFT) & 0b1) report.wButtons |= XUSB_GAMEPAD_DPAD_LEFT;
    if((data[1] >> GB_OFF_RIGHT) & 0b1) report.wButtons |= XUSB_GAMEPAD_DPAD_RIGHT;

    report.sThumbLX = (data[2] & 0xff) | (data[3] << 8);
    // data comes inverted
    report.sThumbLY = -((data[4] & 0xff) | (data[5] << 8)) - 1;
    report.sThumbRX = (data[6] & 0xff) | (data[7] << 8);
    // data comes inverted
    report.sThumbRY = -((data[8] & 0xff) | (data[9] << 8)) - 1;

	report.bLeftTrigger = map((data[10] & 0xff) | (data[11] << 8), 32767, 255);
	report.bRightTrigger = map(((data[12] & 0xff) | (data[13] << 8)), 32767, 255);
	return report;
}