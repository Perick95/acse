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
	ADDI R3 R0 #3
	ADD (R1) R0 R3
	MOVA R1 L0
	ADDI R1 R1 #4
	ADDI R3 R0 #4
	ADD (R1) R0 R3
	MOVA R1 L0
	ADDI R1 R1 #5
	ADDI R3 R0 #5
	ADD (R1) R0 R3
	SUBI R2 R2 #1
	ADDI R1 R0 #1
L1 : 	BLE L2
	MOVA R3 L0
	ADD R4 R0 (R3)
	MOVA R3 L0
	ADD R3 R3 R2
	ADD (R3) R0 R4
	SUBI R1 R1 #1
	BT L1
L2 : 	MOVA R2 L0
	ADD R1 R0 (R2)
	WRITE R1 0
	MOVA R1 L0
	ADDI R1 R1 #1
	ADD R2 R0 (R1)
	WRITE R2 0
	MOVA R2 L0
	ADDI R2 R2 #2
	ADD R1 R0 (R2)
	WRITE R1 0
	MOVA R1 L0
	ADDI R1 R1 #3
	ADD R2 R0 (R1)
	WRITE R2 0
	MOVA R2 L0
	ADDI R2 R2 #4
	ADD R1 R0 (R2)
	WRITE R1 0
	MOVA R1 L0
	ADDI R1 R1 #5
	ADD R2 R0 (R1)
	WRITE R2 0
	HALT
