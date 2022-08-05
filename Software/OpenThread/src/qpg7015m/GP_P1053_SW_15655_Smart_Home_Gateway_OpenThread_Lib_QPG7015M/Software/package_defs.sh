TOOLCHAIN_RPI="${TOOLCHAIN_RPI-/mnt/c/gpHub/TOOL_RPi/vlatest/bin/arm-linux-gnueabihf}"
BUNDLE_NAME=OpenThread_Lib_QPG7015M

PACKAGE_ARCHIVES=( \
"OpenThread_Lib_QPG7015M_196357_v1.5.1.0.tgz" \
)
PACKAGE_ARTIFACTS=( \
"OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi_cli_mtd_socket/libQorvoQPG7015M_rpi_cli_mtd_socket.a" \
"OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi_cli_ftd_socket/libQorvoQPG7015M_rpi_cli_ftd_socket.a" \
"OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi_rcp_socket/libQorvoQPG7015M_rpi_rcp_socket.a" \
)
MAKE_TARGETS=( \
"Makefile.QorvoQPG7015M_rpi_cli_mtd_socket applib TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.QorvoQPG7015M_rpi_cli_ftd_socket applib TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.QorvoQPG7015M_rpi_rcp_socket applib TOOLCHAIN=${TOOLCHAIN_RPI}" \
)
CLEAN_TARGETS=( \
"Makefile.QorvoQPG7015M_rpi_cli_mtd_socket clean TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.QorvoQPG7015M_rpi_cli_ftd_socket clean TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.QorvoQPG7015M_rpi_rcp_socket clean TOOLCHAIN=${TOOLCHAIN_RPI}" \
)
BUILD_DEPENDENCIES=( \
)
COPY_DEPENDENCIES=( \
)
