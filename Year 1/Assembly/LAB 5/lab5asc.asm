bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions


segment data use32 class=data
    ; ...
    s1 db 1, 3, 6, 2, 3, 7
    s2 db 6, 3, 8, 1, 2, 5
    len equ ($-s2)
    d resb len
    ;d: 1, 3, 6, 1, 2, 5
;Se dau 2 siruri de octeti S1 si S2 de aceeasi lungime. Sa se construiasca sirul D
;astfel incat fiecare element din D sa reprezinte minumul dintre elementele de pe pozitiile corespunzatoare din S1 si S2
segment code use32 class=code
    start:
        mov esi, 0
        
        start_loop:
            mov al, byte[s1+esi]
            mov ah, byte[s2+esi]
            
            cmp al, ah
            ja s1_mare
            
                mov byte[d+esi], al
                jmp final

            s1_mare:
                mov byte[d+esi], ah
                
            final:
            
            inc esi
            cmp esi, len
        jb start_loop
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
