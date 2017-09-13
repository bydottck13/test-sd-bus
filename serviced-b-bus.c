#include "serviced-b.h"

static int method_do_multiply(sd_bus_message *message, void *userdata, sd_bus_error *ret_error) {
	int64_t x, y;
	int r;
	int64_t reply;
	sd_bus_error error = SD_BUS_ERROR_NULL;
	sd_bus_message *m_fr_demoA = NULL;

	/* Read the parameters */
	r = sd_bus_message_read(message, "xx", &x, &y);
	if (r < 0) {
		fprintf(stderr, "Failed to parse parameters: %s\n", strerror(-r));
		return r;
	}

	/* Issue the method call and store the response message in m_fr_demoA */
	r = sd_bus_call_method(
		manager->bus,
		"com.cybernut.demoA",			/* service to contact */
		"/com/cybernut/demoA/ServiceA",	/* object path */
		"com.cybernut.demoA.ServiceA",	/* interface name */
		"Multiply",						/* method name */
		&error,							/* object to return error in */
		&m_fr_demoA,					/* return message on success */
		"xx",							/* input signature */
		x,								/* first argument */
		y);							/* second argument */
	if (r < 0) {
		fprintf(stderr, "Failed to issue method call: %s\n", error.message);
	}

	/* Parse the response message */
	r = sd_bus_message_read(m_fr_demoA, "x", &reply);
	if (r < 0) {
		fprintf(stderr, "Failed to parse response message: %s\n", strerror(-r));
	}

	printf("The multiply result is %ld.\n", reply);

	sd_bus_error_free(&error);
	sd_bus_message_unref(m_fr_demoA);

	/* Reply with the response */
	return sd_bus_reply_method_return(message, "x", reply);
}

int match_signal_test(sd_bus_message *message, void *userdata, sd_bus_error *ret_error) {
	int64_t test_message;
	int r;

	//printf("Hello, match_signal_test\n");

	r = sd_bus_message_read(message, "x", &test_message);
	if (r < 0) {
		fprintf(stderr, "Failed to parse signal: %s\n", strerror(-r));
		return 0;
	}

	printf("Received a signal from demoA: %ld\n", test_message);

	return 0;
}

/* The vtable of our little object, implements the interface */
// SD_BUS_METHOD(_member, _signature, _result, _handler, _flag)
// SD_BUS_SIGNAL(_member, _signature, _flags) 
// types for signature: 
// BYTE: y
// BOOLEAN: b
// INT16: n, UINT16: q
// INT32: i, UINT32: u
// INT64: x, UINT64: t
// DOUBLE: d
// UNIX_FD: h
// STRING: s
// OBJECT_PATH: o
// SIGNATURE: g
// ARRAY: a, ARRAY of two Int32: a(ii)

const sd_bus_vtable service_vtable[] = {
	SD_BUS_VTABLE_START(0),
	SD_BUS_METHOD("DoMultiply", "xx", "x", method_do_multiply, SD_BUS_VTABLE_UNPRIVILEGED),

	SD_BUS_SIGNAL("SignalTestB", "x", 0),
	SD_BUS_VTABLE_END
};
