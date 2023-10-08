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
 
# kVoid test1(kInt32 a) 
test1:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -8 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# a: 4($fp) 
init.0:
entry.0:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.0 
	nop 
	j 	if.else.0 
	nop 
if.then.0:
	ori 	$t1, $zero, 1 
	sw 	$t1, 4($fp) 
	j 	if.end.0 
	nop 
if.else.0:
	ori 	$t1, $zero, 2 
	sw 	$t1, 4($fp) 
	j 	if.end.0 
	nop 
if.end.0:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.1 
	nop 
	j 	if.end.1 
	nop 
if.then.1:
	j 	return.0 
	nop 
	j 	if.end.1 
	nop 
if.end.1:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.2 
	nop 
	j 	if.else.2 
	nop 
if.then.2:
	j 	return.0 
	nop 
	j 	if.end.2 
	nop 
if.else.2:
	j 	return.0 
	nop 
	j 	if.end.2 
	nop 
if.end.2:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.3 
	nop 
	j 	if.end.3 
	nop 
if.then.3:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.4 
	nop 
	j 	if.else.4 
	nop 
if.then.4:
	ori 	$t1, $zero, 1 
	sw 	$t1, 4($fp) 
	j 	if.end.4 
	nop 
if.else.4:
	ori 	$t1, $zero, 2 
	sw 	$t1, 4($fp) 
	j 	if.end.4 
	nop 
if.end.4:
	j 	if.end.3 
	nop 
if.end.3:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.5 
	nop 
	j 	if.end.5 
	nop 
if.then.5:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.6 
	nop 
	j 	if.else.6 
	nop 
if.then.6:
	ori 	$t1, $zero, 1 
	sw 	$t1, 4($fp) 
	j 	if.end.6 
	nop 
if.else.6:
	ori 	$t1, $zero, 2 
	sw 	$t1, 4($fp) 
	j 	if.end.6 
	nop 
if.end.6:
	j 	if.end.5 
	nop 
if.end.5:
	j 	return.0 
	nop 
return.0:
	lw 	$t1, 4($sp) 
	addiu 	$sp, $sp, 4 
	ori 	$sp, $fp, 0 
	lw 	$ra, 0($fp) 
	lw 	$fp, -4($fp) 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 test2(kInt32 a, kInt32 b, kInt32 c) 
test2:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -12 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# a: 12($fp) 
	# b: 8($fp) 
	# c: 4($fp) 
	# retval.0: -8($fp) 
init.1:
entry.1:
while.cond.0:
	lw 	$t1, 12($fp) 
	bne 	$t1, $zero, while.body.0 
	nop 
	j 	while.end.0 
	nop 
while.body.0:
	lw 	$t2, 8($fp) 
	ori 	$t1, $zero, 1 
	subu 	$t1, $t2, $t1 
	sw 	$t1, 12($fp) 
	j 	while.cond.0 
	nop 
while.end.0:
while.cond.1:
	lw 	$t1, 8($fp) 
	bne 	$t1, $zero, while.body.1 
	nop 
	j 	while.end.1 
	nop 
while.body.1:
	lw 	$t2, 8($fp) 
	ori 	$t1, $zero, 1 
	subu 	$t1, $t2, $t1 
	sw 	$t1, 8($fp) 
	j 	while.cond.1 
	nop 
	j 	while.end.1 
	nop 
	j 	while.cond.1 
	nop 
while.end.1:
while.cond.2:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, while.body.2 
	nop 
	j 	while.end.2 
	nop 
while.body.2:
	lw 	$t2, 8($fp) 
	ori 	$t1, $zero, 1 
	subu 	$t1, $t2, $t1 
	sw 	$t1, 8($fp) 
	j 	while.cond.2 
	nop 
while.end.2:
	lw 	$t1, 12($fp) 
	lw 	$t2, 8($fp) 
	addu 	$t1, $t1, $t2 
	lw 	$t2, 4($fp) 
	subu 	$t1, $t1, $t2 
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
 
# kVoid test1(kInt32 a) 
test1:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -8 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# a: 4($fp) 
init.0:
entry.0:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.0 
	nop 
	j 	if.else.0 
	nop 
if.then.0:
	ori 	$t1, $zero, 1 
	sw 	$t1, 4($fp) 
	j 	if.end.0 
	nop 
if.else.0:
	ori 	$t1, $zero, 2 
	sw 	$t1, 4($fp) 
	j 	if.end.0 
	nop 
if.end.0:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.1 
	nop 
	j 	if.end.1 
	nop 
if.then.1:
	j 	return.0 
	nop 
	j 	if.end.1 
	nop 
if.end.1:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.2 
	nop 
	j 	if.else.2 
	nop 
if.then.2:
	j 	return.0 
	nop 
	j 	if.end.2 
	nop 
if.else.2:
	j 	return.0 
	nop 
	j 	if.end.2 
	nop 
if.end.2:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.3 
	nop 
	j 	if.end.3 
	nop 
if.then.3:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.4 
	nop 
	j 	if.else.4 
	nop 
if.then.4:
	ori 	$t1, $zero, 1 
	sw 	$t1, 4($fp) 
	j 	if.end.4 
	nop 
if.else.4:
	ori 	$t1, $zero, 2 
	sw 	$t1, 4($fp) 
	j 	if.end.4 
	nop 
if.end.4:
	j 	if.end.3 
	nop 
if.end.3:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.5 
	nop 
	j 	if.end.5 
	nop 
if.then.5:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, if.then.6 
	nop 
	j 	if.else.6 
	nop 
if.then.6:
	ori 	$t1, $zero, 1 
	sw 	$t1, 4($fp) 
	j 	if.end.6 
	nop 
if.else.6:
	ori 	$t1, $zero, 2 
	sw 	$t1, 4($fp) 
	j 	if.end.6 
	nop 
if.end.6:
	j 	if.end.5 
	nop 
if.end.5:
	j 	return.0 
	nop 
return.0:
	lw 	$t1, 4($sp) 
	addiu 	$sp, $sp, 4 
	ori 	$sp, $fp, 0 
	lw 	$ra, 0($fp) 
	lw 	$fp, -4($fp) 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 test2(kInt32 a, kInt32 b, kInt32 c) 
test2:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -12 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# a: 12($fp) 
	# b: 8($fp) 
	# c: 4($fp) 
	# retval.0: -8($fp) 
init.1:
entry.1:
while.cond.0:
	lw 	$t1, 12($fp) 
	bne 	$t1, $zero, while.body.0 
	nop 
	j 	while.end.0 
	nop 
while.body.0:
	lw 	$t2, 8($fp) 
	ori 	$t1, $zero, 1 
	subu 	$t1, $t2, $t1 
	sw 	$t1, 12($fp) 
	j 	while.cond.0 
	nop 
while.end.0:
while.cond.1:
	lw 	$t1, 8($fp) 
	bne 	$t1, $zero, while.body.1 
	nop 
	j 	while.end.1 
	nop 
while.body.1:
	lw 	$t2, 8($fp) 
	ori 	$t1, $zero, 1 
	subu 	$t1, $t2, $t1 
	sw 	$t1, 8($fp) 
	j 	while.cond.1 
	nop 
	j 	while.end.1 
	nop 
	j 	while.cond.1 
	nop 
while.end.1:
while.cond.2:
	lw 	$t1, 4($fp) 
	bne 	$t1, $zero, while.body.2 
	nop 
	j 	while.end.2 
	nop 
while.body.2:
	lw 	$t2, 8($fp) 
	ori 	$t1, $zero, 1 
	subu 	$t1, $t2, $t1 
	sw 	$t1, 8($fp) 
	j 	while.cond.2 
	nop 
while.end.2:
	lw 	$t1, 12($fp) 
	lw 	$t2, 8($fp) 
	addu 	$t1, $t1, $t2 
	lw 	$t2, 4($fp) 
	subu 	$t1, $t1, $t2 
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
 
# kInt32 main(kVoid) 
main:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -20 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# retval.1: -8($fp) 
	# a: -12($fp) 
	# b: -16($fp) 
init.2:
entry.2:
	lw 	$t1, -12($fp) 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function test1 begin 
	jal 	test1 
	nop 
	addiu 	$sp, $sp, 4 
	# call function test1 end 
	lw 	$t1, -16($fp) 
	sw 	$t1, 0($sp) 
	sw 	$t1, -4($sp) 
	sw 	$t1, -8($sp) 
	addiu 	$sp, $sp, -12 
	# call function test2 begin 
	jal 	test2 
	nop 
	addiu 	$sp, $sp, 12 
	# call function test2 end 
return.2:
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
