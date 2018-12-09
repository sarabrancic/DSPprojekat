	.public _coefficients
	.public _gain2
	.public _input_gain
	.public _p
	.public _sampleBuffer
	.public _x_history1
	.public _x_history2
	.public _x_history3
	.public _y_history1
	.public _y_history2
	.public _y_history3
	.extern _cl_wavread_bits_per_sample
	.extern _cl_wavread_close
	.extern _cl_wavread_frame_rate
	.extern _cl_wavread_getnchannels
	.extern _cl_wavread_number_of_frames
	.extern _cl_wavread_open
	.extern _cl_wavread_recvsample
	.extern _cl_wavwrite_close
	.extern _cl_wavwrite_open
	.extern _cl_wavwrite_sendsample
	.public _main
	.extern _p_function
	.extern _printf
	.public _second_order_IIR
	.extern _strcpy
	.extern __div
	.ydata_ovly
_coefficients
	.dw  (0x52d265)
	.dw  (0xa5a4ca)
	.dw  (0x52d265)
	.dw  (0x7fffffff)
	.dw  (0x89766e96)
	.dw  (0x6e617095)
	.ydata_ovly
_gain2
	.dw  (0x65ac8a37)
	.ydata_ovly
_input_gain
	.dw  (0x50c332f0)
	.xdata_ovly
_p
	.bss (0x1)
	.xdata_ovly
_sampleBuffer
	.bss (0x80)
	.xdata_ovly
_string_const_0
	.dw  (0x45)
	.dw  (0x72)
	.dw  (0x72)
	.dw  (0x6f)
	.dw  (0x72)
	.dw  (0x3a)
	.dw  (0x20)
	.dw  (0x43)
	.dw  (0x6f)
	.dw  (0x75)
	.dw  (0x6c)
	.dw  (0x64)
	.dw  (0x20)
	.dw  (0x6e)
	.dw  (0x6f)
	.dw  (0x74)
	.dw  (0x20)
	.dw  (0x6f)
	.dw  (0x70)
	.dw  (0x65)
	.dw  (0x6e)
	.dw  (0x20)
	.dw  (0x69)
	.dw  (0x6e)
	.dw  (0x70)
	.dw  (0x75)
	.dw  (0x74)
	.dw  (0x20)
	.dw  (0x77)
	.dw  (0x61)
	.dw  (0x76)
	.dw  (0x65)
	.dw  (0x66)
	.dw  (0x69)
	.dw  (0x6c)
	.dw  (0x65)
	.dw  (0x2e)
	.dw  (0xa)
	.dw  (0x0)
	.xdata_ovly
_string_const_1
	.dw  (0x45)
	.dw  (0x72)
	.dw  (0x72)
	.dw  (0x6f)
	.dw  (0x72)
	.dw  (0x3a)
	.dw  (0x20)
	.dw  (0x43)
	.dw  (0x6f)
	.dw  (0x75)
	.dw  (0x6c)
	.dw  (0x64)
	.dw  (0x20)
	.dw  (0x6e)
	.dw  (0x6f)
	.dw  (0x74)
	.dw  (0x20)
	.dw  (0x6f)
	.dw  (0x70)
	.dw  (0x65)
	.dw  (0x6e)
	.dw  (0x20)
	.dw  (0x6f)
	.dw  (0x75)
	.dw  (0x74)
	.dw  (0x70)
	.dw  (0x75)
	.dw  (0x74)
	.dw  (0x20)
	.dw  (0x77)
	.dw  (0x61)
	.dw  (0x76)
	.dw  (0x65)
	.dw  (0x66)
	.dw  (0x69)
	.dw  (0x6c)
	.dw  (0x65)
	.dw  (0x2e)
	.dw  (0xa)
	.dw  (0x0)
	.xdata_ovly
_x_history1
	.dw  (0x0)
	.dw  (0x0)
	.xdata_ovly
_x_history2
	.dw  (0x0)
	.dw  (0x0)
	.xdata_ovly
_x_history3
	.dw  (0x0)
	.dw  (0x0)
	.ydata_ovly
_y_history1
	.dw  (0x0)
	.dw  (0x0)
	.ydata_ovly
_y_history2
	.dw  (0x0)
	.dw  (0x0)
	.ydata_ovly
_y_history3
	.dw  (0x0)
	.dw  (0x0)
	.code_ovly



	# This construction should ensure linking of crt0 in case when target is a standalone program without the OS
	.if defined(_OVLY_)
		.if .strcmp('standalone',_OVLY_)=0
		.if .strcmp('crystal32',_TARGET_FAMILY_)=0
			.extern __start         # dummy use of __start to force linkage of crt0
dummy		.equ(__start)
		.else
			.extern __intvec         # dummy use of __intvec to force linkage of intvec
dummy		.equ(__intvec)
		.endif
		.endif
	.endif

_main:			/* LN: 90 | CYCLE: 0 | RULES: () */ 
	xmem[i7] = i7			# LN: 90 | 
	i7 += 1			# LN: 90 | 
	i7 = i7 + (0x20d)			# LN: 90 | 
	i1 = i7 - (0x1)			# LN: 90 | 
	xmem[i1] = a0h			# LN: 90 | 
	i1 = i7 - (0x2)			# LN: 90 | 
	xmem[i1] = i0			# LN: 90 | 
cline_90_0:			/* LN: 105 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x2)			# LN: 105 | 
	i0 = xmem[i0]			# LN: 105 | 
	i1 = i7 - (258 - 0)			# LN: 105 | 
	i4 = xmem[i0]			# LN: 105 | 
	i0 = i1			# LN: 105 | 
	i1 = i4			# LN: 105 | 
	call (_strcpy)			# LN: 105 | 
cline_105_0:			/* LN: 106 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (258 - 0)			# LN: 106 | 
	call (_cl_wavread_open)			# LN: 106 | 
	AnyReg(i0, a0h)			# LN: 106 | 
	i1 = i7 - (0x103)			# LN: 106 | 
	xmem[i1] = i0			# LN: 106 | 
cline_106_0:			/* LN: 107 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x103)			# LN: 107 | 
	a0 = xmem[i0]			# LN: 107 | 
	a0 & a0			# LN: 107 | 
	if (a != 0) jmp (else_0)			# LN: 107 | 
cline_107_0:			/* LN: 109 | CYCLE: 0 | RULES: () */ 
	i0 = (0) + (_string_const_0)			# LN: 109 | 
	call (_printf)			# LN: 109 | 
cline_109_0:			/* LN: 110 | CYCLE: 0 | RULES: () */ 
	halfword(a0) = (0xffff)			# LN: 110 | 
	jmp (__epilogue_224)			# LN: 110 | 
cline_110_0:			/* LN: 116 | CYCLE: 0 | RULES: () */ 
endif_0:			/* LN: 107 | CYCLE: 0 | RULES: () */ 
else_0:			/* LN: 107 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x103)			# LN: 116 | 
	i0 = xmem[i0]			# LN: 116 | 
	call (_cl_wavread_getnchannels)			# LN: 116 | 
	i0 = i7 - (0x104)			# LN: 116 | 
	xmem[i0] = a0h			# LN: 116 | 
cline_116_0:			/* LN: 117 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x103)			# LN: 117 | 
	i0 = xmem[i0]			# LN: 117 | 
	call (_cl_wavread_bits_per_sample)			# LN: 117 | 
	i0 = i7 - (0x105)			# LN: 117 | 
	xmem[i0] = a0h			# LN: 117 | 
cline_117_0:			/* LN: 118 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x103)			# LN: 118 | 
	i0 = xmem[i0]			# LN: 118 | 
	call (_cl_wavread_frame_rate)			# LN: 118 | 
	i0 = i7 - (0x106)			# LN: 118 | 
	xmem[i0] = a0h			# LN: 118 | 
cline_118_0:			/* LN: 119 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x103)			# LN: 119 | 
	i0 = xmem[i0]			# LN: 119 | 
	call (_cl_wavread_number_of_frames)			# LN: 119 | 
	i0 = i7 - (0x107)			# LN: 119 | 
	xmem[i0] = a0h			# LN: 119 | 
cline_119_0:			/* LN: 124 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x2)			# LN: 124 | 
	i0 = xmem[i0]			# LN: 124 | 
	i1 = i7 - (519 - 0)			# LN: 124 | 
	i0 += 1			# LN: 124 | 
	i4 = xmem[i0]			# LN: 124 | 
	i0 = i1			# LN: 124 | 
	i1 = i4			# LN: 124 | 
	call (_strcpy)			# LN: 124 | 
cline_124_0:			/* LN: 125 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (519 - 0)			# LN: 125 | 
	i1 = i7 - (0x105)			# LN: 125 | 
	a0 = xmem[i1]			# LN: 125 | 
	uhalfword(a1) = (0x6)			# LN: 125 | 
	i1 = i7 - (0x106)			# LN: 125 | 
	b0 = xmem[i1]			# LN: 125 | 
	call (_cl_wavwrite_open)			# LN: 125 | 
	AnyReg(i0, a0h)			# LN: 125 | 
	i1 = i7 - (0x208)			# LN: 125 | 
	xmem[i1] = i0			# LN: 125 | 
cline_125_0:			/* LN: 126 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x208)			# LN: 126 | 
	a0 = xmem[i0]			# LN: 126 | 
	a0 & a0			# LN: 126 | 
	if (a != 0) jmp (else_1)			# LN: 126 | 
cline_126_0:			/* LN: 128 | CYCLE: 0 | RULES: () */ 
	i0 = (0) + (_string_const_1)			# LN: 128 | 
	call (_printf)			# LN: 128 | 
cline_128_0:			/* LN: 129 | CYCLE: 0 | RULES: () */ 
	halfword(a0) = (0xffff)			# LN: 129 | 
	jmp (__epilogue_224)			# LN: 129 | 
cline_129_0:			/* LN: 140 | CYCLE: 0 | RULES: () */ 
endif_1:			/* LN: 126 | CYCLE: 0 | RULES: () */ 
else_1:			/* LN: 126 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x107)			# LN: 140 | 
	a0 = xmem[i0]			# LN: 140 | 
	uhalfword(a1) = (0x10)			# LN: 140 | 
	call (__div)			# LN: 140 | 
	i0 = i7 - (0x209)			# LN: 140 | 
	xmem[i0] = a0h			# LN: 140 | 
cline_140_0:			/* LN: 142 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20a)			# LN: 142 | 
	a0 = 0			# LN: 142 | 
	xmem[i0] = a0h			# LN: 142 | 
for_0:			/* LN: 142 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20a)			# LN: 142 | 
	a0 = xmem[i0]			# LN: 142 | 
	i0 = i7 - (0x209)			# LN: 142 | 
	a1 = xmem[i0]			# LN: 142 | 
	a0 - a1			# LN: 142 | 
	if (a >= 0) jmp (for_end_0)			# LN: 142 | 
cline_142_0:			/* LN: 144 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20b)			# LN: 144 | 
	a0 = 0			# LN: 144 | 
	xmem[i0] = a0h			# LN: 144 | 
	do (0x10), label_end_92			# LN: 144 | 
cline_144_0:			/* LN: 146 | CYCLE: 0 | RULES: () */ 
label_begin_92:			/* LN: 144 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20c)			# LN: 146 | 
	a0 = 0			# LN: 146 | 
	xmem[i0] = a0h			# LN: 146 | 
for_2:			/* LN: 146 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20c)			# LN: 146 | 
	a0 = xmem[i0]			# LN: 146 | 
	i0 = i7 - (0x104)			# LN: 146 | 
	a1 = xmem[i0]			# LN: 146 | 
	a0 - a1			# LN: 146 | 
	if (a >= 0) jmp (for_end_2)			# LN: 146 | 
cline_146_0:			/* LN: 148 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x103)			# LN: 148 | 
	i0 = xmem[i0]			# LN: 148 | 
	call (_cl_wavread_recvsample)			# LN: 148 | 
	i0 = i7 - (0x20d)			# LN: 148 | 
	xmem[i0] = a0h			# LN: 148 | 
cline_148_0:			/* LN: 149 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20c)			# LN: 149 | 
	a0 = xmem[i0]			# LN: 149 | 
	a0 = a0 << 4			# LN: 149 | 
	i0 = a0			# LN: 149 | 
	i1 = i7 - (0x20b)			# LN: 149 | 
	i0 = i0 + (_sampleBuffer + 0)			# LN: 149 | 
	a0 = xmem[i1]			# LN: 149 | 
	a1 = i0			# LN: 149 | 
	a0 = a1 + a0			# LN: 149 | 
	AnyReg(i0, a0h)			# LN: 149 | 
	i1 = i7 - (0x20d)			# LN: 149 | 
	a0 = xmem[i1]			# LN: 149 | 
	xmem[i0] = a0h			# LN: 149 | 
cline_149_0:			/* LN: 146 | CYCLE: 0 | RULES: () */ 
init_latch_label_0:			/* LN: 150 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20c)			# LN: 146 | 
	a0 = xmem[i0]			# LN: 146 | 
	uhalfword(a1) = (0x1)			# LN: 146 | 
	a0 = a0 + a1			# LN: 146 | 
	i0 = i7 - (0x20c)			# LN: 146 | 
	xmem[i0] = a0h			# LN: 146 | 
	jmp (for_2)			# LN: 146 | 
cline_146_1:			/* LN: 144 | CYCLE: 0 | RULES: () */ 
init_latch_label_1:			/* LN: 151 | CYCLE: 0 | RULES: () */ 
for_end_2:			/* LN: 146 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20b)			# LN: 144 | 
	a0 = xmem[i0]			# LN: 144 | 
	uhalfword(a1) = (0x1)			# LN: 144 | 
	a0 = a0 + a1			# LN: 144 | 
	i0 = i7 - (0x20b)			# LN: 144 | 
label_end_92:			# LN: 144 | CYCLE: 5 | RULES: ()
	xmem[i0] = a0h			# LN: 144 | 
cline_144_1:			/* LN: 155 | CYCLE: 0 | RULES: () */ 
for_end_1:			/* LN: 144 | CYCLE: 0 | RULES: () */ 
	call (_p_function)			# LN: 155 | 
cline_155_0:			/* LN: 158 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20b)			# LN: 158 | 
	a0 = 0			# LN: 158 | 
	xmem[i0] = a0h			# LN: 158 | 
	do (0x10), label_end_94			# LN: 158 | 
cline_158_0:			/* LN: 160 | CYCLE: 0 | RULES: () */ 
label_begin_94:			/* LN: 158 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20c)			# LN: 160 | 
	a0 = 0			# LN: 160 | 
	xmem[i0] = a0h			# LN: 160 | 
	do (0x6), label_end_93			# LN: 160 | 
cline_160_0:			/* LN: 162 | CYCLE: 0 | RULES: () */ 
label_begin_93:			/* LN: 160 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20c)			# LN: 162 | 
	a0 = xmem[i0]			# LN: 162 | 
	a0 = a0 << 4			# LN: 162 | 
	i0 = a0			# LN: 162 | 
	i1 = i7 - (0x20b)			# LN: 162 | 
	i0 = i0 + (_sampleBuffer + 0)			# LN: 162 | 
	a0 = xmem[i1]			# LN: 162 | 
	a1 = i0			# LN: 162 | 
	a0 = a1 + a0			# LN: 162 | 
	AnyReg(i0, a0h)			# LN: 162 | 
	i1 = i7 - (0x20d)			# LN: 162 | 
	a0 = xmem[i0]			# LN: 162 | 
	xmem[i1] = a0h			# LN: 162 | 
cline_162_0:			/* LN: 163 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x208)			# LN: 163 | 
	i1 = i7 - (0x20d)			# LN: 163 | 
	a0 = xmem[i1]			# LN: 163 | 
	i0 = xmem[i0]			# LN: 163 | 
	call (_cl_wavwrite_sendsample)			# LN: 163 | 
cline_163_0:			/* LN: 160 | CYCLE: 0 | RULES: () */ 
init_latch_label_2:			/* LN: 164 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20c)			# LN: 160 | 
	a0 = xmem[i0]			# LN: 160 | 
	uhalfword(a1) = (0x1)			# LN: 160 | 
	a0 = a0 + a1			# LN: 160 | 
	i0 = i7 - (0x20c)			# LN: 160 | 
label_end_93:			# LN: 160 | CYCLE: 5 | RULES: ()
	xmem[i0] = a0h			# LN: 160 | 
cline_160_1:			/* LN: 158 | CYCLE: 0 | RULES: () */ 
init_latch_label_3:			/* LN: 165 | CYCLE: 0 | RULES: () */ 
for_end_4:			/* LN: 160 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20b)			# LN: 158 | 
	a0 = xmem[i0]			# LN: 158 | 
	uhalfword(a1) = (0x1)			# LN: 158 | 
	a0 = a0 + a1			# LN: 158 | 
	i0 = i7 - (0x20b)			# LN: 158 | 
label_end_94:			# LN: 158 | CYCLE: 5 | RULES: ()
	xmem[i0] = a0h			# LN: 158 | 
cline_158_1:			/* LN: 142 | CYCLE: 0 | RULES: () */ 
init_latch_label_4:			/* LN: 166 | CYCLE: 0 | RULES: () */ 
for_end_3:			/* LN: 158 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20a)			# LN: 142 | 
	a0 = xmem[i0]			# LN: 142 | 
	uhalfword(a1) = (0x1)			# LN: 142 | 
	a0 = a0 + a1			# LN: 142 | 
	i0 = i7 - (0x20a)			# LN: 142 | 
	xmem[i0] = a0h			# LN: 142 | 
	jmp (for_0)			# LN: 142 | 
cline_142_1:			/* LN: 171 | CYCLE: 0 | RULES: () */ 
for_end_0:			/* LN: 142 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x103)			# LN: 171 | 
	i0 = xmem[i0]			# LN: 171 | 
	call (_cl_wavread_close)			# LN: 171 | 
cline_171_0:			/* LN: 172 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x208)			# LN: 172 | 
	i0 = xmem[i0]			# LN: 172 | 
	call (_cl_wavwrite_close)			# LN: 172 | 
cline_172_0:			/* LN: 175 | CYCLE: 0 | RULES: () */ 
	a0 = 0			# LN: 175 | 
	jmp (__epilogue_224)			# LN: 175 | 
cline_175_0:			/* LN: 176 | CYCLE: 0 | RULES: () */ 
__epilogue_224:			/* LN: 176 | CYCLE: 0 | RULES: () */ 
	i7 = i7 - (0x20d)			# LN: 176 | 
	i7 -= 1			# LN: 176 | 
	ret			# LN: 176 | 



_second_order_IIR:			/* LN: 57 | CYCLE: 0 | RULES: () */ 
	xmem[i7] = i7			# LN: 57 | 
	i7 += 1			# LN: 57 | 
	i7 = i7 + (0x9)			# LN: 57 | 
	i5 = i7 - (0x1)			# LN: 57 | 
	xmem[i5] = a0h			# LN: 57 | 
	i5 = i7 - (0x2)			# LN: 57 | 
	xmem[i5] = i0			# LN: 57 | 
	i0 = i7 - (0x3)			# LN: 57 | 
	xmem[i0] = i1			# LN: 57 | 
	i0 = i7 - (0x4)			# LN: 57 | 
	xmem[i0] = i4			# LN: 57 | 
cline_57_0:			/* LN: 58 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x7)			# LN: 58 | 
	a0 = 0			# LN: 58 | 
	xmem[i0] = a0g; i0 += 1			# LN: 58, 58 | 
	xmem[i0] = a0h; i0 += 1			# LN: 58, 58 | 
	xmem[i0] = a0l			# LN: 58 | 
cline_58_0:			/* LN: 59 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x4)			# LN: 59 | 
	i0 = xmem[i0]			# LN: 59 | 
	i1 = i7 - (0x8)			# LN: 59 | 
	a0 = ymem[i0]			# LN: 59 | 
	xmem[i1] = a0h			# LN: 59 | 
cline_59_0:			/* LN: 60 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x3)			# LN: 60 | 
	i0 = xmem[i0]			# LN: 60 | 
	i1 = i7 - (0x9)			# LN: 60 | 
	a0 = xmem[i0]			# LN: 60 | 
	xmem[i1] = a0h			# LN: 60 | 
cline_60_0:			/* LN: 63 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x7)			# LN: 63 | 
	a0g = xmem[i0]; i0 += 1			# LN: 63, 63 | 
	a0h = xmem[i0]; i0 += 1			# LN: 63, 63 | 
	a0l = xmem[i0]			# LN: 63 | 
	i0 = i7 - (0x2)			# LN: 63 | 
	i0 = xmem[i0]			# LN: 63 | 
	i1 = i7 - (0x1)			# LN: 63 | 
	y0 = xmem[i1]			# LN: 63 | 
#asm begin
	x0 = xmem[i0]; i0+=1 
	 a0+=x0*y0
#asm end			# LN: 63 | 
	i1 = i7 - (0x7)			# LN: 63 | 
	xmem[i1] = a0g; i1 += 1			# LN: 63, 63 | 
	xmem[i1] = a0h; i1 += 1			# LN: 63, 63 | 
	xmem[i1] = a0l			# LN: 63 | 
	i1 = i7 - (0x2)			# LN: 63 | 
	xmem[i1] = i0			# LN: 63 | 
cline_63_0:			/* LN: 66 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x7)			# LN: 66 | 
	a0g = xmem[i0]; i0 += 1			# LN: 66, 66 | 
	a0h = xmem[i0]; i0 += 1			# LN: 66, 66 | 
	a0l = xmem[i0]			# LN: 66 | 
	i0 = i7 - (0x2)			# LN: 66 | 
	i0 = xmem[i0]			# LN: 66 | 
	i1 = i7 - (0x3)			# LN: 66 | 
	i1 = xmem[i1]			# LN: 66 | 
#asm begin
	x0 = xmem[i0]; i0+=1 
	 x1 = xmem[i1]; i1+=1 
	 a0+=x0*x1
#asm end			# LN: 66 | 
	i4 = i7 - (0x7)			# LN: 66 | 
	xmem[i4] = a0g; i4 += 1			# LN: 66, 66 | 
	xmem[i4] = a0h; i4 += 1			# LN: 66, 66 | 
	xmem[i4] = a0l			# LN: 66 | 
	i4 = i7 - (0x2)			# LN: 66 | 
	xmem[i4] = i0			# LN: 66 | 
	i0 = i7 - (0x3)			# LN: 66 | 
	xmem[i0] = i1			# LN: 66 | 
cline_66_0:			/* LN: 69 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x7)			# LN: 69 | 
	a0g = xmem[i0]; i0 += 1			# LN: 69, 69 | 
	a0h = xmem[i0]; i0 += 1			# LN: 69, 69 | 
	a0l = xmem[i0]			# LN: 69 | 
	i0 = i7 - (0x2)			# LN: 69 | 
	i0 = xmem[i0]			# LN: 69 | 
	i1 = i7 - (0x3)			# LN: 69 | 
	i1 = xmem[i1]			# LN: 69 | 
#asm begin
	x0 = xmem[i0]; i0+=1 
	 x1 = xmem[i1]; i1-=1 
	 a0+=x0*x1
#asm end			# LN: 69 | 
	i4 = i7 - (0x7)			# LN: 69 | 
	xmem[i4] = a0g; i4 += 1			# LN: 69, 69 | 
	xmem[i4] = a0h; i4 += 1			# LN: 69, 69 | 
	xmem[i4] = a0l			# LN: 69 | 
	i4 = i7 - (0x2)			# LN: 69 | 
	xmem[i4] = i0			# LN: 69 | 
	i0 = i7 - (0x3)			# LN: 69 | 
	xmem[i0] = i1			# LN: 69 | 
cline_69_0:			/* LN: 72 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x7)			# LN: 72 | 
	a0g = xmem[i0]; i0 += 1			# LN: 72, 72 | 
	a0h = xmem[i0]; i0 += 1			# LN: 72, 72 | 
	a0l = xmem[i0]			# LN: 72 | 
	i0 = i7 - (0x2)			# LN: 72 | 
	i0 = xmem[i0]			# LN: 72 | 
	i1 = i7 - (0x4)			# LN: 72 | 
	i1 = xmem[i1]			# LN: 72 | 
#asm begin
	x0 = xmem[i0]; i0+=1 
	 y0 = ymem[i1]; i1+=1 
	 a0-=x0*y0
#asm end			# LN: 72 | 
	i4 = i7 - (0x7)			# LN: 72 | 
	xmem[i4] = a0g; i4 += 1			# LN: 72, 72 | 
	xmem[i4] = a0h; i4 += 1			# LN: 72, 72 | 
	xmem[i4] = a0l			# LN: 72 | 
	i4 = i7 - (0x2)			# LN: 72 | 
	xmem[i4] = i0			# LN: 72 | 
	i0 = i7 - (0x4)			# LN: 72 | 
	xmem[i0] = i1			# LN: 72 | 
cline_72_0:			/* LN: 75 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x7)			# LN: 75 | 
	a0g = xmem[i0]; i0 += 1			# LN: 75, 75 | 
	a0h = xmem[i0]; i0 += 1			# LN: 75, 75 | 
	a0l = xmem[i0]			# LN: 75 | 
	i0 = i7 - (0x2)			# LN: 75 | 
	i0 = xmem[i0]			# LN: 75 | 
	i1 = i7 - (0x4)			# LN: 75 | 
	i1 = xmem[i1]			# LN: 75 | 
#asm begin
	x0 = xmem[i0] 
	 y0 = ymem[i1];              
	 a0-=x0*y0
#asm end			# LN: 75 | 
	i4 = i7 - (0x7)			# LN: 75 | 
	xmem[i4] = a0g; i4 += 1			# LN: 75, 75 | 
	xmem[i4] = a0h; i4 += 1			# LN: 75, 75 | 
	xmem[i4] = a0l			# LN: 75 | 
	i4 = i7 - (0x2)			# LN: 75 | 
	xmem[i4] = i0			# LN: 75 | 
	i0 = i7 - (0x4)			# LN: 75 | 
	xmem[i0] = i1			# LN: 75 | 
cline_75_0:			/* LN: 78 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x7)			# LN: 78 | 
	a0g = xmem[i0]; i0 += 1			# LN: 78, 78 | 
	a0h = xmem[i0]; i0 += 1			# LN: 78, 78 | 
	a0l = xmem[i0]			# LN: 78 | 
	i0 = i7 - (0x2)			# LN: 78 | 
	i0 = xmem[i0]			# LN: 78 | 
	i1 = i7 - (0x4)			# LN: 78 | 
	i1 = xmem[i1]			# LN: 78 | 
#asm begin
	x0 = xmem[i0] 
	 y0 = ymem[i1]; i1-=1        
	 a0-=x0*y0
#asm end			# LN: 78 | 
	i4 = i7 - (0x7)			# LN: 78 | 
	xmem[i4] = a0g; i4 += 1			# LN: 78, 78 | 
	xmem[i4] = a0h; i4 += 1			# LN: 78, 78 | 
	xmem[i4] = a0l			# LN: 78 | 
	i4 = i7 - (0x2)			# LN: 78 | 
	xmem[i4] = i0			# LN: 78 | 
	i0 = i7 - (0x4)			# LN: 78 | 
	xmem[i0] = i1			# LN: 78 | 
cline_78_0:			/* LN: 81 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x4)			# LN: 81 | 
	i0 = xmem[i0]			# LN: 81 | 
	i1 = i7 - (0x4)			# LN: 81 | 
	i0 += 1			# LN: 81 | 
	xmem[i1] = i0			# LN: 81 | 
	i0 = i7 - (0x8)			# LN: 81 | 
	i1 = i7 - (0x4)			# LN: 81 | 
	i1 = xmem[i1]			# LN: 81 | 
	a0 = xmem[i0]			# LN: 81 | 
	ymem[i1] = a0h			# LN: 81 | 
cline_81_0:			/* LN: 82 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x4)			# LN: 82 | 
	i0 = xmem[i0]			# LN: 82 | 
	i1 = i7 - (0x4)			# LN: 82 | 
	i0 -= 1			# LN: 82 | 
	xmem[i1] = i0			# LN: 82 | 
	i0 = i7 - (0x7)			# LN: 82 | 
	a0g = xmem[i0]; i0 += 1			# LN: 82, 82 | 
	a0h = xmem[i0]; i0 += 1			# LN: 82, 82 | 
	i1 = i7 - (0x4)			# LN: 82 | 
	i1 = xmem[i1]			# LN: 82 | 
	a0l = xmem[i0]			# LN: 82 | 
	ymem[i1] = a0			# LN: 82 | 
cline_82_0:			/* LN: 83 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x3)			# LN: 83 | 
	i0 = xmem[i0]			# LN: 83 | 
	i1 = i7 - (0x3)			# LN: 83 | 
	i0 += 1			# LN: 83 | 
	xmem[i1] = i0			# LN: 83 | 
	i0 = i7 - (0x9)			# LN: 83 | 
	i1 = i7 - (0x3)			# LN: 83 | 
	i1 = xmem[i1]			# LN: 83 | 
	a0 = xmem[i0]			# LN: 83 | 
	xmem[i1] = a0h			# LN: 83 | 
cline_83_0:			/* LN: 84 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x3)			# LN: 84 | 
	i0 = xmem[i0]			# LN: 84 | 
	i1 = i7 - (0x3)			# LN: 84 | 
	i0 -= 1			# LN: 84 | 
	xmem[i1] = i0			# LN: 84 | 
	i0 = i7 - (0x1)			# LN: 84 | 
	i1 = i7 - (0x3)			# LN: 84 | 
	i1 = xmem[i1]			# LN: 84 | 
	a0 = xmem[i0]			# LN: 84 | 
	xmem[i1] = a0h			# LN: 84 | 
cline_84_0:			/* LN: 86 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x7)			# LN: 86 | 
	a0g = xmem[i0]; i0 += 1			# LN: 86, 86 | 
	a0h = xmem[i0]; i0 += 1			# LN: 86, 86 | 
	a0l = xmem[i0]			# LN: 86 | 
	a0 = a0			# LN: 86 | 
	jmp (__epilogue_222)			# LN: 86 | 
cline_86_0:			/* LN: 88 | CYCLE: 0 | RULES: () */ 
__epilogue_222:			/* LN: 88 | CYCLE: 0 | RULES: () */ 
	i7 = i7 - (0x9)			# LN: 88 | 
	i7 -= 1			# LN: 88 | 
	ret			# LN: 88 | 
