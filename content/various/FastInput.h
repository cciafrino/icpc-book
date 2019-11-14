/**
 * Author: chilli
 * License: CC0
 * Source:
 * Description: Returns an integer. Usage requires your program to pipe in
 * input from file. Can replace calls to $gc()$ with $\text{getchar_unlocked}()$ if extra
 * speed isn't necessary ($60\%$ slowdown).
 * Status: tested on SPOJ INTEST
 * Time: About 5x as fast as cin/scanf.
 * Usage: int a, b[5]; ll c; read_int(a, b[0], c);
 */

struct GC {
    char buf[1 << 16 | 1];
    int bc = 0, be = 0;
    char operator()() {
        if (bc >= be) {
            be = fread(buf, 1, sizeof(buf) - 1, stdin);
            buf[be] = bc = 0;
        }
        return buf[bc++]; // return 0 on EOF
    }
} gc;

void read_int() {}
template <class T, class... S>
inline void read_int(T &a, S &... b) {
    char c, s = 1;
    while (isspace(c = gc()));
    if (c == '-') s = -1, c = gc();
    for (a = c - '0'; isdigit(c = gc()); a = a * 10 + c - '0');
    a *= s;
    read_int(b...);
}

void read_float() {}
template <class T, class... S> inline void read_float(T &a, S &... b) {
    int c, s = 1, fp = 0, fpl = 1;
    while (isspace(c = gc()));
    if (c == '-') s = -1, c = gc();
    for (a = c - '0'; isdigit(c = gc()); a = a * 10 + c - '0');
    a *= s;
    if (c == '.')
        for (; isdigit(c = gc()); fp = fp * 10 + c - '0', fpl *= 10);
    a += (double)fp / fpl;
    read_float(b...);
}