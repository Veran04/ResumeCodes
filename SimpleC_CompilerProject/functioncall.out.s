.file "stdin"
.text
.globl fi
.type fi, @function
fi:
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
.globl do
.type do, @function
do:
	push	%rbp
	mov	%rsp, %rbp
	sub	$8, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$100, %rax
	push	%rax
	pop	%rax
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
.text
.globl go
.type go, @function
go:
	push	%rbp
	mov	%rsp, %rbp
	sub	$8, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$42, %rax
	push	%rax
	pop	%rax
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
.text
.globl no
.type no, @function
no:
	push	%rbp
	mov	%rsp, %rbp
	sub	$8, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
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
	sub	$48, %rsp
	push	%rbx
	# move argc and argv from parameter registers to the stack
	mov	%rdi, -40(%rbp)
	mov	%rsi, -48(%rbp)
	# generate code for the body
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	fi
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	do
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	mov	-24(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	go
	push	%rax
	pop	%rax
	mov	%rax, -32(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	fi
	push	%rax
	mov	-24(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	do
	push	%rax
	pop	%rbx
	pop	%rax
	add	%rbx, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	do
	push	%rax
	mov	-32(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	go
	push	%rax
	pop	%rbx
	pop	%rax
	sub	%rbx, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	cdq
	idiv	%rbx
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	go
	push	%rax
	mov	-24(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	go
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	go
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
	call	go
	push	%rax
	# push the integer
	mov	$5, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	mov	-24(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	go
	push	%rax
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	go
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
	pop	%rax
	mov	%rax, -24(%rbp)
	# push the integer
	mov	$1, %rax
	push	%rax
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	fi
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
	call	do
	push	%rax
	# push the integer
	mov	$10, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	cdq
	idiv	%rbx
	push	%rax
	pop	%rbx
	pop	%rax
	sub	%rbx, %rax
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	go
	push	%rax
	# push the integer
	mov	$5, %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	mov	-24(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	go
	push	%rax
	mov	-8(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	go
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
	pop	%rbx
	pop	%rax
	cdq
	idiv	%rbx
	push	%rdx
	pop	%rax
	mov	%rax, -32(%rbp)
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	no
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	# push the integer
	mov	$2, %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	do
	push	%rax
	mov	-16(%rbp), %rax
	push	%rax
	pop	%rbx
	pop	%rax
	imul	%rbx, %rax
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	# push the integer
	mov	$777, %rax
	push	%rax
	pop	%rax
	mov	%rax, -32(%rbp)
	mov	-32(%rbp), %rax
	push	%rax
	mov	-32(%rbp), %rax
	push	%rax
	pop	%rax
	mov	%rax, %rdi
	call	go
	push	%rax
	pop	%rbx
	pop	%rax
	cdq
	idiv	%rbx
	push	%rdx
	pop	%rax
	mov	%rax, -32(%rbp)
	# generate code for the return expression
	# push the integer
	mov	$5, %rax
	push	%rax
	# save the return expression into %rax per the abi
	pop	%rax
	# emit main's epilogue
	pop	%rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
