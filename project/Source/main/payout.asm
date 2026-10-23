
.code

PUBLIC ApplyResult

; ============================================================
; ApplyResult
;
; 引数（Windows x64 呼び出し規約）
; RCX = 当選役ID
; RDX = リール停止結果（1 = 成立、0 = 不成立）
; R8  = メダル所持数のアドレス
; R9  = リプレイ権のアドレス
;
; 戻り値 EAX
; 0 = 払い出しなし
; 2 = 2枚払い出し
; 3 = 3枚払い出し
; ============================================================

ApplyResult PROC

    ; リール停止結果が不成立なら払い出しなし
    test edx, edx
    jz NO_PAYOUT

    ; ベル：ID 1
    cmp ecx, 1
    je PAY_BELL

    ; リプレイ：ID 2
    cmp ecx, 2
    je PAY_REPLAY

    ; スイカ：ID 3
    cmp ecx, 3
    je PAY_WATERMELON

    ; チャンスリプレイ：ID 9
    cmp ecx, 9
    je PAY_CHANCE_REPLAY

    ; その他の役は払い出しなし
    jmp NO_PAYOUT


PAY_BELL:
    add DWORD PTR [r8], 2
    mov eax, 2
    ret


PAY_WATERMELON:
    add DWORD PTR [r8], 3
    mov eax, 3
    ret


PAY_REPLAY:
    mov DWORD PTR [r9], 1
    xor eax, eax
    ret


PAY_CHANCE_REPLAY:
    mov DWORD PTR [r9], 1
    xor eax, eax
    ret


NO_PAYOUT:
    xor eax, eax
    ret

ApplyResult ENDP

END
