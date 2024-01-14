	processor 6502
	seg Code
	org $F000
Start:
	lda #$82	; Load the A register with the literal hexadecimal value $82
	ldx #82		; Load the X register with the literal decimal value 82
	ldy $82		; Load the Y register with the value that is inside memory position $82

        jmp Start

	org $FFFC
	.word Start
	.word Start
