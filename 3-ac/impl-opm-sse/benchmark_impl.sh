#!/bin/bash

genimage() {
	SIZE=$1
	echo -ne "P5\n$SIZE $SIZE 255\n" >image.pgm
	head -c $(($SIZE*$SIZE)) /dev/zero >>image.pgm
}

maintimed() {
	./main $* | grep 'Process' | cut -c 13-
}

SIZE=512

echo -e "SIZE\tSEQ\tOMP\tSSE\tOMPSSE"

export OMP_PROC_BIND=true
export OMP_NUM_THREADS=24
export OMP_DYNAMIC=false

while [ $SIZE -le 32768 ]; do
	echo -ne "$SIZE\t"

	genimage $SIZE
	maintimed -t -i image.pgm -n 1 | tr '\n' '\t'

	genimage $SIZE
	maintimed -t -i image.pgm -n 1 -m | tr '\n' '\t'

	genimage $SIZE
	maintimed -t -i image.pgm -n 1 -s | tr '\n' '\t'

	genimage $SIZE
	maintimed -t -i image.pgm -n 1 -s -m

	SIZE=$(($SIZE + 512))
done
