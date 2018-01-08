#!/bin/bash

genimage() {
	SIZE=$1
	echo -ne "P5\n$SIZE $SIZE 255\n" >image.pgm
	head -c $(($SIZE*$SIZE)) /dev/zero >>image.pgm
}

maintimed() {
	./main $* | grep 'Process' | cut -c 13-
}

CORES=(2 4 6 8 12 16 24 32 128)
SIZE=512

echo -ne "SIZE\tSEQ"
for I in ${CORES[@]}; do
	echo -ne "\tMP_$I"
done
echo ""

while [ $SIZE -le 32768 ]; do
	echo -ne "$SIZE\t"

	genimage $SIZE
	maintimed -t -i image.pgm -n 1 | tr -d '\n'

	for I in ${CORES[@]}; do
		genimage $SIZE
		export OMP_PROC_BIND=true
		export OMP_NUM_THREADS=$I
		export OMP_DYNAMIC=false

		echo -ne "\t"
		maintimed -t -m -i image.pgm -n 1 | tr -d '\n'
	done

	echo ""	

	SIZE=$(($SIZE + 512))
done
