	.data
L0 : 	.SPACE 24
	.text
	MOVA R1 L0
	ADDI R2 R0 #0
	ADD (R1) R0 R2
	MOVA R1 L0
	ADDI R1 R1 #1
	ADDI R2 R0 #1
	ADD (R1) R0 R2
	MOVA R1 L0
	ADDI R1 R1 #2
	ADDI R2 R0 #2
	ADD (R1) R0 R2
	MOVA R1 L0
	ADDI R1 R1 #3
	ADDI R2 R0 #3
	ADD (R1) R0 R2
	MOVA R1 L0
	ADDI R1 R1 #4
	ADDI R2 R0 #4
	ADD (R1) R0 R2
	MOVA R1 L0
	ADDI R1 R1 #5
	ADDI R2 R0 #5
	ADD (R1) R0 R2
	ADDI R1 R0 #0
	ADDI R2 R0 #6
	SUBI R2 R2 #1
L1 : 	SUB R3 R2 R1
	BLE L2
	MOVA R3 L0
	ADD R3 R3 R1
	ADD R4 R0 (R3)
	MOVA R3 L0
	ADD R3 R3 R2
	ADD R5 R0 (R3)
	MOVA R3 L0
	ADD R3 R3 R1
	ADD (R3) R0 R5
	MOVA R5 L0
	ADD R5 R5 R2
	ADD (R5) R0 R4
	ADDI R1 R1 #1
	SUBI R2 R2 #1
	BT L1
L2 : 	ADDI R1 R0 #0
	ADDI R2 R0 #3
	SUBI R2 R2 #1
L3 : 	SUB R4 R2 R1
	BLE L4
	MOVA R4 L0
	ADD R4 R4 R1
	ADD R5 R0 (R4)
	MOVA R4 L0
	ADD R4 R4 R2
	ADD R3 R0 (R4)
	MOVA R4 L0
	ADD R4 R4 R1
	ADD (R4) R0 R3
	MOVA R3 L0
	ADD R3 R3 R2
	ADD (R3) R0 R5
	ADDI R1 R1 #1
	SUBI R2 R2 #1
	BT L3
L4 : 	ADDI R1 R0 #3
	ADDI R2 R0 #6
	SUBI R2 R2 #1
L5 : 	SUB R5 R2 R1
	BLE L6
	MOVA R5 L0
	ADD R5 R5 R1
	ADD R3 R0 (R5)
	MOVA R5 L0
	ADD R5 R5 R2
	ADD R4 R0 (R5)
	MOVA R5 L0
	ADD R5 R5 R1
	ADD (R5) R0 R4
	MOVA R4 L0
	ADD R4 R4 R2
	ADD (R4) R0 R3
	ADDI R1 R1 #1
	SUBI R2 R2 #1
	BT L5
L6 : 	MOVA R1 L0
	ADD R2 R0 (R1)
	WRITE R2 0
	MOVA R2 L0
	ADDI R2 R2 #1
	ADD R1 R0 (R2)
	WRITE R1 0
	MOVA R1 L0
	ADDI R1 R1 #2
	ADD R2 R0 (R1)
	WRITE R2 0
	MOVA R2 L0
	ADDI R2 R2 #3
	ADD R1 R0 (R2)
	WRITE R1 0
	MOVA R1 L0
	ADDI R1 R1 #4
	ADD R2 R0 (R1)
	WRITE R2 0
	MOVA R2 L0
	ADDI R2 R2 #5
	ADD R1 R0 (R2)
	WRITE R1 0
	HALT
