bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)

;a - byte, b - word, c - double word, d - qword - Interpretare fara semn
; (c+c-a)-(d+d)-b
segment data use32 class=data
    ; ...
    a db 11h
    b dw 2233h
    cc dd 11223344h
    d dq 1122334455667788h
    var1 resq 1
    var2 resq 1
    var3 resq 1
 ; a: 11 b: 33 22 c: 44 33 22 11 d: 88 77 66 55 44 33 22 11
 
    ;var2 : xx xx xx xx <-low(0-3)   xx xx xx xx <-high(4-7)
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov eax,dword[cc]
        add eax, dword[cc]
        ; daca s a facut cf aici 1
        
        mov edx, 0
        adc edx, 0 ; punem carry flg
        
        mov ecx, 0
        mov cl, byte[a]
        
        sub eax, ecx
        
        
        mov dword[var1], eax ; 
        mov dword[var1+4], edx ; var1 = qword(c+c-a)
        
        mov eax,0
        mov edx, 0
        
        mov eax, dword[d]
        mov edx, dword[d+4]
        
        add eax, dword[d]
        adc edx, dword[d+4]
        
        mov dword[var2], eax 
        mov dword[var2+4], edx ; var2 = qword (d+d)
       
       mov eax,0
       mov edx, 0
       
       mov ax, word[b]
       
       mov word[var3], ax 
       mov word[var3+2],0
       mov dword[var3+4], 0;var3 = qword(b)
       
       mov eax,0
       mov edx, 0
       
       mov eax, dword[var1]
       mov edx, dword[var1+4]
       
       sub eax, dword[var2]
       sbb eax, dword[var2+4]
       
       sub eax, dword[var3]
       sbb eax, dword[var3+4]
       
       ; rezultat in edx:eax
       
       
       
       
       
       
       
        
        
        
        
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
