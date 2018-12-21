BUILD=`pwd`/build
if [[ "$OSTYPE" == "linux-gnu" ]]; then
	export LD_PRELOAD=${BUILD}/libInter.so
elif [[ "$OSTYPE" == "darwin"* ]]; then
	export DYLD_INSERT_LIBRARIES=${BUILD}/libInter.dylib
fi
chmod +x ${BUILD}/client
${BUILD}/client