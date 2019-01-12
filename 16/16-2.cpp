#include <iostream>
#include <exception>

using namespace std;

int reg[4];

void assertReg(int i) {
    if (i < 0 || i > 3) throw invalid_argument("Invalid register");
}

void addr(int a, int b, int c) {
    assertReg(a);
    assertReg(b);
    assertReg(c);
    reg[c] = reg[a] + reg[b];
}

void addi(int a, int b, int c) {
    assertReg(a);
    assertReg(c);
    reg[c] = reg[a] + b;
}

void mulr(int a, int b, int c) {
    assertReg(a);
    assertReg(b);
    assertReg(c);
    reg[c] = reg[a] * reg[b];
}

void muli(int a, int b, int c) {
    assertReg(a);
    assertReg(c);
    reg[c] = reg[a] * b;
}

void banr(int a, int b, int c) {
    assertReg(a);
    assertReg(b);
    assertReg(c);
    reg[c] = reg[a] & reg[b];
}

void bani(int a, int b, int c) {
    assertReg(a);
    assertReg(c);
    reg[c] = reg[a] & b;
}

void borr(int a, int b, int c) {
    assertReg(a);
    assertReg(b);
    assertReg(c);
    reg[c] = reg[a] | reg[b];
}

void bori(int a, int b, int c) {
    assertReg(a);
    assertReg(c);
    reg[c] = reg[a] | b;
}

void setr(int a, int b, int c) {
    assertReg(a);
    assertReg(c);
    reg[c] = reg[a];
}

void seti(int a, int b, int c) {
    assertReg(c);
    reg[c] = a;
}

void gtir(int a, int b, int c) {
    assertReg(b);
    assertReg(c);
    reg[c] = a > reg[b] ? 1 : 0;
}

void gtri(int a, int b, int c) {
    assertReg(a);
    assertReg(c);
    reg[c] = reg[a] > b ? 1 : 0;
}

void gtrr(int a, int b, int c) {
    assertReg(a);
    assertReg(b);
    assertReg(c);
    reg[c] = reg[a] > reg[b] ? 1 : 0;
}

void eqir(int a, int b, int c) {
    assertReg(b);
    assertReg(c);
    reg[c] = a == reg[b] ? 1 : 0;
}

void eqri(int a, int b, int c) {
    assertReg(a);
    assertReg(c);
    reg[c] = reg[a] == b ? 1 : 0;
}

void eqrr(int a, int b, int c) {
    assertReg(a);
    assertReg(b);
    assertReg(c);
    reg[c] = reg[a] == reg[b] ? 1 : 0;
}

void (*commands[]) (int a, int b, int c) = {
    gtri, // 0
    bani, // 1
    eqrr, // 2
    gtir, // 3
    eqir, // 4
    bori, // 5
    seti, // 6
    setr, // 7
    addr, // 8
    borr, // 9
    muli, // 10
    banr, // 11
    addi, // 12
    eqri, // 13
    mulr, // 14
    gtrr  // 15    
};

int main() {
    int op, a, b, c;
    
    while (cin >> op >> a >> b >> c) {
        commands[op](a, b, c);
    }

    cout << reg[0] << endl;

    return 0;
}