# NINA GUI App #

Nina GUI for the Raspberry Pi (64-bit), using QT5.

### Building the Nina GUI app ###

To clone the Nina GUI app the --recurse-submodules flag must be used:

$ git clone --recurse-submodules https://github.com/Melbourne-Instruments/nina_gui.git

The Nina GUI app uses QMake as its build system, which creates the makefile from the 
synthia_gui.pro file. To create the makefile:
$ qmake

Once created, make is used to build the Nina GUI app:
$ make

To cross compile for the Raspberry Pi, the Melbourne Instruments SDK *must* be used (it can be downloaded from Sharepoint).
It is recommended to install the SDK in the /opt folder on your Ubuntu PC.
Once this has been done, source the environment script to set-up the build environment, for example:

$ source /opt/elk/0.1.0/environment-setup-cortexa72-elk-linux

### Dependancies ###

  * QT5

---
Copyright 2021-2023 Melbourne Instruments, Australia.
