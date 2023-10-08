.DATA 
	x: .space 8
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
 
# kInt32 sum(kInt32 x, kInt32 y) 
sum:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -20 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	sw 	$t3, -8($sp) 
	addiu 	$sp, $sp, -12 
	# x: 8($fp) 
	# y: 4($fp) 
	# retval.0: -8($fp) 
	# a: -12($fp) 
	# b: -16($fp) 
init.0:
entry.0:
	lw 	$t1, 8($fp) 
	ori 	$t2, $zero, 1 
	subu 	$t1, $t1, $t2 
	sw 	$t1, -12($fp) 
	lw 	$t3, 4($fp) 
	addu 	$t2, $t3, $t2 
	sw 	$t2, -16($fp) 
	addu 	$t1, $t1, $t2 
	sw 	$t1, -8($fp) 
	j 	return.0 
	nop 
return.0:
	lw 	$t1, -8($fp) 
	ori 	$v0, $t1, 0 
	lw 	$t1, 12($sp) 
	lw 	$t2, 8($sp) 
	lw 	$t3, 4($sp) 
	addiu 	$sp, $sp, 12 
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
	addiu 	$sp, $fp, -16 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# retval.1: -8($fp) 
	# z: -12($fp) 
init.1:
entry.1:
	ori 	$t1, $zero, 3 
	ori 	$t2, $zero, 4 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function sum begin 
	jal 	sum 
	nop 
	addiu 	$sp, $sp, 8 
	# call function sum end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -12($fp) 
	addiu 	$t2, $t2, 0 
	sw 	$t1, 0($t2) 
	ori 	$t2, $zero, 5 
	slt 	$t1, $t2, $t1 
	bne 	$t1, $zero, if.then.0 
	nop 
	j 	if.else.0 
	nop 
if.then.0:
	addiu 	$t2, $zero, 0xfc60 
	lw 	$t1, -12($fp) 
	sw 	$t1, 0($t2) 
	j 	if.end.0 
	nop 
if.else.0:
	addiu 	$t2, $zero, 0xfc60 
	ori 	$t1, $zero, 0 
	sw 	$t1, 0($t2) 
	j 	if.end.0 
	nop 
if.end.0:
	ori 	$t1, $zero, 0 
	sw 	$t1, -8($fp) 
	j 	return.1 
	nop 
return.1:
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
