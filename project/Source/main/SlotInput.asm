
EXTERN GetAsyncKeyState:PROC

.data
prevX     DWORD 0
prevSpace DWORD 0
prevLeft  DWORD 0
prevDown  DWORD 0
prevRight DWORD 0

.code

; 戻り値 EAX のビット
; bit 0 (1)  = Xキー：MAX BET
; bit 1 (2)  = SPACE：レバー
; bit 2 (4)  = LEFT：左停止
; bit 3 (8)  = DOWN：中停止
; bit 4 (16) = RIGHT：右停止
;
; 押した瞬間だけ、対応するビットを1にする

GetSlotButtons PROC
    push rbx
    sub rsp, 20h

    xor ebx, ebx

    ; -------------------------
    ; Xキー：MAX BET
    ; -------------------------
    mov ecx, 58h
    call GetAsyncKeyState

    xor edx, edx
    test ax, 8000h
    setnz dl

    cmp dword ptr [prevX], 0
    jne x_store
    test edx, edx
    jz x_store
    or ebx, 1

x_store:
    mov dword ptr [prevX], edx

    ; -------------------------
    ; SPACE：レバー
    ; -------------------------
    mov ecx, 20h
    call GetAsyncKeyState

    xor edx, edx
    test ax, 8000h
    setnz dl

    cmp dword ptr [prevSpace], 0
    jne space_store
    test edx, edx
    jz space_store
    or ebx, 2

space_store:
    mov dword ptr [prevSpace], edx

    ; -------------------------
    ; LEFT：左停止
    ; -------------------------
    mov ecx, 25h
    call GetAsyncKeyState

    xor edx, edx
    test ax, 8000h
    setnz dl

    cmp dword ptr [prevLeft], 0
    jne left_store
    test edx, edx
    jz left_store
    or ebx, 4

left_store:
    mov dword ptr [prevLeft], edx

    ; -------------------------
    ; DOWN：中停止
    ; -------------------------
    mov ecx, 28h
    call GetAsyncKeyState

    xor edx, edx
    test ax, 8000h
    setnz dl

    cmp dword ptr [prevDown], 0
    jne down_store
    test edx, edx
    jz down_store
    or ebx, 8

down_store:
    mov dword ptr [prevDown], edx

    ; -------------------------
    ; RIGHT：右停止
    ; -------------------------
    mov ecx, 27h
    call GetAsyncKeyState

    xor edx, edx
    test ax, 8000h
    setnz dl

    cmp dword ptr [prevRight], 0
    jne right_store
    test edx, edx
    jz right_store
    or ebx, 16

right_store:
    mov dword ptr [prevRight], edx

    ; 検出したボタン一覧を返す
    mov eax, ebx

    add rsp, 20h
    pop rbx
    ret
GetSlotButtons ENDP

END
