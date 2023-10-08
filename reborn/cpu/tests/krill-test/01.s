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
	addiu 	$sp, $fp, -52 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# retval.0: -8($fp) 
	# a: -48($fp) 
init.0:
entry.0:
	ori 	$t1, $zero, 12 
	addiu 	$t0, $fp, -48 
	addu 	$t2, $t0, $t1 
	ori 	$t1, $zero, 1 
	sw 	$t1, 0($t2) 
	ori 	$t1, $zero, 16 
	addiu 	$t0, $fp, -48 
	addu 	$t2, $t0, $t1 
	ori 	$t1, $zero, 2 
	sw 	$t1, 0($t2) 
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
