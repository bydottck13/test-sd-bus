#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <systemd/sd-bus.h>
#include <systemd/sd-id128.h>

#define new0(t, n) ((t*) calloc((n), sizeof(t)))

#define SERVICE_NAME "com.cybernut.demoB"
#define OBJECT_PATH "/com/cybernut/demoB/ServiceB"
#define INTERFACE_NAME "com.cybernut.demoB.ServiceB"

typedef struct Manager Manager;

struct Manager {
	sd_bus *bus;
	sd_bus_slot *slot;

	// Add some configurations here.
};

extern const sd_bus_vtable service_vtable[];
extern Manager *manager;

int match_signal_test(sd_bus_message *message, void *userdata, sd_bus_error *ret_error);
