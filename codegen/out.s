.text
main:
addiu $sp $sp -28
move $t0 $sp
sw $t0 0($sp)
sw $ra 4($t0)
li $a0 0
sw $a0 8($t0)
addiu $sp $sp -4
li $a0 9
sw $a0 20($t0)
li $a0 2
sw $a0 16($t0)
lw $a0 20($t0)
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 16($t0)
lw $t1 4($sp)
addiu $sp $sp 4
div $t1 $a0
mfhi	$a0
sw $a0 12($t0)
lw $a0 12($t0)
sw $a0 24($t0)
li $v0 1
lw $a0 24($t0)
syscall
.data
res_str0: .asciiz "\n"
.text
li $v0 4
la $a0 res_str0
syscall
li $a0 0
move $v0 $a0
lw $ra 4($t0)
addiu $sp $sp 32
jr $ra
lw $ra 4($t0)
addiu $sp $sp 32
jr $ra
