#include "serviced-a.h"

static int method_multiply(sd_bus_message *message, void *userdata, sd_bus_error *ret_error) {
	int64_t x, y;
	int r;

	/* Read the parameters */
	r = sd_bus_message_read(message, "xx", &x, &y);
	if (r < 0) {
		fprintf(stderr, "Failed to parse parameters: %s\n", strerror(-r));
		return r;
	}

	/* Reply with the response */
	return sd_bus_reply_method_return(message, "x", x * y);
}

static int method_hello(sd_bus_message *message, void *userdata, sd_bus_error *ret_error) {
	const char *read_message;
	int r;

	/* Read the parameters */
	r = sd_bus_message_read(message, "s", &read_message);
	if (r < 0) {
		fprintf(stderr, "Failed to parse parameters: %s\n", strerror(-r));
		return r;
	}

	return sd_bus_reply_method_return(message, "s", "Hello test!");
}

static int method_hello_no_reply(sd_bus_message *message, void *userdata, sd_bus_error *ret_error) {
	const char *read_message;
	int r;

	/* Read the parameters */
	r = sd_bus_message_read(message, "s", &read_message);
	if (r < 0) {
		fprintf(stderr, "Failed to parse parameters: %s\n", strerror(-r));
		return r;
	}
	printf("method_hello_no_reply %s\n", read_message);
	return r;
}

/*int match_name_owner_changed(sd_bus_message *message, void *userdata, sd_bus_error *ret_error) {
	const char *path, *unit, *ssss;
	int r;

	printf("Hello, match_name_owner_changed\n");

	r = sd_bus_message_read(message, "sss", &unit, &path, &ssss);
	if (r < 0) {
		fprintf(stderr, "Failed to parse NameOwnerChanged signal: %s\n", strerror(-r));
		return 0;
	}

	printf("match_name_owner_changed: unit: %s, path: %s\n", unit, path);

	return 0;
}*/

int match_signal_test(sd_bus_message *message, void *userdata, sd_bus_error *ret_error) {
	bool test_bool=0;
	int16_t test_int16=0;
	uint16_t test_uint16=0;
	int32_t test_int32=0;
	uint32_t test_uint32=0;
	int64_t test_int64=0;
	uint64_t test_uint64=0;
	char *test_string="";
	int r;

	//printf("Hello, match_signal_test\n");

	r = sd_bus_message_read(message, "bnqiuxts", 
		&test_bool, &test_int16, &test_uint16, &test_int32, &test_uint32, &test_int64, &test_uint64,
		&test_string);
	if (r < 0) {
		fprintf(stderr, "Failed to parse signal: %s\n", strerror(-r));
		return 0;
	}

	printf("Received a signal from demoB:\n");
	printf("test_bool %d, test_int16 %d, test_uint16 %d,\n", 
			test_bool, test_int16, test_uint16);
	printf("test_int32 %" PRId32 ", test_uint32 %" PRIu32 ", test_int64 %" PRId64 ", test_uint64 %" PRIu64 ",\n", 
			test_int32, test_uint32, test_int64, test_uint64);
	printf("test_string %s\n\n", test_string);

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
	SD_BUS_METHOD("Multiply", "xx", "x", method_multiply, SD_BUS_VTABLE_UNPRIVILEGED),
	SD_BUS_METHOD("Hello", "s", "s", method_hello, SD_BUS_VTABLE_UNPRIVILEGED),
	SD_BUS_METHOD("HelloNoReply", "s", "", method_hello_no_reply, SD_BUS_VTABLE_UNPRIVILEGED),

	SD_BUS_SIGNAL("SignalTestA", "x", 0),
	SD_BUS_VTABLE_END
};
