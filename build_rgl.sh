#/bin/bash

source ./shell_colors.sh

./build_shaders.sh

build_lin() {
	echo "Compiling RGL for Linux..."
	make -f linux.mk install
}

build_win() {
	echo "Compiling RGL for Windows..."
	make -f windows.mk install
}

echo "==========================="
echo "Platform? [lin/win]"
read platform

if [ "$platform" = "lin" ] ; then
	build_lin
elif [ "$platform" = "win" ] ; then
	build_win
else
	build_lin
fi

if [ $? -ne 0 ] ; then
	echoColor $RED "Failed to compile RGL, please submit a bug report to https://github.com/rxtthin/rgl/issues"
	exit 1
else
	echoColor $GREEN "Successfully built RGL"
fi
