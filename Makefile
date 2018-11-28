DIR=.
BUILD=${DIR}/build
CC=clang++

all: clean setup libA client libInter

libA: libA.h libA.cpp
	${CC} ${CFLAGS} -dynamiclib libA.cpp -o ${BUILD}/libA.dylib

client: client.cpp
	${CC} ${CFLAGS} client.cpp ${BUILD}/libA.dylib -o ${BUILD}/client

libInter: libInter.cpp
	${CC} ${CFLAGS} -dynamiclib ${BUILD}/libA.dylib libInter.cpp -o ${BUILD}/libInter.dylib

.PHONY: clean setup
clean:
	rm -rf ${BUILD}

setup:
	mkdir -p ${BUILD}
