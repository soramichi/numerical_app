#!/bin/sh

make clean > /dev/null
make debug > /dev/null

do_test () {
    echo "Comparing './gemv $1' and './gemv_block $1 $2'"
    ./gemv $1 > gemv_test.out
    ./gemv_block $1 $2 > gemv_block_test.out
    diff gemv_test.out gemv_block_test.out > /dev/null
    if [ $? != 0 ]; then
	echo "NG! There must be a bug!"
    else
	echo "OK!"
    fi
    echo ""
    rm -f gemv_test.out gemv_block_test.out
}

do_test 2 1
do_test 4 1
do_test 4 2
do_test 10 5
do_test 32 4
do_test 32 8
do_test 100 4
do_test 100 50

make clean > /dev/null
