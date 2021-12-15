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
    ;Sa se obtina sirul format din octetii inferiori ai
 ;cuvintelor superioare din elementele sirului de dublucuvinte care sunt palindrom in scrierea in baza 10.    xxXXxxxx
    s DD 12345678h, 1A2C3C4Dh, 98FCDC76h
    len equ ($-s)/4
   ; => 2Ch, 0FCh
    pali db 1
    initial db 1
    d RESB 3
; our code starts here
segment code use32 class=code
    start:
        ; ...
        xor eax, eax
        mov esi, s
        mov bl, 10
        mov cl, 0
        mov edi, d
        mov ecx, len
        repeta:
            lodsw
            lodsw ;in AL vom avea byte ul cautat
            mov [initial], al ; initial = byte ul initial
            mov dl, 0
            mov [pali], dl
                repeta_palindrom:
                    mov ah, 0
                    
                    div bl ; al=ax/10   ah=ax%10
                    
                    mov dl, al ;salvez in dl restul si catul
                    mov dh, ah
                    
                    mov al, byte[pali] ;bag datele in palindrom
                    mul bl ;*10
                    add al, dh
                    
                    mov [pali], al ; pun noul palindrom in variabila pali
                    mov al, dl
                    
                    cmp al, 0
                jnz repeta_palindrom
            ; in palindrom avem acum oglinditul byte-ului initial
            
            mov al, [initial]
            
            cmp [pali], al
            jnz sfarsit
            
            stosb ; stocehaza in d daca e palindrom
            
            sfarsit:
                ;aici sare daca nu e palindrom
           
        loop repeta          
            
                
                
                
                
              
            
            
  
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
