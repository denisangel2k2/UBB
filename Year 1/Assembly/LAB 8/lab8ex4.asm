bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit
extern scanf               ; tell nasm that exit exists even if we won't be defining it
extern printf

import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)

; Se dau doua numere naturale a si b (a, b: word, definite in segmentul de date). Sa se calculeze produsul lor si sa se afiseze in urmatorul format: "<a> * <b> = <result>"
; Exemplu: "2 * 4 = 8"
; Valorile vor fi afisate in format decimal (baza 10) cu semn.
format_afisare db "<%d> * <%d> = <%d>", 0
;format_citire db "%d", 0
format_citire db "%d %d", 0


a resd 1
b resd 1

segment data use32 class=data
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        push dword b                ; punem a doua variabila citita in continutul de la adresa b
        push dword a                ; punem prima variabila citita in continutul de la adresa a
        push dword format_citire    ; punem pe stiva formatul pentru citire
        call [scanf]                ; apelam functia de citire scanf din msvcrt.dll
        add esp, 4*3                ; incrementam stiva de 12 ori ca sa o neutralizam
        
        
        
        
        mov ax, [b]                 ; pun in eax continutul de la variabila citita
        imul word[a]                ; inmultesc cu semn cu wordul de la adresa a, si voi avea rezultatul in dx:ax
        
        push dx                     ; pun pe stiva partea high a rezultatului inmultirii
        push ax                     ; pun pe stiva partea low a rezultatului inmultirii
        pop eax                     ; pun in eax rezultatul inmultirii ca dword
        
        push eax                    ; pun rezultatul inmultirii pe stiva ca parametru pentru printare
        push dword [b]              ; pun al doilea operand al inmultirii pe stiva ca parametru pentru printare
        push dword [a]              ; pun primul operand al inmultirii pe stiva ca parametru pentru printare
        push dword format_afisare   ; pun adresa formatului pentru printare pe stiva
        call [printf]               ; apelez functia de afisare printf din msvcrt.dll
        add esp, 4*3                ; incrementam stiva de 12 ori ca sa o neutralizam
        
        
        

        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
        
        
; push dword b ; punem a doua variabila citita in continutul de la adresa a+1
        ; push dword format_citire ; punem pe stiva formatul pentru citire
        ; call [scanf] ; apelam functia de citire
        ; add esp, 4*2 ; incrementam stiva de 12 ori ca sa o neutralizam
        
        ; push dword a
        ; push dword format_citire
        ; call [scanf]
        ; add esp, 4*2