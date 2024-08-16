bits 64

section .data
check:
	db	"indexFrom = %d", 10, 0

section .text

extern printf

fileFrom	equ	8
fileTo	equ	fileFrom+8
x	equ	fileTo+8
y	equ	x+8
n	equ	y+8

global work_with_image_asm
work_with_image_asm:
;	sub	rsp, 8
	push	rbp
	mov	rbp, rsp
	sub	rsp, n
	;xor	r9, r9
	push	rbx
	push	r10 ; i
	push	r12 ; indexFrom
	push	r13 ; indexTo
	push	r14 ; j
	push	r15 ; x / 2 + 1
	mov	[rbp-fileFrom], rdi
	mov	[rbp-fileTo], rsi
	mov	r15, rdx
	shr	r15, 1
	inc	r15
	mov	[rbp-x], rdx
	mov	[rbp-y], rcx
;	mov	[rbp-n], r8
	xor	r10, r10
	xor	r13, r13
	xor	rbx, rbx
	xor	rdx, rdx
	dec	r10
;	xor	rcx, rcx
.start_loop1:
	xor	r14, r14
	dec	r14
	inc	r10
	cmp	r10, [rbp - y]
	je	.end
.start_loop2:
	inc	r14
	cmp	r14, r15
	je	.start_loop1
.for:
	mov	rax, r10
	mul	qword [rbp - x]
	add	rax, r14
	mul	r8
	mov	r12, rax
	mov	rax, r10
	inc	rax
	mul	qword [rbp - x]
	dec	rax
	sub	rax, r14
	mul	r8
	mov	r13, rax
	cmp	r12, r13
	jge	.start_loop2
	xor	rcx, rcx
	mov	rbx, r12
	mov	rdx, r13
	dec	rcx
.start_loop3:
	inc	rcx
	cmp	rcx, r8
	je	.start_loop2
.for2:		
	movzx	ax, byte [rdi+rbx]
	;movzx	ax, byte [rdi+r12]
	mov	[rsi+rdx], al
	movzx	ax, byte [rdi+rdx]
	mov	[rsi+rbx], al
	inc	rdx ;1
	inc	rbx
	jmp	.start_loop3
;	movzx	bx, byte [rdi+r12]
;	mov	[rsi + r13], bl
;	movzx	bx, byte [rdi+r13]
;	mov	[rsi+r12], bl
;	inc	r12 ;2
;	inc	r13
;	movzx	cx, byte [rdi+r12]
;	mov	[rsi+r13], cl
;	movzx	cx, byte [rdi+r13]
;	mov	[rsi+r12], cl
;	inc	r12 ;3
;	inc	r13
;	movzx	dx, byte [rdi+r12] 	
;	mov	[rsi+r13], dl
;	movzx	dx, byte [rdi+r13]
;	mov	[rsi+r12], dl
 ;	jmp	.start_loop2

.end:
	xor	rax, rax
	pop	r15
	pop	r14
	pop	r13
	pop	r12
	pop	r10
	pop	rbx
	leave
;	add	rsp, 8
	ret
