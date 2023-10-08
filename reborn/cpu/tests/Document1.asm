.data
  led: .word 0xFFFFFC60
  digits: .word 0xFFFFFC00
  maxui: .word 0xFFFFFFFF
  beep: .word 0xFFFFFD10
  switch: .word 0xFFFFFC70
  enable_led: .word 0xFFFFFFFF
  kbd: .word 0xFFFFFC10

.text

sleep1s:
  addiu $t7, $0, 0
  lui $t7, 0xff5f
sleep1sloop:
  addiu $t7, $t7, 1
  bgez $t7, sleep1sloop
sleep1sdone:
  jr $ra


start:
  jal sleep1s
  addiu $t1, $t1, 1
  lw $t0, led($0)
  sw $t1, 0($t0)
  j start
  nop

done:
  nop
