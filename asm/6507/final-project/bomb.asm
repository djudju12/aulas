;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Program Name: Bomber Game
;; Author: https://www.udemy.com/course/programming-games-for-the-atari-2600
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    processor 6502

    include "vcs.h"
    include "macro.h"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Variables segment
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    seg.u Variables
    org $80

JetXPos         byte
JetYPos         byte
BomberXPos      byte
BomberYPos      byte
JetSpritePtr    word
JetColorPtr     word
BomberSpritePtr word
BomberColorPtr  word
JetAnimOffset   byte
Random          byte

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Constants
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
JET_HEIGHT = 9
BOMBER_HEIGHT = 9

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Start of the program
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    seg code
    org $F000

Reset:
    CLEAN_START

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Init RAM variables and TIA register
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    LDA #50
    STA JetXPos
    LDA #10
    STA JetYPos

    LDA #40
    STA BomberXPos
    LDA #54
    STA BomberYPos

    LDA #%11010100
    STA Random

    LDA #<JetSprite
    STA JetSpritePtr
    LDA #>JetSprite
    STA JetSpritePtr+1

    LDA #<JetColor
    STA JetColorPtr
    LDA #>JetColor
    STA JetColorPtr+1

    LDA #<BomberSprite
    STA BomberSpritePtr
    LDA #>BomberSprite
    STA BomberSpritePtr+1

    LDA #<BomberColor
    STA BomberColorPtr
    LDA #>BomberColor
    STA BomberColorPtr+1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Start of the main loop
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
StartFrame:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Calculations and tasks performed in the pre-VBlank
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    LDA JetXPos
    LDY #0
    JSR SetObjectXPos

    LDA BomberXPos
    LDY #1
    JSR SetObjectXPos

    STA WSYNC
    STA HMOVE

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Generate the three lines of the VSYNC and 37 lines of the VBLANK
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    LDA #02
    STA VBLANK
    STA VSYNC
    REPEAT 3
        sta WSYNC
    REPEND
    LDA #0
    STA VSYNC
    REPEAT 37
        STA WSYNC
    REPEND
    STA VBLANK

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Display the scoreboard lines
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    LDA #0
    STA PF0
    STA PF1
    STA PF2
    STA GRP0
    STA GRP1
    STA COLUPF
    REPEAT 20
        STA WSYNC
    REPEND

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Display the visibles scanlines of the game
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
GameVisibleLine:
    LDA #$84            ; blue
    STA COLUBK

    LDA #$C2
    STA COLUPF          ; green

    LDA #1              ; Reflect playfield
    STA CTRLPF

    LDA #%11110000
    STA PF0

    LDA #%11110000
    STA PF1

    LDA #0
    STA PF2

    LDX #84             ; remaining of the visible scanlines
.GameLineLoop:
.AreWeInsideJetSprite:
    TXA
    SEC
    SBC JetYPos
    CMP JET_HEIGHT
    BCC .DrawSpriteP0
    LDA #0

.DrawSpriteP0:
    CLC
    ADC JetAnimOffset

    TAY                 ; load Y so we can work with the pointer
    LDA (JetSpritePtr),Y
    STA WSYNC
    STA GRP0
    LDA (JetColorPtr),Y
    STA COLUP0

.AreWeInsideBomberSprite:
    TXA
    SEC
    SBC BomberYPos
    CMP BOMBER_HEIGHT
    BCC .DrawSpriteP1
    LDA #0

.DrawSpriteP1:
    TAY                 ; load Y so we can work with the pointer
    LDA #5
    STA NUSIZ1          ; stretch player 1 sprite
    LDA (BomberSpritePtr),Y
    STA WSYNC
    STA GRP1
    LDA (BomberColorPtr),Y
    STA COLUP1

    DEX
    BNE .GameLineLoop
    LDA #0
    STA JetAnimOffset

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Output the 30 more VBLANK oversacan lines
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    LDA #2
    STA VBLANK
    REPEAT 30
        STA WSYNC
    REPEND
    LDA #0
    STA VBLANK

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Process joystick input for P0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
CheckP0Up:
    LDA #%00010000
    BIT SWCHA
    BNE CheckP0Down
    ; logic goes here \/
    INC JetYPos
    LDA #0
    STA JetAnimOffset

CheckP0Down:
    LDA #%00100000
    BIT SWCHA
    BNE CheckP0Left
    ; logic goes here \/
    DEC JetYPos
    LDA #0
    STA JetAnimOffset

CheckP0Left:
    LDA #%01000000
    BIT SWCHA
    BNE CheckP0Right
    ; logic goes here \/
    DEC JetXPos
    LDA JET_HEIGHT
    STA JetAnimOffset

CheckP0Right:
    LDA #%10000000
    BIT SWCHA
    BNE EndInputCheck
    ; logic goes here \/
    INC JetXPos
    LDA JET_HEIGHT
    STA JetAnimOffset


EndInputCheck:
    ; logic goes here \/

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Update positions
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
UpdateBomberPos:
    LDA BomberYPos
    CLC
    CMP #0
    BMI .ResetBomberPosition
    DEC BomberYPos
    JMP EndPositionUpdate

.ResetBomberPosition
    JSR GetRandomBomberPos

EndPositionUpdate:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Watch for the collisions
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
CheckCollissionP0P1:
    LDA  #%10000000
    BIT CXPPMM
    BNE .CollisionP0P1
    JMP CheckCollisionP0PF

CheckCollisionP0PF:
    LDA #%10000000
    BIT CXP0FB
    BNE .CollisionP0PF
    JMP EndCollisionCheck

.CollisionP0PF:
    JSR GameOver

.CollisionP0P1:
    JSR GameOver

EndCollisionCheck:
    STA CXCLR

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; End of the main loop
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    JMP StartFrame

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Game Over
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
GameOver subroutine
    LDA #$30
    STA COLUBK
    RTS

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Subroutine to handle object horizontal position with fine offset
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; A is the target x-coord position in pixels of our object
;; Y is the object type (0: P0, 1: P1, 2: Missile0, 3: Missile1, 4: Ball)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
SetObjectXPos subroutine
    STA WSYNC
    SEC
.Div15Loop
    SBC #15
    BCS .Div15Loop
    EOR #7
    ASL
    ASL
    ASL
    ASL
    STA HMP0,Y
    STA RESP0,Y
    RTS

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Subroutine to generate a LFSR random number
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Generate a LFSR random number
;; Divide the random value by 4 to limit the size of the result match river.
;; After, sums 30 to compensate the green PF
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
GetRandomBomberPos subroutine
    LDA Random          ; Load starting random seed
    ASL                 ; arithmetic shift-left
    EOR Random          ; XOR Accumulator with Random
    ASL                 ; arithmetic shift-left
    EOR Random          ; XOR Accumulator with Random
    ASL                 ; arithmetic shift-left
    ASL                 ; arithmetic shift-left
    EOR Random          ; XOR Accumulator with Random
    ASL                 ; arithmetic shift-left
    ROL Random          ; rotate left

    LSR                 ;
    LSR                 ; divide by 4
    STA BomberXPos
    LDA #30
    ADC BomberXPos
    STA BomberXPos

    LDA #84
    STA BomberYPos

    RTS

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Lookup table for the sprites
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
JetSprite:
    .byte #%00000000
    .byte #%00001000
    .byte #%01111111
    .byte #%00111110
    .byte #%00011100
    .byte #%00011100
    .byte #%00001000
    .byte #%00001000
    .byte #%00001000

JetSpriteTurn:
    .byte #%00000000
    .byte #%00001000
    .byte #%00111110
    .byte #%00011100
    .byte #%00011100
    .byte #%00011100
    .byte #%00001000
    .byte #%00001000
    .byte #%00001000

JetColor:
    .byte #$00
    .byte #$FE
    .byte #$08
    .byte #$0A
    .byte #$0C
    .byte #$02
    .byte #$B8
    .byte #$0A
    .byte #$04

    .byte #$00
    .byte #$FE
    .byte #$08
    .byte #$0A
    .byte #$0C
    .byte #$02
    .byte #$B8
    .byte #$0A
    .byte #$04

BomberSprite:
    .byte #%00000000
    .byte #%00001000
    .byte #%00001000
    .byte #%00101010
    .byte #%01111111
    .byte #%00111110
    .byte #%00101010
    .byte #%00001000
    .byte #%00011100

BomberColor:
    .byte #$00
    .byte #$24
    .byte #$24
    .byte #$0C
    .byte #$40
    .byte #$40
    .byte #$40
    .byte #$40
    .byte #$40

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Filling the 4kb memory needed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    org $FFFC
    .word Reset
    .word Reset