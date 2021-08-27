.file "stdin"
.text
.globl a
.type a, @function
a:
	push	%rbp
	mov	%rsp, %rbp
	sub	$8, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$5, %rax
	push	%rax
	pop	%rax
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
.text
.globl b
.type b, @function
b:
	push	%rbp
	mov	%rsp, %rbp
	sub	$8, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$10, %rax
	push	%rax
	pop	%rax
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
.text
.globl c
.type c, @function
c:
	push	%rbp
	mov	%rsp, %rbp
	sub	$8, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$15, %rax
	push	%rax
	pop	%rax
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
.text
.globl d
.type d, @function
d:
	push	%rbp
	mov	%rsp, %rbp
	sub	$8, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$20, %rax
	push	%rax
	pop	%rax
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
.text
.globl e
.type e, @function
e:
	push	%rbp
	mov	%rsp, %rbp
	sub	$8, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$25, %rax
	push	%rax
	pop	%rax
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
.text
.globl f
.type f, @function
f:
	push	%rbp
	mov	%rsp, %rbp
	sub	$8, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$30, %rax
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
	sub	$8, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$35, %rax
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
	sub	$48, %rsp
	push	%rbx
	# move argc and argv from parameter registers to the stack
	mov	%rdi, -40(%rbp)
	mov	%rsi, -48(%rbp)
	# generate code for the body
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	a
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	# push the integer
	mov	$2, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -32(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	sub	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	b
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	# push the integer
	mov	$2, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -32(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	mov	-24(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	c
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	# push the integer
	mov	$2, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -32(%rbp)
	mov	-24(%rbp), %rax
	push	%rax
	mov	-24(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	a
	push	%rax
	pop	%rbx
	pop	%rax
	cdq
	idiv	%rbx
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	d
	push	%rax
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	a
	push	%rax
	pop	%rbx
	pop	%rax
	cdq
	idiv	%rbx
	push	%rdx
	pop	%rax
	mov	%rax, -24(%rbp)
	# push the integer
	mov	$2, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -32(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	g
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	g
	push	%rax
	pop	%rbx
	pop	%rax
	sub	%rbx, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	sub	%rbx, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	f
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	b
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	sub	%rbx, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	# push the integer
	mov	$1, %rax
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
	mov	%rax, -24(%rbp)
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	e
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	# push the integer
	mov	$2, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -32(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	g
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	g
	push	%rax
	pop	%rbx
	pop	%rax
	sub	%rbx, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	# push the integer
	mov	$1, %rax
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
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	f
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	b
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	cdq
	idiv	%rbx
	push	%rdx
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	# push the integer
	mov	$2, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	a
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	# push the integer
	mov	$29, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	f
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	# push the integer
	mov	$35, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	g
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	mov	-24(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	mov	-24(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	cdq
	idiv	%rbx
	push	%rax
	mov	-24(%rbp), %rax
	push	%rax
	mov	-24(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
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
