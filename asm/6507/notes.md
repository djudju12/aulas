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

### pseudo-random numbers

**LFSR**
you actually can revert this generation redoing the operations in the oposite order
```asm
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Linear-Feedback Shift Register (LFSR)
;; Co to output a random value in the Accumulator
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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
```

**Generating random bit**
```asm
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Subroutine to generate RandomBit
;; Rand1, Rand2, Rand3, Rand4 are RAM location, initilized to anu nonzero value
;; at program initialization.
;; A random BIT is generated by XORing bits 27 and 38 of the register, then
;; shifting the entire thing one BIT to the left and placing the new bit on the
;; right. This algorithm produces a sequence of 2**31 - 1 random bits before
;; repeting.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
GenerateRandomBit subroutine
    LDA Rand4
    ASL
    ASL
    ASL
    EOR Rand4           ; new bit is now in bit 6 of A
    ASL
    ASL                 ; new bit is now in carry
    ROL Rand1           ; shift new bit to 0 of A, bit 7 goes to carry
    ROL Rand2           ; shift old bit 7 into bit 8, etc
    ROL Rand3
    ROL Rand4
    RTS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Subroutine to generate random byte
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
GenerateRandomByte subroutine
    LDX #8
.RandomByteLoop
    JSR GenerateRandomBit
    DEX
    BNE .RandomByteLoop
    LDA Rand1
    RTS

```

### Checking Collision

* TIA has 15 different collision flags
* Pixel perfect collision between objects
* Check for collision using `CX**` registers
* Strobe `CXCLR` clears all collision flags

|  XX  |D7|D6|D5|D4|D3|D2|D1|D0|xx|D7  |D6  |
|------|--|--|--|--|--|--|--|--|--|----|----|
|CXM0P | 1| 1| .| .| .| .| .| .|xx|M0P1|M1P1|
|CXM1P | 1| 1| .| .| .| .| .| .|xx|M1P0|M1P1|
|CXP0FB| 1| 1| .| .| .| .| .| .|xx|P0PF|P0BL|
|CXP1FB| 1| 1| .| .| .| .| .| .|xx|P1PF|P1BL|
|CXM0FB| 1| 1| .| .| .| .| .| .|xx|M0PF|M0BL|
|CXM1FB| 1| 1| .| .| .| .| .| .|xx|M1PF|M1BL|
|CXBLPF| 1| 1| .| .| .| .| .| .|xx|BLPF|xxxx|
|CXPPMM| 1| 1| .| .| .| .| .| .|xx|P0P1|M0M1|

Sample code:
```asm
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Check collision between player0 and playfield
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
CheckCollisionP0PF:
    LDA #%10000000
    BIT CXP0FB
    BNE .CollisionP0PF
    JMP EndCollisionCheck

.CollisionP0PF:
    JSR GameOver

EndCollisionCheck:
    STA CXCLR             ; Clear all collision flags
```

### BDC mode

One single byte has 256 possibles values, ranging from `$00` to `$FF` in hex.
The most common way of representing numbers is using binary numbers (or, more specifically, unsigned integers).

In BCD, a byte represents a number from 0 to 99. But in this case, `$00` to `$09` represents 0 to 9,
`$10` to `$19` represents 10 to 19, and so on... All the way up to `$90` to `$99`.

These 100 values are called  **valid** BCD numbers. The other 156 possible values of a byte are called invalid BCD numbers.

### Sound Registers

* The TIA chip supports two sounds channels, meaning we can play two sounds at the same time
* Each sound/channel can be tweaked by using three registers:

| CH0 | CH1 | Description | Range |
|-----|-----|-------------|-------|
|AUDV0|AUDV1|Volume       |0 to 15|
|AUDF0|AUDF1|Frequency    |0 to 31|
|AUDC0|AUDC1|tone type    |0 to 15|

| HEX | Register | Bits used |
|-----|----------|-----------|
| 15  | AUDC0    | 00001111  |
| 16  | AUDC1    | 00001111  |
| 17  | AUDF0    | 00011111  |
| 18  | AUDF1    | 00011111  |
| 19  | AUDV0    | 00001111  |
| 1A  | AUDV1    | 00001111  |

**Audio tone**

| Value  | Tone Type   |
|--------|:----------- |
|0, 11   |Silent       |
|1       |Buzz         |
|2, 3    |Rumble       |
|4, 5    |Pure Tone    |
|6, 10   |Square Wave  |
|7, 9    |Buzz         |
|8       |White Noise  |
|12, 13  |Pure tone    |
|14      |Square Wave  |
|15      | Buzz        |