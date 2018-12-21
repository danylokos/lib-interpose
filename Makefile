DIR=.
BUILD=${DIR}/build
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CC=g++
	CFLAGS=-w
	LIB_CFLGAS=-fPIC -shared
	LIB_EXT=so
	LIBINTER_SRC=libInter_linux.cpp
	DL_LIBS_FLAG=-ldl
endif
ifeq ($(UNAME_S),Darwin)
	CC=clang++
	# BASE_SDK=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk
	# CFLAGS=-isysroot ${BASE_SDK} -miphoneos-version-min=9.0 -arch armv7 -arch arm64
	LIB_CFLGAS=-dynamiclib
	LIB_EXT=dylib
	LIBINTER_SRC=libInter_darwin.cpp
	DL_LIBS_FLAG=
endif

all: clean setup libA client libInter

libA: libA.h libA.cpp
	${CC} ${CFLAGS} ${LIB_CFLGAS} libA.cpp -o ${BUILD}/libA.${LIB_EXT}

client: client.cpp
	${CC} ${CFLAGS} client.cpp ${BUILD}/libA.${LIB_EXT} -o ${BUILD}/client

libInter: ${LIBINTER_SRC}
	${CC} ${CFLAGS} ${LIB_CFLGAS} ${BUILD}/libA.${LIB_EXT} ${LIBINTER_SRC} \
					-o ${BUILD}/libInter.${LIB_EXT} \
					${DL_LIBS_FLAG}

.PHONY: clean setup
clean:
	rm -rf ${BUILD}

setup:
	mkdir -p ${BUILD}
