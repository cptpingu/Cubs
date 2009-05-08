#!/bin/sh

usage()
{
    echo "Usage: $1 file.ext"
    echo
    echo "It will check and call correct compiler, depending on the ext"
    echo "Supported ext:"
    echo ".cc/.cpp/.c: g++"
    echo ".asm/.s: nasm"
    echo ".dot : dotty"
    echo ".mmc: cubs"
}

attrib_bin()
{
    EXE=`which $1`
    test -x /usr/bin/$1 && EXE=/usr/bin/$1
    test -x /usr/local/bin/$1 && EXE=/usr/local/bin/$1
    test -x $1 && EXE=./$1
    echo $EXE
}

check_exists()
{
    # Hack :)
    $1 --version -v > /dev/null 2> /dev/null
    if [ $? -eq 127 ]; then
	return 0
    fi
    return 1
}

if [ $# -ne 1 ]; then
    usage $0
    exit 1
fi

#Get the ext
file=$1
ext=${file##*.}

case $ext in
    "cc" | "cpp" | "c")
	out="${file%.*}.exe"
	echo "== Compiling with g++ =="
	GCC=`attrib_bin "g++"`
	check_exists $GCC
	if [ $? -ne 1 ]; then
	    echo "g++ not found on your system"
	    exit 2
	fi
	$GCC -W -Wall -o3 $file -o $out
	;;
    "asm" | "s")
	out="${file%.*}.exe"
	echo "== Compiling with nasm =="
	NASM=`attrib_bin "nasm"`
	check_exists $NASM
	if [ $? -ne 1 ]; then
	    echo "nasm not found on your system"
	    exit 2
	fi
	LD=`attrib_bin "ld"`
	check_exists $LD
	if [ $? -ne 1 ]; then
	    echo "ld not found on your system"
	    exit 2
	fi
	$NASM -o /tmp/tmp.o -f elf -d ELF_TYPE $file && \
	$LD -s --dynamic-linker /lib/ld-linux.so.2 -lc /tmp/tmp.o -o $out && \
	rm -rf /tmp/tmp.o
	;;
    "dot")
	out="${file%.*}.png"
	echo "== Compiling with dotty =="
	DOT=`attrib_bin "dot"`
	check_exists $DOT
	if [ $? -ne 1 ]; then
	    echo "dot not found on your system"
	    exit 2
	fi
	$DOT -Tpng $file > $out
	;;
    "mmc")
	echo "== Executing with cubs =="
	CUBS=`attrib_bin "cubs"`
	check_exists $CUBS
	if [ $? -ne 1 ]; then
	    echo "cubs not found on your system"
	    exit 2
	fi
	$CUBS $file
	;;
    *)
	echo "$ext: Unknow extension."
	exit 2
	;;
esac
