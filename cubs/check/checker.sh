#!/bin/bash

BIN="./minicompil" # To change
WHITE=$'\E[m'
RED=$'\E[01;31m'
GREEN=$'\E[01;32m'
PURPLE=$'\E[01;34m'
YELLOW=$'\E[01;33m'
ORANGE=$'\E[01;30m'
SEP="${PURPLE}|${WHITE}"

dir=`dirname $0`
my_output="$dir/my.txt"
ref_output="$dir/ref.txt"
glob_ret=0


function get_output()
{
    echo -n > $my_output
    local nb=`cat $1 | wc -l`
    nb=$(($nb - 4))
    local activ=1
    local delim=`cat $1 | head -n 3 | tail -n 1`
    for i in `seq 4 $nb`; do
	if [ $activ -eq 1 ]; then
	    local line=`cat $1 | head -n $i | tail -n 1`
	    if [ "$line" == "$delim" ]; then
		activ=0
	    else
		line=${line###}
		echo $line >> $my_output
	    fi
	fi
    done
}

function test_file()
{
    local header=`cat $1 | head -n 1`
    if [ "$header" != "#!/bin/cub" ]; then
	return 255
    fi
    local attempted=`cat $1 | head -n 2 | tail -n 1`
    if [ "$attempted" == "#skip" ]; then
	return 254
    fi
    attempted=${attempted###}
    `$BIN $1 2> /dev/null > $ref_output`
    local ret=$?
    glob_ret=$ret
    glob_attempted=$attempted
    if [ "$ret" != "$attempted" ]; then
	echo -n > $my_output
	return 1
    fi
    get_output $1

    return 0
}

function echoformat()
{
    case ${#1} in
	0)
	    echo -n "  0"
	    ;;
	1)
	    echo -n "  $1"
	    ;;
	2)
	    echo -n " $1"
	    ;;
	*)
	    echo -n "$1"
	    ;;
    esac
}

function apply_test_to_file()
{
    test_file $1
    local ret=$?
    local my=$glob_ret
    local ref=$glob_attempted
    if [ $ret -ne 255 ]; then
	local res=""
	local outvalue=" Same "
	if [ $ret -ne 254 ]; then
	    diff $my_output $ref_output > /dev/null
	    if [ $? -ne 0 ]; then
		outvalue="Differ"
		ret=1
	    fi
	fi
	case $ret in
	    0)
		res="${GREEN}[OK]${WHITE}"
		;;
	    254)
		res="${ORANGE}SKIP${WHITE}"
		;;
	    *)
		res="${RED}[KO]${WHITE}"
		;;
	esac
	echo -n "$res $SEP "
	echoformat $my
	echo -n " $SEP "
	echoformat $ref
	echo -n " $SEP $outvalue $SEP"
	echo " $2"
    fi
}

function apply_to_all_files()
{
    echo
    echo "${YELLOW}In $2: ${WHITE}"
    echo -n " ${PURPLE}RES${WHITE} $SEP ${PURPLE}My${WHITE}"
    echo -n "  $SEP ${PURPLE}Ref${WHITE} "
    echo -n "$SEP ${PURPLE}Output${WHITE} "
    echo -n "$SEP ${PURPLE}File${WHITE}"
    echo
    echo "${PURPLE}-----------------------------------${WHITE}"
    for i in `ls $1/$2/*.mmc`; do
	local file=`basename $i`
	glob_ret=0
	glob_attempted=0
	apply_test_to_file $i $file
    done
}

function main()
{
    for i in `ls "$dir"`; do
	if [ -d $dir/$i ]; then
	    apply_to_all_files $dir $i
	fi
    done
}

main $*
