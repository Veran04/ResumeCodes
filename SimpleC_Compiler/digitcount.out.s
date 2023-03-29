.file "stdin"
.text
.globl digitminus
.type digitminus, @function
digitminus:
	push	%rbp
	mov	%rsp, %rbp
	sub	$16, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	# push the integer
	mov	$100, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	sub	%rbx, %rax
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
.globl digitadd
.type digitadd, @function
digitadd:
	push	%rbp
	mov	%rsp, %rbp
	sub	$16, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
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
.globl digitmult
.type digitmult, @function
digitmult:
	push	%rbp
	mov	%rsp, %rbp
	sub	$16, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	# push the integer
	mov	$10, %rax
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
.globl digitdiv
.type digitdiv, @function
digitdiv:
	push	%rbp
	mov	%rsp, %rbp
	sub	$16, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	# push the integer
	mov	$100, %rax
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
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
.text
.globl digitmod
.type digitmod, @function
digitmod:
	push	%rbp
	mov	%rsp, %rbp
	sub	$16, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	# push the integer
	mov	$100, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	cdq
	idiv	%rbx
	push	%rdx
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
.globl digitall
.type digitall, @function
digitall:
	push	%rbp
	mov	%rsp, %rbp
	sub	$16, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	mov	-8(%rbp), %rax
	push	%rax
	# push the integer
	mov	$234, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	sub	%rbx, %rax
	push	%rax
	mov	-8(%rbp), %rax
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
	add	%rbx, %rax
	push	%rax
	mov	-8(%rbp), %rax
	push	%rax
	# push the integer
	mov	$10, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	mov	-8(%rbp), %rax
	push	%rax
	# push the integer
	mov	$100, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	cdq
	idiv	%rbx
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	mov	-8(%rbp), %rax
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
	add	%rbx, %rax
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
	sub	$24, %rsp
	push	%rbx
	# move argc and argv from parameter registers to the stack
	mov	%rdi, -16(%rbp)
	mov	%rsi, -24(%rbp)
	# generate code for the body
	# push the integer
	mov	$1234, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	digitminus
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	# push the integer
	mov	$1234, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	digitadd
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	# push the integer
	mov	$1234, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	digitmult
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	# push the integer
	mov	$1234, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	digitmod
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	# push the integer
	mov	$1234, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	digitall
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
