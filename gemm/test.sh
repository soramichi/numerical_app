#!/bin/sh

make clean > /dev/null
make debug > /dev/null

do_test () {
    echo "Comparing './gemm $1' and './gemm_block $1 $2'"
    ./gemm $1 > gemm_test.out
    ./gemm_block $1 $2 > gemm_block_test.out
    diff gemm_test.out gemm_block_test.out > /dev/null
    if [ $? != 0 ]; then
	echo "NG! There must be a bug!"
    else
	echo "OK!"
    fi
    echo ""
    rm -f gemm_test.out gemm_block_test.out
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
