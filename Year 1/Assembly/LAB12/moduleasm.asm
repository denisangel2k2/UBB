global _substring
segment data public data use32
    lungime_sir dd 0
    lungime_sir2 dd 0
segment code public code use32
;substring(sir1,sir2) ; caut sirul1 in sirul2
_substring:
   
   mov dword[lungime_sir], 0
   mov dword[lungime_sir2], 0
   push ebp
   mov ebp, esp
   pushad
   ; am nevoie de lungimea sirului 1 si a sirului 2
   cld ; DF=0 pt parcurgere de la stanga la dreapta
   mov esi, [ebp+8] ;pun adresa sirului 1 in esi ca sa il parcurg
   _repeta:
      lodsb ; iau fiecare litera din sirul 1
      cmp al, 0 ; compar litera cu null
      je _afara ; daca e null atunci am ajuns la finalul sirului
      
      inc dword[lungime_sir] ; incrementez lungimea sirului altfel
      
    jmp _repeta ; repet pt ca nu am ajuns la finalul sirului 1
      
   _afara:
   
   ;analog aceeasi tehnica pentru al doilea sir
   mov esi, [ebp+12]
   _repeta1:
      lodsb
      cmp al, 0
      je _afara1
      
      inc dword[lungime_sir2]
      
    jmp _repeta1
      
   _afara1:
   
   ;am in lungime_sir lungimea sirului 1, ar in lungime_sir2 lungimea sirului 2

   mov edi, [ebp+12] ; edi=adresa sirului 2
   mov edx, [lungime_sir2] ; edx=1
   mov ecx, [lungime_sir]
   _not_eq:
        cmp edx, 1 ; compar sa vad daca s-a parcurs intreg sirul 2
        je _final ; daca s-a parcurs, atunci sar la final
        
        cmp ecx, [lungime_sir] ; compar sa vad daca s-a parcurs ceva din primul sir
        je _here ; daca da, sare la here
        
        dec edi
        inc edx
        
        _here:
        mov ecx, [lungime_sir] ; reface ecx cu lungime_sir
        mov esi, [ebp+8] ; repune adresa primului sir in esi
        ;jmp _rep
        
   _rep:
        lodsb ; pun in AL litera ce urmeaza din primul sir
        dec edx ; incrementez registrul care se ocupa de indexul parcurgerii sirului 2
        scasb ; compar litera din AL cu litera curenta din sirul 2
        jne _not_eq ; daca cele doua litere nu sunt egale, sar la eticheta _not_eq
        dec ecx ; decrementez indexul pt sirul 1, daca literele sunt egale
       
        
        cmp ecx, 1  ; compar sa vad daca am terminat verificarea, adica daca am ajuns cu indexul pt primul sir la 1
        jz _subsir
        
        cmp edx, 1 ; compar sa vad daca s-a parcurs intreg sirul 2
        jne _rep ; daca nu am ajuns, atunci repet instructiunile
        
   
   
        
   popad ; refac toti registrii
   
   _final: 
   mov eax, 0 ; returnez 0
   jmp _gata ; sar afara
   
   _subsir:
        mov eax, 1 ; returnez 1
   _gata:
   mov esp, ebp ; sar la ebp
   pop ebp ; refac ebp-ul
   
   ret ;ret