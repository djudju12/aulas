    processor 6502
    seg Code         ; Define a new segment named "Code"
    org $F000        ; Define the origin of the ROM code at memory address $F000
Start:
    LDY #10          ; Loop counter
Loop:
    TYA              ; Transfer Y to A
    STA $80,Y        ; Store the value of A in the memory pos $80+Y
    DEY              ; DEC Y
    BPL  Loop        ; Loop

    JMP Start

    org $FFFC        ; End the ROM by adding required values to memory position $FFFC
    .word Start      ; Put 2 bytes with the reset address at memory position $FFFC
    .word Start      ; Put 2 bytes with the break address at memory position $FFFE