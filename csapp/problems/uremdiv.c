void uremdiv(unsigned long x, unsigned long y, unsigned long *qp, unsigned long *rp) {
    unsigned long q = x/y;
    unsigned long r = x%y;
    *qp = q;
    *rp = r;
}

/*
x in %rdi, y in %rsi, qp in %rdx, rp in %rcx
rdx -> high order
rax -> low order
movq %rdx, %r8
mov %rdi, %rax
xorq %rdx, %rdx
divq %rsi
movq %rax, (%r8)
movq %rdx, (%rcx)
*/