.data
    ; 魔魂の所持数
    makonCount DWORD 0

    ; 乱数の状態を保存
    randomSeed DWORD 0

.code

; ==========================================
; 乱数生成処理
; 戻り値 EAX = 32ビット乱数
; ==========================================
GetRandom PROC

    ; 初回だけRDTSCで初期値を取得
    mov eax, DWORD PTR [randomSeed]
    test eax, eax
    jnz RANDOM_START

    rdtsc
    xor eax, edx

    ; 乱数の初期値が0なら別の値を設定
    test eax, eax
    jnz RANDOM_START

    mov eax, 0A341316Ch

RANDOM_START:

    ; Xorshift32
    mov edx, eax
    shl edx, 13
    xor eax, edx

    mov edx, eax
    shr edx, 17
    xor eax, edx

    mov edx, eax
    shl edx, 5
    xor eax, edx

    ; 次回のために保存
    mov DWORD PTR [randomSeed], eax

    ret

GetRandom ENDP


; ==========================================
; 魔魂抽選
; 戻り値
; EAX = 1 : 当選
; EAX = 0 : ハズレ
; ==========================================
MakonLottery PROC

    ; GetRandomを呼び出すための領域
    sub rsp, 40

    call GetRandom

    add rsp, 40

    ; 乱数を100で割る
    xor edx, edx
    mov ecx, 100
    div ecx

    ; 余りが0～9なら当選
    cmp edx, 10
    jb LOTTERY_HIT

    xor eax, eax
    ret

LOTTERY_HIT:
    mov eax, 1
    ret

MakonLottery ENDP


; ==========================================
; 魔魂の獲得・消費
; ECX = 0 : 獲得
; ECX = 1 : 消費
; 戻り値 EAX = 処理後の所持数
; ==========================================
MakonControl PROC

    cmp ecx, 0
    je MAKON_ADD

    cmp ecx, 1
    je MAKON_USE

    jmp MAKON_END

MAKON_ADD:
    add DWORD PTR [makonCount], 1
    jmp MAKON_END

MAKON_USE:
    cmp DWORD PTR [makonCount], 0
    jle MAKON_END

    sub DWORD PTR [makonCount], 1

MAKON_END:
    mov eax, DWORD PTR [makonCount]
    ret

MakonControl ENDP


; ==========================================
; 魔魂所持数取得
; ==========================================
GetMakon PROC

    mov eax, DWORD PTR [makonCount]
    ret

GetMakon ENDP


; ==========================================
; 魔魂初期化
; ==========================================
ResetMakon PROC

    mov DWORD PTR [makonCount], 0
    ret

ResetMakon ENDP

END