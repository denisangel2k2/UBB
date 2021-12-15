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
    a db 11h
    b dw 1122h
    cc dd 11223344h
    d dq 1122334455667788h
    var1 resq 1
    var2 resq 1
    var3 resq 1
    var4 resq 1
    
; our code starts here
; a: 11 b: 22 11 c: 44 33 22 11 d: 88 77 66 55 44 33 22 11

; a - byte, b - word, c - double word, d - qword - Interpretare cu semn

;(d+a)-(c-b)-(b-a)+(c+d)
segment code use32 class=code
    start:
        ; ...
        
        mov al, byte[a]
        cbw
        cwde
        cdq
        
        add eax, dword[d]
        adc edx, dword[d+4]
        mov dword[var1], eax
        mov dword[var1+4], edx ; var1=d+a  quad
        
        mov ax, [b]
        neg ax
        cwde
        cdq
        add eax, dword[cc]
        adc edx, 0
        mov dword[var2], eax
        mov dword[var2+4],edx ; var2=c-b quad
        
        mov al, byte[a]
        neg al
        cbw
        cwde
        cdq
        mov dword[var3], eax
        mov dword[var3+4], edx ;var3 = -a quad
        
        mov ax, word[b]
        cwde
        cdq
        add eax, dword[var3]
        adc edx, dword[var3+4]
        
        mov dword[var3], eax
        mov dword[var3+4], edx ;var3 = b-a quad
        
        mov eax, dword[cc]
        cdq
        add eax, dword[d]
        adc edx, dword[d+4] ; edx:eax=c+d
        
        add eax, dword[var1]
        adc edx, dword[var1+4] ; edx:eax=(c+d)+(d+a)
        
        sub eax, dword[var2]
        sbb edx, dword[var2+4]; edx:eax=(c+d)+(d+a)-(c-b)
        
        sub eax, dword[var3]
        sbb edx, dword[var3+4]; edx:eax=(c+d)+(d+a)-(c-b)-(b-a)
        
        
        
        
        
        
        
        
        
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
