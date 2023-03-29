.file "stdin"
.text
.globl countdown
.type countdown, @function
countdown:
	push	%rbp
	mov	%rsp, %rbp
	sub	$40, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	# push the integer
	mov	$4, %rax
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rax
	mov	%rax, -32(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	mov	-32(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	sub	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	mov	-24(%rbp), %rax
	push	%rax
	mov	-32(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	mov	-32(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	mov	-24(%rbp), %rax
	push	%rax
	mov	-32(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	mov	-32(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	cdq
	idiv	%rbx
	push	%rdx
	pop	%rax
	mov	%rax, -40(%rbp)
	# push the integer
	mov	$0, %rax
	push	%rax
	pop	%rax
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
.text
.globl main
.type main, @function
main:
	# stack space for argc and argv
	# emit main's prologue
	push	%rbp
	mov	%rsp, %rbp
	sub	$16, %rsp
	push	%rbx
	# move argc and argv from parameter registers to the stack
	mov	%rdi, -8(%rbp)
	mov	%rsi, -16(%rbp)
	# generate code for the body
	# generate code for the return expression
	# push the integer
	mov	$4, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	countdown
	push	%rax
	# save the return expression into %rax per the abi
	pop	%rax
	# emit main's epilogue
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
