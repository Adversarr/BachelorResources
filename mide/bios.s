.DATA 
	sleep_count:
		.space 4
.TEXT 
	jal 	bios_main 
	nop
	nop
 
# kInt32 sleep(kVoid) 
sleep:
	sw 	$fp, 0($sp) 
	sw 	$t1, -4($sp) 
	sw 	$t2, -8($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -20 
	# retval.0: -12($fp) 
	# x: -16($fp) 
entry.0:
	ori 	$t1, $zero, 0 
	sw 	$t1, -16($fp) 
while.cond.0:
	lw 	$t2, -16($fp) 
	lw 	$t1, sleep_count($zero) 
	slt 	$t1, $t2, $t1 
	bne 	$t1, $zero, while.body.0 
	nop 
	j 	while.end.0 
	nop 
while.body.0:
	lw 	$t2, -16($fp) 
	ori 	$t1, $zero, 1 
	addu 	$t1, $t2, $t1 
	sw 	$t1, -16($fp) 
	j 	while.cond.0 
	nop 
while.end.0:
	lw 	$t1, -16($fp) 
	sw 	$t1, -12($fp) 
	j 	return.0 
	nop 
return.0:
	lw 	$t1, -12($fp) 
	ori 	$v0, $t1, 0 
	lw 	$fp, 0($fp) 
	lw 	$t1, -4($fp) 
	lw 	$t2, -8($fp) 
	ori 	$sp, $fp, 0 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 set_sleep_count(kInt32 ms) 
set_sleep_count:
	sw 	$fp, 0($sp) 
	sw 	$t1, -4($sp) 
	sw 	$t2, -8($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -16 
	# ms: 4($fp) 
	# retval.1: -12($fp) 
entry.1:
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 0x51e 
	mult 	$t1, $t2 
	mflo 	$t1 
	sw 	$t1, sleep_count($zero) 
	lw 	$t1, sleep_count($zero) 
	sw 	$t1, -12($fp) 
	j 	return.1 
	nop 
return.1:
	lw 	$t1, -12($fp) 
	ori 	$v0, $t1, 0 
	lw 	$fp, 0($fp) 
	lw 	$t1, -4($fp) 
	lw 	$t2, -8($fp) 
	ori 	$sp, $fp, 0 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 sleep_ms(kInt32 ms) 
sleep_ms:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	sw 	$t1, -8($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -16 
	# ms: 4($fp) 
	# retval.2: -12($fp) 
entry.2:
	lw 	$t1, 4($fp) 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_sleep_count begin 
	jal 	set_sleep_count 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_sleep_count end 
	addiu 	$sp, $sp, 0 
	# call function sleep begin 
	jal 	sleep 
	nop 
	addiu 	$sp, $sp, 0 
	# call function sleep end 
	ori 	$t1, $zero, 0 
	sw 	$t1, -12($fp) 
	j 	return.2 
	nop 
return.2:
	lw 	$t1, -12($fp) 
	ori 	$v0, $t1, 0 
	lw 	$ra, 0($fp) 
	lw 	$fp, -4($fp) 
	lw 	$t1, -8($fp) 
	ori 	$sp, $fp, 0 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 set_led_value(kInt32 value) 
set_led_value:
	sw 	$fp, 0($sp) 
	sw 	$t1, -4($sp) 
	sw 	$t2, -8($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -16 
	# value: 4($fp) 
	# retval.3: -12($fp) 
entry.3:
	addiu 	$t1, $zero, 0xfc60 
	lw 	$t2, 4($fp) 
	sw 	$t2, 0($t1) 
	lw 	$t1, 4($fp) 
	sw 	$t1, -12($fp) 
	j 	return.3 
	nop 
return.3:
	lw 	$t1, -12($fp) 
	ori 	$v0, $t1, 0 
	lw 	$fp, 0($fp) 
	lw 	$t1, -4($fp) 
	lw 	$t2, -8($fp) 
	ori 	$sp, $fp, 0 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 get_led_value(kVoid) 
get_led_value:
	sw 	$fp, 0($sp) 
	sw 	$t1, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -16 
	# retval.4: -8($fp) 
	# x: -12($fp) 
entry.4:
	addiu 	$t1, $zero, 0xfc60 
	lw 	$t1, 0($t1) 
	sw 	$t1, -12($fp) 
	lw 	$t1, -12($fp) 
	sw 	$t1, -8($fp) 
	j 	return.4 
	nop 
return.4:
	lw 	$t1, -8($fp) 
	ori 	$v0, $t1, 0 
	lw 	$fp, 0($fp) 
	lw 	$t1, -4($fp) 
	ori 	$sp, $fp, 0 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 set_digital_higher_value(kInt32 a, kInt32 b, kInt32 c, kInt32 d) 
set_digital_higher_value:
	sw 	$fp, 0($sp) 
	sw 	$t1, -4($sp) 
	sw 	$t2, -8($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -20 
	# a: 16($fp) 
	# b: 12($fp) 
	# c: 8($fp) 
	# d: 4($fp) 
	# retval.5: -12($fp) 
	# x: -16($fp) 
entry.5:
	lw 	$t2, 16($fp) 
	ori 	$t1, $zero, 15 
	and 	$t1, $t2, $t1 
	sw 	$t1, 16($fp) 
	lw 	$t1, 12($fp) 
	ori 	$t2, $zero, 15 
	and 	$t1, $t1, $t2 
	sw 	$t1, 12($fp) 
	lw 	$t2, 8($fp) 
	ori 	$t1, $zero, 15 
	and 	$t1, $t2, $t1 
	sw 	$t1, 8($fp) 
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 15 
	and 	$t1, $t1, $t2 
	sw 	$t1, 4($fp) 
	lw 	$t1, 16($fp) 
	sw 	$t1, -16($fp) 
	lw 	$t2, -16($fp) 
	ori 	$t1, $zero, 4 
	sllv 	$t2, $t2, $t1 
	lw 	$t1, 12($fp) 
	or 	$t1, $t2, $t1 
	sw 	$t1, -16($fp) 
	lw 	$t1, -16($fp) 
	ori 	$t2, $zero, 4 
	sllv 	$t1, $t1, $t2 
	lw 	$t2, 8($fp) 
	or 	$t1, $t1, $t2 
	sw 	$t1, -16($fp) 
	lw 	$t2, -16($fp) 
	ori 	$t1, $zero, 4 
	sllv 	$t2, $t2, $t1 
	lw 	$t1, 4($fp) 
	or 	$t1, $t2, $t1 
	sw 	$t1, -16($fp) 
	addiu 	$t2, $zero, 0xfc00 
	lw 	$t1, -16($fp) 
	sw 	$t1, 0($t2) 
return.5:
	lw 	$t1, -12($fp) 
	ori 	$v0, $t1, 0 
	lw 	$fp, 0($fp) 
	lw 	$t1, -4($fp) 
	lw 	$t2, -8($fp) 
	ori 	$sp, $fp, 0 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 set_digital_lower_value(kInt32 a, kInt32 b, kInt32 c, kInt32 d) 
set_digital_lower_value:
	sw 	$fp, 0($sp) 
	sw 	$t1, -4($sp) 
	sw 	$t2, -8($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -20 
	# a: 16($fp) 
	# b: 12($fp) 
	# c: 8($fp) 
	# d: 4($fp) 
	# retval.6: -12($fp) 
	# x: -16($fp) 
entry.6:
	lw 	$t1, 16($fp) 
	ori 	$t2, $zero, 15 
	and 	$t1, $t1, $t2 
	sw 	$t1, 16($fp) 
	lw 	$t1, 12($fp) 
	ori 	$t2, $zero, 15 
	and 	$t1, $t1, $t2 
	sw 	$t1, 12($fp) 
	lw 	$t2, 8($fp) 
	ori 	$t1, $zero, 15 
	and 	$t1, $t2, $t1 
	sw 	$t1, 8($fp) 
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 15 
	and 	$t1, $t1, $t2 
	sw 	$t1, 4($fp) 
	lw 	$t1, 16($fp) 
	sw 	$t1, -16($fp) 
	lw 	$t2, -16($fp) 
	ori 	$t1, $zero, 4 
	sllv 	$t2, $t2, $t1 
	lw 	$t1, 12($fp) 
	or 	$t1, $t2, $t1 
	sw 	$t1, -16($fp) 
	lw 	$t1, -16($fp) 
	ori 	$t2, $zero, 4 
	sllv 	$t1, $t1, $t2 
	lw 	$t2, 8($fp) 
	or 	$t1, $t1, $t2 
	sw 	$t1, -16($fp) 
	lw 	$t2, -16($fp) 
	ori 	$t1, $zero, 4 
	sllv 	$t2, $t2, $t1 
	lw 	$t1, 4($fp) 
	or 	$t1, $t2, $t1 
	sw 	$t1, -16($fp) 
	addiu 	$t2, $zero, 0xfc02 
	lw 	$t1, -16($fp) 
	sw 	$t1, 0($t2) 
return.6:
	lw 	$t1, -12($fp) 
	ori 	$v0, $t1, 0 
	lw 	$fp, 0($fp) 
	lw 	$t1, -4($fp) 
	lw 	$t2, -8($fp) 
	ori 	$sp, $fp, 0 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 set_digital_status(kInt32 enable_lower, kInt32 enable_higher) 
set_digital_status:
	sw 	$fp, 0($sp) 
	sw 	$t1, -4($sp) 
	sw 	$t2, -8($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -20 
	# enable_lower: 8($fp) 
	# enable_higher: 4($fp) 
	# retval.7: -12($fp) 
	# x: -16($fp) 
entry.7:
	ori 	$t1, $zero, 0 
	sw 	$t1, -16($fp) 
	lw 	$t2, 8($fp) 
	ori 	$t1, $zero, 0xff 
	and 	$t1, $t2, $t1 
	sw 	$t1, 8($fp) 
	lw 	$t1, 8($fp) 
	ori 	$t2, $zero, 0x100 
	mult 	$t1, $t2 
	mflo 	$t1 
	sw 	$t1, 8($fp) 
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 0xff 
	and 	$t1, $t1, $t2 
	sw 	$t1, 4($fp) 
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 0x1000 
	mult 	$t1, $t2 
	mflo 	$t1 
	sw 	$t1, 4($fp) 
	lw 	$t2, 8($fp) 
	lw 	$t1, 4($fp) 
	addu 	$t2, $t2, $t1 
	ori 	$t1, $zero, 0xff 
	addu 	$t1, $t2, $t1 
	sw 	$t1, -16($fp) 
	addiu 	$t2, $zero, 0xfc04 
	lw 	$t1, -16($fp) 
	sw 	$t1, 0($t2) 
return.7:
	lw 	$t1, -12($fp) 
	ori 	$v0, $t1, 0 
	lw 	$fp, 0($fp) 
	lw 	$t1, -4($fp) 
	lw 	$t2, -8($fp) 
	ori 	$sp, $fp, 0 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 get_switch_value(kVoid) 
get_switch_value:
	sw 	$fp, 0($sp) 
	sw 	$t1, -4($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -16 
	# retval.8: -8($fp) 
	# x: -12($fp) 
entry.8:
	addiu 	$t1, $zero, 0xfc70 
	lw 	$t1, 0($t1) 
	sw 	$t1, -12($fp) 
	lw 	$t1, -12($fp) 
	sw 	$t1, -8($fp) 
	j 	return.8 
	nop 
return.8:
	lw 	$t1, -8($fp) 
	ori 	$v0, $t1, 0 
	lw 	$fp, 0($fp) 
	lw 	$t1, -4($fp) 
	ori 	$sp, $fp, 0 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 extract(kInt32 x, kInt32 d) 
extract:
	sw 	$fp, 0($sp) 
	sw 	$t1, -4($sp) 
	sw 	$t2, -8($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -16 
	# x: 8($fp) 
	# d: 4($fp) 
	# retval.9: -12($fp) 
entry.9:
	lw 	$t1, 8($fp) 
	lw 	$t2, 4($fp) 
	srlv 	$t1, $t1, $t2 
	ori 	$t2, $zero, 1 
	and 	$t1, $t1, $t2 
	sw 	$t1, -12($fp) 
	j 	return.9 
	nop 
return.9:
	lw 	$t1, -12($fp) 
	ori 	$v0, $t1, 0 
	lw 	$fp, 0($fp) 
	lw 	$t1, -4($fp) 
	lw 	$t2, -8($fp) 
	ori 	$sp, $fp, 0 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 keyboard_is_pressed(kInt32 required) 
keyboard_is_pressed:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	sw 	$t1, -8($sp) 
	sw 	$t2, -12($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -28 
	# required: 4($fp) 
	# retval.10: -16($fp) 
	# x: -20($fp) 
	# retval: -24($fp) 
entry.10:
	ori 	$t1, $zero, 0 
	sw 	$t1, -24($fp) 
	addiu 	$t1, $zero, 0xfc10 
	lw 	$t1, 0($t1) 
	sw 	$t1, -20($fp) 
	lw 	$t2, -20($fp) 
	ori 	$t1, $zero, -1 
	and 	$t1, $t2, $t1 
	sw 	$t1, -24($fp) 
	lw 	$t2, 4($fp) 
	ori 	$t1, $zero, 0 
	xor 	$t1, $t2, $t1 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.0 
	nop 
	j 	if.end.0 
	nop 
if.then.0:
	lw 	$t2, -20($fp) 
	ori 	$t1, $zero, 8 
	sw 	$t2, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.0 
	nop 
if.end.0:
	lw 	$t2, 4($fp) 
	ori 	$t1, $zero, 1 
	xor 	$t1, $t2, $t1 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.1 
	nop 
	j 	if.end.1 
	nop 
if.then.1:
	lw 	$t2, -20($fp) 
	ori 	$t1, $zero, 15 
	sw 	$t2, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.1 
	nop 
if.end.1:
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 2 
	xor 	$t1, $t1, $t2 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.2 
	nop 
	j 	if.end.2 
	nop 
if.then.2:
	lw 	$t2, -20($fp) 
	ori 	$t1, $zero, 11 
	sw 	$t2, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.2 
	nop 
if.end.2:
	lw 	$t2, 4($fp) 
	ori 	$t1, $zero, 3 
	xor 	$t1, $t2, $t1 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.3 
	nop 
	j 	if.end.3 
	nop 
if.then.3:
	lw 	$t1, -20($fp) 
	ori 	$t2, $zero, 7 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.3 
	nop 
if.end.3:
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 4 
	xor 	$t1, $t1, $t2 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.4 
	nop 
	j 	if.end.4 
	nop 
if.then.4:
	lw 	$t1, -20($fp) 
	ori 	$t2, $zero, 14 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.4 
	nop 
if.end.4:
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 5 
	xor 	$t1, $t1, $t2 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.5 
	nop 
	j 	if.end.5 
	nop 
if.then.5:
	lw 	$t2, -20($fp) 
	ori 	$t1, $zero, 10 
	sw 	$t2, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.5 
	nop 
if.end.5:
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 6 
	xor 	$t1, $t1, $t2 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.6 
	nop 
	j 	if.end.6 
	nop 
if.then.6:
	lw 	$t2, -20($fp) 
	ori 	$t1, $zero, 6 
	sw 	$t2, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.6 
	nop 
if.end.6:
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 7 
	xor 	$t1, $t1, $t2 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.7 
	nop 
	j 	if.end.7 
	nop 
if.then.7:
	lw 	$t2, -20($fp) 
	ori 	$t1, $zero, 13 
	sw 	$t2, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.7 
	nop 
if.end.7:
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 8 
	xor 	$t1, $t1, $t2 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.8 
	nop 
	j 	if.end.8 
	nop 
if.then.8:
	lw 	$t2, -20($fp) 
	ori 	$t1, $zero, 9 
	sw 	$t2, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.8 
	nop 
if.end.8:
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 9 
	xor 	$t1, $t1, $t2 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.9 
	nop 
	j 	if.end.9 
	nop 
if.then.9:
	lw 	$t1, -20($fp) 
	ori 	$t2, $zero, 5 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.9 
	nop 
if.end.9:
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 10 
	xor 	$t1, $t1, $t2 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.10 
	nop 
	j 	if.end.10 
	nop 
if.then.10:
	lw 	$t1, -20($fp) 
	ori 	$t2, $zero, 3 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.10 
	nop 
if.end.10:
	lw 	$t2, 4($fp) 
	ori 	$t1, $zero, 11 
	xor 	$t1, $t2, $t1 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.11 
	nop 
	j 	if.end.11 
	nop 
if.then.11:
	lw 	$t2, -20($fp) 
	ori 	$t1, $zero, 2 
	sw 	$t2, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.11 
	nop 
if.end.11:
	lw 	$t2, 4($fp) 
	ori 	$t1, $zero, 12 
	xor 	$t1, $t2, $t1 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.12 
	nop 
	j 	if.end.12 
	nop 
if.then.12:
	lw 	$t1, -20($fp) 
	ori 	$t2, $zero, 1 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.12 
	nop 
if.end.12:
	lw 	$t2, 4($fp) 
	ori 	$t1, $zero, 13 
	xor 	$t1, $t2, $t1 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.13 
	nop 
	j 	if.end.13 
	nop 
if.then.13:
	lw 	$t2, -20($fp) 
	ori 	$t1, $zero, 0 
	sw 	$t2, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.13 
	nop 
if.end.13:
	lw 	$t1, 4($fp) 
	ori 	$t2, $zero, 14 
	xor 	$t1, $t1, $t2 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.14 
	nop 
	j 	if.end.14 
	nop 
if.then.14:
	lw 	$t2, -20($fp) 
	ori 	$t1, $zero, 12 
	sw 	$t2, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.14 
	nop 
if.end.14:
	lw 	$t2, 4($fp) 
	ori 	$t1, $zero, 15 
	xor 	$t1, $t2, $t1 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.15 
	nop 
	j 	if.end.15 
	nop 
if.then.15:
	lw 	$t1, -20($fp) 
	ori 	$t2, $zero, 4 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function extract begin 
	jal 	extract 
	nop 
	addiu 	$sp, $sp, 8 
	# call function extract end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -24($fp) 
	j 	if.end.15 
	nop 
if.end.15:
	lw 	$t1, -24($fp) 
	sw 	$t1, -16($fp) 
	j 	return.10 
	nop 
return.10:
	lw 	$t1, -16($fp) 
	ori 	$v0, $t1, 0 
	lw 	$ra, 0($fp) 
	lw 	$fp, -4($fp) 
	lw 	$t1, -8($fp) 
	lw 	$t2, -12($fp) 
	ori 	$sp, $fp, 0 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 set_buzzer_freq(kInt32 freq) 
set_buzzer_freq:
	sw 	$fp, 0($sp) 
	sw 	$t1, -4($sp) 
	sw 	$t2, -8($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -20 
	# freq: 4($fp) 
	# retval.11: -12($fp) 
	# cnt: -16($fp) 
entry.11:
	lw 	$t2, 4($fp) 
	ori 	$t1, $zero, 0 
	xor 	$t1, $t2, $t1 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.16 
	nop 
	j 	if.else.16 
	nop 
if.then.16:
	ori 	$t1, $zero, 0 
	sw 	$t1, -16($fp) 
	j 	if.end.16 
	nop 
if.else.16:
	lui 	$t2, 0x140 
	ori 	$t2, $t2, 0 
	lw 	$t1, 4($fp) 
	div 	$t2, $t1 
	mflo 	$t1 
	sw 	$t1, -16($fp) 
	j 	if.end.16 
	nop 
if.end.16:
	addiu 	$t2, $zero, 0xfd10 
	lw 	$t1, -16($fp) 
	sw 	$t1, 0($t2) 
return.11:
	lw 	$t1, -12($fp) 
	ori 	$v0, $t1, 0 
	lw 	$fp, 0($fp) 
	lw 	$t1, -4($fp) 
	lw 	$t2, -8($fp) 
	ori 	$sp, $fp, 0 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 has_keyboard_down(kVoid) 
has_keyboard_down:
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	sw 	$t1, -8($sp) 
	sw 	$t2, -12($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -24 
	# retval.12: -16($fp) 
	# temp: -20($fp) 
entry.12:
	ori 	$t1, $zero, 0xff 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function keyboard_is_pressed begin 
	jal 	keyboard_is_pressed 
	nop 
	addiu 	$sp, $sp, 4 
	# call function keyboard_is_pressed end 
	ori 	$t1, $v0, 0 
	sw 	$t1, -20($fp) 
	lw 	$t1, -20($fp) 
	ori 	$t2, $zero, 0 
	xor 	$t1, $t1, $t2 
	slti 	$t1, $t1, 1 
	bne 	$t1, $zero, if.then.17 
	nop 
	j 	if.else.17 
	nop 
if.then.17:
	ori 	$t1, $zero, 0 
	sw 	$t1, -20($fp) 
	j 	if.end.17 
	nop 
if.else.17:
	ori 	$t1, $zero, 1 
	sw 	$t1, -20($fp) 
	j 	if.end.17 
	nop 
if.end.17:
	lw 	$t1, -20($fp) 
	sw 	$t1, -16($fp) 
	j 	return.12 
	nop 
return.12:
	lw 	$t1, -16($fp) 
	ori 	$v0, $t1, 0 
	lw 	$ra, 0($fp) 
	lw 	$fp, -4($fp) 
	lw 	$t1, -8($fp) 
	lw 	$t2, -12($fp) 
	ori 	$sp, $fp, 0 
	jr 	$ra 
	nop 
	nop 
 
# kInt32 main(kVoid) 
bios_main:
	ori 	$fp, $zero, 0x8000 
	ori 	$sp, $zero, 0x7ff8 
	sw 	$ra, 0($sp) 
	sw 	$fp, -4($sp) 
	sw 	$t1, -8($sp) 
	sw 	$t2, -12($sp) 
	sw 	$t3, -16($sp) 
	sw 	$t4, -20($sp) 
	ori 	$fp, $sp, 0 
	addiu 	$sp, $fp, -28 
	# retval.13: -24($fp) 
entry.13:
	ori 	$t1, $zero, 0x7d0 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_sleep_count begin 
	jal 	set_sleep_count 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_sleep_count end 
	ori 	$t4, $zero, 1 
	ori 	$t3, $zero, 2 
	ori 	$t2, $zero, 3 
	ori 	$t1, $zero, 4 
	sw 	$t4, 0($sp) 
	sw 	$t3, -4($sp) 
	sw 	$t2, -8($sp) 
	sw 	$t1, -12($sp) 
	addiu 	$sp, $sp, -16 
	# call function set_digital_higher_value begin 
	jal 	set_digital_higher_value 
	nop 
	addiu 	$sp, $sp, 16 
	# call function set_digital_higher_value end 
	ori 	$t4, $zero, 5 
	ori 	$t3, $zero, 6 
	ori 	$t2, $zero, 7 
	ori 	$t1, $zero, 8 
	sw 	$t4, 0($sp) 
	sw 	$t3, -4($sp) 
	sw 	$t2, -8($sp) 
	sw 	$t1, -12($sp) 
	addiu 	$sp, $sp, -16 
	# call function set_digital_lower_value begin 
	jal 	set_digital_lower_value 
	nop 
	addiu 	$sp, $sp, 16 
	# call function set_digital_lower_value end 
	ori 	$t1, $zero, 15 
	ori 	$t2, $zero, 15 
	sw 	$t1, 0($sp) 
	sw 	$t2, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function set_digital_status begin 
	jal 	set_digital_status 
	nop 
	addiu 	$sp, $sp, 8 
	# call function set_digital_status end 
	addiu 	$sp, $sp, 0 
	# call function sleep begin 
	jal 	sleep 
	nop 
	addiu 	$sp, $sp, 0 
	# call function sleep end 
	ori 	$t1, $zero, 0xc8 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_buzzer_freq begin 
	jal 	set_buzzer_freq 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_buzzer_freq end 
	addiu 	$sp, $sp, 0 
	# call function sleep begin 
	jal 	sleep 
	nop 
	addiu 	$sp, $sp, 0 
	# call function sleep end 
	ori 	$t1, $zero, 0xfa0 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_buzzer_freq begin 
	jal 	set_buzzer_freq 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_buzzer_freq end 
	addiu 	$sp, $sp, 0 
	# call function sleep begin 
	jal 	sleep 
	nop 
	addiu 	$sp, $sp, 0 
	# call function sleep end 
	ori 	$t1, $zero, 0x3e8 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_buzzer_freq begin 
	jal 	set_buzzer_freq 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_buzzer_freq end 
	addiu 	$sp, $sp, 0 
	# call function sleep begin 
	jal 	sleep 
	nop 
	addiu 	$sp, $sp, 0 
	# call function sleep end 
	ori 	$t1, $zero, 0 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_buzzer_freq begin 
	jal 	set_buzzer_freq 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_buzzer_freq end 
	lui 	$t1, 0x5555 
	ori 	$t1, $t1, 0x5555 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_led_value begin 
	jal 	set_led_value 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_led_value end 
	addiu 	$sp, $sp, 0 
	# call function sleep begin 
	jal 	sleep 
	nop 
	addiu 	$sp, $sp, 0 
	# call function sleep end 
	lui 	$t1, 0xaaaa 
	ori 	$t1, $t1, 0xaaaa 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_led_value begin 
	jal 	set_led_value 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_led_value end 
	addiu 	$sp, $sp, 0 
	# call function sleep begin 
	jal 	sleep 
	nop 
	addiu 	$sp, $sp, 0 
	# call function sleep end 
	addiu 	$t1, $zero, -1 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_led_value begin 
	jal 	set_led_value 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_led_value end 
	addiu 	$sp, $sp, 0 
	# call function sleep begin 
	jal 	sleep 
	nop 
	addiu 	$sp, $sp, 0 
	# call function sleep end 
	ori 	$t1, $zero, 0 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_led_value begin 
	jal 	set_led_value 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_led_value end 
while.cond.1:
	addiu 	$sp, $sp, 0 
	# call function has_keyboard_down begin 
	jal 	has_keyboard_down 
	nop 
	addiu 	$sp, $sp, 0 
	# call function has_keyboard_down end 
	ori 	$t2, $v0, 0 
	ori 	$t1, $zero, 1 
	xor 	$t1, $t2, $t1 
	sltiu 	$t1, $t1, 1 
	sltiu 	$t1, $t1, 1 
	bne 	$t1, $zero, while.body.1 
	nop 
	j 	while.end.1 
	nop 
while.body.1:
	addiu 	$sp, $sp, 0 
	# call function sleep begin 
	jal 	sleep 
	nop 
	addiu 	$sp, $sp, 0 
	# call function sleep end 
	lui 	$t1, 0xaaaa 
	ori 	$t1, $t1, 0xaaaa 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_led_value begin 
	jal 	set_led_value 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_led_value end 
	addiu 	$sp, $sp, 0 
	# call function sleep begin 
	jal 	sleep 
	nop 
	addiu 	$sp, $sp, 0 
	# call function sleep end 
	lui 	$t1, 0x5555 
	ori 	$t1, $t1, 0x5555 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_led_value begin 
	jal 	set_led_value 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_led_value end 
	j 	while.cond.1 
	nop 
while.end.1:
	ori 	$t1, $zero, 0 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_led_value begin 
	jal 	set_led_value 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_led_value end 
	ori 	$t1, $zero, 0 
	ori 	$t3, $zero, 0 
	ori 	$t4, $zero, 0 
	ori 	$t2, $zero, 0 
	sw 	$t1, 0($sp) 
	sw 	$t3, -4($sp) 
	sw 	$t4, -8($sp) 
	sw 	$t2, -12($sp) 
	addiu 	$sp, $sp, -16 
	# call function set_digital_lower_value begin 
	jal 	set_digital_lower_value 
	nop 
	addiu 	$sp, $sp, 16 
	# call function set_digital_lower_value end 
	ori 	$t2, $zero, 0 
	ori 	$t4, $zero, 0 
	ori 	$t3, $zero, 0 
	ori 	$t1, $zero, 0 
	sw 	$t2, 0($sp) 
	sw 	$t4, -4($sp) 
	sw 	$t3, -8($sp) 
	sw 	$t1, -12($sp) 
	addiu 	$sp, $sp, -16 
	# call function set_digital_higher_value begin 
	jal 	set_digital_higher_value 
	nop 
	addiu 	$sp, $sp, 16 
	# call function set_digital_higher_value end 
	ori 	$t1, $zero, 0x3e8 
	sw 	$t1, 0($sp) 
	addiu 	$sp, $sp, -4 
	# call function set_sleep_count begin 
	jal 	set_sleep_count 
	nop 
	addiu 	$sp, $sp, 4 
	# call function set_sleep_count end 
	addiu 	$sp, $sp, 0 
	# call function sleep begin 
	jal 	sleep 
	nop 
	addiu 	$sp, $sp, 0 
	# call function sleep end 
	ori 	$t2, $zero, 0 
	ori 	$t1, $zero, 0 
	sw 	$t2, 0($sp) 
	sw 	$t1, -4($sp) 
	addiu 	$sp, $sp, -8 
	# call function set_digital_status begin 
	jal 	set_digital_status 
	nop 
	addiu 	$sp, $sp, 8 
	# call function set_digital_status end 
	ori 	$t1, $zero, 0 
	sw 	$t1, -24($fp) 
	j 	return.13 
	nop 
return.13:
	lw 	$t1, -24($fp) 
	ori 	$v0, $t1, 0 
	lw 	$ra, 0($fp) 
	lw 	$fp, -4($fp) 
	lw 	$t1, -8($fp) 
	lw 	$t2, -12($fp) 
	lw 	$t3, -16($fp) 
	lw 	$t4, -20($fp) 
	ori 	$sp, $fp, 0 
	nop 
	nop 


user_program_begin:
 	nop
  	# call function sleep begin 
	jal 	sleep 
	nop 
	addiu 	$sp, $sp, 0 
	# call function sleep end 
	nop
	nop
	nop
	j user_program_begin
	nop
	nop
