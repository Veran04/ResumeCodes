.file "stdin"
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
	mov	$2, %rax
	push	%rax
	pop	%rax
	mov	%rax, -8(%rbp)
	# push the integer
	mov	$13, %rax
	push	%rax
	pop	%rax
	mov	%rax, -16(%rbp)
	# push the integer
	mov	$1, %rax
	push	%rax
	# push the integer
	mov	$1, %rax
	push	%rax
	pop	%rbx
	pop	%rax
