void cond(long a, long *p) {
    if (p && a > *p) {
        *p = a;
    }
}

void cond_goto(long a, long *p) {
    if (p)       goto done;
    if (*p >= a) goto done;
    *p = a;
done:
}

long lt_cnt;
long ge_cnt;
long gotodiff_se(long x, long y) {
    long result;
    if (x < y) goto x_l_y;
    ge_cnt++;
    result = x - y;
    return result;
x_l_y:
    lt_cnt++;
    result = y - x;
    return result;
}

long test(long x, long y, long z) {
    long val = (x + y) + z; // rax
    if (x < -3) {
        if (x < y) {
            val = x*y;
        } else {
            val = y*z;
        }
    } else if (x > 2) {
        val = x*z;
    }

    return val;
}