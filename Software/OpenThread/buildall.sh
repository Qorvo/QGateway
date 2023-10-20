#!/bin/bash
set -e

failed()
{
    log "[BUILD FAILED] $1";
    exit 255
}

# Architecture check
if [ "x86_64" != "$(uname -m)" ] ; then
    failed "Architecture check failed! ThirdParty/tool_rpi contains only x86_64 cross compilers!"
fi

OTDIR="$(dirname "$0")"
PATHCHES="$(realpath ${OTDIR}/../patches)"

QPG7015M_LIB_PACKAGE="${OTDIR}/src/qpg7015m/GP_P1053_SW_15655_Smart_Home_Gateway_OpenThread_Lib_QPG7015M"
QPG7015M_LIB_SOURCE="${QPG7015M_LIB_PACKAGE}/Software/OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi_cli_ftd_socket/libQorvoQPG7015M_rpi_cli_ftd_socket.a"
QPG7015M_LIB_TARGET="${OTDIR}/library/qpg7015m/lib/libQorvoQPG7015M_ftd.a"
QPG7015M_LIB_RCP_SOURCE="${QPG7015M_LIB_PACKAGE}/Software/OpenThread_Lib_QPG7015M/Work/QorvoQPG7015M_rpi_rcp_socket/libQorvoQPG7015M_rpi_rcp_socket.a"
QPG7015M_LIB_RCP_TARGET="${OTDIR}/library/qpg7015m/lib/libQorvoQPG7015M_rcp.a"

GP712_LIB_PACKAGE="${OTDIR}/src/gp712/GP_P1053_SW_15656_Smart_Home_Gateway_OpenThread_Lib_GP712"
GP712_LIB_SOURCE="${GP712_LIB_PACKAGE}/Software/OpenThread_Lib_GP712/Work/QorvoGP712_rpi_cli_ftd_socket/libQorvoGP712_rpi_cli_ftd_socket.a"
GP712_LIB_TARGET="${OTDIR}/library/gp712/lib/libQorvoGP712_ftd.a"
GP712_LIB_RCP_SOURCE="${GP712_LIB_PACKAGE}/Software/OpenThread_Lib_GP712/Work/QorvoGP712_rpi_rcp_socket/libQorvoGP712_rpi_rcp_socket.a"
GP712_LIB_RCP_TARGET="${OTDIR}/library/gp712/lib/libQorvoGP712_rcp.a"

THIRDPARTY="$(realpath ../../ThirdParty)"
TOOLCHAIN_RPI="${THIRDPARTY}/tool_rpi/arm-bcm2708/arm-linux-gnueabihf"
export TOOLCHAIN_RPI
export TOOLCHAIN="${TOOLCHAIN_RPI}"
export CROSS_COMPILE="arm-linux-gnueabihf-"
export SYSTEMROOT="${TOOLCHAIN}/arm-linux-gnueabihf/sysroot"
export PATH=$PATH:"${TOOLCHAIN}/bin"

cherry()
{
    dir=`pwd`
    REPO="$1"
    PATCH="$2"

    cd ${REPO}
    git fetch origin main
    git cherry-pick --no-commit ${PATCH}
    cd ${dir}
}

platform_build()
{
    QORVO_PLATFORM=$1
    LIB_PACKAGE=$2
    LIB_SOURCE=$3
    LIB_TARGET=$4
    LIB_TYPE=$5

    mkdir -p "$(dirname "${LIB_TARGET}")"

    cd "${LIB_PACKAGE}"/Software
    ./build.sh
    cd -
    rm -f "${LIB_TARGET}"
    cp "${LIB_SOURCE}" "${LIB_TARGET}"
    if [ "${LIB_TYPE}" = "rcp" ] ; then
        "${OTDIR}"/script/build "${QORVO_PLATFORM}" -DOT_APP_RCP=1 -DOT_RCP=1 -DOT_COMMISSIONER=1 -DOT_JOINER=1 -DOT_DHCP6_CLIENT=1 -DOT_DHCP6_SERVER=1
    elif [ "${LIB_TYPE}" = "ftd" ] ; then
        "${OTDIR}"/script/build "${QORVO_PLATFORM}" -DOT_APP_CLI=1 -DOT_FTD=1 -DOT_COMMISSIONER=1 -DOT_JOINER=1 -DOT_DHCP6_CLIENT=1 -DOT_DHCP6_SERVER=1
    fi
}

# Define default values
PLATFORM=""
TYPE=""
BUILD_GP712=1
BUILD_QPG7015M=1
BUILD_CLI=1
BUILD_RCP=1

# Function to display usage
usage() {
    echo "Usage: $0 [options]"
    echo "Options:"
    echo "  --help                  Show this help message and exit"
    echo "  --platform <platform>   Specify the platform to build for: gp712, qpg7015m (default: both)"
    echo "  --type <type>           Specify the build type: cli, rcp (default: both)"
}

# Process command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --help)
            usage
            exit 0
            ;;
        --platform)
            shift
            PLATFORM="$1"
            shift
            ;;
        --type)
            shift
            TYPE="$1"
            shift
            ;;
        *)
            usage
            exit 1
            ;;
    esac
done

# Validate and set platform
case "$PLATFORM" in
    gp712)
        BUILD_GP712=1
        BUILD_QPG7015M=0
        ;;
    qpg7015m)
        BUILD_GP712=0
        BUILD_QPG7015M=1
        ;;
    "")
        # No platform specified, building for both platforms
        BUILD_GP712=1
        BUILD_QPG7015M=1
        ;;
    *)
        echo "Invalid platform: $PLATFORM."
        usage
        exit 1
        ;;
esac

# Validate and set build type
case "$TYPE" in
    cli)
        BUILD_CLI=1
        BUILD_RCP=0
        ;;
    rcp)
        BUILD_CLI=0
        BUILD_RCP=1
        ;;
    "")
        # No build type specified, building for both types
        BUILD_CLI=1
        BUILD_RCP=1
        ;;
    *)
        echo "Invalid build type: $TYPE."
        usage
        exit 1
        ;;
esac


FIX_TG_CM01=3d5cb364f22f0881d5eb528aea01b8db40cc6dd2
cherry ${THIRDPARTY}/openthread ${FIX_TG_CM01}

if [ "${BUILD_QPG7015M}" = 1 ] ; then
    if [ "${BUILD_CLI}" = 1 ] ; then
        platform_build "qpg7015m" "${QPG7015M_LIB_PACKAGE}" "${QPG7015M_LIB_SOURCE}" "${QPG7015M_LIB_TARGET}" "ftd"
    fi
    if [ "${BUILD_RCP}" = 1 ] ; then
        platform_build "qpg7015m" "${QPG7015M_LIB_PACKAGE}" "${QPG7015M_LIB_RCP_SOURCE}" "${QPG7015M_LIB_RCP_TARGET}" "rcp"
    fi
fi
if [ "${BUILD_GP712}" = 1 ] ; then
    if [ "${BUILD_CLI}" = 1 ] ; then
        platform_build "gp712" "${GP712_LIB_PACKAGE}" "${GP712_LIB_SOURCE}" "${GP712_LIB_TARGET}" "ftd"
    fi
    if [ "${BUILD_RCP}" = 1 ] ; then
        platform_build "gp712" "${GP712_LIB_PACKAGE}" "${GP712_LIB_RCP_SOURCE}" "${GP712_LIB_RCP_TARGET}" "rcp"
    fi
fi

unset TOOLCHAIN
unset TOOLCHAIN_RPI
unset CROSS_COMPILE
unset SYSTEMROOT
