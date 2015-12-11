
.data 0x1000
AA: .space 4 * 10 * 10
BB: .space 4 * 10 * 10
VV: .space 4 * 10

.text 0x100
main:
	; R1 = puntero VV
	; R2 = contador creciente
	; R3 = contador decreciente
	; R4 = fijo a 4
	; R5 = temporal

	ADDI R1, R0, #8
	ADDI R2, R0, #0
	ADDI R3, R0, #8
	ADDI R4, R0, #4

	MULT R5, R2, R4

	ADDI R2, R2, #1
bucle_vv:
	SW VV-8(R1), R5

	MULT R5, R2, R4

	ADDI R1, R1, #4
	ADDI R2, R2, #1
	ADDI R3, R3, #-1
	BNEZ R3, bucle_vv

	SW VV-8(R1), R5
	MULT R5, R2, R4
	SW VV-4(R1), R5

	; R1 = puntero AA
	; R2 = contador ext creciente
	; R3 = contador ext decreciente
	; R4 = fijo a 20
	; R5 = contador int creciente
	; R6 = contador int decreciente
	ADDI R1, R0, #0
	ADDI R2, R0, #0
	ADDI R3, R0, #10
	ADDI R4, R0, #20

bucle_aa_ext:
	ADDI R5, R0, #0
	ADDI R6, R0, #10

bucle_aa_int:
	ADD R7, R2, R5
	SUB R7, R4, R7
	SW AA(R1), R7

	ADDI R1, R1, #4
	ADDI R5, R5, #1
	ADDI R6, R6, #-1
	BNEZ R6, bucle_aa_int

	ADDI R2, R2, #1
	ADDI R3, R3, #-1
	BNEZ R3, bucle_aa_ext

	; R1 = puntero AA y BB
	; R3 = contador ext decreciente
	; R4 = fijo a 20
	; R6 = contador int decreciente
	; R7 = puntero VV
	ADDI R1, R0, #0
	ADDI R3, R0, #10
	ADDI R4, R0, #20

bucle_bb_ext:

	LW R8, VV(R0)
	LW R9, AA(R1)
	MULT R10, R8, R9

	LW R8, VV+4(R0)
	LW R9, AA+4(R1)

	ADDI R1, R1, #8
	ADDI R6, R0, #8
	ADDI R7, R0, #8
bucle_bb_int:
	SW BB-8(R1), R10

	MULT R10, R8, R9

	LW R8, VV(R7)
	LW R9, AA(R1)

	ADDI R1, R1, #4
	ADDI R7, R7, #4
	ADDI R6, R6, #-1
	BNEZ R6, bucle_bb_int

	SW BB-8(R1), R10
	MULT R10, R8, R9
	SW BB-4(R1), R10

	ADDI R3, R3, #-1
	BNEZ R3, bucle_bb_ext

	TRAP 0
