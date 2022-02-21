#!/bin/bash
set -ex

OTDIR="$(dirname "$0")"

BUILD_QPG7015M=1
QPG7015M_LIB_PACKAGE="${OTDIR}/src/qpg7015m/GP_P1053_SW_15655_Smart_Home_Gateway_OpenThread_Lib_QPG7015M"
QPG7015M_LIB_SOURCE="${QPG7015M_LIB_PACKAGE}/Software/OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi_cli_ftd_socket/libQorvoQPG7015M_rpi_cli_ftd_socket.a"
QPG7015M_LIB_TARGET="${OTDIR}/library/qpg7015m/lib/libQorvoQPG7015M_ftd.a"

BUILD_GP712=1
GP712_LIB_PACKAGE="${OTDIR}/src/gp712/GP_P1053_SW_15656_Smart_Home_Gateway_OpenThread_Lib_GP712"
GP712_LIB_SOURCE="${GP712_LIB_PACKAGE}/Software/OpenThread_Lib_GP712/Work/QorvoGP712_rpi_cli_ftd_socket/libQorvoGP712_rpi_cli_ftd_socket.a"
GP712_LIB_TARGET="${OTDIR}/library/gp712/lib/libQorvoGP712_ftd.a"

TOOLCHAIN_RPI="$(realpath ../../ThirdParty/tool_rpi/arm-bcm2708/arm-linux-gnueabihf)"
export TOOLCHAIN_RPI
export TOOLCHAIN="${TOOLCHAIN_RPI}"
export CROSS_COMPILE="arm-linux-gnueabihf-"
export SYSTEMROOT="${TOOLCHAIN}/arm-linux-gnueabihf/sysroot"
export PATH=$PATH:"${TOOLCHAIN}/bin"

usage()
{
    echo "Options:"
    echo "-h This menu"
    echo "-5 only build for QPG7015M platform"
    echo "-G only build for GP712 platorm"
}

platform_build()
{
QORVO_PLATFORM=$1
LIB_PACKAGE=$2
LIB_SOURCE=$3
LIB_TARGET=$4

mkdir -p "$(dirname "${LIB_TARGET}")"

cd "${LIB_PACKAGE}"/Software
./build.sh
cd -
rm -f "${LIB_TARGET}"
cp "${LIB_SOURCE}" "${LIB_TARGET}"
"${OTDIR}"/script/build "${QORVO_PLATFORM}" -DOT_MTD=0 -DOT_COMMISSIONER=1 -DOT_JOINER=1 -DOT_DHCP6_CLIENT=1 -DOT_DHCP6_SERVER=1 
}


while getopts "h5G" OPTION ; do
    case $OPTION in
        h)
            usage
            exit 0
            ;;
        5)
            BUILD_GP712=0
            BUILD_QPG7015M=1
            ;;
        G)
            BUILD_GP712=1
            BUILD_QPG7015M=0
            ;;
        *)
            usage
            exit 1
            ;;
    esac
done

if [ "${BUILD_QPG7015M}" = 1 ] ; then
    platform_build "qpg7015m" "${QPG7015M_LIB_PACKAGE}" "${QPG7015M_LIB_SOURCE}" "${QPG7015M_LIB_TARGET}"
fi
if [ "${BUILD_GP712}" = 1 ] ; then
    platform_build "gp712" "${GP712_LIB_PACKAGE}" "${GP712_LIB_SOURCE}" "${GP712_LIB_TARGET}"
fi

unset TOOLCHAIN
unset TOOLCHAIN_RPI
unset CROSS_COMPILE
unset SYSTEMROOT
