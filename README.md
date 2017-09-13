A D-BUS sample by using sd-bus
	This includes testing emiting signals and call methods with D-BUS architecture.
	
DESCRIPTIONS:
	There are other d-bus packages, like glib. However, accourding to IBM testing, ad-bus is the fastest, so the IPC of PegaBot would dependend mainly on sd-bus. For more information concerning performance, see http://blog.asleson.org/index.php/2015/09/01/d-bus-signaling-performance/ for reference.
	
REQUIREMENTS:
	Testing OS: ubuntu-16.04.2-desktop-amd64
	# sudo apt-get install libsystemd-dev
	
BUILD CODE:
	# make all
	# ./serviced-a
	Open a new terminal
	# ./serviced-b
	
MISCELLANEOUS:
	Some useful tools for debugging:
	1. D-Feet: install from Ubuntu Software
	2. busctl e.g. busctl --user tree INTERFACE_NAME
	3. dbus-monitor
