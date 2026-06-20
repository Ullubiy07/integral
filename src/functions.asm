section .data
    const1 dq -1.0
    const2 dq -2.0
    const3 dq 1.0
    const4 dq 2.0
    const5 dq 3.0

section .text
    global f1, f2, f3, df1, df2, df3
f1:
    push   ebp
    mov    ebp, esp
    finit

    fld    qword [ebp + 8]
    call   exp

    fadd   qword [const4]
    pop    ebp
    ret

f2:
    push   ebp
    mov    ebp, esp
    finit
    fld    qword [const1]
    fdiv   qword [ebp + 8]
    pop    ebp
    ret

f3:
    push   ebp
    mov    ebp, esp
    finit
    fld    qword [const3]
    fadd   qword [ebp + 8]
    fmul   qword [const2]
    fdiv   qword [const5]
    pop    ebp
    ret

df1:
    push   ebp
    mov    ebp, esp
    finit

    fld    qword [ebp + 8]
    call   exp

    pop    ebp
    ret

df2:
    push   ebp
    mov    ebp, esp
    finit
    fld    qword [const3]
    fld    qword [ebp + 8]
    fmul   qword [ebp + 8]
    fdiv
    pop    ebp
    ret

df3:
    push   ebp
    mov    ebp, esp
    finit
    fld    qword [const2]
    fdiv   qword [const5]
    pop    ebp
    ret

exp:
    fldl2e
    fmulp  st1, st0               ; st0 = t = xlog2(e) = N + F
    fld    st0                    ; st0 = t, st1 = t

    frndint                       ; st0 = N (integer part of t), st1 = t
    fsub   st1, st0               ; st0 = N, st1 = F (float part of t)

    fxch                          ; st0 = F, st1 = N
    f2xm1                         ; st0 = 2^F-1, st1 = N
    fadd   qword [const3]         ; st0 = 2^F, st1 = N
    fscale                        ; st0 = st0 * 2^st1 = 2^F * 2^N = 2^t = e^x, st1 = N
    fstp   st1                    ; st0 = e^x (st1 = st0 and pop st0)
    ret
