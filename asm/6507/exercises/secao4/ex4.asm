    processor 6502
    seg Code         ; Define a new segment named "Code"
    org $F000        ; Define the origin of the ROM code at memory address $F000
Start:

    lda #100 ; Load the A register with the literal decimal value 100 ($64)

    clc      ; always clear the carry when performing add
    adc #5   ; Add the decimal value 5 to the accumulator ($69)

    sec      ; always set the carry when calling sbc
    sbc #10  ; Subtract the decimal value 10 from the accumulator 95 (or $5F in hexadecimal)

    JMP Start

    org $FFFC        ; End the ROM by adding required values to memory position $FFFC
    .word Start      ; Put 2 bytes with the reset address at memory position $FFFC
    .word Start      ; Put 2 bytes with the break address at memory position $FFFE
