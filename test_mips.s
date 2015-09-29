.text
main:
.data
sukhpal: .asciiz "sukhpal singh"
.text
la $a0 sukhpal
li $v0 4
syscall
jr $ra