		.ORIG	x3000
		AND	R0, R0, #0
		AND	R1, R1, #0
		AND	R2, R2, #0
		AND	R3, R3, #0
		AND	R4, R4, #0
		AND	R5, R5, #0
		AND	R6, R6, #0
		AND	R7, R7, #0
		LD	R6, func_stack	;��ȡջ��ʼ��ַ
		JSR	main
		LD	R0, main_ret	;��ȡ����ֵ
		HALT

main		ST	R7, main_R7	;���R7������ķ��ص�ַ
		GETC
		LD	R1, c_n30
		ADD	R1, R0, R1	;�����ʼn
		LD	R6, func_stack	;��ȡջ��ʼ��ַ
		STR	R1, R6, #2	;��n�浽R6+#1��
		AND	R1, R1, #0	;��ʼ��R1Ϊ0
		STR	R1, R6, #3	;a����Ϊ0
		STR	R1, R6, #4	;b����Ϊ0
		STR	R1, R6, #5	;c����Ϊ0
		STR	R1, R6, #6	;d����Ϊ0
		STR	R1, R6, #7	;e����Ϊ0
		STR	R1, R6, #8	;f����Ϊ0
		JSR	func		;����func
		LDR	R0, R6, #0	;��ȡ����ֵ
		ADD	R6, R6, #-12	;R6����
		ST	R0, main_ret	;����ֵд��main��������ֵ��
		LD	R7, main_R7
		RET
main_ret	.BLKW	1
main_R7		.BLKW	1

func		STR	R7, R6, #1	;���R7������ķ��ص�ַ
		GETC			;����t��ʼ
		LD	R1, c_n30	
		ADD	R0, R0, R1	;t-='0'
		LDR	R1, R6, #3	;���ڴ��ȡa
		ADD	R0, R0, R1	;����a
		LDR	R1, R6, #4	;���ڴ��ȡb
		ADD	R0, R0, R1	;����b
		LDR	R1, R6, #5	;���ڴ��ȡc
		ADD	R0, R0, R1	;����c
		LDR	R1, R6, #6	;���ڴ��ȡd
		ADD	R0, R0, R1	;����d
		LDR	R1, R6, #7	;���ڴ��ȡe
		ADD	R0, R0, R1	;����e
		LDR	R1, R6, #8	;���ڴ��ȡf	
		ADD	R0, R0, R1	;����f, ����t����
		STR	R0, R6, #9	;���t

		LDR	R1, R6, #2	;��ȡn
		ADD	R2, R1, #-1	;����n-1
		BRnz	ELSE		;��n-1<=0,��ת��ELSE

		ADD	R6, R6, #12	;��R6ָ����һ��ջ�ռ䣬Ϊ��һ�εݹ������׼��
		LD	R3, stack_size	;��ȡջ�ռ��ܴ�С
		LD	R4, func_stack	;��ȡջ�ռ���ʼλ��
		ADD	R3, R3, R4	;����ջ�ռ�ĩβλ��
		NOT	R3, R3
		ADD	R3, R3, #1	;����ջ�ռ�ĩλ�õ��෴��
		ADD	R3, R3, R6	;R6-ջ�ռ�ĩλ��
		BRz	stackoverflow	;ջ���
		LDR	R1, R6, #-10	;���ڴ��ȡn
		ADD	R2, R1, #-1	;��n-1
		STR	R2, R6, #2	;�浽R6+#2��
		LDR	R1, R6, #-9	;���ڴ��ȡa
		STR	R1, R6, #3	;�浽R6+#3��
		LDR	R1, R6, #-8	;���ڴ��ȡb
		STR	R1, R6, #4	;�浽R6+#4��
		LDR	R1, R6, #-7	;���ڴ��ȡc
		STR	R1, R6, #5	;�浽R6+#5��
		LDR	R1, R6, #-6	;���ڴ��ȡd
		STR	R1, R6, #6	;�浽R6+#6��
		LDR	R1, R6, #-5	;���ڴ��ȡe
		STR	R1, R6, #7	;�浽R6+#7��
		LDR	R1, R6, #-4	;���ڴ��ȡf
		STR	R1, R6, #8	;�浽R6+#8��
		JSR	func		;�ݹ��������x
		LDR	R0, R6, #0	;��ȡ�ݹ������x�õ��ķ���ֵ
		STR	R0, R6, #-2	;���ڵ�ǰջ��x�ռ�λ����
		LDR	R1, R6, #-10	;���ڴ��ȡn
		ADD	R2, R1, #-2	;��n-2
		STR	R2, R6, #2	;�浽R6+#2��
					;����R1��R6��һ�ξ��Ѿ���ã���δ�ı�
		JSR	func		;�ݹ��������y
		LDR	R0, R6, #0	;��ȡ�ݹ������y�õ��ķ���ֵ
		STR	R0, R6, #-1	;���ڵ�ǰջ��y�ռ�λ����
		
		ADD	R6, R6, #-12	;ջָ��ָ�ص�ǰ���ú�����Ӧջ

		LDR	R0, R6, #9	;��ȡt��R0
		LDR	R1, R6, #10	;��ȡx��R1
		ADD	R0, R0, R1	;��t+x
		LDR	R1, R6, #11	;��ȡy��R1
		ADD	R0, R0, R1	;��t+x+y
		ADD	R0, R0, #-1	;��t+x+y-1
		STR	R0, R6, #0	;����ֵ����R6+#0

		LDR	R7, R6, #1	;��ȡR7������ķ��ص�ַ
		RET			;���������n>1�����
					;������n<=1�����
ELSE		LDR	R0, R6, #9	;����t,��t��ֵ����R0
		STR	R0, R6, #0	;����ֵ����R6+#0
		LDR	R7, R6, #1	;��ȡR7������ķ��ص�ַ
		RET			;n<=1��ֱ�ӷ���
stackoverflow	LEA	R0, sof_message
		PUTS
		HALT


sof_message	.STRINGZ "Stack OverFlow!"	
c_n30		.FILL	x-30		;'0'��ASCII���෴��
;stack_size	.FILL	#36		
stack_size	.FILL	x1C2C		;ջ�Ĵ�С+#12, x1C2C+#12=#7212
func_stack	.FILL	xD000		;Ϊfunc������ջ�����ռ�
					;func����ջ�ռ�洢����������ʽ��
					;1. ÿ12���ڴ��ַΪһ��
					;2. ÿ��˳���ţ�
					;	x0	����ֵ
					;	x1	RETӦ���ص���R7
					;	x2	n
					;	x3	a
					;	x4	b
					;	x5	c
					;	x6	d
					;	x7	e
					;	x8	f
					;	x9	t
					;	xA	x
					;	xB	y

		.END