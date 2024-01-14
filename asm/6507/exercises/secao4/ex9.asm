    processor 6502
    seg Code         ; Define a new segment named "Code"
    org $F000        ; Define the origin of the ROM code at memory address $F000
Start:
    LDA #1

Loop:
    CLC
    ADC #1

    CMP #10
    BNE Loop

    JMP Start

    org $FFFC        ; End the ROM by adding required values to memory position $FFFC
    .word Start      ; Put 2 bytes with the reset address at memory position $FFFC
    .word Start      ; Put 2 bytes with the break address at memory position $FFFE