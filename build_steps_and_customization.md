# Buil Steps and customization

This document describes the steps used by the [buildall.sh script](Software/OpenThread/buildall.sh) to build OpenThread _CLI_ and _RCP_ for the Raspberry Pi, it also includes instructions on building for custom platforms. Please refer to the [README.md](README.md) for more information about the architecture.

> **NOTE** this guide will only refer to GPG1715M for simplicity, but the steps are the same for GP712.

---

- [Buil Steps and customization](#buil-steps-and-customization)
    - [Build steps](#build-steps)
        - [Building libQorvo](#building-libqorvo)
        - [Building RCP and CLI](#building-rcp-and-cli)
            - [Prepare the environment](#prepare-the-environment)
            - [Build CLI](#build-cli)
            - [Build RCP](#build-rcp)
    - [Building libQorvo for Custom Platform](#building-libqorvo-for-custom-platform)
        - [Customizing Compiler Settings](#customizing-compiler-settings)
---

## Build steps

### Building libQorvo

The sources and makefiles to build `libQorvo` are available under [Software/OpenThread/src/qpg7015m/GP_P1053_SW_15655_Smart_Home_Gateway_OpenThread_Lib_QPG7015M](Software/OpenThread/src/qpg7015m/GP_P1053_SW_15655_Smart_Home_Gateway_OpenThread_Lib_QPG7015M) and can be built as:

```shell
cd Software/OpenThread/src/qpg7015m/GP_P1053_SW_15655_Smart_Home_Gateway_OpenThread_Lib_QPG7015M/Software
./build.sh
```

If everything is configured correctly, the build script will generate library files at (paths are relative to `build.sh` location):

- `OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi_cli_ftd_socket/libQorvoQPG7015M_rpi_cli_ftd_socket.a`
- `OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi_cli_mtd_socket/libQorvoQPG7015M_rpi_cli_mtd_socket.a`
- `OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi_rcp_socket/libQorvoQPG7015M_rpi_rcp_socket.a`

The compiler for `build.sh` and underlying makefiles can be configured by setting system environment variables.

Here is an example from [buildall.sh script](Software/OpenThread/buildall.sh) and more details can be found in [Customizing Compiler Settings](#customizing-compiler-settings).

```shell
export TOOLCHAIN_RPI="<path-to-QGateway>/ThirdParty/tool_rpi/arm-bcm2708/arm-linux-gnueabihf)"
export TOOLCHAIN="${TOOLCHAIN_RPI}"
export CROSS_COMPILE="arm-linux-gnueabihf-"
export SYSTEMROOT="${TOOLCHAIN}/arm-linux-gnueabihf/sysroot"
```

When the compiler is configured, the libraries can be also built by running the makefiles that are included in the libQorvo source package:

`GP_P1053_SW_15655_Smart_Home_Gateway_OpenThread_Lib_QPG7015M/Software/OpenThread_Lib_QPG7015M`

```shell
make –f Makefile.QorvoQPG7015M_rpi_cli_ftd_socket
make –f Makefile.QorvoQPG7015M_rpi_cli_mtd_socket
make –f Makefile.QorvoQPG7015M_rpi_rcp_socket
```

**Note:** Both _Full Thread Device_ and _Minimal Thread Device_ libraries are provided, although FTD is a more likely scenario in a gateway context (the one used in `buildall.sh`). the difference is that FTD library supports Commissioner role while MTD library does not.

### Building RCP and CLI

#### Prepare the environment

Add the compiler to `$PATH`

```shell
export PATH=<path-to-QGateway>/ThirdParty/tool_rpi/arm-bcm2708/arm-linux-gnueabihf/bin/:$PATH
```

Prepare folder structure

```shell
cd Software/OpenThread
mkdir -p library/qpg7015m/lib
```

OpenThread provides a series of configuration switches to enable additional functionality in the build. For a list of the regular and the advanced features we refer you to [common-switches.mk](https://github.com/openthread/openthread/tree/master/examples/common-switches.mk) and the enhanced feature menu on the [build instructions landing page](https://openthread.io/guides/build), respectively.

#### Build CLI

Copy the library generated in the [Building libQorvo](#building-libqorvo) step to `Software/OpenThread/library/qpg7015m/lib/libQorvoQPG7015M_ftd.a`

```shell
rm -f ./library/qpg7015m/lib/libQorvoQPG7015M_ftd.a
cp ./src/qpg7015m/GP_P1053_SW_15655_Smart_Home_Gateway_OpenThread_Lib_QPG7015M/Software/OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi_cli_ftd_socket/libQorvoQPG7015M_rpi_cli_ftd_socket.a ./library/qpg7015m/lib/libQorvoQPG7015M_ftd.a
```

The basic build command for the QPG7015M is:

```shell
./script/build qpg7015m
```
This will build the CLI application for *Full Thread Device*. The output will be the following `.elf` file located in `Software/OpenThread/build/bin`

- `qpg7015m-ot-cli-ftd.elf`

Note that the Raspberry Pi binaries available in the QPG7015M DK have both commissioner and joiner functionality built-in since they are built with:

```shell
./script/build qpg7015m -DOT_APP_CLI=1 -DOT_FTD=1 -DOT_COMMISSIONER=1 -DOT_JOINER=1 -DOT_DHCP6_CLIENT=1 -DOT_DHCP6_SERVER=1
```

#### Build RCP

Copy library generated in [Building libQorvo](#building-libqorvo) step to `Software/OpenThread/library/qpg7015m/lib/libQorvoQPG7015M_rcp.a`

```shell
rm -f ./library/qpg7015m/lib/libQorvoQPG7015M_rcp.a
cp ./src/qpg7015m/GP_P1053_SW_15655_Smart_Home_Gateway_OpenThread_Lib_QPG7015M/Software/OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi_cli_ftd_socket/libQorvoQPG7015M_rpi_cli_rcp_socket.a ./library/qpg7015m/lib/libQorvoQPG7015M_rcp.a
```

```shell
./script/build qpg7015m -DOT_APP_RCP=1 -DOT_RCP=1 -DOT_COMMISSIONER=1 -DOT_JOINER=1 -DOT_DHCP6_CLIENT=1 -DOT_DHCP6_SERVER=1
```

This will build the CLI application for *RCP*. The output will be the following `.elf` file located in `Software/OpenThread/build/bin`

- `qpg7015m-ot-cli-rcp.elf`


### Building libQorvo for Custom Platform

The OpenThread implementation provides network stack source and platform-independent APIs to build applications on top of it. Device-specific code is separated from platform libraries such as libQorvo. The Qorvo OpenThread package provides the following components:

- libQorvo sources for building on the target platform including needed components
- Makefile with buildflags
- Toolchain defines for make

#### Customizing Compiler Settings

Toolchain path and settings can be configured by editing Makefiles in `Software/OpenThread/src/qpg7015m/GP_P1053_SW_15655_Smart_Home_Gateway_OpenThread_Lib_QPG7015M/Software/OpenThread_Lib_QPG7015M` directory. Target compiler can be selected by editing `COMPILER` variable in Makefile, i.e. `COMPILER:=rpi_bcm2708` will use `Software/OpenThread/src/qpg7015m/GP_P1053_SW_15655_Smart_Home_Gateway_OpenThread_Lib_QPG7015M/Software/OpenThread_Lib_QPG7015M/make/compilers/rpi_bcm2708/compiler_defines.mk`

Basic `compiler_defines.mk` toolchain
configuration includes:

Path to toolchain root:

```shell
TOOLCHAIN ?=$(ROOTDIR)/gpHub/TOOL_RPi/bin/arm-gcc-4.7.1
```

Architecture name:

```shell
ARCH ?=arm
```

Toolchain prefix:

```shell
CROSS_COMPILE ?=$(ARCH)-bcm2708hardfp-linux-gnueabi-
```

System root definition:

```shell
SYSTEMROOT ?=$(TOOLCHAIN)/arm-bcm2708hardfp-linux-gnueabi/sysroot
```

Default compiler flags:

```shell
FLAGS_COMPILER += -Os
FLAGS_COMPILER += -march=armv6j
FLAGS_COMPILER += -Wall
```

C compiler flags:

```shell
CFLAGS_COMPILER += $(FLAGS_COMPILER_FILTERED)
```

C++ compiler flags:

```shell
CXXFLAGS_COMPILER += $(FLAGS_COMPILER_FILTERED)
CXXFLAGS_COMPILER +=-Wno-reorder
```

Assembler flags:

```shell
ASFLAGS_COMPILER+=
```

Linker options:

```shell
LDFLAGS_COMPILER+=--sysroot=$(SYSTEMROOT)
```

Library options:

```shell
LIBFLAGS_COMPILER+=
```