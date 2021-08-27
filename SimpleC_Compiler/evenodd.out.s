.file "stdin"
.text
.globl isodd
.type isodd, @function
isodd:
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
.globl iseven
.type iseven, @function
iseven:
	push	%rbp
	mov	%rsp, %rbp
	sub	$8, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$2, %rax
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
	sub	$40, %rsp
	push	%rbx
	# move argc and argv from parameter registers to the stack
	mov	%rdi, -32(%rbp)
	mov	%rsi, -40(%rbp)
	# generate code for the body
	# push the integer
	mov	$3, %rax
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	# push the integer
	mov	$2, %rax
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	isodd
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	iseven
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	isodd
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	iseven
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	# generate code for the return expression
	mov	-16(%rbp), %rax
	push	%rax
	# save the return expression into %rax per the abi
	pop	%rax
	# emit main's epilogue
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
