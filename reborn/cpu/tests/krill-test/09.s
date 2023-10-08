.DATA 
	queens_glb: .space 40
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
 
# kVoid print_queens(kInt32[8] queens) 
print_queens:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -12 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	sw 	$t3, -8($sp) 
	addiu 	$sp, $sp, -12 
	# queens: 4($fp) 
	# i: -8($fp) 
init.0:
entry.0:
while.cond.0:
	lw 	$t2, -8($fp) 
	ori 	$t1, $zero, 8 
	slt 	$t1, $t2, $t1 
	bne 	$t1, $zero, while.body.0 
	nop 
	j 	while.end.0 
	nop 
while.body.0:
	lw 	$t1, -8($fp) 
	ori 	$t2, $zero, 4 
	mult 	$t1, $t2 
	mflo 	$t3 
	addiu 	$t2, $t3, 0 
	lw 	$t0, 4($fp) 
	addu 	$t3, $t0, $t3 
	lw 	$t3, 0($t3) 
	sw 	$t3, 0($t2) 
	ori 	$t2, $zero, 1 
	addu 	$t1, $t1, $t2 
	sw 	$t1, -8($fp) 
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
 
# kInt32 is_legal(kInt32[8] queens, kInt32 size) 
is_legal:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -208 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	sw 	$t3, -8($sp) 
	sw 	$t4, -12($sp) 
	sw 	$t5, -16($sp) 
	addiu 	$sp, $sp, -20 
	# queens: 8($fp) 
	# size: 4($fp) 
	# retval.0: -8($fp) 
	# i: -12($fp) 
	# x: -16($fp) 
	# y: -20($fp) 
	# rows: -52($fp) 
	# cols: -84($fp) 
	# cross1: -144($fp) 
	# cross2: -204($fp) 
init.1:
entry.1:
	ori 	$t1, $zero, 0 
	sw 	$t1, -12($fp) 
while.cond.1:
	lw 	$t1, -12($fp) 
	ori 	$t2, $zero, 8 
	slt 	$t1, $t1, $t2 
	bne 	$t1, $zero, while.body.1 
	nop 
	j 	while.end.1 
	nop 
while.body.1:
	lw 	$t1, -12($fp) 
	ori 	$t2, $zero, 4 
	mult 	$t1, $t2 
	mflo 	$t4 
	addiu 	$t0, $fp, -52 
	addu 	$t3, $t0, $t4 
	ori 	$t2, $zero, 0 
	sw 	$t2, 0($t3) 
	addiu 	$t0, $fp, -84 
	addu 	$t3, $t0, $t4 
	sw 	$t2, 0($t3) 
	ori 	$t2, $zero, 1 
	addu 	$t1, $t1, $t2 
	sw 	$t1, -12($fp) 
	j 	while.cond.1 
	nop 
while.end.1:
	ori 	$t1, $zero, 0 
	sw 	$t1, -12($fp) 
while.cond.2:
	lw 	$t2, -12($fp) 
	ori 	$t1, $zero, 15 
	slt 	$t1, $t2, $t1 
	bne 	$t1, $zero, while.body.2 
	nop 
	j 	while.end.2 
	nop 
while.body.2:
	lw 	$t1, -12($fp) 
	ori 	$t2, $zero, 4 
	mult 	$t1, $t2 
	mflo 	$t4 
	addiu 	$t0, $fp, -144 
	addu 	$t3, $t0, $t4 
	ori 	$t2, $zero, 0 
	sw 	$t2, 0($t3) 
	addiu 	$t0, $fp, -204 
	addu 	$t3, $t0, $t4 
	sw 	$t2, 0($t3) 
	ori 	$t2, $zero, 1 
	addu 	$t1, $t1, $t2 
	sw 	$t1, -12($fp) 
	j 	while.cond.2 
	nop 
while.end.2:
	ori 	$t1, $zero, 0 
	sw 	$t1, -20($fp) 
while.cond.3:
	lw 	$t1, -20($fp) 
	lw 	$t2, 4($fp) 
	slt 	$t1, $t1, $t2 
	bne 	$t1, $zero, while.body.3 
	nop 
	j 	while.end.3 
	nop 
while.body.3:
	lw 	$t2, -20($fp) 
	ori 	$t1, $zero, 4 
	mult 	$t2, $t1 
	mflo 	$t2 
	lw 	$t0, 8($fp) 
	addu 	$t2, $t0, $t2 
	lw 	$t2, 0($t2) 
	sw 	$t2, -16($fp) 
	mult 	$t2, $t1 
	mflo 	$t1 
	addiu 	$t0, $fp, -84 
	addu 	$t1, $t0, $t1 
	lw 	$t1, 0($t1) 
	bne 	$t1, $zero, if.then.0 
	nop 
	j 	if.end.0 
	nop 
if.then.0:
	ori 	$t1, $zero, 0 
	sw 	$t1, -8($fp) 
	j 	return.1 
	nop 
	j 	if.end.0 
	nop 
if.end.0:
	lw 	$t2, -20($fp) 
	ori 	$t1, $zero, 4 
	mult 	$t2, $t1 
	mflo 	$t1 
	addiu 	$t0, $fp, -52 
	addu 	$t1, $t0, $t1 
	lw 	$t1, 0($t1) 
	bne 	$t1, $zero, if.then.1 
	nop 
	j 	if.end.1 
	nop 
if.then.1:
	ori 	$t1, $zero, 0 
	sw 	$t1, -8($fp) 
	j 	return.1 
	nop 
	j 	if.end.1 
	nop 
if.end.1:
	lw 	$t1, -16($fp) 
	lw 	$t2, -20($fp) 
	addu 	$t2, $t1, $t2 
	ori 	$t1, $zero, 4 
	mult 	$t2, $t1 
	mflo 	$t1 
	addiu 	$t0, $fp, -144 
	addu 	$t1, $t0, $t1 
	lw 	$t1, 0($t1) 
	bne 	$t1, $zero, if.then.2 
	nop 
	j 	if.end.2 
	nop 
if.then.2:
	ori 	$t1, $zero, 0 
	sw 	$t1, -8($fp) 
	j 	return.1 
	nop 
	j 	if.end.2 
	nop 
if.end.2:
	lw 	$t2, -16($fp) 
	lw 	$t1, -20($fp) 
	subu 	$t2, $t2, $t1 
	ori 	$t1, $zero, 7 
	addu 	$t2, $t2, $t1 
	ori 	$t1, $zero, 4 
	mult 	$t2, $t1 
	mflo 	$t1 
	addiu 	$t0, $fp, -204 
	addu 	$t1, $t0, $t1 
	lw 	$t1, 0($t1) 
	bne 	$t1, $zero, if.then.3 
	nop 
	j 	if.end.3 
	nop 
if.then.3:
	ori 	$t1, $zero, 0 
	sw 	$t1, -8($fp) 
	j 	return.1 
	nop 
	j 	if.end.3 
	nop 
if.end.3:
	lw 	$t4, -16($fp) 
	ori 	$t2, $zero, 4 
	mult 	$t4, $t2 
	mflo 	$t1 
	addiu 	$t0, $fp, -84 
	addu 	$t3, $t0, $t1 
	ori 	$t1, $zero, 1 
	sw 	$t1, 0($t3) 
	lw 	$t3, -20($fp) 
	mult 	$t3, $t2 
	mflo 	$t5 
	addiu 	$t0, $fp, -52 
	addu 	$t5, $t0, $t5 
	sw 	$t1, 0($t5) 
	addu 	$t5, $t4, $t3 
	mult 	$t5, $t2 
	mflo 	$t5 
	addiu 	$t0, $fp, -144 
	addu 	$t5, $t0, $t5 
	sw 	$t1, 0($t5) 
	subu 	$t4, $t4, $t3 
	ori 	$t5, $zero, 7 
	addu 	$t4, $t4, $t5 
	mult 	$t4, $t2 
	mflo 	$t2 
	addiu 	$t0, $fp, -204 
	addu 	$t2, $t0, $t2 
	sw 	$t1, 0($t2) 
	addu 	$t1, $t3, $t1 
	sw 	$t1, -20($fp) 
	j 	while.cond.3 
	nop 
while.end.3:
	ori 	$t1, $zero, 1 
	sw 	$t1, -8($fp) 
	j 	return.1 
	nop 
return.1:
	lw 	$t1, -8($fp) 
	ori 	$v0, $t1, 0 
	lw 	$t1, 20($sp) 
	lw 	$t2, 16($sp) 
	lw 	$t3, 12($sp) 
	lw 	$t4, 8($sp) 
	lw 	$t5, 4($sp) 
	addiu 	$sp, $sp, 20 
	ori 	$sp, $fp, 0 
	lw 	$ra, 0($fp) 
	lw 	$fp, -4($fp) 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 solve_queens(kInt32[8] queens, kInt32 size) 
solve_queens:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -16 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	sw 	$t3, -8($sp) 
	addiu 	$sp, $sp, -12 
	# queens: 8($fp) 
	# size: 4($fp) 
	# retval.1: -8($fp) 
	# y: -12($fp) 
init.2:
entry.2:
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 8 
	xor 	$t1, $t1, $t2 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.4 
	nop 
	j 	if.end.4 
	nop 
if.then.4:
	lw 	$t0, 8($fp) 
	sw 	$t0, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function print_queens begin 
	jal 	print_queens 
	nop 
	addiu 	$sp, $sp, 4 
	# call function print_queens end 
	ori 	$t1, $zero, 1 
	sw 	$t1, -8($fp) 
	j 	return.2 
	nop 
	j 	if.end.4 
	nop 
if.end.4:
	ori 	$t1, $zero, 0 
	sw 	$t1, -12($fp) 
while.cond.4:
	lw 	$t2, -12($fp) 
	ori 	$t1, $zero, 8 
	slt 	$t1, $t2, $t1 
	bne 	$t1, $zero, while.body.4 
	nop 
	j 	while.end.4 
	nop 
while.body.4:
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 4 
	mult 	$t1, $t2 
	mflo 	$t2 
	lw 	$t0, 8($fp) 
	addu 	$t2, $t0, $t2 
	lw 	$t3, -12($fp) 
	sw 	$t3, 0($t2) 
	ori 	$t2, $zero, 1 
	addu 	$t1, $t1, $t2 
	lw 	$t0, 8($fp) 
	sw 	$t0, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function is_legal begin 
	jal 	is_legal 
	nop 
	addiu 	$sp, $sp, 8 
	# call function is_legal end 
	ori 	$t1, $v0, 0 
	bne 	$t1, $zero, if.then.5 
	nop 
	j 	if.end.5 
	nop 
if.then.5:
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 1 
	addu 	$t1, $t1, $t2 
	lw 	$t0, 8($fp) 
	sw 	$t0, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function solve_queens begin 
	jal 	solve_queens 
	nop 
	addiu 	$sp, $sp, 8 
	# call function solve_queens end 
	ori 	$t1, $v0, 0 
	bne 	$t1, $zero, if.then.6 
	nop 
	j 	if.end.6 
	nop 
if.then.6:
	ori 	$t1, $zero, 1 
	sw 	$t1, -8($fp) 
	j 	return.2 
	nop 
	j 	if.end.6 
	nop 
if.end.6:
	j 	if.end.5 
	nop 
if.end.5:
	lw 	$t2, -12($fp) 
	ori 	$t1, $zero, 1 
	addu 	$t1, $t2, $t1 
	sw 	$t1, -12($fp) 
	j 	while.cond.4 
	nop 
while.end.4:
	ori 	$t1, $zero, 0 
	sw 	$t1, -8($fp) 
	j 	return.2 
	nop 
return.2:
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
	addiu 	$sp, $fp, -48 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# retval.2: -8($fp) 
	# queens: -40($fp) 
	# success: -44($fp) 
init.3:
entry.3:
	ori 	$t1, $zero, 0 
	addiu 	$t0, $fp, -40 
	sw 	$t0, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function solve_queens begin 
	jal 	solve_queens 
	nop 
	addiu 	$sp, $sp, 8 
	# call function solve_queens end 
	ori 	$t2, $v0, 0 
	sw 	$t2, -44($fp) 
	sw 	$t1, -8($fp) 
	j 	return.3 
	nop 
return.3:
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
