void decode1(long *xp, long *yp, long *zp) {
    // xp in rdi, yp in rsi, zp in rdx
    long r8 = *xp;
    long rcx = *yp;
    long rax = *zp;
    *yp = r8;
    *zp = rcx;
    *xp = rax;
}