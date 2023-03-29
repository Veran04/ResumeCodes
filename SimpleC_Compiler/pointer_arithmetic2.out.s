.file "stdin"
.text
.globl zzz
.type zzz, @function
zzz:
	push	%rbp
	mov	%rsp, %rbp
	sub	$8, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	# push the integer
	mov	$7, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
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
	mov	$1, %rax
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	# push the integer
	mov	$2, %rax
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	pop	%rbx
	pop	%rax
	sub	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	zzz
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	pop	%rax
	mov	%rax, -24(%rbp)
	# generate code for the return expression
	# save the return expression into %rax per the abi
	pop	%rax
	# emit main's epilogue
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
