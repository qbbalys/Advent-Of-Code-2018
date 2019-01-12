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

void (*instructions[]) (int a, int b, int c) = {
    addr,
    addi,
    mulr,
    muli,
    banr,
    bani,
    borr,
    bori,
    setr,
    seti,
    gtir,
    gtri,
    gtrr,
    eqir,
    eqri,
    eqrr
};

bool matchesThree(int initial[4], int expected[4], int a, int b, int c) {
    int matches = 0;

    for (auto cmd : instructions) {
        bool succeeded = true;

        for (int i = 0; i < 4; ++i) {
            reg[i] = initial[i];
        }

        try {
            cmd(a, b, c);
        } catch (const invalid_argument &e) {
            succeeded = false;
        }

        if (succeeded) {
            for (int i = 0; i < 4; ++i) {
                if (reg[i] != expected[i]) succeeded = false;
            }
        }
        
        if (succeeded) ++matches;
        if (matches > 2) return true;
    }

    return false;
}

int main() {
    int result = 0;
    string keyword;
    cin >> keyword;

    while (keyword == "Before:") {
        int op, a, b, c;
        int initialReg[4];
        int expectedReg[4];

        cin.ignore(INT_MAX, '[');
        cin >> initialReg[0];
        cin.ignore(INT_MAX, ',');
        cin >> initialReg[1];
        cin.ignore(INT_MAX, ',');
        cin >> initialReg[2];
        cin.ignore(INT_MAX, ',');
        cin >> initialReg[3];
        cin.ignore(INT_MAX, '\n');

        cin >> op;
        cin >> a;
        cin >> b;
        cin >> c;

        cin >> keyword;
        cin.ignore(INT_MAX, '[');
        cin >> expectedReg[0];
        cin.ignore(INT_MAX, ',');
        cin >> expectedReg[1];
        cin.ignore(INT_MAX, ',');
        cin >> expectedReg[2];
        cin.ignore(INT_MAX, ',');
        cin >> expectedReg[3];
        cin.ignore(INT_MAX, '\n');

        if (matchesThree(initialReg, expectedReg, a, b, c)) {
            ++result;
        }

        cin >> keyword;
    }

    cout << result << endl;

    return 0;
}