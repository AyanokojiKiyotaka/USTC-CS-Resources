		.ORIG	x3000

LOOP		NOT	R2, R1
		ADD	R2, R2, #1
		ADD	R3, R0, R2
		BRnz	NZ		;R0 > R1
P		ADD	R3, R3, R2	;������
		BRp	P		;���������������
		ADD	R0, R1, R3	;����R0ΪR1+R3
		BRnzp	LOOP
NZ		BRn	N		
		BRnzp	OK		;��0������
N		ADD	R3, R3, R0	;�Ӽӿ�
		BRn	N		;�Ǹ�����ӵ��Ǹ�
		NOT	R3, R3
		ADD	R3, R3, #1
		ADD	R1, R0, R3	;����R1ΪR0-R3
		BRnzp	LOOP

OK		HALT

		.END