section .data
fmt db '%lf', 0
three dd 3.0
two dd 2.0

section .bss
cur resq 1


section .text
extern exp


global f1
f1:
push ebp
mov ebp, esp
push dword [ebp + 12]
push dword [ebp + 8]
fld1
call exp
add esp, 8
fdivp st1, st0
fadd dword [three]
pop ebp
ret


global f2

f2:
push ebp
mov ebp, esp
fld qword [ebp + 8]
fmul dword [two]
fsub dword [two]
pop ebp
ret


global f3
f3:
push ebp
mov ebp, esp
fld1
fld qword [ebp + 8]
fdivp st1, st0
pop ebp
ret
