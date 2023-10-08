.DATA 
	arr_glb: .space 40
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
 
# kVoid print(kInt32[10] arr, kInt32 x) 
print:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -12 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	sw 	$t3, -8($sp) 
	addiu 	$sp, $sp, -12 
	# arr: 8($fp) 
	# x: 4($fp) 
	# i: -8($fp) 
init.0:
entry.0:
	ori 	$t1, $zero, 0 
	sw 	$t1, -8($fp) 
while.cond.0:
	lw 	$t2, -8($fp) 
	ori 	$t1, $zero, 10 
	slt 	$t1, $t2, $t1 
	bne 	$t1, $zero, while.body.0 
	nop 
	j 	while.end.0 
	nop 
while.body.0:
	lw 	$t2, -8($fp) 
	ori 	$t1, $zero, 4 
	mult 	$t2, $t1 
	mflo 	$t2 
	lw 	$t0, 8($fp) 
	addu 	$t1, $t0, $t2 
	lw 	$t0, 8($fp) 
	addu 	$t2, $t0, $t2 
	lw 	$t3, 0($t2) 
	ori 	$t2, $zero, 3 
	addu 	$t2, $t3, $t2 
	sw 	$t2, 0($t1) 
	j 	while.cond.0 
	nop 
while.end.0:
	j 	return.0 
	nop 
return.0:
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
	addiu 	$sp, $fp, -56 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	sw 	$t3, -8($sp) 
	addiu 	$sp, $sp, -12 
	# retval.0: -8($fp) 
	# arr: -48($fp) 
	# i: -52($fp) 
init.1:
entry.1:
	ori 	$t1, $zero, 0 
	sw 	$t1, -52($fp) 
while.cond.1:
	lw 	$t1, -52($fp) 
	ori 	$t2, $zero, 10 
	slt 	$t1, $t1, $t2 
	bne 	$t1, $zero, while.body.1 
	nop 
	j 	while.end.1 
	nop 
while.body.1:
	lw 	$t1, -52($fp) 
	ori 	$t2, $zero, 4 
	mult 	$t1, $t2 
	mflo 	$t2 
	addiu 	$t0, $fp, -48 
	addu 	$t2, $t0, $t2 
	ori 	$t3, $zero, 2 
	mult 	$t1, $t3 
	mflo 	$t3 
	sw 	$t3, 0($t2) 
	ori 	$t2, $zero, 1 
	addu 	$t1, $t1, $t2 
	sw 	$t1, -52($fp) 
	j 	while.cond.1 
	nop 
while.end.1:
	ori 	$t1, $zero, 0 
	addiu 	$t0, $fp, -48 
	addu 	$t2, $t0, $t1 
	lw 	$t2, 0($t2) 
	addiu 	$t0, $fp, -48 
	sw 	$t0, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function print begin 
	jal 	print 
	nop 
	addiu 	$sp, $sp, 8 
	# call function print end 
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
