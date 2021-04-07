.file "stdin"
.text
.globl do
.type do, @function
do:
	push	%rbp
	mov	%rsp, %rbp
	sub	$8, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rax
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
.text
.globl re
.type re, @function
re:
	push	%rbp
	mov	%rsp, %rbp
	sub	$16, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$2, %rax
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
