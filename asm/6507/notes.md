## The 6507 Processor

* The 6507 is a 28-pin processor used in the Atari 2600 game console.
* 13 address lines, 8 data lines.
* Remaining are:
  * Power
  * CPU timing clock
  * CPU reset
  * Request bus wait (RDY)
  * Read/Write (R/W)
* Theres is no IRQ or NMI.
* The CPU ticks at 1.19 MHz.

![6507 Pinout](media/pinout.gif)

The processor have 6 registers:
* Program Counter (PC): 16-bit register that holds the address of the next instruction to be executed.
* Stack Pointer (SP): 8-bit register that holds the address of the top of the stack. Actually, has 9 bits, but the 9th bit is always 1 (0000 0001 .... ....)
* Processor Flags (P): 8-bit register that holds the status of the processor.
* Accumulator (A): 8-bit register that holds the result of arithmetic and logical operations. Only one that can be used with the ALU.
* X and Y are general purpose registers.

![6507 architecture](media/arch.png)

Processor Status Register (P):
 7 6 5 4 3 2 1 0
[n v - b d i z c]

* n: Negative     - 0: Positive, 1: Negative
* v: Overflow     - 0: No overflow, 1: Overflow
* -: Unused
* b: Break        - 0: No break, 1: Break
* d: Decimal mode - 0: Normal, 1: Decimal mode
* i: Interrupt    - 0: Interrupts enabled, 1: Interrupts disabled
* z: Zero         - 0: Non-zero, 1: Zero
* c: Carry        - 0: No carry, 1: Carry

### difference between carry and overflow

Carry is used when making arithmetic operations and the result is bigger than 255 (8-bit).
for example

   1 1 1 1  1 1 1 1
+  0 0 0 0  0 0 0 1
-------------------
1  0 0 0 0  0 0 0 0
|
+---> Carry

Overflow has something to do with the sign of the number. It is used when making arithmetic operations and the result is bigger than 127 (8-bit).

   0 1 1 1  1 1 1 1 = 127
+  0 0 0 0  0 0 0 1 = 1
-------------------
   1 0 0 0  0 0 0 0 = -128

NOTE: we dont have a carry here, but we have an overflow.

This is related with the implementation of negative numbers in the 6507. The 6507 uses the complement of 2 to represent negative numbers.

### Complement of 2

* The 6507 uses the complement of 2 to represent negative numbers.

a good way to explain how it works is to think of the MSB as the amount of negative summed to the number.

-
1
2 6 3 1
8 4 2 6  8 4 2 1

0 1 1 1  1 1 1 1 = 127

-
1
2 6 3 1
8 4 2 6  8 4 2 1

1 0 0 0  0 0 0 0 = -128

1 1 1 1  1 1 1 1 = -1

### Popular instructions

```assembly
; Load and Store:

LDA ; Load Accumulator
LDX ; Load X
LDY ; Load Y
STA ; Store Accumulator
STX ; Store X
STY ; Store Y

; Arithmetic:

ADC ; Add with Carry

SBC ; Subtract with Carry

; Its always a good idea to clear or set the carry flag before using ADC or SBC

CLC ; Clear Carry, use before ADC
SEC ; Set Carry, use before SBC

INC ; Increment
INX ; Increment X
INY ; Increment Y

DEC ; Decrement
DEX ; Decrement X
DEY ; Decrement Y

; inc and dec instructions set the zero and negative flags

JMP ; Jump (GOTO)
BCC ; Branch if Carry Clear     C == 0
BCS ; Branch if Carry Set       C == 1
BEQ ; Branch if Equal           Z == 1
BNQ ; Branch if Not Equal       Z == 0
BMI ; Branch if Minus           N == 1
BPL ; Branch if Positive        N == 0
BVC ; Branch if Overflow Clear  V == 0
BVS ; Branch if Overflow Set    V == 1

; loop example

    ldy #100 ;y=100
Loop:
    dey      ;y--
    bne Loop ;if y != 0, loop

```


### Importante Assembly Terminology

* Directives: commands that we can send to the assembler to tell it to do something, like locating code in memory, or inserting raw data into the ROM. Directives should always be indented to the right and some programmers start them with a dot. e.g. `.org $F000`.
* Labels: a label is a name that we give to a memory address. Labels should always be indented to the left and end with a colon. e.g. `Loop:`
* Operands: the arguments that we pass to an instruction. e.g. `LDA #$80`

### Addressing Modes

* Immediate: `LDA #80`
* Absolute: `LDA $80`

One important thing to notice is that `LDA $80` is not the same as `LDA #80`. The first loads the IMMEDIATE value 80 to the accumulator and the second loads the accumulator with the value inside the MEMORY ADDRESS $80. Thats is very important and the difference is not just hex/dec.

Thats why we have to load the IMMEDIATE HEX DECIMAL VALUE in the register to manipulate has a number, like `LDX #$80`

### Memory Map (where things located in address space?)
```
[V] - - -
[C]     | TIA (Television Interface Adapter)
[S]     |
[B] - - - PIA (Peripheral Interface Adapter)
[U]     |
[S]     | ROM (Cartridge)
[S] - - -

$00 - - - - - - - - - - -
$01   |                 |
 .    |                 |
 .    | - - - TIA       |
$7D   |                 |
$7E   |                 |
$7F - -                 |
                        | - - - Zero Page
$80 - -                 |
$80   |                 |
 .    |                 |
 .    | - - - PIA RAM   |
$FD   |                 |
$FE   |                 |
$FF - - - - - - - - - - -
 .
 .
$F000-|
$F001 |
$F002 |
 .    |
 .    | - - - Cartridge ROM
$FFFD |
$FFFE |
$FFFF-|
```

### TIA Objects

* Background
  * Takes the whole visible screen (160x192)
  * We can only change de bg color per each horizontal scanline (COLUBK)
  * The bg is always displayed behind all the other elements
* Playfield:
  * 20-bit pattern, rendered over the left side of the scanline (config the left side)
  * One color per horizontal scanline
  * The right side will either be a REPEAT or REFLECT of the same pattern
    * PF0, PF1, PF2
    * COLUPF
    * CTRLPF
      * D0: Reflect
      * D1: Score
      * D2: Priority
      * D4-D5: Ball size (1, 2, 4, 8)
* Player:
  * Each is an independent 8-bit pattern (GRP0, GRP1) with foreground color (COLUP0, COLUP1) that can by positioned at any column of the scanline
  * Each player can be horizontally stretched, multiplied of inverted
    * NUSIZ0, NUSIZ1(number/size)
    * REFP0, REFP1 (reflect player)
* MIssiles/ball:
  *  Can be positioned just like player, but no bit pattern
  *  Just one Pixel, but it can be horizontally stretched (2x, 4x, 8x)
  *  M0 and M1 use P0/P1 colors
  *  BL uses the PF foreground color
  *  We have a limitation of up to 2 missiles only on the same horizontal space

**How rendering works with playfield**

```
Bit pattern that says if this pixel
is active or not. Not the order if
PF1 and PF2
   \/         \/            \/

   PF0        PF1           PF2
|4 5 6 7|7 6 5 4 3 2 1 0|0 1 2 3 4 5 6 7|
| | | | | | | | | | | | | | | | | | | | | -> REFLECTS OR MIRROR TO THE RIGHT
._|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_._._._._._._._._._._._._._._._._._._._.
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
| | | | | | | | | | | | | | | | | | | | |                                       |
.-------------------------------------------------------------------------------.
```

### Input (PIA)

* `$280` SWCHA - Joysticks/Controllers
* `$282` SWCHB - Front-panel Switches

*SWCHA:*
```
P0\/     P1\/
1 0 1 1 | 1 1 1 1
          | | | |_ P1 - up
          | | |___ P1 - down
          | |_____ P1 - left
          |_______ P1 - right
```

```asm6507
;; Joystick input test

;;     0b00010000
;; bit 0b11111111
;;     ----------
;;     0b00010000 -> 16
;;
;;     0b00010000
;; bit 0b11101111
;;     ----------
;;     0b00000000  -> 0
;;
;; bne CheckP0Down -> if (Z != 0) CheckP0Down;
;; vai ser 0 se estiver ativo

CheckP0Up:
  lda #%00010000
  bit SWCHA
  bne CheckP0Down
  ; logic

CheckP0Down:
  lda #%00100000
  bit SWCHA
  bne CheckP0Left
  ; logic

CheckP0Left:
  lda #%01000000
  bit SWCHA
  bne CheckP0Right
  ; logic

CheckP0Right:
  lda #%10000000
  bit SWCHA
  bne NoInput
  ; logic

NoInput:
  ; logic
```

### Indirect Addressing

```asm
seg.u Variables

SpritPtr word   ; 16bit pointer

  lda #<ArrowDown
  sta SpritePrt   ; low byte
  lda #>ArrowDown
  sta SpritePtr+1 ; hi byte

  ldy #5

  lda (SpritePtr),Y  ; 1 - look up the 16bit value at SpritePtr and SpritePtr+1 (lo and hi byte)
                    ; 2 - convert it to an address
                    ; 3 - the add y to it

  sta Value
```