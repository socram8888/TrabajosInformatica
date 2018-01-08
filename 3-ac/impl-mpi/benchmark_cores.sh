#!/bin/bash

genimage() {
	SIZE=$1
	echo -ne "P5\n$SIZE $SIZE 255\n" >image.pgm
	head -c $(($SIZE*$SIZE)) /dev/zero >>image.pgm
}

CORES=(2 4 8 12 32 64 128)
SIZE=6144

echo -e "SIZE\tCORES\tINIT\tLOAD\tSCATTER\tPROCESS\tGATHER\tSAVE"

while [ $SIZE -le 40000 ]; do
	for I in ${CORES[@]}; do
		echo -ne "$SIZE\t$I\t"
		genimage $SIZE

		mpirun -np $I --hostfile hostfile ./main -t -i image.pgm -n 4 | cut -c 13- | tr '\n' '\t'

		echo ""
	done

	SIZE=$(($SIZE + 6144))
done
