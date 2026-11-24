
.data

;================================
; 小役抽選テーブル
;
; DWORD 1 = 抽選範囲の上限
; DWORD 2 = 小役ID
;================================

LotteryTable DWORD 1998, 1
             DWORD 3996, 2
             DWORD 5994, 3
             DWORD 7992, 4

             DWORD 9875, 5
             DWORD 11758, 6
             DWORD 13641, 7
             DWORD 15524, 8

             DWORD 16344, 9
             DWORD 16673, 10
             DWORD 17002, 11
             DWORD 17167, 12
             DWORD 17332, 13
             DWORD 17661, 14
             DWORD 17991, 15

             DWORD 19165, 16
             DWORD 20339, 17
             DWORD 21513, 18
             DWORD 22687, 19


.code

PUBLIC FlagSymbol
EXTERN GetRandom:PROC


FlagSymbol PROC

    ; スタック領域確保
    sub rsp, 28h

    ; 乱数取得
    call GetRandom

    ; 0～65535に変換
    and eax, 0FFFFh

    ; 抽選値保存
    mov r8d, eax

    ; テーブル先頭
    lea rdx, LotteryTable

    xor r9d, r9d


LotteryLoop:

    ; 19種類確認したか
    cmp r9d, 19
    jae LotteryMiss

    ; 抽選値と上限を比較
    cmp r8d, DWORD PTR [rdx+r9*8]
    jb LotteryHit

    inc r9d
    jmp LotteryLoop


LotteryHit:

    ; 小役IDを取得
    mov eax, DWORD PTR [rdx+r9*8+4]

    add rsp, 28h
    ret


LotteryMiss:

    ; ハズレ
    xor eax, eax

    add rsp, 28h
    ret

FlagSymbol ENDP

END
