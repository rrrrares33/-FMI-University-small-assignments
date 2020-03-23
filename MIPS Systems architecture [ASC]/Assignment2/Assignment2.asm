.data
    v: .word 5 7 10 4 2 3           #vectorul care urmeaza sa fie prelucrat
    n: .word 6                      #numarul de elemente din vector
    sp: .asciiz " "                 #spatiul utilizat pentru afisare

.text
                     
main:
   la $t0, v                        #incarc adresa vectorului in $t0
   li $t1, 0                        #$t1 - contor pentru elemente vector care creste din 1 in 1
   lw $t2, n                        #$t2 retine numarul de elemente ale vectorului
   
   subu $sp, $sp, 4                 #salvez n pe stiva
   sw $t2, 0($sp)
   subu $sp, $sp, 4                 #salvez adresa lui $t0 ca word pe stiva
   sw $t0, 0($sp)
   
   # $sp:(*v)(n)
   jal modifica                     #apelez procedura modificã
   
   addu $sp, $sp,8                  #restaurez stiva
                  
   li $t3, 0                        #contor pentru afisare care creste din 4 in 4
   li $t1, 0                        #contor pentru afisare care creste din 1 in 1 pentru oprire
   
   for2:
    beq $t1, $t2, exit              #daca t1 ajunge egal cu n, am terminat afisarea
    
    lw $a0, v($t3)                  #afisez elementul de pe pozitia t1 din vector ( cu t3 corespondent )
    li $v0, 1
    syscall
    la $a0, sp                      #afisez spatiu
    li $v0, 4                        
    syscall
    addi $t1, $t1, 1                #iterez t1 cu 1 penntru a sti pe ce pozitie din vector ne aflam
    addi $t3, $t3, 4                #iterez t3 cu 4 pentru urmatoarea afisare
                 
    j for2                          #revenim la urmatoarea afisare
    
   exit:                            #se incheie programul aici
    li $v0, 10
    syscall
    
    
modifica:
    # $sp:(*v)(n)
    subu $sp, $sp, 4
    sw $fp, 0($sp)
    addi $fp, $sp, 4
    subu $sp, $sp, 4
    sw $ra, 0($sp)
    subu $sp, $sp, 4
    sw $s0, 0($sp)
    subu $sp, $sp, 4
    sw $s1, 0($sp)
    # $sp:($s0v)($s1v)($rav)($fpv) $fp:(*v)(n)
    
    lw $s0, 0($fp)         #*v
    lw $s1, 4($fp)         #n
    li $t0, 0              #i
    
    for:
      bge $t0, $s1, exit_modifica    #daca i=n atunci executarea s-a incheiat
      lw $t1, 0($s0)                 #$t1 = v[i]
      move $a0, $t1                  #transmit prin a0 elementul pentru care urmeaza sa fie aplicata functia sum_squares
      jal suma_patrate
      sw $v0, 0($s0)                 #salvez valoarea elemntului in vector, care se afla pe stiva  
      addi $t0, $t0, 1               #incrementez t0 care creste din 1 in 1 pana ajunge cat n
      addi $s0, $s0, 4               #incrementez s0 pentru a trece la urmatorul element din vector
      j for   
                
    exit_modifica:
                     lw $s1,-16($fp)
                     lw $s0, -12($fp)
                     lw $ra, -8($fp)
                     lw $fp, -4($fp)
                     addu $sp, $sp, 16
                     #restaurez stiva
                     jr $ra
    
suma_patrate:
    subu $sp, $sp, 12
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)
    
    li $v0, 0                #retin in v0 suma dupa fiecare parcurgere
    ble $a0, 0, sum_squares_done
    
    move $s0, $a0            #mut in s0 valoarea lui a0
    sub  $s0, $s0, 1         #scad din s0 1 deoarece suma este a elementelor strict mai mici
    sub  $a0, $a0, 1         #reduc si a0 si reiau recursiv functia
    jal  suma_patrate
    
    mul $s1, $s0, $s0        #in s1 retin patratul lui s0 curent
    add $v0, $v0, $s1        #si il adun la v0
    
    sum_squares_done:
                     lw $ra, 0($sp)
                     lw $s0, 4($sp)
                     lw $s1, 8($sp)
                     addu $sp, $sp, 12
                     #restaurez sitva
                     jr $ra