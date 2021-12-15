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
                                ;Se dau octetii A si B. Sa se obtina dublucuvantul C:
                                ;bitii 16-31 ai lui C sunt 1
                                ;bitii 0-3 ai lui C coincid cu bitii 3-6 ai lui B
                                ;bitii 4-7 ai lui C au valoarea 0
                                ;bitii 8-10 ai lui C au valoarea 110
                                ;bitii 11-15 ai lui C coincid cu bitii 0-4 ai lui A
   a db 01010111b
   b db 11010011b
   c dd 00000000h 
   
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;Cerinta: 1111 1111 1111 1111 1011 1110 0000 1010
        ;Output : 1111 1111 1111 1111 1011 1110 0000 1010
        
        ;bitii 16-31 ai lui C sunt 1
        mov eax, 0FFFF0000h
        or dword[c], eax
        ;bitii 0-3 ai lui C coincid cu bitii 3-6 ai lui B=x1010xxx
        xor eax, eax
        mov al, byte[b]
        and al, 01111000b
        mov cl, 3
        shr al, cl
        or dword[c], eax
        ;bitii 4-7 ai lui C au valoarea 0
        
        ;bitii 8-10 ai lui C au valoarea 110
        xor eax, eax
        mov ax, 0000011000000000b
        or dword[c], eax
        
        ;bitii 11-15 ai lui C coincid cu bitii 0-4 ai lui A
        xor eax, eax
        mov al, byte[a]
        and al, 00011111b ;0000 0000 0000 0000    0000 0000 0001 1111
        mov cl, 11
        shl ax, cl
        or dword[c], eax
        mov eax, dword[c]
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
