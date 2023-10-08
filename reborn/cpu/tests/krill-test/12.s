.DATA 
	a: .space 4
	b: .space 12
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
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	sw 	$t3, -8($sp) 
	addiu 	$sp, $sp, -12 
entry.point.init:
	ori 	$t1, $zero, 3 
	sw 	$t1, a($zero) 
	ori 	$t2, $zero, 0 
	addiu 	$t3, $t2, 4 
	ori 	$t2, $zero, 1 
	sw 	$t2, 0($t3) 
	ori 	$t2, $zero, 4 
	addiu 	$t3, $t2, 4 
	ori 	$t2, $zero, 2 
	sw 	$t2, 0($t3) 
	ori 	$t2, $zero, 8 
	addiu 	$t2, $t2, 4 
	sw 	$t1, 0($t2) 
entry.point.return:
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
	addiu 	$sp, $fp, -20 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# retval.0: -8($fp) 
	# c: -12($fp) 
	# d: -16($fp) 
init.0:
	ori 	$t1, $zero, 4 
	sw 	$t1, -12($fp) 
	ori 	$t1, $zero, 0 
	addiu 	$t0, $fp, -16 
	addu 	$t2, $t0, $t1 
	ori 	$t1, $zero, 5 
	sw 	$t1, 0($t2) 
entry.0:
	ori 	$t1, $zero, 0 
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
