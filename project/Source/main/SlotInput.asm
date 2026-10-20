EXTERN GetAsyncKeyState:PROC

.data
prevSpace DWORD 0

.code

SpacePressedOnce PROC
    sub rsp, 28h

    mov ecx, 20h          ; スペースキー
    call GetAsyncKeyState

    add rsp, 28h

    xor edx, edx
    test ax, 8000h
    setnz dl

    cmp dword ptr [prevSpace], 0
    jne was_pressed

    mov dword ptr [prevSpace], edx
    mov eax, edx
    ret

was_pressed:
    mov dword ptr [prevSpace], edx
    xor eax, eax
    ret

SpacePressedOnce ENDP

END