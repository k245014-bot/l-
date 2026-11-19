
.data
    ; ======================================
    ; 魔魂管理データ
    ; ======================================

    makonCount DWORD 0       ; 魔魂所持数
    randomSeed DWORD 0       ; 乱数の状態

.code

PUBLIC GetRandom
PUBLIC MakonLottery
PUBLIC MakonControl
PUBLIC MakonBattle
PUBLIC GetMakon
PUBLIC ResetMakon


; ==========================================
; 乱数生成処理
;
; 戻り値 EAX = 32ビット乱数
;
; RDTSCで初期値を作り、
; Xorshift32で乱数を生成する
; ==========================================
GetRandom PROC

    ; 初期化されていなければ初期値を取得
    mov eax, DWORD PTR [randomSeed]
    test eax, eax
    jnz RANDOM_START

    rdtsc
    xor eax, edx

    ; 0の場合は固定値を設定
    test eax, eax
    jnz RANDOM_START

    mov eax, 0A341316Ch

RANDOM_START:

    ; Xorshift32 その1
    mov edx, eax
    shl edx, 13
    xor eax, edx

    ; Xorshift32 その2
    mov edx, eax
    shr edx, 17
    xor eax, edx

    ; Xorshift32 その3
    mov edx, eax
    shl edx, 5
    xor eax, edx

    ; 次回のために保存
    mov DWORD PTR [randomSeed], eax

    ret

GetRandom ENDP


; ==========================================
; 魔魂獲得抽選
;
; 10%で当選
;
; 戻り値
; EAX = 1 : 当選
; EAX = 0 : ハズレ
; ==========================================
MakonLottery PROC

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
; 魔魂の加算・消費
;
; 引数 ECX
; 0 : 魔魂獲得
; 1 : 魔魂消費
;
; 戻り値 EAX : 処理後の所持数
; ==========================================
MakonControl PROC

    cmp ecx, 0
    je MAKON_ADD

    cmp ecx, 1
    je MAKON_USE

    jmp MAKON_END


; 魔魂獲得
MAKON_ADD:

    ; 所持数の上限チェック
    mov eax, DWORD PTR [makonCount]
    cmp eax, 7FFFFFFFh
    jae MAKON_END

    add DWORD PTR [makonCount], 1
    jmp MAKON_END


; 魔魂消費
MAKON_USE:

    ; 所持数が0なら消費しない
    cmp DWORD PTR [makonCount], 0
    jle MAKON_END

    sub DWORD PTR [makonCount], 1


MAKON_END:

    mov eax, DWORD PTR [makonCount]
    ret

MakonControl ENDP


; ==========================================
; バトル処理
;
; 魔魂を1個消費して勝敗抽選
;
; 戻り値
; EAX =  1 : 勝利
; EAX =  0 : 敗北
; EAX = -1 : 魔魂不足
;
; 勝率50%
; ==========================================
MakonBattle PROC

    ; 魔魂の所持数確認
    cmp DWORD PTR [makonCount], 1
    jl BATTLE_NO_MAKON

    ; 魔魂を1個消費
    sub DWORD PTR [makonCount], 1

    ; 乱数生成
    sub rsp, 40

    call GetRandom

    add rsp, 40

    ; 乱数を100で割る
    xor edx, edx
    mov ecx, 100
    div ecx

    ; 25%で勝利
    cmp edx, 25
    jb BATTLE_WIN

    ; 敗北
    xor eax, eax
    ret


BATTLE_WIN:

    mov eax, 1
    ret


BATTLE_NO_MAKON:

    mov eax, -1
    ret

MakonBattle ENDP


; ==========================================
; 魔魂所持数取得
;
; 戻り値 EAX = 所持数
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
