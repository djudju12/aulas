### MOV

MOV instructions are the simplest of the classes.
They operate in 4 different sizers

* movb -> byte
* movw -> word (2 bytes)
* movl -> long (4 bytes)
* movq -> quad (8 bytes)
* movabsq -> mov abs quad (I,R := R <- I)

movabsq its needed because movq can only work with immediate 32bits integers

With x86-64, we cannot use two mem locations to do a mov instruction.
First, we have to load the value of mem1 to a register and the mov the value to the destination.

Register operands for this instructions can be any of the labeled 16 register.
But is important to notice that the size of the register MUST match the last char of the instruction.

```assembly
movl $0x4050,%eax       # Immediate--Register, 4 bytes
movw %bp,%sp            # Register--Register, 2 bytes
movb (%rdi,%rcx),%al    # Memory--Register, 1 byte
movb $-17,(%esp)        # Immediate--Memory, 1 byte
movq %rax,-12(%rbp)     # register--Memory, 8 bytes
```

To copy a value to a larger destination, we can use the following set of instructions:

* movzbw
* movzbl
* movzwl
* movzwq
* movzwq

Note that the instruction `movzlq` doenst exist. This instruction can be implemented with `movl` to a register, taking
advantage of the fact that **a instruction with 4-byte value with a register with destination will set to zero the ramaining bytes**.

Instruction that do signed extension:

* movsbw
* movsbl
* movswl
* movswq
* movswq
* movsql

### Problem 3.3

```assembly
movb $OxF, (%ebx)     # cannot use ebx as address value
movl %rax, (%rsp)     # Wrong size of the source (vish)
movw (%rax),4(%rsp)   # Cannot use memory values as dest and source at the same time
movb %al,%sl          # i think %sl dont exists
movq %rax,$0x123      # Dest cannot be a immediate value
movl %eax,%dx         # %rdx is to large
movb %si, 8(%rbp)     # mismatch (si is w)
```

### Problem 3.5
```
src_t *sp;
dest_t *dp;
*dp = (dest_t) *sp;

long -> long:
movq (%rdi), %rax
movq %rax,(%rsi)

char -> int:
movsbl (%rdi), %eax
movl %eax, (%rsi)

char -> unsigned;
movzbl (%rdi), %eax
movl %eax, (%rsi)

int -> char:
movl (%rdi), %eax
movb %al,(%rsi)

unsigned -> unsigned char:
movl (%rdi),%eax
movb %al,(%rsi)

char -> short:
movsbw (%rdi),%ax
movw %ax,(%rsi)
```