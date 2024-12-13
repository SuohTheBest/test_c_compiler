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

bit_and:
addi    $sp, $sp, -24
sw      $ra, 20($sp)
sw      $fp, 16($sp)
addi    $fp, $sp, 24
lw      $t0, -12($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -12($fp)
lw      $t0, -16($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -16($fp)
lw      $t0, -12($fp)
lw      $t1, -16($fp)
beq     $t0, $t1, label0
j       label1
label0:
lw      $t0, -20($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -20($fp)
lw      $t0, -20($fp)
move    $v0, $t0
lw      $ra, 20($sp)
lw      $fp, 16($sp)
addi    $sp, $sp, 24
jr      $ra
j       label2
label1:
lw      $t0, -24($fp)
lw      $t1, 4($fp)
move    $t0, $t1
sw      $t0, -24($fp)
lw      $t0, -24($fp)
move    $v0, $t0
lw      $ra, 20($sp)
lw      $fp, 16($sp)
addi    $sp, $sp, 24
jr      $ra
label2:

bit_or:
addi    $sp, $sp, -24
sw      $ra, 20($sp)
sw      $fp, 16($sp)
addi    $fp, $sp, 24
lw      $t0, -12($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -12($fp)
lw      $t0, -16($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -16($fp)
lw      $t0, -12($fp)
lw      $t1, -16($fp)
beq     $t0, $t1, label3
j       label4
label3:
lw      $t0, -20($fp)
lw      $t1, 4($fp)
move    $t0, $t1
sw      $t0, -20($fp)
lw      $t0, -20($fp)
move    $v0, $t0
lw      $ra, 20($sp)
lw      $fp, 16($sp)
addi    $sp, $sp, 24
jr      $ra
j       label5
label4:
lw      $t0, -24($fp)
li      $t1, 1
move    $t0, $t1
sw      $t0, -24($fp)
lw      $t0, -24($fp)
move    $v0, $t0
lw      $ra, 20($sp)
lw      $fp, 16($sp)
addi    $sp, $sp, 24
jr      $ra
label5:

bit_not:
addi    $sp, $sp, -24
sw      $ra, 20($sp)
sw      $fp, 16($sp)
addi    $fp, $sp, 24
lw      $t0, -12($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -12($fp)
lw      $t0, -16($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -16($fp)
lw      $t0, -12($fp)
lw      $t1, -16($fp)
beq     $t0, $t1, label6
j       label7
label6:
lw      $t0, -20($fp)
li      $t1, 1
move    $t0, $t1
sw      $t0, -20($fp)
lw      $t0, -20($fp)
move    $v0, $t0
lw      $ra, 20($sp)
lw      $fp, 16($sp)
addi    $sp, $sp, 24
jr      $ra
j       label8
label7:
lw      $t0, -24($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -24($fp)
lw      $t0, -24($fp)
move    $v0, $t0
lw      $ra, 20($sp)
lw      $fp, 16($sp)
addi    $sp, $sp, 24
jr      $ra
label8:

mod:
addi    $sp, $sp, -36
sw      $ra, 32($sp)
sw      $fp, 28($sp)
addi    $fp, $sp, 36
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
lw      $t1, 4($fp)
move    $t0, $t1
sw      $t0, -28($fp)
lw      $t0, -32($fp)
lw      $t1, -24($fp)
lw      $t2, -28($fp)
mul     $t0, $t1, $t2
sw      $t0, -32($fp)
lw      $t0, -36($fp)
lw      $t1, -12($fp)
lw      $t2, -32($fp)
sub     $t0, $t1, $t2
sw      $t0, -36($fp)
lw      $t0, -36($fp)
move    $v0, $t0
lw      $ra, 32($sp)
lw      $fp, 28($sp)
addi    $sp, $sp, 36
jr      $ra

and:
addi    $sp, $sp, -824
sw      $ra, 820($sp)
sw      $fp, 816($sp)
addi    $fp, $sp, 824
lw      $t0, -12($fp)
li      $t1, 32
move    $t0, $t1
sw      $t0, -12($fp)
lw      $t0, -16($fp)
lw      $t1, -12($fp)
move    $t0, $t1
sw      $t0, -16($fp)
lw      $t0, -148($fp)
addi    $t1, $fp, -144
move    $t0, $t1
sw      $t0, -148($fp)
lw      $t0, -280($fp)
addi    $t1, $fp, -276
move    $t0, $t1
sw      $t0, -280($fp)
lw      $t0, -412($fp)
addi    $t1, $fp, -408
move    $t0, $t1
sw      $t0, -412($fp)
lw      $t0, -416($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -416($fp)
lw      $t0, -420($fp)
lw      $t1, -416($fp)
move    $t0, $t1
sw      $t0, -420($fp)
lw      $t0, -424($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -424($fp)
lw      $t0, -428($fp)
lw      $t1, -424($fp)
move    $t0, $t1
sw      $t0, -428($fp)
lw      $t0, -432($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -432($fp)
lw      $t0, -436($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -436($fp)
lw      $t0, -432($fp)
lw      $t1, -436($fp)
ble     $t0, $t1, label9
j       label12
label12:
lw      $t0, -440($fp)
lw      $t1, 4($fp)
move    $t0, $t1
sw      $t0, -440($fp)
lw      $t0, -444($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -444($fp)
lw      $t0, -440($fp)
lw      $t1, -444($fp)
ble     $t0, $t1, label9
j       label10
label9:
lw      $t0, -448($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -448($fp)
lw      $t0, -448($fp)
move    $v0, $t0
lw      $ra, 820($sp)
lw      $fp, 816($sp)
addi    $sp, $sp, 824
jr      $ra
label10:
label13:
lw      $t0, -452($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -452($fp)
lw      $t0, -456($fp)
lw      $t1, -16($fp)
move    $t0, $t1
sw      $t0, -456($fp)
lw      $t0, -452($fp)
lw      $t1, -456($fp)
blt     $t0, $t1, label14
j       label15
label14:
lw      $t0, -460($fp)
lw      $t1, -148($fp)
move    $t0, $t1
sw      $t0, -460($fp)
lw      $t0, -464($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -464($fp)
lw      $t0, -468($fp)
lw      $t1, -464($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -468($fp)
lw      $t0, -472($fp)
lw      $t1, -460($fp)
lw      $t2, -468($fp)
add     $t0, $t1, $t2
sw      $t0, -472($fp)
lw      $t0, -476($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -476($fp)
lw      $t0, -472($fp)
lw      $t1, -476($fp)
sw      $t1, 0($t0)
lw      $t0, -484($fp)
lw      $t1, -280($fp)
move    $t0, $t1
sw      $t0, -484($fp)
lw      $t0, -488($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -488($fp)
lw      $t0, -492($fp)
lw      $t1, -488($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -492($fp)
lw      $t0, -496($fp)
lw      $t1, -484($fp)
lw      $t2, -492($fp)
add     $t0, $t1, $t2
sw      $t0, -496($fp)
lw      $t0, -500($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -500($fp)
lw      $t0, -496($fp)
lw      $t1, -500($fp)
sw      $t1, 0($t0)
lw      $t0, -504($fp)
lw      $t1, -412($fp)
move    $t0, $t1
sw      $t0, -504($fp)
lw      $t0, -508($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -508($fp)
lw      $t0, -512($fp)
lw      $t1, -508($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -512($fp)
lw      $t0, -516($fp)
lw      $t1, -504($fp)
lw      $t2, -512($fp)
add     $t0, $t1, $t2
sw      $t0, -516($fp)
lw      $t0, -520($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -520($fp)
lw      $t0, -516($fp)
lw      $t1, -520($fp)
sw      $t1, 0($t0)
lw      $t0, -524($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -524($fp)
lw      $t0, -528($fp)
li      $t1, 1
move    $t0, $t1
sw      $t0, -528($fp)
lw      $t0, -532($fp)
lw      $t1, -524($fp)
lw      $t2, -528($fp)
add     $t0, $t1, $t2
sw      $t0, -532($fp)
lw      $t0, -420($fp)
lw      $t1, -532($fp)
move    $t0, $t1
sw      $t0, -420($fp)
j       label13
label15:
lw      $t0, -536($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -536($fp)
lw      $t0, -420($fp)
lw      $t1, -536($fp)
move    $t0, $t1
sw      $t0, -420($fp)
label16:
lw      $t0, -540($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -540($fp)
lw      $t0, -544($fp)
lw      $t1, -16($fp)
move    $t0, $t1
sw      $t0, -544($fp)
lw      $t0, -540($fp)
lw      $t1, -544($fp)
blt     $t0, $t1, label17
j       label18
label17:
lw      $t0, -548($fp)
lw      $t1, -148($fp)
move    $t0, $t1
sw      $t0, -548($fp)
lw      $t0, -552($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -552($fp)
lw      $t0, -556($fp)
lw      $t1, -552($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -556($fp)
lw      $t0, -560($fp)
lw      $t1, -548($fp)
lw      $t2, -556($fp)
add     $t0, $t1, $t2
sw      $t0, -560($fp)
lw      $t0, -564($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -564($fp)
lw      $t0, -568($fp)
li      $t1, 2
move    $t0, $t1
sw      $t0, -568($fp)
lw      $t0, -568($fp)
sw      $t0, 4($sp)
lw      $t0, -564($fp)
sw      $t0, 0($sp)
jal     mod
lw      $t0, -572($fp)
move    $t0, $v0
sw      $t0, -572($fp)
lw      $t0, -560($fp)
lw      $t1, -572($fp)
sw      $t1, 0($t0)
lw      $t0, -576($fp)
lw      $t1, -280($fp)
move    $t0, $t1
sw      $t0, -576($fp)
lw      $t0, -580($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -580($fp)
lw      $t0, -584($fp)
lw      $t1, -580($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -584($fp)
lw      $t0, -588($fp)
lw      $t1, -576($fp)
lw      $t2, -584($fp)
add     $t0, $t1, $t2
sw      $t0, -588($fp)
lw      $t0, -592($fp)
lw      $t1, 4($fp)
move    $t0, $t1
sw      $t0, -592($fp)
lw      $t0, -596($fp)
li      $t1, 2
move    $t0, $t1
sw      $t0, -596($fp)
lw      $t0, -596($fp)
sw      $t0, 4($sp)
lw      $t0, -592($fp)
sw      $t0, 0($sp)
jal     mod
lw      $t0, -600($fp)
move    $t0, $v0
sw      $t0, -600($fp)
lw      $t0, -588($fp)
lw      $t1, -600($fp)
sw      $t1, 0($t0)
lw      $t0, -604($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -604($fp)
lw      $t0, -608($fp)
li      $t1, 2
move    $t0, $t1
sw      $t0, -608($fp)
lw      $t0, -612($fp)
lw      $t1, -604($fp)
lw      $t2, -608($fp)
div     $t1, $t2
mflo    $t0
sw      $t0, -612($fp)
lw      $t0, 0($fp)
lw      $t1, -612($fp)
move    $t0, $t1
sw      $t0, 0($fp)
lw      $t0, -620($fp)
lw      $t1, 4($fp)
move    $t0, $t1
sw      $t0, -620($fp)
lw      $t0, -624($fp)
li      $t1, 2
move    $t0, $t1
sw      $t0, -624($fp)
lw      $t0, -628($fp)
lw      $t1, -620($fp)
lw      $t2, -624($fp)
div     $t1, $t2
mflo    $t0
sw      $t0, -628($fp)
lw      $t0, 4($fp)
lw      $t1, -628($fp)
move    $t0, $t1
sw      $t0, 4($fp)
lw      $t0, -636($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -636($fp)
lw      $t0, -640($fp)
li      $t1, 1
move    $t0, $t1
sw      $t0, -640($fp)
lw      $t0, -644($fp)
lw      $t1, -636($fp)
lw      $t2, -640($fp)
add     $t0, $t1, $t2
sw      $t0, -644($fp)
lw      $t0, -420($fp)
lw      $t1, -644($fp)
move    $t0, $t1
sw      $t0, -420($fp)
j       label16
label18:
lw      $t0, -648($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -648($fp)
lw      $t0, -420($fp)
lw      $t1, -648($fp)
move    $t0, $t1
sw      $t0, -420($fp)
label19:
lw      $t0, -652($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -652($fp)
lw      $t0, -656($fp)
lw      $t1, -16($fp)
move    $t0, $t1
sw      $t0, -656($fp)
lw      $t0, -652($fp)
lw      $t1, -656($fp)
blt     $t0, $t1, label20
j       label21
label20:
lw      $t0, -660($fp)
lw      $t1, -412($fp)
move    $t0, $t1
sw      $t0, -660($fp)
lw      $t0, -664($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -664($fp)
lw      $t0, -668($fp)
lw      $t1, -664($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -668($fp)
lw      $t0, -672($fp)
lw      $t1, -660($fp)
lw      $t2, -668($fp)
add     $t0, $t1, $t2
sw      $t0, -672($fp)
lw      $t0, -676($fp)
lw      $t1, -148($fp)
move    $t0, $t1
sw      $t0, -676($fp)
lw      $t0, -680($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -680($fp)
lw      $t0, -684($fp)
lw      $t1, -680($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -684($fp)
lw      $t0, -688($fp)
lw      $t1, -676($fp)
lw      $t2, -684($fp)
add     $t0, $t1, $t2
sw      $t0, -688($fp)
lw      $t0, -692($fp)
lw      $t1, -688($fp)
lw      $t1, 0($t1)
move    $t0, $t1
sw      $t0, -692($fp)
lw      $t0, -696($fp)
lw      $t1, -280($fp)
move    $t0, $t1
sw      $t0, -696($fp)
lw      $t0, -700($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -700($fp)
lw      $t0, -704($fp)
lw      $t1, -700($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -704($fp)
lw      $t0, -708($fp)
lw      $t1, -696($fp)
lw      $t2, -704($fp)
add     $t0, $t1, $t2
sw      $t0, -708($fp)
lw      $t0, -712($fp)
lw      $t1, -708($fp)
lw      $t1, 0($t1)
move    $t0, $t1
sw      $t0, -712($fp)
lw      $t0, -712($fp)
sw      $t0, 4($sp)
lw      $t0, -692($fp)
sw      $t0, 0($sp)
jal     bit_and
lw      $t0, -716($fp)
move    $t0, $v0
sw      $t0, -716($fp)
lw      $t0, -672($fp)
lw      $t1, -716($fp)
sw      $t1, 0($t0)
lw      $t0, -720($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -720($fp)
lw      $t0, -724($fp)
li      $t1, 1
move    $t0, $t1
sw      $t0, -724($fp)
lw      $t0, -728($fp)
lw      $t1, -720($fp)
lw      $t2, -724($fp)
add     $t0, $t1, $t2
sw      $t0, -728($fp)
lw      $t0, -420($fp)
lw      $t1, -728($fp)
move    $t0, $t1
sw      $t0, -420($fp)
j       label19
label21:
lw      $t0, -732($fp)
lw      $t1, -16($fp)
move    $t0, $t1
sw      $t0, -732($fp)
lw      $t0, -736($fp)
li      $t1, 1
move    $t0, $t1
sw      $t0, -736($fp)
lw      $t0, -740($fp)
lw      $t1, -732($fp)
lw      $t2, -736($fp)
sub     $t0, $t1, $t2
sw      $t0, -740($fp)
lw      $t0, -420($fp)
lw      $t1, -740($fp)
move    $t0, $t1
sw      $t0, -420($fp)
label22:
lw      $t0, -744($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -744($fp)
lw      $t0, -748($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -748($fp)
lw      $t0, -744($fp)
lw      $t1, -748($fp)
bge     $t0, $t1, label23
j       label24
label23:
lw      $t0, -752($fp)
lw      $t1, -428($fp)
move    $t0, $t1
sw      $t0, -752($fp)
lw      $t0, -756($fp)
li      $t1, 2
move    $t0, $t1
sw      $t0, -756($fp)
lw      $t0, -760($fp)
lw      $t1, -752($fp)
lw      $t2, -756($fp)
mul     $t0, $t1, $t2
sw      $t0, -760($fp)
lw      $t0, -764($fp)
lw      $t1, -412($fp)
move    $t0, $t1
sw      $t0, -764($fp)
lw      $t0, -768($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -768($fp)
lw      $t0, -772($fp)
lw      $t1, -768($fp)
li      $t2, 4
mul     $t0, $t1, $t2
sw      $t0, -772($fp)
lw      $t0, -776($fp)
lw      $t1, -764($fp)
lw      $t2, -772($fp)
add     $t0, $t1, $t2
sw      $t0, -776($fp)
lw      $t0, -780($fp)
lw      $t1, -776($fp)
lw      $t1, 0($t1)
move    $t0, $t1
sw      $t0, -780($fp)
lw      $t0, -784($fp)
lw      $t1, -760($fp)
lw      $t2, -780($fp)
add     $t0, $t1, $t2
sw      $t0, -784($fp)
lw      $t0, -428($fp)
lw      $t1, -784($fp)
move    $t0, $t1
sw      $t0, -428($fp)
lw      $t0, -788($fp)
lw      $t1, -420($fp)
move    $t0, $t1
sw      $t0, -788($fp)
lw      $t0, -792($fp)
li      $t1, 1
move    $t0, $t1
sw      $t0, -792($fp)
lw      $t0, -796($fp)
lw      $t1, -788($fp)
lw      $t2, -792($fp)
sub     $t0, $t1, $t2
sw      $t0, -796($fp)
lw      $t0, -420($fp)
lw      $t1, -796($fp)
move    $t0, $t1
sw      $t0, -420($fp)
j       label22
label24:
lw      $t0, -800($fp)
lw      $t1, -428($fp)
move    $t0, $t1
sw      $t0, -800($fp)
lw      $t0, -800($fp)
move    $v0, $t0
lw      $ra, 820($sp)
lw      $fp, 816($sp)
addi    $sp, $sp, 824
jr      $ra

main:
addi    $sp, $sp, -52
sw      $ra, 48($sp)
sw      $fp, 44($sp)
addi    $fp, $sp, 52
jal     read
lw      $t0, -12($fp)
move    $t0, $v0
sw      $t0, -12($fp)
lw      $t0, -16($fp)
lw      $t1, -12($fp)
move    $t0, $t1
sw      $t0, -16($fp)
jal     read
lw      $t0, -20($fp)
move    $t0, $v0
sw      $t0, -20($fp)
lw      $t0, -24($fp)
lw      $t1, -20($fp)
move    $t0, $t1
sw      $t0, -24($fp)
lw      $t0, -28($fp)
lw      $t1, -16($fp)
move    $t0, $t1
sw      $t0, -28($fp)
lw      $t0, -32($fp)
lw      $t1, -24($fp)
move    $t0, $t1
sw      $t0, -32($fp)
lw      $t0, -32($fp)
sw      $t0, 4($sp)
lw      $t0, -28($fp)
sw      $t0, 0($sp)
jal     and
lw      $t0, -36($fp)
move    $t0, $v0
sw      $t0, -36($fp)
lw      $t0, -36($fp)
move    $a0, $t0
jal     write
lw      $t0, -44($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -44($fp)
lw      $t0, -44($fp)
move    $v0, $t0
lw      $ra, 48($sp)
lw      $fp, 44($sp)
addi    $sp, $sp, 52
jr      $ra

