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
	ADDI R20, R0, #18 	; R20 es el contador
	ADDI R1, R0, #8
	LF F1, CTE1
	LF F2, CTE2

	lf f3, datosX(R0)
	lf f4, datosY(R0)
	lf f5, datosZ(R0)

	multf f3, f3, f1
	divf f4, f4, f2
	multf f5, f5, f1

	lf f13, datosX+4(R0)
	lf f14, datosY+4(R0)
	lf f15, datosZ+4(R0)
bucle:
	addf f3, f3, f4
	addf f3, f3, f5
	sf datosX-8(r1), f3

	multf f3, f13, f1
	divf f4, f14, f2
	multf f5, f15, f1

	lf f13, datosX(r1)
	lf f14, datosY(r1)
	lf f15, datosZ(r1)

	addi r1, r1, #4
	addi r20, r20, #-1
	bnez r20, bucle

	addf f3, f3, f4
	addf f3, f3, f5
	sf datosX-8(r1), f3

	multf f3, f13, f1
	divf f4, f14, f2
	multf f5, f15, f1

	addf f3, f3, f4
	addf f3, f3, f5
	sf datosX-4(r1), f3

	trap 0
