.data
  eroare_prim: .asciiz "Numarul introdus nu este prim."
  generator_afisare: .asciiz "Generatorul pentru p-ul dat este: "
  criptare_text: .asciiz "Criptarea primului sir dat este: "
  decriptare_text: .asciiz "Decriptarea celui de al doilea sir dat este: "
  insert_p: .asciiz "Introduceti p-ul: "
  insert_text1: .asciiz "Introduceti textul ce urmeaza sa fie criptat: "
  insert_text2: .asciiz "Introduceti textul ce urmeaza sa fie decriptat: "
  new_line: .asciiz "\n"
  alfabet: .asciiz "ABCDEFGHIJKLMOPQRSTUVWXYZ"
  p: .word 4                                               #trebuie sa fie prim
  text1: .space 40                                         #textul ce urmeaza sa fie criptat
  text2: .space 40                                         #textul ce urmeaza sa fie decriptat
  g: .space 4                                              #generatorul pentru p-ul prim dat (in cazul in care este prim)
  v: .space 400                                            #vectorul in care o sa retin resturile pentru a gasi generatorul, criptare si decriptare

.text

main:
  la $a0, insert_p         #afisez primul text pentru citirea p-ului de la tastatura
  li $v0, 4
  syscall
  li $v0, 5
  syscall
  move $t0, $v0
  sw $t0, p             #citeste p-ul pentru criptare                                                            
  
  la $a0, insert_text1      #afisez cel de al doilea text pentru citirea textului ce urmeaza sa fie criptat
  li $v0, 4
  syscall
  li $v0, 8
  la $a0, text1
  li $a1, 40
  syscall                   #citeste mesajul care trebuie sa fie CRIPTAT                                         (MERGE)
  
  la $a0, insert_text2     #afisez cel de al treilea text pentru citirea textului ce urmeaza sa fie decriptat
  li $v0, 4
  syscall
  li $v0, 8
  la $a0, text2
  li $a1, 40
  syscall                   #citeste mesajul care trebuie sa fie DECRIPTAT                                       (MERGE)
  
  la $a0, new_line          # trec output-ul pe o noua linie
  li $v0, 4
  syscall
 
  lw $t0, p                #t0 o sa retina pentru moment p-ul dat
  blt $t0, 2, exit_error_prim   #daca numarul este mai mic decat 2, atunci nu este prim si afisam mesajul de eroare      
  div $t1, $t0, 2               #verificare daca numarul este prim o sa mearga pana la <p/2, pentru a fi eficient
  li $t2, 2                     #contorul pentru repetitiva ce va urma, care incepe de la 2
  
loop1:
  bgt $t2, $t1, continue1      #daca contorul($t2) este mai mare sau egal cu p/2 numarul este prim si algoritmul poate continua spre crearea unui generator  |optimizare|
  rem $t3, $t0, $t2            #retin restul impartirii lui p la contor
  beq $t3, 0, exit_error_prim       #daca restul este egal cu 0, atunci numarul nu este prim si afisam mesajul de eroare
  addi $t2,$t2,1              #incrementam contorul($t2)
  j loop1
  
    
exit_error_prim:                    #Daca numarul dat nu este prim, se va afisa mesajul corespunzator stocat in eroare_prim
   la $a0, eroare_prim              #si se va termina executarea programului
   li $v0, 4
   syscall
   li $v0, 10
   syscall

continue1:                     #generam generatorul :)  
  li $t2, 2                    #retin in $t2 un potential generator   
  loop2:
   addi  $t4, $t2, 0                   #retin o copie dupa $t2 in $t4 pentru ca $t2 o sa isi schimbe valoarea
   li $t1, 0                           #retin in $t1 contorul elementelor din vector
   li $t3, 1
   sw  $t3, v($t1)                     #salvez restul 1 in vector
   mul $t3, $t4, $t2
   addi $t1, $t1, 4                    #trec la urmatorul element din vector
   
   loop3:
    beq  $t3, 1, exit_loop3            #daca restul impartirii este 1 atunci am terminat de construit vectorul
    rem  $t3, $t2, $t0                 #calculez restul dintre t2 actual si p-ul dat
    sw   $t3, v($t1)                   #retin resturile in vectorul pentru generator
    addi $t1, $t1, 4                   #trec la urmatorul element in vector
    mul  $t2, $t4, $t2                 #ridic la putere numarul dat
    rem  $t2, $t2, $t0                 #retin restul impartirii puterii la p-ul dat($t0) in $t2               |optimizare|
    j loop3
   
   exit_loop3:
   li $t3, 2                                #primul element pe care o sa-l caut secvential in vector
    loop4: 
     bge $t3, $t0, generator_gasit          #Daca elementul pe care il caut este egal cu p($t0) inseamna ca toate celelalte au fost gasite deja printre resturi deci $t4 este generator
     li $t5, 0                              #initializez cautarea secventiala in vector, incepand cu pozitia 0
      loop5:
       beq $t5, $t1, generator_prost        #Daca cautarea a ajuns la sfarsit($t5=$t1) si nu s-a gasit unul dintre elementele lui Zp inseamna ca generatorul nu este bun si trecem la urmatorul
       lw $t6, v($t5)                       #Incarc in $t6 valoarea din v($t5)
       beq $t3, $t6 , element_gasit         #Daca t3 si t6 sunt egale inseamna ca elementul t3 curent se afla in vector, asa ca trecem la t3+1
       addi $t5,$t5, 4                      #Incrementam i-ul vectorului
       j loop5
      element_gasit:
       addi $t3,$t3,1                       #In cazul in care gasim un element, trecem la cautarea urmatorului element
       j loop4
    
  generator_prost:
   addi $t2, $t2, 1                         #Daca un generator este prost, verificam daca generator($t2)+1 este si el generator
   j loop2
  
  generator_gasit:
   sw $t4, g                                #Generatorul bun a fost gasit ($t4) , asa ca putem salva valoarea lui in memorie sub numele g
   la $a0, generator_afisare                #Si il afisam frumos pe ecran
   li $v0, 4
   syscall
   la $a0,($t4)                             #afisez generatorul gasit care se afla la adresa de memorie salvata in t4
   li $v0, 1
   syscall
   la $a0, new_line                        #trec output-ul pe o noua linie
   li $v0, 4
   syscall
   j codare_mesaj                          #Incepem codarea primului mesaj
     
   codare_mesaj:                           #PENTRU CODARE TREBUIE SA FAC DIFERENTA DINTRE VALOAREA DIN VECTOR SI CEA DIN ALFABET SI DUPA,
    li $t2, 0
    lb $t3, text1($t2)                     #In $t2 o sa retin lungimea sirului ce trebuie codat si o sa incrementeze trecerea de la o litera la alta
    loop6:
     beqz $t3, exit_loop6                  #Daca in t3 este caracterul null, atunci am terminat numararea
     li  $t5, 0                            #Retine pe ce pozitie din alfabet se afla elementul pe care eu il caut
     
     loop7:
      lb $t6, alfabet($t5)                 #In t6 se afla un caracter din alfabet
      beq  $t6, $t3, exit_loop7            #Daca t6 si t3 sunt egale, atunci pe pozitia t5 in alfabet se afla caracterul cautat de mine
      addi $t5, $t5, 1                     #incrementez t5
      beq  $t5, 30, exit_loop6             #Daca contorul pentru alfabet depaseste 30 inseamna ca elementul cautat nu se afla in alfabet (Aveam un BUG care s-a fixat cu chestia asta)
      j loop7

     exit_loop7:
       addi $t6, $t5, 0                     #copiez continutul din t5 in t6                    
       li $t1, 0                            #retin pozitia din v din 4 in 4
       
       loop8:
        beqz $t6, exit_loop8                #Daca t6 este 0 inseamna ca t1 a ajuns la pozitia pe care o cautam din v
        addi $t1, $t1, 4                    #Retine pozitia din v si se incrementeaza din 4 in 4
        addi $t6, $t6, -1                   #Decrementare t6
        j loop8
        
        exit_loop8:
           
      modifica_caracter:
        lw $t5, v($t1)                       #Incarc valoarea de pe pozitia $t1 din v in $t5 
        lb $t6, alfabet($t5)                 #Incarc caracterul(byte-ul) de pe pozitia $t5 din alfabet in t6
        sb $t6, text1($t2)                   #Modific caracterul pe care lucrez din text1 
      j iesire_modifica_caracter
      
      iesire_modifica_caracter:
      addi $t2, $t2, 1                     #Crestem contorul care urmareste pozitia fiecarui caracter din text1
      lb $t3, text1($t2)                   #Incarcam in t3 urmatorul caracter care urmeaza sa fie codat
     j loop6                               #si reiau criptarea de la inceput
    
    exit_loop6:
    
    afisare_mesaj_codat:
      la $a0, criptare_text                   #Afisez textul stocat la criptare_text                  
      li $v0, 4
      syscall
      la $t2, text1                           #Afisez textul criptat
      move $a0, $t2
      li $v0, 4       
      syscall
      j decriptare_mesaj                      #Trec la decriptarea celui de al doilea mesaj
      
    decriptare_mesaj:
     li $t2, 0                                #in t2 retin pozitia caracterului cu care lucrez pentru a-l decripta
     lb $t3, text2($t2)                       #in t3 retin caracterul care urmeaza sa fie decriptat
     loop9:
       beqz $t3, afisare_mesaj_decodat        #Daca t3=NULL inseamna ca s-a terminat decriptare si sar direct la afisare
       li $t5, 0                              #In t5 retin pozitia din alfabet pe care se afla caracterul nostru
       
       loop10:
        lb $t6, alfabet($t5)                  #incarc din alfabet caracterul de pe pozitia t5
        beq $t3, $t6, exit_loop10             #Daca coincide cu caracterul care urmeaza sa fie prelucrat, atunci i-am gasit pozitia
        addi $t5, $t5, 1                      #Altfel incrementez cu 1 $t5
        beq $t5, 30, afisare_mesaj_decodat    
        j loop10
       
       exit_loop10:
       li $t1, 0                                       #contor vector care creste din 4 in 4
       li $t4, 0                                       #contor pentru alfabet care creste odata cu cel pentru vector doar ca din 1 in 1
       j loop11
       
       loop11:
        lw $t7, v($t1)                                 #Incarc in $t7 elementul de pe pozitia $t1(cea in care am stocat aparitia elementului in alfabet) din vectorul de resturi
        beq $t5, $t7, inlocuire_valoare                #Daca t5 si t7 sunt egale, atunci trec la inlocuire
        addi $t1, $t1, 4                               #altfel incrementez t1 cu 4 si t4 cu 1
        addi $t4, $t4, 1
        j loop11
       
       inlocuire_valoare:
        lb $t7, alfabet($t4)                           #elemntul care se afla acum pe pozitia $t4 din alfabet este cel cautat si il incarc in t7
        sb $t7, text2($t2)                             #dupa care il retin in locul caracterului pe care l-am decriptat
       j iesire_inlocuire_valoare
       
       iesire_inlocuire_valoare:
         addi $t2, $t2, 1                              #incrementez t2 pentru a trece pe pozitia urmatoare in cuvant
         lb $t3, text2($t2)                            #incarc caracterul care urmeaza sa fie modific in t3
      j loop9                                          #revin la inceputul decriptarii
    
    afisare_mesaj_decodat:
     la $a0, decriptare_text                           #incarc pentru afisare textul pentru facilitarea citirii salvat in memorie
     li $v0, 4
     syscall
     la $a0, text2                                     #incarc pentru afisare text2 care acum este decriptat
     li $v0, 4
     syscall
     j exit_program                                    #sar la iesirea din program
    
    exit_program:
      li $v0, 10                                       #INCHEIERE PROGRAM.
      syscall                                                                                                                                                                                                                                                                               