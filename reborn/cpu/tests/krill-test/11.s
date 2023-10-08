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
	addiu 	$sp, $fp, -28 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# retval.0: -8($fp) 
	# a: -12($fp) 
	# b: -16($fp) 
	# a: -20($fp) 
	# b: -24($fp) 
init.0:
entry.0:
	ori 	$t1, $zero, 3 
	sw 	$t1, -12($fp) 
	ori 	$t1, $zero, 4 
	sw 	$t1, -16($fp) 
	ori 	$t1, $zero, 5 
	sw 	$t1, -20($fp) 
	ori 	$t1, $zero, 6 
	sw 	$t1, -24($fp) 
	ori 	$t1, $zero, 0 
	sw 	$t1, -8($fp) 
	j 	return.0 
	nop 
return.0:
	lw 	$t1, -8($fp) 
	ori 	$v0, $t1, 0 
	lw 	$t1, 4($sp) 
	addiu 	$sp, $sp, 4 
	ori 	$sp, $fp, 0 
	lw 	$ra, 0($fp) 
	lw 	$fp, -4($fp) 
	jr 	$ra 
	nop 
	nop 
