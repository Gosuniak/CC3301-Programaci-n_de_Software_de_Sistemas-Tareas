	.file	"sort-c-nbits.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	sort
	.type	sort, @function
sort:
	slli	t3,a1,2
	addi	t3,t3,-4
	add	t3,a0,t3
	mv	t1,a0
	li	a7,32
	bltu	a0,t3,.L2
	ret
.L7:
	sw	a1,0(t1)
	sw	a6,4(t1)
	mv	t1,a0
.L2:
	lw	a6,0(t1)
	lw	a1,4(t1)
	li	a5,0
	li	a2,0
	li	a3,0
.L6:
	srl	a4,a6,a5
	andi	a4,a4,1
	add	a3,a3,a4
	srl	a4,a1,a5
	andi	a4,a4,1
	add	a2,a2,a4
	addi	a5,a5,1
	bne	a5,a7,.L6
	blt	a3,a2,.L7
	addi	t1,t1,4
	bgtu	t3,t1,.L2
	ret
	.size	sort, .-sort
	.ident	"GCC: (GNU) 11.1.0"
