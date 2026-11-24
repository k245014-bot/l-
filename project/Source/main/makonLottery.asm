
;==========================================================
; makon.asm
;
; 魔魂管理・魔魂獲得抽選・逆押し魔魂揃い抽選
;
; 乱数生成は random.asm に一本化
;
; 小役ID
;   0  HAZURE
;   1  BELLA
;   2  BELLB
;   3  BELLC
;   4  BELLD
;   5  REPLAYA
;   6  REPLAYB
;   7  REPLAYC
;   8  REPLAYD
;   9  WATERMELON
;   10 CHERRY_A_WEAK
;   11 CHERRY_B_WEAK
;   12 CHERRY_A_STRONG
;   13 CHERRY_B_STRONG
;   14 CHANCE
;   15 CHANCE_REPLAY
;   16 BELL_ORDER_A
;   17 BELL_ORDER_B
;   18 BELL_ORDER_C
;   19 BELL_ORDER_D
;
;==========================================================


.data

;----------------------------------------------------------
; 魔魂ストック
;----------------------------------------------------------
makonCount DWORD 0


;----------------------------------------------------------
; 通常の魔魂獲得確率（%）
;
; 小役IDと同じ順番で設定
;----------------------------------------------------------
MakonRateTable DWORD 0, 5,5,5,5, 3,3,3,3, 30, 15,15, 30,30, 25,25, 5,5,5,5


;----------------------------------------------------------
; 逆押し魔魂揃い抽選確率（%）
;
; ベルA～D・リプレイA～Dのみ使用
;----------------------------------------------------------
ReverseMakonRate DWORD 10


;----------------------------------------------------------
; 魔魂バトル勝利確率（%）
;----------------------------------------------------------
BattleWinRate DWORD 50


.code


;----------------------------------------------------------
; random.asm の関数を外部参照
;----------------------------------------------------------
EXTERN GetRandom:PROC
EXTERN SetRandomSeed:PROC


PUBLIC MakonLottery
PUBLIC MakonControl
PUBLIC MakonBattle
PUBLIC GetMakon
PUBLIC ResetMakon
PUBLIC SetMakonRate
PUBLIC SetReverseMakonRate
PUBLIC SetBattleWinRate



;==========================================================
; MakonLottery
;
; ECX = 成立した小役ID
;
; 処理
; ① 通常魔魂獲得抽選
; ② ベル・リプレイの場合のみ逆押し魔魂揃い抽選
; ③ ベルA・リプレイAのみ逆押し抽選当選で魔魂獲得
;
; 戻り値
; EAX =  1 : 魔魂獲得
; EAX =  0 : 魔魂獲得なし
; EAX = -1 : 不正な小役ID
;==========================================================

MakonLottery PROC

    ; 小役ID確認
    cmp ecx, 19
    ja InvalidRole

    ; スタック確保
    ; Shadow Space 32byte + Local 8byte
    sub rsp, 28h

    ; 小役ID保存
    mov DWORD PTR [rsp+32], ecx


    ;------------------------------------------------------
    ; ① 通常魔魂獲得抽選
    ;------------------------------------------------------

    ; 小役IDに対応した確率を取得
    mov eax, ecx
    lea rdx, MakonRateTable
    mov eax, DWORD PTR [rdx+rax*4]

    ; 確率を保存
    mov DWORD PTR [rsp+36], eax

    ; 乱数取得
    call GetRandom

    ; 0～99に変換
    xor edx, edx
    mov ecx, 100
    div ecx

    ; 通常抽選判定
    cmp edx, DWORD PTR [rsp+36]
    jb NormalHit


    ;------------------------------------------------------
    ; ② ベルA～D・リプレイA～Dか確認
    ;------------------------------------------------------

    mov ecx, DWORD PTR [rsp+32]

    cmp ecx, 1
    jb LotteryMiss

    cmp ecx, 8
    ja LotteryMiss


    ;------------------------------------------------------
    ; ③ 逆押し魔魂揃い抽選
    ;------------------------------------------------------

    call GetRandom

    ; 0～99に変換
    xor edx, edx
    mov ecx, 100
    div ecx

    ; 逆押し魔魂揃い抽選
    cmp edx, DWORD PTR [ReverseMakonRate]
    jae LotteryMiss


    ;------------------------------------------------------
    ; ④ ベルA・リプレイAか確認
    ;------------------------------------------------------

    mov ecx, DWORD PTR [rsp+32]

    ; BELLA = 1
    cmp ecx, 1
    je ReverseHit

    ; REPLAYA = 5
    cmp ecx, 5
    je ReverseHit

    ; ベルB～D・リプレイB～D
    jmp LotteryMiss



;----------------------------------------------------------
; 通常抽選当選
;----------------------------------------------------------
NormalHit:

    cmp DWORD PTR [makonCount], 7FFFFFFFh
    jae NormalHitReturn

    inc DWORD PTR [makonCount]

NormalHitReturn:

    mov eax, 1
    add rsp, 28h
    ret



;----------------------------------------------------------
; 逆押し抽選当選
;----------------------------------------------------------
ReverseHit:

    cmp DWORD PTR [makonCount], 7FFFFFFFh
    jae ReverseHitReturn

    inc DWORD PTR [makonCount]

ReverseHitReturn:

    mov eax, 1
    add rsp, 28h
    ret



;----------------------------------------------------------
; 魔魂獲得なし
;----------------------------------------------------------
LotteryMiss:

    xor eax, eax
    add rsp, 28h
    ret



;----------------------------------------------------------
; 不正な小役ID
;----------------------------------------------------------
InvalidRole:

    mov eax, -1
    ret

MakonLottery ENDP



;==========================================================
; MakonControl
;
; ECX = 操作タイプ
;
; 0 : 魔魂を1個加算
; 1 : 魔魂を1個消費
;
; 戻り値
; EAX = 現在の魔魂数
;==========================================================

MakonControl PROC

    cmp ecx, 0
    je AddMakon

    cmp ecx, 1
    je ConsumeMakon

    jmp MakonControlEnd


AddMakon:

    cmp DWORD PTR [makonCount], 7FFFFFFFh
    jae MakonControlEnd

    inc DWORD PTR [makonCount]
    jmp MakonControlEnd


ConsumeMakon:

    cmp DWORD PTR [makonCount], 0
    jbe MakonControlEnd

    dec DWORD PTR [makonCount]


MakonControlEnd:

    mov eax, DWORD PTR [makonCount]
    ret

MakonControl ENDP



;==========================================================
; MakonBattle
;
; 魔魂を1個消費してバトル抽選
;
; 戻り値
; EAX =  1 : 勝利
; EAX =  0 : 敗北
; EAX = -1 : 魔魂不足
;==========================================================

MakonBattle PROC

    ; 魔魂確認
    cmp DWORD PTR [makonCount], 0
    jle BattleNoMakon

    ; 魔魂を1個消費
    dec DWORD PTR [makonCount]

    ; スタック確保
    sub rsp, 28h

    ; 乱数取得
    call GetRandom

    ; 0～99に変換
    xor edx, edx
    mov ecx, 100
    div ecx

    ; 勝利確率判定
    cmp edx, DWORD PTR [BattleWinRate]
    jb BattleWin

    ; 敗北
    xor eax, eax
    add rsp, 28h
    ret


BattleWin:

    mov eax, 1
    add rsp, 28h
    ret


BattleNoMakon:

    mov eax, -1
    ret

MakonBattle ENDP



;==========================================================
; GetMakon
;
; 現在の魔魂数を取得
;==========================================================

GetMakon PROC

    mov eax, DWORD PTR [makonCount]
    ret

GetMakon ENDP



;==========================================================
; ResetMakon
;
; 魔魂数・乱数Seedを初期化
;==========================================================

ResetMakon PROC

    ; スタック確保
    sub rsp, 28h

    ; 魔魂数を初期化
    mov DWORD PTR [makonCount], 0

    ; 共通乱数Seedを初期化
    mov ecx, 0A341316Ch
    call SetRandomSeed

    add rsp, 28h

    ret

ResetMakon ENDP



;==========================================================
; SetMakonRate
;
; ECX = 小役ID
; EDX = 通常魔魂獲得確率（0～100）
;
; 戻り値
; EAX = 1 : 設定成功
; EAX = 0 : 設定失敗
;==========================================================

SetMakonRate PROC

    cmp ecx, 19
    ja SetRateError

    cmp edx, 100
    ja SetRateError

    lea rax, MakonRateTable
    mov DWORD PTR [rax+rcx*4], edx

    mov eax, 1
    ret


SetRateError:

    xor eax, eax
    ret

SetMakonRate ENDP



;==========================================================
; SetReverseMakonRate
;
; ECX = 逆押し魔魂揃い抽選確率（0～100）
;
; 戻り値
; EAX = 1 : 設定成功
; EAX = 0 : 設定失敗
;==========================================================

SetReverseMakonRate PROC

    cmp ecx, 100
    ja ReverseRateError

    mov DWORD PTR [ReverseMakonRate], ecx

    mov eax, 1
    ret


ReverseRateError:

    xor eax, eax
    ret

SetReverseMakonRate ENDP



;==========================================================
; SetBattleWinRate
;
; ECX = バトル勝利確率（0～100）
;
; 戻り値
; EAX = 1 : 設定成功
; EAX = 0 : 設定失敗
;==========================================================

SetBattleWinRate PROC

    cmp ecx, 100
    ja BattleRateError

    mov DWORD PTR [BattleWinRate], ecx

    mov eax, 1
    ret


BattleRateError:

    xor eax, eax
    ret

SetBattleWinRate ENDP


END
