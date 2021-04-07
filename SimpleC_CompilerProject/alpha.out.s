.file "stdin"
.text
.globl f
.type f, @function
f:
	push	%rbp
	mov	%rsp, %rbp
	sub	$16, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$1, %rax
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
.globl g
.type g, @function
g:
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
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
.text
.globl h
.type h, @function
h:
	push	%rbp
	mov	%rsp, %rbp
	sub	$16, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$3, %rax
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
.globl i
.type i, @function
i:
	push	%rbp
	mov	%rsp, %rbp
	sub	$16, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$4, %rax
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
	sub	$64, %rsp
	push	%rbx
	# move argc and argv from parameter registers to the stack
	mov	%rdi, -56(%rbp)
	mov	%rsi, -64(%rbp)
	# generate code for the body
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	f
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	mov	-24(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	g
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	mov	-32(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	h
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	mov	-40(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	h
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	mov	-48(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	i
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	# generate code for the return expression
	# push the integer
	mov	$0, %rax
	push	%rax
	# save the return expression into %rax per the abi
	pop	%rax
	# emit main's epilogue
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
