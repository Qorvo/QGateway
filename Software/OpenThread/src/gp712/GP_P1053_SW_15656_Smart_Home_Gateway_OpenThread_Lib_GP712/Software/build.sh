#!/bin/bash
set -x
# Script settings
source package_defs.sh

if grep -qE "(Microsoft|WSL)" /proc/sys/kernel/osrelease ; then
    BUILD_OS='OS_USED=WSL'
fi

# Print log
log ()
{
    echo "$1"
}

# Fail with message
failed()
{
    log "[BUILD FAILED] $1";
    exit 255
}

print_info()
{
    log "${BUNDLE_NAME}"
}

preconditions()
{
    pushd . || failed
    COUNTER=0

    test -f Module.symvers && rm Module.symvers
    for DEPENDENCY_LINK in "${BUILD_DEPENDENCIES[@]}"; do
        # LKM build Workaround: with 5.10.17, MODPOST fails unless Kbuild or Makefile
        # exist and point to the Makefile.xxx 
        DEPENDENCY_KEY="${DEPENDENCY_LINK%%|*}"
        if [ "${DEPENDENCY_KEY}" != "$1" ]
        then
            continue
        fi
        DEPENDENCY="${DEPENDENCY_LINK#*|}"
        # word splitting with cp destination in variable (SC2086,SC2225 are required)
        # shellcheck disable=SC2086,SC2225
        test -f Kbuild && rm Kbuild
        # shellcheck disable=SC2086
        ln -s ${DEPENDENCY%% *} Kbuild
        # shellcheck disable=SC2086
        make -j4 -f ${DEPENDENCY} ${BUILD_OS}|| failed "Unable to do make ${DEPENDENCY}"
        if [ -f Module.symvers ]
        then
            mv Module.symvers Module.symvers.$COUNTER
            let COUNTER++
        fi
    done
#    cat Module.symvers.* |sort -k 1 |tee Module.symvers

    popd || failed

}

make_unpack()
{
    pushd . || failed
    for ARCHIVE in "${PACKAGE_ARCHIVES[@]}"; do
        ARCHIVE_NAME=$(basename -- "${ARCHIVE}")
        ARCHIVE_DIR=$(dirname -- "${ARCHIVE}")
        UNPACKED_ARCHIVE="${ARCHIVE_NAME%_*_*}"
        cd "${ARCHIVE_DIR}" || failed
        if [ -d "${UNPACKED_ARCHIVE}" ] ; then
            log "${UNPACKED_ARCHIVE} already available, extracting ${ARCHIVE_NAME} skipped"
        else
            tar -xzvf "${ARCHIVE_NAME}" || failed "Unable to extract tar"
        fi
        
        cd - || failed
    done
    popd || failed
}

make_target()
{
    pushd . || failed
    cd "${BUNDLE_NAME}/" || failed
    for TARGET in "${MAKE_TARGETS[@]}"; do
        for COPY_DEPENDENCY in "${COPY_DEPENDENCIES[@]}"; do
            if [[ "${TARGET%% *}" == Makefile."${COPY_DEPENDENCY%%|*}" ]]; then
                # word splitting with cp destination in variable (SC2086,SC2225 are required)
                # shellcheck disable=SC2086,SC2225
                cp -v ${COPY_DEPENDENCY##*|} || failed
            fi
        done
        # LKM build Workaround: with 5.10.17, MODPOST fails unless Kbuild or Makefile
        # exist and point to the Makefile.xxx 
        preconditions "${TARGET%% *}"
        # word splitting (SC2086 is required)
        test -f Kbuild && rm Kbuild
        # shellcheck disable=SC2086
        ln -s ${TARGET%% *} Kbuild
        # shellcheck disable=SC2086
        make -f ${TARGET} ${BUILD_OS}|| failed "Unable to do make ${TARGET}"
    done
    popd || failed
}

check_artifacts()
{
    pushd . || failed
    for ARTIFACT in "${PACKAGE_ARTIFACTS[@]}"; do
        if [ ! -f "${ARTIFACT}" ]; then
            failed "Artifact not found: ${ARTIFACT}"
        fi
    done
    popd || failed
}

make_clean()
{
    pushd . || failed
    cd "${BUNDLE_NAME}/" || failed
    for TARGET in "${CLEAN_TARGETS[@]}"; do
        # word splitting (SC2086 is required)
        # shellcheck disable=SC2086
        make -f ${TARGET} ${BUILD_OS}|| failed "Unable to do make ${TARGET}"
    done
    popd || failed
}

print_info && make_unpack
[[ $1 == "clean" ]] && make_clean
make_target && check_artifacts

