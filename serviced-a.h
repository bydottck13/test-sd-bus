#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <inttypes.h>
#include <systemd/sd-bus.h>
#include <systemd/sd-id128.h>

#define new0(t, n) ((t*) calloc((n), sizeof(t)))

#define SERVICE_NAME "com.cybernut.demoA"
#define OBJECT_PATH "/com/cybernut/demoA/ServiceA"
#define INTERFACE_NAME "com.cybernut.demoA.ServiceA"

typedef struct Manager Manager;

struct Manager {
	sd_bus *bus;
	sd_bus_slot *slot;

	// Add some configurations here.
};

extern const sd_bus_vtable service_vtable[];
extern Manager *manager;

int match_signal_test(sd_bus_message *message, void *userdata, sd_bus_error *ret_error);
//int match_name_owner_changed(sd_bus_message *message, void *userdata, sd_bus_error *ret_error);
