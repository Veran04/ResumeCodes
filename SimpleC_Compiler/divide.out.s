.file "stdin"
.text
.globl divide
.type divide, @function
divide:
	push	%rbp
	mov	%rsp, %rbp
	sub	$16, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	# push the integer
	mov	$2, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	cdq
	idiv	%rbx
	push	%rdx
	# push the integer
	mov	$10, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	mov	-8(%rbp), %rax
	push	%rax
	# push the integer
	mov	$2, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	cdq
	idiv	%rbx
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	mov	-16(%rbp), %rax
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
	sub	$32, %rsp
	push	%rbx
	# move argc and argv from parameter registers to the stack
	mov	%rdi, -24(%rbp)
	mov	%rsi, -32(%rbp)
	# generate code for the body
	# push the integer
	mov	$10, %rax
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	divide
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	# generate code for the return expression
	# push the integer
	mov	$1, %rax
	push	%rax
	# save the return expression into %rax per the abi
	pop	%rax
	# emit main's epilogue
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
