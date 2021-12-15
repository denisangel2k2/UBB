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
; our code starts here

; b: 11 a: 22 11 c: 44 33 22 11 x: 88 77 66 55 44 33 22 11
; double word : xx xx xx xx
; a-word; b-byte; c-doubleword; x-qword

; (a*a+b+x)/(b+b)+c*c;

segment code use32 class=code
    start:
        ; ...
        mov eax, 0
        mov edx, 0
        mov ax, word[a]
        mul word[a]
        ; dx;ax -> a*a
        mov word[var1], ax
        mov word[var1+2], dx ; var1=a*a
        
        mov eax, dword[var1] ; eax=a*a
        
        mov edx,0
        mov ecx, 0
        mov cl, byte[b]
        
        add eax, ecx ; eax=a*a+b
        adc edx,0
        
        add eax, dword[x]
        adc edx, dword[x+4] ;edx:eax = a*a+b+x
        
        mov dword[var2],eax; bag in alta variabila
        mov dword[var2+4], edx ;var2 = a*a+b+x
        
        mov eax, 0
        mov edx, 0
        
        mov al, byte[b]
        add al, byte[b]
        
        mov dword[var1],0
        mov byte[var1], al ;var1=b+b
        
        mov eax,0
        mov edx, 0
        mov eax, dword[var2]
        mov edx, dword[var2+4] ;edx:eax=a*a+b+x 
        
        div dword[var1] 
        mov dword[var1], eax ; var1=(a*a+b+x)/(b+b)
        
        mov eax, dword[cc]
        mul dword[cc] ; edx:eax = c*c
        add eax, dword[var1]
        adc edx, dword[var1+4]
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
