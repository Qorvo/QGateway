BUNDLE_NAME=OpenThread_Lib_QPG7015M
TOOLCHAIN_RPI="${TOOLCHAIN_RPI-/mnt/c/gpHub/TOOL_RPi/vlatest/bin/arm-gcc-4.7.1}"

PACKAGE_ARCHIVES=( \
"OpenThread_Lib_QPG7015M_193072_v1.5.0.2.tgz" \
)
PACKAGE_ARTIFACTS=( \
"OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi_cli_mtd_socket/libQorvoQPG7015M_rpi_cli_mtd_socket.a" \
"OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi_cli_ftd_socket/libQorvoQPG7015M_rpi_cli_ftd_socket.a" \
"OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi/libQorvoQPG7015M_rpi.a" \
"OpenThread_Lib_QPG7015M/Work/OpenThreadQorvoGlue_qpg7015m_mtd/libOpenThreadQorvoGlue_qpg7015m_mtd.a" \
"OpenThread_Lib_QPG7015M/Work/OpenThreadQorvoGlue_qpg7015m_ftd/libOpenThreadQorvoGlue_qpg7015m_ftd.a" \
)
MAKE_TARGETS=( \
"Makefile.QorvoQPG7015M_rpi_cli_mtd_socket applib TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.QorvoQPG7015M_rpi_cli_ftd_socket applib TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.QorvoQPG7015M_rpi applib TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.OpenThreadQorvoGlue_qpg7015m_mtd applib TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.OpenThreadQorvoGlue_qpg7015m_ftd applib TOOLCHAIN=${TOOLCHAIN_RPI}" \
)
CLEAN_TARGETS=( \
"Makefile.QorvoQPG7015M_rpi_cli_mtd_socket clean TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.QorvoQPG7015M_rpi_cli_ftd_socket clean TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.QorvoQPG7015M_rpi clean TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.OpenThreadQorvoGlue_qpg7015m_mtd clean TOOLCHAIN=${TOOLCHAIN_RPI}" \
"Makefile.OpenThreadQorvoGlue_qpg7015m_ftd clean TOOLCHAIN=${TOOLCHAIN_RPI}" \
)
BUILD_DEPENDENCIES=( \
)
COPY_DEPENDENCIES=( \
)
