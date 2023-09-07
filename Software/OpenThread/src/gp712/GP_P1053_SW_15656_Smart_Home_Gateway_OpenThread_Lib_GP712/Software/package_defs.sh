BUNDLE_NAME=OpenThread_Lib_GP712
TOOLCHAIN_RPI="${TOOLCHAIN_RPI-/mnt/c/gpHub/TOOL_RPi/vlatest/bin/arm-linux-gnueabihf}"

PACKAGE_ARCHIVES=( \
"OpenThread_Lib_GP712_2334f_v1.5.2.0.tgz" \
)
PACKAGE_ARTIFACTS=( \
"OpenThread_Lib_GP712/Work/QorvoGP712_rpi_cli_mtd_socket/libQorvoGP712_rpi_cli_mtd_socket.a" \
"OpenThread_Lib_GP712/Work/QorvoGP712_rpi_cli_ftd_socket/libQorvoGP712_rpi_cli_ftd_socket.a" \
"OpenThread_Lib_GP712/Work/QorvoGP712_rpi_rcp_socket/libQorvoGP712_rpi_rcp_socket.a" \
)
MAKE_TARGETS=( \
"Makefile.QorvoGP712_rpi_cli_mtd_socket applib TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.QorvoGP712_rpi_cli_ftd_socket applib TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.QorvoGP712_rpi_rcp_socket applib TOOLCHAIN=${TOOLCHAIN_RPI}" \
)
CLEAN_TARGETS=( \
"Makefile.QorvoGP712_rpi_cli_mtd_socket clean TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.QorvoGP712_rpi_cli_ftd_socket clean TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.QorvoGP712_rpi_rcp_socket clean TOOLCHAIN=${TOOLCHAIN_RPI}" \
)
BUILD_DEPENDENCIES=( \
)
COPY_DEPENDENCIES=( \
)
