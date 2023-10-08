.DATA 
	fib: .space 80
	glb: .space 4
.TEXT 
	ori 	$fp, $zero, 0x8000 
	ori 	$sp, $zero, 0x8000 
	jal 	entry.point.function 
	nop 
	jal 	main 
	nop 
global.end.loop:
	j 	global.end.loop 
	nop 
	nop 
 
# kVoid entry.point.function(kVoid) 
entry.point.function:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -8 
	addiu 	$sp, $sp, 0 
entry.point.init:
entry.point.return:
	addiu 	$sp, $sp, 0 
	ori 	$sp, $fp, 0 
	lw 	$ra, 0($fp) 
	lw 	$fp, -4($fp) 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 add(kInt32 x, kInt32 y) 
add:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -16 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# x: 8($fp) 
	# y: 4($fp) 
	# retval.0: -8($fp) 
	# sum: -12($fp) 
init.0:
entry.0:
	lw 	$t1, 8($fp) 
	lw 	$t2, 4($fp) 
	addu 	$t1, $t1, $t2 
	sw 	$t1, -12($fp) 
	sw 	$t1, -8($fp) 
	j 	return.0 
	nop 
return.0:
	lw 	$t1, -8($fp) 
	ori 	$v0, $t1, 0 
	lw 	$t1, 8($sp) 
	lw 	$t2, 4($sp) 
	addiu 	$sp, $sp, 8 
	ori 	$sp, $fp, 0 
	lw 	$ra, 0($fp) 
	lw 	$fp, -4($fp) 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 main(kVoid) 
main:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -20 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	sw 	$t3, -8($sp) 
	sw 	$t4, -12($sp) 
	sw 	$t5, -16($sp) 
	sw 	$t6, -20($sp) 
	addiu 	$sp, $sp, -24 
	# retval.1: -8($fp) 
	# len: -12($fp) 
	# i: -16($fp) 
init.1:
entry.1:
	ori 	$t1, $zero, 20 
	sw 	$t1, -12($fp) 
	ori 	$t1, $zero, 0 
	addiu 	$t2, $t1, 0 
	ori 	$t1, $zero, 1 
	sw 	$t1, 0($t2) 
	ori 	$t2, $zero, 4 
	addiu 	$t2, $t2, 0 
	sw 	$t1, 0($t2) 
	ori 	$t1, $zero, 2 
	sw 	$t1, -16($fp) 
while.cond.0:
	lw 	$t2, -16($fp) 
	lw 	$t1, -12($fp) 
	slt 	$t1, $t2, $t1 
	bne 	$t1, $zero, while.body.0 
	nop 
	j 	while.end.0 
	nop 
while.body.0:
	lw 	$t1, -16($fp) 
	ori 	$t4, $zero, 4 
	mult 	$t1, $t4 
	mflo 	$t2 
	addiu 	$t2, $t2, 0 
	ori 	$t3, $zero, 1 
	subu 	$t5, $t1, $t3 
	mult 	$t5, $t4 
	mflo 	$t5 
	addiu 	$t5, $t5, 0 
	lw 	$t5, 0($t5) 
	ori 	$t6, $zero, 2 
	subu 	$t6, $t1, $t6 
	mult 	$t6, $t4 
	mflo 	$t4 
	addiu 	$t4, $t4, 0 
	lw 	$t4, 0($t4) 
	addu 	$t4, $t5, $t4 
	sw 	$t4, 0($t2) 
	addu 	$t1, $t1, $t3 
	sw 	$t1, -16($fp) 
	j 	while.cond.0 
	nop 
while.end.0:
	ori 	$t1, $zero, 0 
	sw 	$t1, glb($zero) 
	sw 	$t1, -16($fp) 
while.cond.1:
	lw 	$t2, -16($fp) 
	lw 	$t1, -12($fp) 
	slt 	$t1, $t2, $t1 
	bne 	$t1, $zero, while.body.1 
	nop 
	j 	while.end.1 
	nop 
while.body.1:
	lw 	$t2, glb($zero) 
	lw 	$t1, -16($fp) 
	ori 	$t3, $zero, 4 
	mult 	$t1, $t3 
	mflo 	$t3 
	addiu 	$t3, $t3, 0 
	lw 	$t3, 0($t3) 
	sw 	$t2, 0($sp) 
	sw 	$t3, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function add begin 
	jal 	add 
	nop 
	addiu 	$sp, $sp, 8 
	# call function add end 
	ori 	$t2, $v0, 0 
	sw 	$t2, glb($zero) 
	ori 	$t2, $zero, 1 
	addu 	$t1, $t1, $t2 
	sw 	$t1, -16($fp) 
	j 	while.cond.1 
	nop 
while.end.1:
	ori 	$t1, $zero, 0 
	sw 	$t1, -8($fp) 
	j 	return.1 
	nop 
return.1:
	lw 	$t1, -8($fp) 
	ori 	$v0, $t1, 0 
	lw 	$t1, 24($sp) 
	lw 	$t2, 20($sp) 
	lw 	$t3, 16($sp) 
	lw 	$t4, 12($sp) 
	lw 	$t5, 8($sp) 
	lw 	$t6, 4($sp) 
	addiu 	$sp, $sp, 24 
	ori 	$sp, $fp, 0 
	lw 	$ra, 0($fp) 
	lw 	$fp, -4($fp) 
	jr 	$ra 
	nop 
	nop 
