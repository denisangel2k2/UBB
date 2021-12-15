bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    b db 1h
    a dw 2h
    cc dd 2h
    x dq 1
    var1 resd 1
    var2 resq 1

; b: 11 a: 22 11 c: 44 33 22 11 x: 88 77 66 55 44 33 22 11
; double word : xx xx xx xx

; a-word; b-byte; c-doubleword; x-qword

; (a*a+b+x)/(b+b)+c*c;
segment code use32 class=code
    start:
        ; ...
        
        mov ax, word[a]
        imul ax
        
        push dx
        push ax
        pop edx ; edx = a*a
        mov dword[var1],edx ; var1=a*a dword
        
        mov al, byte[b]
        cbw
        cwde
        cdq ;edx:eax=b - quad
        
        add eax, dword[x]
        adc edx, dword[x+4] ; edx:eax=b+x quad
        
        add eax, dword[var1] ; edx:eax=b+x+a*a quad
        adc edx, 0
        
         mov dword[var2], eax
         mov dword[var2+4], edx ; var2 = a*a+b+x quad
         
         mov al, byte[b]
         add al, al
         cbw
         cwde
         
         mov ebx, eax ; ebx = b+b dword
         mov eax, dword[var2]
         mov edx, dword[var2+4]
         idiv ebx ; eax = (a*a+b+x)/(b+b)
         mov ebx, eax
         
         mov eax, dword[cc]
         imul eax ; edx:eax = c*c
         add eax, ebx
         adc edx,0 ;  edx:eax =(a*a+b+x)/(b+b)+c*c
        
        
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
