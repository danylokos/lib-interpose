BUILD=`pwd`/build
chmod +x ${BUILD}/client_rand
DYLD_INSERT_LIBRARIES=${BUILD}/libInter_rand.dylib ${BUILD}/client_rand