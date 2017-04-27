.EXPORT _testFillBytesFromTo
.include "mem.sh"

.PROC _testFillBytesFromTo
    lda #$04
    pha
    lda #$c2
    pha
    ldx #$04
    ldy #$c0
    lda #$55
    jsr fillbytefromto
    pla
    pla

    lda #$78
    pha
    lda #$93
    pha
    ldx #$0e
    ldy #$81
    lda #$aa
    jsr fillbytefromto
    pla
    pla
    rts
.ENDPROC

