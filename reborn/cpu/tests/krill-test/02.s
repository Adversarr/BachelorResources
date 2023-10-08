.DATA 
	a: .space 4
	b: .space 40
	c: .space 4
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
 
# kInt32 main(kVoid) 
main:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -72 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	sw 	$t3, -8($sp) 
	sw 	$t4, -12($sp) 
	sw 	$t5, -16($sp) 
	sw 	$t6, -20($sp) 
	sw 	$t7, -24($sp) 
	addiu 	$sp, $sp, -28 
	# retval.0: -8($fp) 
	# a: -12($fp) 
	# b: -16($fp) 
	# c: -20($fp) 
	# d: -24($fp) 
	# e: -28($fp) 
	# f: -68($fp) 
init.0:
entry.0:
	addiu 	$t3, $zero, -6 
	sw 	$t3, -12($fp) 
	ori 	$t2, $zero, 0x78 
	sw 	$t2, -16($fp) 
	addu 	$t5, $t3, $t2 
	sw 	$t5, -20($fp) 
	and 	$t4, $t3, $t2 
	xor 	$t6, $t3, $zero 
	sltiu 	$t6, $t6, 1 
	sltiu 	$t6, $t6, 1 
	xor 	$t7, $t2, $zero 
	sltiu 	$t7, $t7, 1 
	sltiu 	$t7, $t7, 1 
	and 	$t6, $t6, $t7 
	xor 	$t6, $t6, $zero 
	sltiu 	$t6, $t6, 1 
	sltiu 	$t6, $t6, 1 
	xor 	$t5, $t5, $zero 
	sltiu 	$t5, $t5, 1 
	sltiu 	$t5, $t5, 1 
	or 	$t6, $t6, $t5 
	xor 	$t5, $t1, $zero 
	sltiu 	$t5, $t5, 1 
	sltiu 	$t5, $t5, 1 
	xor 	$t5, $t6, $t5 
	or 	$t4, $t4, $t5 
	sw 	$t4, -24($fp) 
	slt 	$t5, $t2, $t3 
	ori 	$t6, $zero, 3 
	slt 	$t6, $t6, $t3 
	xor 	$t5, $t5, $t6 
	slti 	$t5, $t5, 1 
	slt 	$t3, $t3, $t4 
	xor 	$t3, $t5, $t3 
	sltiu 	$t3, $t3, 1 
	sltiu 	$t3, $t3, 1 
	lw 	$t4, -28($fp) 
	xor 	$t2, $t2, $t4 
	slti 	$t2, $t2, 1 
	xor 	$t3, $t3, $zero 
	sltiu 	$t3, $t3, 1 
	sltiu 	$t3, $t3, 1 
	xor 	$t2, $t2, $zero 
	sltiu 	$t2, $t2, 1 
	sltiu 	$t2, $t2, 1 
	and 	$t2, $t3, $t2 
	sw 	$t2, -28($fp) 
return.0:
	lw 	$t2, -8($fp) 
	ori 	$v0, $t2, 0 
	lw 	$t1, 28($sp) 
	lw 	$t2, 24($sp) 
	lw 	$t3, 20($sp) 
	lw 	$t4, 16($sp) 
	lw 	$t5, 12($sp) 
	lw 	$t6, 8($sp) 
	lw 	$t7, 4($sp) 
	addiu 	$sp, $sp, 28 
	ori 	$sp, $fp, 0 
	lw 	$ra, 0($fp) 
	lw 	$fp, -4($fp) 
	jr 	$ra 
	nop 
	nop 
