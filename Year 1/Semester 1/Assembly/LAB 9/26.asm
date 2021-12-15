bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,fprintf,fclose,fopen,printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll                                                    
import fprintf msvcrt.dll                          
import fclose msvcrt.dll                          
import fopen msvcrt.dll                          
import printf msvcrt.dll                          
; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)

; CERINTA: Se da un nume de fisier (definit in segmentul de date). Sa se creeze un fisier cu numele dat, apoi sa se citeasca de la tastatura cuvinte pana cand se citeste de la tastatura caracterul '$'. Sa se scrie in fisier doar cuvintele care contin cel putin o litera mare (uppercase).

segment data use32 class=data
    ; ...

    fisier_output db "output.txt", 0
    descriptor_output resd 1
    format_citire db "%s", 0
    format_scriere db "%s ", 0
    mod_acces db "w",0
    text db "a intrat", 0
    var db 0 ; trb sa fie pe ultima pozitie?
    

segment code use32 class=code
    start:
        ; apelez fopen ca sa deschid fisierul
        push dword mod_acces
        push dword fisier_output
        call [fopen]
        add esp, 4*2
        
        mov dword[descriptor_output], eax ; salvez descriptorul in variabila
        
        citire:
            push dword var ; citesc cate un sir de caractere terminat in 0 in pointerul var
            push dword format_citire
            call [scanf]
            add esp, 4*2 
            
            cmp byte[var],'$' ; compar sa vad daca sirul meu de caractere este de fapt $
            je final ; iese cand gaseste caracterul asta
            
            mov esi, var ; lucrez cu sir de caractere var
            
            repeta:
                
                lodsb ; pun fiecare litera in al
                cmp al, 0 ; compar sa vad daca e final de sir de caractere
                je afara ; daca este atunci ies din bucla
                
                cmp al, 'a' ; daca nu este, atunci verific daca este litera mare
                jb baga ; daca este litera mare atunci ies din bucla si bag in fisier
                
            jmp repeta ; daca nu am iesit pana acum din bucla inseamna ca nu am terminat si reiau
                
 
             baga: ;daca am gasit litera mare  scriu in fisier
                
                push dword var ; apelez functia fprintf in descriptor_output
                push dword format_scriere
                push dword[descriptor_output]
                call [fprintf]
                add esp, 4*3
                
            afara:
            jmp citire ; sar inapoi sa citesc
            
        final:
            ;inchid fisierul
            push dword [descriptor_output]
            call [fclose]
            add esp, 4
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program