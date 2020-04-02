//
// Created by local on 02.04.2020.
//

#ifndef LOCALGAMEPAD_SERVER_CONTROLLER_CONVERSIONS_H
#define LOCALGAMEPAD_SERVER_CONTROLLER_CONVERSIONS_H
#include <ViGEm/Common.h>

class controller_conversions {
public:
    static XUSB_REPORT data_to_report(char* data);
};

#endif //LOCALGAMEPAD_SERVER_CONTROLLER_CONVERSIONS_H
