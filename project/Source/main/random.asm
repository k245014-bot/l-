
.data

;================================
; 乱数の保存領域
;================================

RandomSeed DWORD 0A341316Ch


.code

PUBLIC GetRandom
PUBLIC SetRandomSeed


;================================
; 乱数の初期値を設定
;
; 引数 RCX = 初期値
;================================

SetRandomSeed PROC

    mov eax, ecx

    ; 0の場合は固定の初期値を使用
    test eax, eax
    jnz SeedSet

    mov eax, 0A341316Ch

SeedSet:
    mov DWORD PTR [RandomSeed], eax

    ret

SetRandomSeed ENDP


;================================
; Xorshift32
;
; 戻り値 EAX = 32bit乱数
;================================

GetRandom PROC

    mov eax, DWORD PTR [RandomSeed]

    ; x ^= x << 13
    mov edx, eax
    shl edx, 13
    xor eax, edx

    ; x ^= x >> 17
    mov edx, eax
    shr edx, 17
    xor eax, edx

    ; x ^= x << 5
    mov edx, eax
    shl edx, 5
    xor eax, edx

    ; 更新した乱数を保存
    mov DWORD PTR [RandomSeed], eax

    ret

GetRandom ENDP

END
