# ***** NOTICE *****
This is a D-BUS sample by using sd-bus includes testing emiting signals and call methods with D-BUS architecture.
	
	
## DESCRIPTIONS
There are other d-bus packages, like glib. However, accourding to IBM testing, ad-bus is the fastest, so the IPC of cybernut would dependend mainly on sd-bus. For more information concerning performance, see [here](http://blog.asleson.org/index.php/2015/09/01/d-bus-signaling-performance/) for reference.
	
	
## REQUIREMENTS:
Testing OS: ubuntu-16.04.2-desktop-amd64
```	
$ sudo apt-get install libsystemd-dev
```

## BUILD CODE:
```
$ make all	
$ ./serviced-a	
```
Open a new terminal
```
$ ./serviced-b
```	

## MISCELLANEOUS:
Some useful tools for debugging:
 * `D-Feet` - install from Ubuntu Software
 * `busctl` - e.g. busctl --user tree INTERFACE_NAME
 * `dbus-monitor` - execute from CLI
