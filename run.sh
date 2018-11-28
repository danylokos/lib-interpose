BUILD=`pwd`/build
export DYLD_INSERT_LIBRARIES=${BUILD}/libInter.dylib
chmod +x ${BUILD}/client
${BUILD}/client