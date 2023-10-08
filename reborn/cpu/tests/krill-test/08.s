.DATA 
	resutl: .space 4
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
 
# kInt32 func2(kInt32 x, kInt32 y, kInt32 z) 
func2:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -16 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# x: 12($fp) 
	# y: 8($fp) 
	# z: 4($fp) 
	# retval.0: -8($fp) 
	# a: -12($fp) 
init.0:
entry.0:
	lw 	$t1, 12($fp) 
	lw 	$t2, 8($fp) 
	subu 	$t1, $t1, $t2 
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
 
# kInt32 func(kInt32 x, kInt32 y) 
func:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -16 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	sw 	$t3, -8($sp) 
	addiu 	$sp, $sp, -12 
	# x: 8($fp) 
	# y: 4($fp) 
	# retval.1: -8($fp) 
	# z: -12($fp) 
init.1:
entry.1:
	lw 	$t2, 8($fp) 
	lw 	$t3, 4($fp) 
	addu 	$t1, $t2, $t3 
	sw 	$t1, -12($fp) 
	sw 	$t2, 0($sp) 
	sw 	$t3, -4($sp) 
	sw 	$t2, -8($sp) 
	addiu 	$sp, $sp, -12 
	# call function func2 begin 
	jal 	func2 
	nop 
	addiu 	$sp, $sp, 12 
	# call function func2 end 
	ori 	$t2, $v0, 0 
	addu 	$t1, $t1, $t2 
	sw 	$t1, -12($fp) 
	sw 	$t1, -8($fp) 
	j 	return.1 
	nop 
return.1:
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
	# retval.2: -8($fp) 
	# z: -12($fp) 
init.2:
entry.2:
	ori 	$t1, $zero, 3 
	ori 	$t2, $zero, 4 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function func begin 
	jal 	func 
	nop 
	addiu 	$sp, $sp, 8 
	# call function func end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -12($fp) 
	sw 	$t1, resutl($zero) 
	ori 	$t1, $zero, 0 
	sw 	$t1, -8($fp) 
	j 	return.2 
	nop 
return.2:
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
