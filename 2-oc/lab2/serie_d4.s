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

	lf f6, datosX+4(r1)
	multf f6, f6, f1

	lf f7, datosY+4(r1)
	divf f7, f7, f2

	lf f8, datosZ+4(r1)
	multf f8, f8, f1

	addf f6, f6, f7
	addf f6, f6, f8
	sf datosX+4(r1), f6
	
	lf f9, datosX+8(r1)
	multf f9, f9, f1

	lf f10, datosY+8(r1)
	divf f10, f10, f2

	lf f11, datosZ+8(r1)
	multf f11, f11, f1

	addf f9, f9, f10
	addf f9, f9, f11
	sf datosX+8(r1), f9
	
	lf f12, datosX+12(r1)
	multf f12, f12, f1

	lf f13, datosY+12(r1)
	divf f13, f13, f2

	lf f14, datosZ+12(r1)
	multf f14, f14, f1

	addf f12, f12, f13
	addf f12, f12, f14
	sf datosX+12(r1), f12

	addi r1, r1, #16
	addi r20, r20, #-4
	bnez r20, bucle

	trap 0
