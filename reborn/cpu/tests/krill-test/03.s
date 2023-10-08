.DATA 
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
	addiu 	$sp, $fp, -64 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	sw 	$t3, -8($sp) 
	addiu 	$sp, $sp, -12 
	# retval.0: -8($fp) 
	# a: -12($fp) 
	# b: -16($fp) 
	# c: -20($fp) 
	# d: -60($fp) 
init.0:
entry.0:
	ori 	$t1, $zero, 0x7b 
	sw 	$t1, -12($fp) 
	ori 	$t1, $zero, 0x1234 
	sw 	$t1, -16($fp) 
	ori 	$t1, $zero, 0xabcd 
	sw 	$t1, -20($fp) 
	ori 	$t3, $zero, 0 
	addiu 	$t0, $fp, -60 
	addu 	$t1, $t0, $t3 
	lui 	$t2, 0xabcd 
	ori 	$t2, $t2, 0x1234 
	sw 	$t2, 0($t1) 
	sw 	$t3, -8($fp) 
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
