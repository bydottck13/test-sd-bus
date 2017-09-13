.PHONY: all clean service-a service-b

CC=gcc
TARGETA=serviced-a
SERVICEA=serviced-a.c serviced-a-bus.c

TARGETB=serviced-b
SERVICEB=serviced-b.c serviced-b-bus.c

CFLAGS=-Wall
LIBRARYA=
LIBRARYB=-lpthread

all: clean service-a service-b

service-a:
	$(CC) -o $(TARGETA) $(SERVICEA) $(shell pkg-config --cflags --libs libsystemd) $(CFLAGS) $(LIBRARYA)

service-b:
	$(CC) -o $(TARGETB) $(SERVICEB) $(shell pkg-config --cflags --libs libsystemd) $(CFLAGS) $(LIBRARYB)

clean:
	rm -rf $(TARGETA) $(TARGETB)