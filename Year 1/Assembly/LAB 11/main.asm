bits 32
global start

import printf msvcrt.dll
import exit msvcrt.dll
extern printf, exit

extern conversie

segment data use32

    numar_init dd 0FAF3FCFDh
    
segment code use32 public code
start:

	push dword [numar_init]
	call conversie
    

	push 0
	call [exit]
