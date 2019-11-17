DIR=.
BUILD=${DIR}/build
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CC=gcc
	CXX=g++
	CFLAGS=-w
	LIB_CFLGAS=-fPIC -shared
	LIB_EXT=so
	LIBINTER_SRC=libInter_linux.cpp
	LIBINTER_RAND_SRC=
	DL_LIBS_FLAG=-ldl
endif
ifeq ($(UNAME_S),Darwin)
	CC=clang
	CXX=clang++
	# BASE_SDK=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk
	# CFLAGS=-isysroot ${BASE_SDK} -miphoneos-version-min=9.0 -arch armv7 -arch arm64
	LIB_CFLGAS=-dynamiclib
	LIB_EXT=dylib
	LIBINTER_SRC=libInter_darwin.cpp
	LIBINTER_RAND_SRC=libInter_rand_darwin.c
	DL_LIBS_FLAG=
endif

all: clean setup libA client libInter

all_rand: clean setup client_rand libInter_rand

libA: libA.h libA.cpp
	${CXX} ${CFLAGS} ${LIB_CFLGAS} libA.cpp -o ${BUILD}/libA.${LIB_EXT}

client: client.cpp
	${CXX} ${CFLAGS} client.cpp ${BUILD}/libA.${LIB_EXT} -o ${BUILD}/client

libInter: ${LIBINTER_SRC}
	${CXX} ${CFLAGS} ${LIB_CFLGAS} ${BUILD}/libA.${LIB_EXT} ${LIBINTER_SRC} \
					-o ${BUILD}/libInter.${LIB_EXT} \
					${DL_LIBS_FLAG}

client_rand: client_rand.c
	${CC} ${CFLAGS} client_rand.c -o ${BUILD}/client_rand

libInter_rand: ${LIBINTER_RAND_SRC}
	${CC} ${CFLAGS} ${LIB_CFLGAS} ${LIBINTER_RAND_SRC} \
					-o ${BUILD}/libInter_rand.${LIB_EXT} \
					${DL_LIBS_FLAG}

.PHONY: clean setup
clean:
	rm -rf ${BUILD}

setup:
	mkdir -p ${BUILD}
