
    processor 6502

    include "../vcs.h"
    include "../macro.h"

    seg code
    org $F000

Reset:
    CLEAN_START

    LDX #$80
    STX COLUBK           ; blue background color

    LDA #$1C             ; yellow playfield color
    STA COLUPF

StartFrame:
    LDA #02
    STA VBLANK
    STA VSYNC

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Generate the three lines of the VSYNC
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    REPEAT 3
        sta WSYNC
    REPEND
    LDA #0
    STA VSYNC

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Let the TIA output the 37 lines of the VBLANK
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    REPEAT 37
        sta WSYNC
    REPEND
    LDA #0
    STA VBLANK

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Set the CTRLPF register to allow playfield reflection
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    LDX #%0000000001   ; CTRLPF register (D0 Menas playfield reflection)
    STX CTRLPF

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Draw the 192 visible scanlines
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ; Skip 7 scanlines with no pf
    LDX #0
    STX PF0
    STX PF1
    STX PF2
    REPEAT 7
        STA WSYNC
    REPEND

    LDX #%11100000
    STX PF0
    LDX #%11111111
    STX PF1
    STX PF2
    REPEAT 7
        STA WSYNC
    REPEND

    LDX #%01100000
    STX PF0
    LDX #%00000000
    LDY #%10000000
    STX PF1
    STY PF2
    REPEAT 164
        STA WSYNC
    REPEND

    LDX #%11100000
    STX PF0
    LDX #%11111111
    STX PF1
    STX PF2
    REPEAT 7
        STA WSYNC
    REPEND

    ; Skip 7 scanlines with no pf
    LDX #0
    STX PF0
    STX PF1
    STX PF2
    REPEAT 7
        STA WSYNC
    REPEND

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Output the 30 more VBLANK oversacan lines
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    LDA #2
    STA VBLANK
    REPEAT 30
        STA WSYNC
    REPEND
    LDA #0
    STA VBLANK

    JMP StartFrame

    org $FFFC
    .word Reset
    .word Reset