.code

; ========================================
; FlagLottery
;
; 戻り値
; 0 = ハズレ
; 1 = ベル
; 2 = リプ
; 3 = スイカ
; 4 = 弱チェリーA
; 5 = 弱チェリーB
; ========================================

FlagLottery PROC

    ; ========================================
    ; ① 0～65535の乱数を作る
    ; ========================================

    rdtsc

    xor edx, edx
    mov ecx, 65536
    div ecx

    ; EDX = 0～65535
    mov r8d, edx


    ; ========================================
    ; ② ベル
    ; ID = 1
    ; 1/8.2
    ; 7992
    ; ========================================

    mov eax, 65536
    xor edx, edx

    mov ecx, 10
    mul ecx

    mov ecx, 82
    div ecx

    cmp r8d, eax
    jl Bell


    ; ========================================
    ; ③ リプレイ
    ; ID = 2
    ; 1/8.7
    ; 7532
    ; ========================================

    mov eax, 65536
    xor edx, edx

    mov ecx, 10
    mul ecx

    mov ecx, 87
    div ecx

    add eax, 7992

    cmp r8d, eax
    jl Replay


    ; ========================================
    ; ④ スイカ
    ; ID = 3
    ; 1/79.9
    ; 820
    ; ========================================

    mov eax, 65536
    xor edx, edx

    mov ecx, 10
    mul ecx

    mov ecx, 799
    div ecx

    add eax, 7992
    add eax, 7532

    cmp r8d, eax
    jl Watermelon


    ; ========================================
    ; ⑤ 弱チェリーA
    ; ID = 4
    ; 1/199.2
    ; 329
    ; ========================================

    mov eax, 65536
    xor edx, edx

    mov ecx, 10
    mul ecx

    mov ecx, 1992
    div ecx

    add eax, 7992
    add eax, 7532
    add eax, 820

    cmp r8d, eax
    jl WeakCherryA


    ; ========================================
    ; ⑥ 弱チェリーB
    ; ID = 5
    ; 1/199.2
    ; 329
    ; ========================================

    mov eax, 65536
    xor edx, edx

    mov ecx, 10
    mul ecx

    mov ecx, 1992
    div ecx

    add eax, 7992
    add eax, 7532
    add eax, 820
    add eax, 329

    cmp r8d, eax
    jl WeakCherryB


    ; ========================================
    ; ⑦ 強チェリーA
    ; ID = 6
    ; 1/397.2
    ; 165
    ; ========================================

    mov eax, 65536
    xor edx, edx

    mov ecx, 10
    mul ecx

    mov ecx, 3972
    div ecx

    add eax, 7992
    add eax, 7532
    add eax, 820
    add eax, 329
    add eax, 329

    cmp r8d, eax
    jl StrongCherryA


    ; ========================================
    ; ⑧ 強チェリーB
    ; ID = 7
    ; 1/397.2
    ; 165
    ; ========================================

    mov eax, 65536
    xor edx, edx

    mov ecx, 10
    mul ecx

    mov ecx, 3972
    div ecx

    add eax, 7992
    add eax, 7532
    add eax, 820
    add eax, 329
    add eax, 329
    add eax, 165

    cmp r8d, eax
    jl StrongCherryB


    ; ========================================
    ; ⑨ チャンス目A
    ; ID = 8
    ; 1/199.2
    ; 329
    ; ========================================

    mov eax, 65536
    xor edx, edx

    mov ecx, 10
    mul ecx

    mov ecx, 1992
    div ecx

    add eax, 7992
    add eax, 7532
    add eax, 820
    add eax, 329
    add eax, 329
    add eax, 165
    add eax, 165

    cmp r8d, eax
    jl ChanceA


    ; ========================================
    ; ⑩ チャンス目リプレイ
    ; ID = 9
    ; 1/198.2
    ; 330
    ; ========================================

    mov eax, 65536
    xor edx, edx

    mov ecx, 10
    mul ecx

    mov ecx, 1982
    div ecx

    add eax, 7992
    add eax, 7532
    add eax, 820
    add eax, 329
    add eax, 329
    add eax, 165
    add eax, 165
    add eax, 329

    cmp r8d, eax
    jl ChanceReplay


    ; ========================================
    ; ⑪ 押し順ベルA
    ; ID = 10
    ; 1/5.58
    ; 1174
    ; ========================================

    mov eax, 65536
    xor edx, edx

    mov ecx, 100
    mul ecx

    mov ecx, 558
    div ecx

    add eax, 7992
    add eax, 7532
    add eax, 820
    add eax, 329
    add eax, 329
    add eax, 165
    add eax, 165
    add eax, 329
    add eax, 330

    cmp r8d, eax
    jl OrderBellA


    ; ========================================
    ; ⑫ 押し順ベルB
    ; ID = 11
    ; 1/5.58
    ; 1174
    ; ========================================

    mov eax, 1174

    add eax, 7992
    add eax, 7532
    add eax, 820
    add eax, 329
    add eax, 329
    add eax, 165
    add eax, 165
    add eax, 329
    add eax, 330
    add eax, 1174

    cmp r8d, eax
    jl OrderBellB


    ; ========================================
    ; ⑬ 押し順ベルC
    ; ID = 12
    ; 1/5.58
    ; 1174
    ; ========================================

    mov eax, 1174

    add eax, 7992
    add eax, 7532
    add eax, 820
    add eax, 329
    add eax, 329
    add eax, 165
    add eax, 165
    add eax, 329
    add eax, 330
    add eax, 1174
    add eax, 1174

    cmp r8d, eax
    jl OrderBellC


    ; ========================================
    ; ⑭ 押し順ベルD
    ; ID = 13
    ; 1/5.58
    ; 1174
    ; ========================================

    mov eax, 1174

    add eax, 7992
    add eax, 7532
    add eax, 820
    add eax, 329
    add eax, 329
    add eax, 165
    add eax, 165
    add eax, 329
    add eax, 330
    add eax, 1174
    add eax, 1174
    add eax, 1174

    cmp r8d, eax
    jl OrderBellD


    ; ========================================
    ; ⑮ ハズレ
    ; ID = 0
    ; ========================================

    mov eax, 0
    ret


; ============================================
; 当選結果
; ============================================

Bell:
    mov eax, 1
    ret


Replay:
    mov eax, 2
    ret


Watermelon:
    mov eax, 3
    ret


WeakCherryA:
    mov eax, 4
    ret


WeakCherryB:
    mov eax, 5
    ret


StrongCherryA:
    mov eax, 6
    ret


StrongCherryB:
    mov eax, 7
    ret


ChanceA:
    mov eax, 8
    ret


ChanceReplay:
    mov eax, 9
    ret


OrderBellA:
    mov eax, 10
    ret


OrderBellB:
    mov eax, 11
    ret


OrderBellC:
    mov eax, 12
    ret


OrderBellD:
    mov eax, 13
    ret


FlagLottery ENDP

END