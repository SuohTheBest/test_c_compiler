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

add:
addi    $sp, $sp, -20
sw      $ra, 16($sp)
sw      $fp, 12($sp)
addi    $fp, $sp, 20
lw      $t0, -12($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -12($fp)
lw      $t0, -16($fp)
lw      $t1, 4($fp)
move    $t0, $t1
sw      $t0, -16($fp)
lw      $t0, -20($fp)
lw      $t1, -12($fp)
lw      $t2, -16($fp)
add     $t0, $t1, $t2
sw      $t0, -20($fp)
lw      $t0, -20($fp)
move    $v0, $t0
lw      $ra, 16($sp)
lw      $fp, 12($sp)
addi    $sp, $sp, 20
jr      $ra

sub:
addi    $sp, $sp, -20
sw      $ra, 16($sp)
sw      $fp, 12($sp)
addi    $fp, $sp, 20
lw      $t0, -12($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -12($fp)
lw      $t0, -16($fp)
lw      $t1, 4($fp)
move    $t0, $t1
sw      $t0, -16($fp)
lw      $t0, -20($fp)
lw      $t1, -12($fp)
lw      $t2, -16($fp)
sub     $t0, $t1, $t2
sw      $t0, -20($fp)
lw      $t0, -20($fp)
move    $v0, $t0
lw      $ra, 16($sp)
lw      $fp, 12($sp)
addi    $sp, $sp, 20
jr      $ra

mul:
addi    $sp, $sp, -20
sw      $ra, 16($sp)
sw      $fp, 12($sp)
addi    $fp, $sp, 20
lw      $t0, -12($fp)
lw      $t1, 0($fp)
move    $t0, $t1
sw      $t0, -12($fp)
lw      $t0, -16($fp)
lw      $t1, 4($fp)
move    $t0, $t1
sw      $t0, -16($fp)
lw      $t0, -20($fp)
lw      $t1, -12($fp)
lw      $t2, -16($fp)
mul     $t0, $t1, $t2
sw      $t0, -20($fp)
lw      $t0, -20($fp)
move    $v0, $t0
lw      $ra, 16($sp)
lw      $fp, 12($sp)
addi    $sp, $sp, 20
jr      $ra

main:
addi    $sp, $sp, -140
sw      $ra, 136($sp)
sw      $fp, 132($sp)
addi    $fp, $sp, 140
jal     read
lw      $t0, -12($fp)
move    $t0, $v0
sw      $t0, -12($fp)
lw      $t0, -16($fp)
lw      $t1, -12($fp)
move    $t0, $t1
sw      $t0, -16($fp)
jal     read
lw      $t0, -24($fp)
move    $t0, $v0
sw      $t0, -24($fp)
lw      $t0, -28($fp)
lw      $t1, -24($fp)
move    $t0, $t1
sw      $t0, -28($fp)
jal     read
lw      $t0, -32($fp)
move    $t0, $v0
sw      $t0, -32($fp)
lw      $t0, -36($fp)
lw      $t1, -32($fp)
move    $t0, $t1
sw      $t0, -36($fp)
jal     read
lw      $t0, -40($fp)
move    $t0, $v0
sw      $t0, -40($fp)
lw      $t0, -44($fp)
lw      $t1, -40($fp)
move    $t0, $t1
sw      $t0, -44($fp)
lw      $t0, -48($fp)
lw      $t1, -16($fp)
move    $t0, $t1
sw      $t0, -48($fp)
lw      $t0, -52($fp)
lw      $t1, -28($fp)
move    $t0, $t1
sw      $t0, -52($fp)
lw      $t0, -52($fp)
sw      $t0, 4($sp)
lw      $t0, -48($fp)
sw      $t0, 0($sp)
jal     sub
lw      $t0, -56($fp)
move    $t0, $v0
sw      $t0, -56($fp)
lw      $t0, -60($fp)
lw      $t1, -16($fp)
move    $t0, $t1
sw      $t0, -60($fp)
lw      $t0, -64($fp)
lw      $t1, -28($fp)
move    $t0, $t1
sw      $t0, -64($fp)
lw      $t0, -64($fp)
sw      $t0, 4($sp)
lw      $t0, -60($fp)
sw      $t0, 0($sp)
jal     sub
lw      $t0, -68($fp)
move    $t0, $v0
sw      $t0, -68($fp)
lw      $t0, -68($fp)
sw      $t0, 4($sp)
lw      $t0, -56($fp)
sw      $t0, 0($sp)
jal     mul
lw      $t0, -72($fp)
move    $t0, $v0
sw      $t0, -72($fp)
lw      $t0, -76($fp)
lw      $t1, -36($fp)
move    $t0, $t1
sw      $t0, -76($fp)
lw      $t0, -80($fp)
lw      $t1, -44($fp)
move    $t0, $t1
sw      $t0, -80($fp)
lw      $t0, -80($fp)
sw      $t0, 4($sp)
lw      $t0, -76($fp)
sw      $t0, 0($sp)
jal     add
lw      $t0, -84($fp)
move    $t0, $v0
sw      $t0, -84($fp)
lw      $t0, -84($fp)
sw      $t0, 4($sp)
lw      $t0, -72($fp)
sw      $t0, 0($sp)
jal     add
lw      $t0, -88($fp)
move    $t0, $v0
sw      $t0, -88($fp)
lw      $t0, -92($fp)
lw      $t1, -88($fp)
move    $t0, $t1
sw      $t0, -92($fp)
lw      $t0, -96($fp)
lw      $t1, -92($fp)
move    $t0, $t1
sw      $t0, -96($fp)
lw      $t0, -96($fp)
move    $a0, $t0
jal     write
lw      $t0, -100($fp)
li      $t1, 0
move    $t0, $t1
sw      $t0, -100($fp)
lw      $t0, -100($fp)
move    $v0, $t0
lw      $ra, 136($sp)
lw      $fp, 132($sp)
addi    $sp, $sp, 140
jr      $ra

