bits 32 

extern printf
import printf msvcrt.dll

segment data use32 public data
    tabhexa db '0123456789ABCDEF'
    format_print db "%c", 0
    sir resd 1
segment code use32 public code
global conversie

conversie:
	mov edx, [esp+4]
    mov [sir],edx
    mov esi, sir+3
    std
    mov ebx, tabhexa
    mov ecx, 4
    .repeta:
            xor eax, eax ; pun eax pe 0 ca sa il pot urca frumos pe stiva mai trz
            lodsb ; pun byte in al
            mov dl, al ; salvez si in dl
            shr al, 4 ; imi duc nibbel ul high in nibbel ul low
            xlat ; translatez binary in hexa
            
            pushad ; imi salvez registrii ca se strica
            push eax 
            push dword format_print
            call [printf] ; printez eax
            add esp, 4*2
            popad ; imi resetez registrii
            
            
            xor eax, eax
            mov al, dl
            and al, 0Fh ; fac o masca pentru bitii low
            xlat
            
            pushad
            push eax
            push dword format_print
            call [printf]
            add esp, 4*2
            popad
      loop .repeta
      ret 4