#!/bin/sh

C_COMPILER=$(which clang)
# C_COMPILER=$(which cc)
EXECUTABLE="my_program"
BUILD_FOLDER="temp_build"
NO_CACHE=true
RELEASE_BUILD=true
EXTRA_COMPILE_FLAGS="-I/usr/local/include"
EXTRA_LINK_FLAGS="-I/usr/local/lib"

#
# Compile `cbuild.c` and then use it to compile the project
#
${C_COMPILER} -o cbuild -g cbuild.c \
    && \
    ENABLE_SANITIZER=true \
    C_COMPILER=${C_COMPILER} \
    EXTRA_COMPILE_FLAGS=${EXTRA_COMPILE_FLAGS} \
    EXTRA_LINK_FLAGS=${EXTRA_LINK_FLAGS} \
    BUILD_FOLDER=${BUILD_FOLDER} \
    NO_CACHE=${NO_CACHE} \
    RELEASE_BUILD=${RELEASE_BUILD} \
    EXECUTABLE=${EXECUTABLE} \
    ./cbuild \
    && \
    ${BUILD_FOLDER}/${EXECUTABLE}
