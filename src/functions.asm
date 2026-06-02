section .data
    const1 dq -1.0
    const2 dq -2.0
    const3 dq 1.0
    const4 dq 2.0
    const5 dq 3.0

section .text
    extern exp
    global f1, f2, f3, df1, df2, df3
f1:
    push   ebp
    mov    ebp, esp
    and    esp, -16
    sub    esp, 16
    mov    eax, dword [ebp + 8]
    mov    [esp], eax
    mov    eax, dword [ebp + 12]
    mov    [esp + 4], eax
    call   exp
    fadd   qword [const4]
    mov    esp, ebp
    pop    ebp
    ret

f2:
    push   ebp
    mov    ebp, esp
    fld    qword [const1]
    fdiv   qword [ebp + 8]
    pop    ebp
    ret

f3:
    push   ebp
    mov    ebp, esp
    fld    qword [const3]
    fadd   qword [ebp + 8]
    fmul   qword [const2]
    fdiv   qword [const5]
    pop    ebp
    ret

df1:
    push   ebp
    mov    ebp, esp
    and    esp, -16
    sub    esp, 16
    mov    eax, dword [ebp + 8]
    mov    [esp], eax
    mov    eax, dword [ebp + 12]
    mov    [esp + 4], eax
    call   exp
    mov    esp, ebp
    pop    ebp
    ret

df2:
    push   ebp
    mov    ebp, esp
    fld    qword [const3]
    fld    qword [ebp + 8]
    fmul   qword [ebp + 8]
    fdiv
    pop    ebp
    ret

df3:
    push   ebp
    mov    ebp, esp
    fld    qword [const2]
    fdiv   qword [const5]
    pop    ebp
    ret

section .note.GNU-stack noexec
