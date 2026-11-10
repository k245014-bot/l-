
EXTERN GetAsyncKeyState:PROC

.data

; 前回のキー状態
prevX       DWORD 0
prevSpace   DWORD 0
prevLeft    DWORD 0
prevDown    DWORD 0
prevRight   DWORD 0

.code

PUBLIC GetSlotButtons

; ============================================================
; GetSlotButtons
;
; 戻り値 EAX
;
; bit 0 = MAXベット (X)
; bit 1 = レバー (SPACE)
; bit 2 = 左ストップ (LEFT)
; bit 3 = 中ストップ (DOWN)
; bit 4 = 右ストップ (RIGHT)
;
; 同時押し対策：
; ・ストップボタン同士の同時押しは禁止
; ・ストップボタンが1つだけなら最優先
; ・複数のストップボタンが押された場合は全て無効
; ・その場合、レバー → MAXベットの順に判定
; ・長押しでは連続判定しない
; ============================================================

GetSlotButtons PROC

    push rbx
    sub rsp, 20h

    xor ebx, ebx

; ------------------------------------------------------------
; Xキー
; ------------------------------------------------------------

    mov ecx, 58h
    call GetAsyncKeyState

    test ax, 8000h
    jz X_RELEASED

    cmp prevX, 0
    jne X_END

    mov prevX, 1
    or ebx, 1
    jmp X_END

X_RELEASED:
    mov prevX, 0

X_END:

; ------------------------------------------------------------
; SPACEキー
; ------------------------------------------------------------

    mov ecx, 20h
    call GetAsyncKeyState

    test ax, 8000h
    jz SPACE_RELEASED

    cmp prevSpace, 0
    jne SPACE_END

    mov prevSpace, 1
    or ebx, 2
    jmp SPACE_END

SPACE_RELEASED:
    mov prevSpace, 0

SPACE_END:

; ------------------------------------------------------------
; LEFTキー
; ------------------------------------------------------------

    mov ecx, 25h
    call GetAsyncKeyState

    test ax, 8000h
    jz LEFT_RELEASED

    cmp prevLeft, 0
    jne LEFT_END

    mov prevLeft, 1
    or ebx, 4
    jmp LEFT_END

LEFT_RELEASED:
    mov prevLeft, 0

LEFT_END:

; ------------------------------------------------------------
; DOWNキー
; ------------------------------------------------------------

    mov ecx, 28h
    call GetAsyncKeyState

    test ax, 8000h
    jz DOWN_RELEASED

    cmp prevDown, 0
    jne DOWN_END

    mov prevDown, 1
    or ebx, 8
    jmp DOWN_END

DOWN_RELEASED:
    mov prevDown, 0

DOWN_END:

; ------------------------------------------------------------
; RIGHTキー
; ------------------------------------------------------------

    mov ecx, 27h
    call GetAsyncKeyState

    test ax, 8000h
    jz RIGHT_RELEASED

    cmp prevRight, 0
    jne RIGHT_END

    mov prevRight, 1
    or ebx, 16
    jmp RIGHT_END

RIGHT_RELEASED:
    mov prevRight, 0

RIGHT_END:

; ============================================================
; 同時押しチェック
; ============================================================

    ; ストップボタンの入力だけ取り出す
    mov eax, ebx
    and eax, 1Ch

    ; 2進数で1ビットだけ立っているか確認
    ; x & (x - 1) が0でなければ複数入力
    mov edx, eax
    dec edx
    and edx, eax
    jnz MULTI_STOP

    ; ストップボタンが1つだけなら優先して返す
    test eax, eax
    jnz RETURN_INPUT

    ; ストップボタンがなければレバーを確認
    test ebx, 2
    jnz RETURN_SPACE

    ; 次にMAXベットを確認
    test ebx, 1
    jnz RETURN_X

    ; 入力なし
    jmp RETURN_INPUT


MULTI_STOP:

    ; ストップボタンが複数なら全て無効にする
    and ebx, 0FFFFFFE3h

    ; レバーを優先
    test ebx, 2
    jnz RETURN_SPACE

    ; 次にMAXベット
    test ebx, 1
    jnz RETURN_X

    ; 有効な入力なし
    jmp RETURN_INPUT


RETURN_SPACE:
    mov ebx, 2
    jmp RETURN_INPUT

RETURN_X:
    mov ebx, 1


RETURN_INPUT:

    mov eax, ebx

    add rsp, 20h
    pop rbx

    ret

GetSlotButtons ENDP

END