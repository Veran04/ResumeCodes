.file "stdin"
.text
.globl fizzbuzz
.type fizzbuzz, @function
fizzbuzz:
	push	%rbp
	mov	%rsp, %rbp
	sub	$32, %rsp
	push	%rbx
	mov	%rdi, -8(%rbp)
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	# push the integer
	mov	$0, %rax
	push	%rax
	pop	%rax
	mov	%rax, -24(%rbp)
	# push the integer
	mov	$0, %rax
	push	%rax
	# push the integer
	mov	$0, %rax
	push	%rax
	pop	%rbx
	pop	%rax
