.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
li      $v0, 4
la      $a0, _prompt
syscall
li      $v0, 5
syscall
jr      $ra

write:
li      $v0, 1
syscall
li      $v0, 4
la      $a0, _ret
syscall
move    $v0, $0
jr      $ra

mod:
addi    $sp, $sp, -40
sw      $ra, 36($sp)
sw      $fp, 32($sp)
addi    $fp, $sp, 40
lw      $t0, -12($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -12($fp)
lw      $t0, -16($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -16($fp)
lw      $t0, -20($fp)
lw      $t1, 4($fp)
move    $t0, $t1
sw      $t0, -20($fp)
lw      $t0, -24($fp)
lw      $t1, -16($fp)
lw      $t2, -20($fp)
div     $t1, $t2
mflo    $t0
sw      $t0, -24($fp)
lw      $t0, -28($fp)
lw      $t1, -24($fp)
move    $t0, $t1
sw      $t0, -28($fp)
lw      $t0, -32($fp)
lw      $t1, 4($fp)
move    $t0, $t1
sw      $t0, -32($fp)
lw      $t0, -36($fp)
lw      $t1, -28($fp)
lw      $t2, -32($fp)
mul     $t0, $t1, $t2
sw      $t0, -36($fp)
lw      $t0, -40($fp)
lw      $t1, -12($fp)
lw      $t2, -36($fp)
sub     $t0, $t1, $t2
sw      $t0, -40($fp)
lw      $t0, -40($fp)
move    $v0, $t0
lw      $ra, 36($sp)
lw      $fp, 32($sp)
addi    $sp, $sp, 40
jr      $ra

IsLeap:
addi    $sp, $sp, -88
sw      $ra, 84($sp)
sw      $fp, 80($sp)
addi    $fp, $sp, 88
lw      $t0, -12($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -12($fp)
lw      $t0, -16($fp)
li      $t1, 400
move    $t0, $t1
sw      $t0, -16($fp)
lw      $t0, -16($fp)
sw      $t0, 4($sp)
lw      $t0, -12($fp)
sw      $t0, 0($sp)
jal     mod
lw      $t0, -20($fp)
move    $t0, $v0
sw      $t0, -20($fp)
lw      $t0, -24($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -24($fp)
lw      $t0, -20($fp)
lw      $t1, -24($fp)
beq     $t0, $t1, label3
j       label4
label4:
lw      $t0, -28($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -28($fp)
lw      $t0, -32($fp)
li      $t1, 4
move    $t0, $t1
sw      $t0, -32($fp)
lw      $t0, -32($fp)
sw      $t0, 4($sp)
lw      $t0, -28($fp)
sw      $t0, 0($sp)
jal     mod
lw      $t0, -36($fp)
move    $t0, $v0
sw      $t0, -36($fp)
lw      $t0, -40($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -40($fp)
lw      $t0, -36($fp)
lw      $t1, -40($fp)
beq     $t0, $t1, label3
j       label1
label3:
lw      $t0, -44($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -44($fp)
lw      $t0, -48($fp)
li      $t1, 100
move    $t0, $t1
sw      $t0, -48($fp)
lw      $t0, -48($fp)
sw      $t0, 4($sp)
lw      $t0, -44($fp)
sw      $t0, 0($sp)
jal     mod
lw      $t0, -52($fp)
move    $t0, $v0
sw      $t0, -52($fp)
lw      $t0, -56($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -56($fp)
lw      $t0, -52($fp)
lw      $t1, -56($fp)
bne     $t0, $t1, label0
j       label1
label0:
lw      $t0, -60($fp)
li      $t1, 1
move    $t0, $t1
sw      $t0, -60($fp)
lw      $t0, -60($fp)
move    $v0, $t0
lw      $ra, 84($sp)
lw      $fp, 80($sp)
addi    $sp, $sp, 88
jr      $ra
j       label2
label1:
lw      $t0, -64($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -64($fp)
lw      $t0, -64($fp)
move    $v0, $t0
lw      $ra, 84($sp)
lw      $fp, 80($sp)
addi    $sp, $sp, 88
jr      $ra
label2:

main:
addi    $sp, $sp, -360
sw      $ra, 356($sp)
sw      $fp, 352($sp)
addi    $fp, $sp, 360
lw      $t0, -12($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -12($fp)
lw      $t0, -16($fp)
lw      $t1, -12($fp)
move    $t0, $t1
sw      $t0, -16($fp)
lw      $t0, -20($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -20($fp)
lw      $t0, -24($fp)
lw      $t1, -20($fp)
move    $t0, $t1
sw      $t0, -24($fp)
lw      $t0, -48($fp)
addi    $t1, $fp, -44
move    $t0, $t1
sw      $t0, -48($fp)
lw      $t0, -52($fp)
lw      $t1, -48($fp)
move    $t0, $t1
sw      $t0, -52($fp)
lw      $t0, -56($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -56($fp)
lw      $t0, -60($fp)
lw      $t1, -56($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -60($fp)
lw      $t0, -64($fp)
lw      $t1, -52($fp)
lw      $t2, -60($fp)
add     $t0, $t1, $t2
sw      $t0, -64($fp)
lw      $t0, -68($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -68($fp)
lw      $t0, -64($fp)
lw      $t1, -68($fp)
sw      $t1, 0($t0)
lw      $t0, -76($fp)
lw      $t1, -48($fp)
move    $t0, $t1
sw      $t0, -76($fp)
lw      $t0, -80($fp)
li      $t1, 1
move    $t0, $t1
sw      $t0, -80($fp)
lw      $t0, -84($fp)
lw      $t1, -80($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -84($fp)
lw      $t0, -88($fp)
lw      $t1, -76($fp)
lw      $t2, -84($fp)
add     $t0, $t1, $t2
sw      $t0, -88($fp)
lw      $t0, -92($fp)
li      $t1, 31
move    $t0, $t1
sw      $t0, -92($fp)
lw      $t0, -88($fp)
lw      $t1, -92($fp)
sw      $t1, 0($t0)
lw      $t0, -96($fp)
lw      $t1, -48($fp)
move    $t0, $t1
sw      $t0, -96($fp)
lw      $t0, -100($fp)
li      $t1, 2
move    $t0, $t1
sw      $t0, -100($fp)
lw      $t0, -104($fp)
lw      $t1, -100($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -104($fp)
lw      $t0, -108($fp)
lw      $t1, -96($fp)
lw      $t2, -104($fp)
add     $t0, $t1, $t2
sw      $t0, -108($fp)
lw      $t0, -112($fp)
li      $t1, 28
move    $t0, $t1
sw      $t0, -112($fp)
lw      $t0, -108($fp)
lw      $t1, -112($fp)
sw      $t1, 0($t0)
lw      $t0, -116($fp)
lw      $t1, -48($fp)
move    $t0, $t1
sw      $t0, -116($fp)
lw      $t0, -120($fp)
li      $t1, 3
move    $t0, $t1
sw      $t0, -120($fp)
lw      $t0, -124($fp)
lw      $t1, -120($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -124($fp)
lw      $t0, -128($fp)
lw      $t1, -116($fp)
lw      $t2, -124($fp)
add     $t0, $t1, $t2
sw      $t0, -128($fp)
lw      $t0, -132($fp)
li      $t1, 31
move    $t0, $t1
sw      $t0, -132($fp)
lw      $t0, -128($fp)
lw      $t1, -132($fp)
sw      $t1, 0($t0)
lw      $t0, -136($fp)
lw      $t1, -48($fp)
move    $t0, $t1
sw      $t0, -136($fp)
lw      $t0, -140($fp)
li      $t1, 4
move    $t0, $t1
sw      $t0, -140($fp)
lw      $t0, -144($fp)
lw      $t1, -140($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -144($fp)
lw      $t0, -148($fp)
lw      $t1, -136($fp)
lw      $t2, -144($fp)
add     $t0, $t1, $t2
sw      $t0, -148($fp)
lw      $t0, -152($fp)
li      $t1, 30
move    $t0, $t1
sw      $t0, -152($fp)
lw      $t0, -148($fp)
lw      $t1, -152($fp)
sw      $t1, 0($t0)
jal     read
lw      $t0, -156($fp)
move    $t0, $v0
sw      $t0, -156($fp)
lw      $t0, -160($fp)
lw      $t1, -156($fp)
move    $t0, $t1
sw      $t0, -160($fp)
lw      $t0, -164($fp)
li      $t1, 1900
move    $t0, $t1
sw      $t0, -164($fp)
lw      $t0, -168($fp)
lw      $t1, -164($fp)
move    $t0, $t1
sw      $t0, -168($fp)
label5:
lw      $t0, -172($fp)
lw      $t1, -168($fp)
move    $t0, $t1
sw      $t0, -172($fp)
lw      $t0, -176($fp)
lw      $t1, -160($fp)
move    $t0, $t1
sw      $t0, -176($fp)
lw      $t0, -172($fp)
lw      $t1, -176($fp)
blt     $t0, $t1, label6
j       label7
label6:
lw      $t0, -180($fp)
lw      $t1, -168($fp)
move    $t0, $t1
sw      $t0, -180($fp)
lw      $t0, -180($fp)
sw      $t0, 0($sp)
jal     IsLeap
lw      $t0, -184($fp)
move    $t0, $v0
sw      $t0, -184($fp)
lw      $t0, -184($fp)
li      $t1, 0
bne     $t0, $t1, label8
j       label9
label8:
lw      $t0, -188($fp)
lw      $t1, -16($fp)
move    $t0, $t1
sw      $t0, -188($fp)
lw      $t0, -192($fp)
li      $t1, 366
move    $t0, $t1
sw      $t0, -192($fp)
lw      $t0, -196($fp)
lw      $t1, -188($fp)
lw      $t2, -192($fp)
add     $t0, $t1, $t2
sw      $t0, -196($fp)
lw      $t0, -16($fp)
lw      $t1, -196($fp)
move    $t0, $t1
sw      $t0, -16($fp)
j       label10
label9:
lw      $t0, -200($fp)
lw      $t1, -16($fp)
move    $t0, $t1
sw      $t0, -200($fp)
lw      $t0, -204($fp)
li      $t1, 365
move    $t0, $t1
sw      $t0, -204($fp)
lw      $t0, -208($fp)
lw      $t1, -200($fp)
lw      $t2, -204($fp)
add     $t0, $t1, $t2
sw      $t0, -208($fp)
lw      $t0, -16($fp)
lw      $t1, -208($fp)
move    $t0, $t1
sw      $t0, -16($fp)
label10:
lw      $t0, -212($fp)
lw      $t1, -168($fp)
move    $t0, $t1
sw      $t0, -212($fp)
lw      $t0, -216($fp)
li      $t1, 1
move    $t0, $t1
sw      $t0, -216($fp)
lw      $t0, -220($fp)
lw      $t1, -212($fp)
lw      $t2, -216($fp)
add     $t0, $t1, $t2
sw      $t0, -220($fp)
lw      $t0, -168($fp)
lw      $t1, -220($fp)
move    $t0, $t1
sw      $t0, -168($fp)
j       label5
label7:
lw      $t0, -224($fp)
lw      $t1, -160($fp)
move    $t0, $t1
sw      $t0, -224($fp)
lw      $t0, -224($fp)
sw      $t0, 0($sp)
jal     IsLeap
lw      $t0, -228($fp)
move    $t0, $v0
sw      $t0, -228($fp)
lw      $t0, -228($fp)
li      $t1, 0
bne     $t0, $t1, label11
j       label12
label11:
lw      $t0, -232($fp)
lw      $t1, -48($fp)
move    $t0, $t1
sw      $t0, -232($fp)
lw      $t0, -236($fp)
li      $t1, 2
move    $t0, $t1
sw      $t0, -236($fp)
lw      $t0, -240($fp)
lw      $t1, -236($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -240($fp)
lw      $t0, -244($fp)
lw      $t1, -232($fp)
lw      $t2, -240($fp)
add     $t0, $t1, $t2
sw      $t0, -244($fp)
lw      $t0, -248($fp)
li      $t1, 29
move    $t0, $t1
sw      $t0, -248($fp)
lw      $t0, -244($fp)
lw      $t1, -248($fp)
sw      $t1, 0($t0)
label12:
lw      $t0, -252($fp)
li      $t1, 1
move    $t0, $t1
sw      $t0, -252($fp)
lw      $t0, -168($fp)
lw      $t1, -252($fp)
move    $t0, $t1
sw      $t0, -168($fp)
label14:
lw      $t0, -256($fp)
lw      $t1, -168($fp)
move    $t0, $t1
sw      $t0, -256($fp)
lw      $t0, -260($fp)
li      $t1, 5
move    $t0, $t1
sw      $t0, -260($fp)
lw      $t0, -256($fp)
lw      $t1, -260($fp)
blt     $t0, $t1, label15
j       label16
label15:
lw      $t0, -264($fp)
lw      $t1, -16($fp)
move    $t0, $t1
sw      $t0, -264($fp)
lw      $t0, -268($fp)
lw      $t1, -48($fp)
move    $t0, $t1
sw      $t0, -268($fp)
lw      $t0, -272($fp)
lw      $t1, -168($fp)
move    $t0, $t1
sw      $t0, -272($fp)
lw      $t0, -276($fp)
lw      $t1, -272($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -276($fp)
lw      $t0, -280($fp)
lw      $t1, -268($fp)
lw      $t2, -276($fp)
add     $t0, $t1, $t2
sw      $t0, -280($fp)
lw      $t0, -284($fp)
lw      $t1, -280($fp)
lw      $t1, 0($t1)
move    $t0, $t1
sw      $t0, -284($fp)
lw      $t0, -288($fp)
lw      $t1, -264($fp)
lw      $t2, -284($fp)
add     $t0, $t1, $t2
sw      $t0, -288($fp)
lw      $t0, -16($fp)
lw      $t1, -288($fp)
move    $t0, $t1
sw      $t0, -16($fp)
lw      $t0, -292($fp)
lw      $t1, -168($fp)
move    $t0, $t1
sw      $t0, -292($fp)
lw      $t0, -296($fp)
li      $t1, 1
move    $t0, $t1
sw      $t0, -296($fp)
lw      $t0, -300($fp)
lw      $t1, -292($fp)
lw      $t2, -296($fp)
add     $t0, $t1, $t2
sw      $t0, -300($fp)
lw      $t0, -168($fp)
lw      $t1, -300($fp)
move    $t0, $t1
sw      $t0, -168($fp)
j       label14
label16:
lw      $t0, -304($fp)
lw      $t1, -16($fp)
move    $t0, $t1
sw      $t0, -304($fp)
lw      $t0, -308($fp)
li      $t1, 7
move    $t0, $t1
sw      $t0, -308($fp)
lw      $t0, -308($fp)
sw      $t0, 4($sp)
lw      $t0, -304($fp)
sw      $t0, 0($sp)
jal     mod
lw      $t0, -312($fp)
move    $t0, $v0
sw      $t0, -312($fp)
lw      $t0, -316($fp)
lw      $t1, -312($fp)
move    $t0, $t1
sw      $t0, -316($fp)
lw      $t0, -320($fp)
li      $t1, 14
move    $t0, $t1
sw      $t0, -320($fp)
lw      $t0, -324($fp)
lw      $t1, -316($fp)
move    $t0, $t1
sw      $t0, -324($fp)
lw      $t0, -328($fp)
lw      $t1, -320($fp)
lw      $t2, -324($fp)
sub     $t0, $t1, $t2
sw      $t0, -328($fp)
lw      $t0, -332($fp)
lw      $t1, -328($fp)
move    $t0, $t1
sw      $t0, -332($fp)
lw      $t0, -336($fp)
li      $t1, 5
move    $t0, $t1
sw      $t0, -336($fp)
lw      $t0, -336($fp)
move    $a0, $t0
jal     write
lw      $t0, -340($fp)
lw      $t1, -332($fp)
move    $t0, $t1
sw      $t0, -340($fp)
lw      $t0, -340($fp)
move    $a0, $t0
jal     write
lw      $t0, -344($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -344($fp)
lw      $t0, -344($fp)
move    $v0, $t0
lw      $ra, 356($sp)
lw      $fp, 352($sp)
addi    $sp, $sp, 360
jr      $ra

