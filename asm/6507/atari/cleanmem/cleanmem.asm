    processor 6502

    seg code
    org $F000   ; Define the code origin at $F000

Start:
    SEI         ; Disable interrupts
    CLD         ; (clear) Disable the BCD decimal math mode
    LDX #$FF    ; Loads the X register with #$FF
    TXS         ; Transfer the X register to the (S)tack Pointer

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Clear the Page Zero region ($00 to $FF)
; Meaning the entire RAM and algo the entire TIA register
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    LDA #0      ; A = 0
    LDX #$FF    ; X = #$FF
    STA $FF     ; make sure $FF is zero before dec
MemLoop:
    DEX         ; X--
    STA $0,X    ; Store the value of A inside memory addres $0 + X
    BNE MemLoop ; if x != 0, MemLoop

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Fill the ROM size to exactly 4KB
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    org $FFFC
    .word Start ; Reset vector at $FFFC (where the program starts)
    .word Start ; Interrupt vector at $FFFE (unused in the VCS)
