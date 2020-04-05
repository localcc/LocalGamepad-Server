//
// Created by local on 02.04.2020.
//

#include <controller/controller.h>
#include <controller/controller_conversion.h>

int controller::handle(unsigned char* data) {
#ifdef WIN32
    return handle_windows(data);
#endif
}

int controller::init() {
#ifdef WIN32
    return init_windows();
#endif
}

void controller::uninit() const {
#ifdef WIN32
    stop_windows();
#endif
}

int controller::init_windows() {
    this->driver_client = vigem_alloc();
    this->driver_target = vigem_target_x360_alloc();
    if (vigem_connect(this->driver_client) != VIGEM_ERROR_NONE) return -80;
    if (vigem_target_add(this->driver_client, this->driver_target) != VIGEM_ERROR_NONE) return -81;

    return 0;
}

int controller::handle_windows(unsigned char* data) {
    vigem_target_x360_update(this->driver_client, this->driver_target, controller_conversion::data_to_report(data));
    return 0;
}


void controller::stop_windows() const {
    vigem_disconnect(this->driver_client);
    vigem_target_remove(this->driver_client, this->driver_target);
    vigem_target_free(this->driver_target);
    vigem_free(this->driver_client);
}

