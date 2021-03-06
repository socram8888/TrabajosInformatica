
.data 0x1000
AA: .space 4 * 10 * 10
BB: .space 4 * 10 * 10
VV: .space 4 * 10

.text 0x100
main:
	; R1 = constante 20
	; R2 = indice i
	; R3 = indice j
	; R4 = offset matriz AA y matriz BB
	; R5 = offset vector VV
	; R6 = constante 4
	ADDI R1, R0, #20
	ADDI R3, R0, #0
	ADDI R5, R0, #0
	ADDI R6, R0, #4
bucle_externo:

	; Comienza cálculo de VV[j]
	MULT R7, R3, R6
	SW VV(R5), R7 ; Guardar VV[j]
	; Fin cálculo VV[j]

	; Comienza cálculo de AA[i] y BB[i]
	ADDI R2, R0, #0
	ADDI R4, R5, #0
bucle_interno:
	; Cálculo AA[i][j]
	ADD R10, R2, R3 ; R10 = (i+j)
	SUB R10, R1, R10 ; R10 = 20 - (i+j)
	SW AA(R4), R10
	; Fin cálculo AA[i][j]

	; Cálculo BB[i][j]
	MULT R11, R10, R7
	SW BB(R4), R11
	; Fin cálculo BB[i][j]

	ADDI R2, R2, #1 ; i++

	; Cálculo AA[i][j]
	ADD R12, R2, R3 ; R12 = (i+j)
	SUB R12, R1, R12 ; R12 = 20 - (i+j)
	SW AA+40(R4), R12
	; Fin cálculo AA[i][j]

	; Cálculo BB[i][j]
	MULT R13, R12, R7
	SW BB+40(R4), R13
	; Fin cálculo BB[i][j]

	ADDI R2, R2, #1 ; i++
	ADDI R4, R4, #80
	SLTI R8, R2, #10
	BNEZ R8, bucle_interno
	; Fin cálculo AA[i]

	ADDI R5, R5, #4
	ADDI R3, R3, #1 ; j++
	SLTI R9, R3, #10
	BNEZ R9, bucle_externo

	TRAP 0
