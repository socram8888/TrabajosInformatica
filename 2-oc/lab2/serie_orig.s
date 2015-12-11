;==============================================================
; SERIES.S : Cabecera para el programa de la P2_OC
;==============================================================

.data 0x1000
datosX: .float 1.2, 2.4, 3.6, 4.8, 5.0, 5.5, 6.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 6.0, 5.5, 5.0, 4.8, 3.6, 2.4, 1.2
datosY: .float 2.2, 3.4, 4.6, 5.8, 6.0, 7.5, 8.0, 9.0, 9.5, 9.9, 9.9, 9.5, 9.0, 8.0, 7.5, 6.0, 5.8, 4.6, 3.4, 2.2
datosZ: .float 0.2, 1.4, 2.6, 3.8, 4.0, 4.5, 5.0, 6.0, 7.0, 8.0, 8.0, 7.0, 6.0, 5.0, 4.5, 4.0, 3.8, 2.6, 1.4, 0.2
CTE1: .float 2.2
CTE2: .float 5.5

.text 0x100
main:
	ADDI R20, R0, #20 	; R20 es el contador
	ADDI R1, R0, #0
	LF F1, CTE1
	LF F2, CTE2

bucle:
	lf f3, datosX(r1)
	multf f3, f3, f1

	lf f4, datosY(r1)
	divf f4, f4, f2

	lf f5, datosZ(r1)
	multf f5, f5, f1

	addf f3, f3, f4
	addf f3, f3, f5
	sf datosX(r1), f3

	addi r1, r1, #4
	addi r20, r20, #-1
	bnez r20, bucle

	trap 0
