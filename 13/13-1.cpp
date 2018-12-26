#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <set>

using namespace std;

static const char UP = '^';
static const char RIGHT = '>';
static const char DOWN = 'v';
static const char LEFT = '<';

struct Cart {
    int x, y, state;
    char dir;

    static bool isCart(char c) {
        return c == UP || c == RIGHT || c == DOWN || c == LEFT;
    }

    static char trackFromCart(char c) {
        switch (c) {
            case UP:
            case DOWN:
                return '|';
            case LEFT:
            case RIGHT:
                return '-';
            default:
                throw invalid_argument("not a cart character");
        }
    }

    Cart(int _x, int _y, char _c) : x(_x), y(_y), dir(_c), state(0) {}

    void move(const vector<string> &map) {
        switch (dir) {
            case UP: --y; break;
            case RIGHT: ++x; break;
            case DOWN: ++y; break;
            case LEFT: --x; break;
        }

        if (y < 0 || y >= map.size() || x < 0 || x >= map[y].size()) {
            throw out_of_range("cart out of map bounds");
        }

        char track = map[y][x];
        switch (track) {
            case '|':
                if (dir != UP && dir != DOWN) throw invalid_argument("invalid cart on vertical track");
                break;

            case '-':
                if (dir != LEFT && dir != RIGHT) throw invalid_argument("invalid cart on horizontal track");
                break;

            case '/':
                switch (dir) {
                    case UP: dir = RIGHT; break;
                    case RIGHT: dir = UP; break;
                    case DOWN: dir = LEFT; break;
                    case LEFT: dir = DOWN; break;
                    default: throw invalid_argument("not a cart character");
                }
                break;

            case '\\':
                switch (dir) {
                    case UP: dir = LEFT; break;
                    case RIGHT: dir = DOWN; break;
                    case DOWN: dir = RIGHT; break;
                    case LEFT: dir = UP; break;
                    default: throw invalid_argument("not a cart character");
                }
                break;

            case '+':
                switch (state) {
                    case 0: turnLeft(); break;
                    case 2: turnRight(); break;
                }
                state = (state + 1) % 3;
                break;

            default:
                throw invalid_argument("not a track character");
        }

    }

    void turnLeft() {
        switch (dir) {
            case UP: dir = LEFT; break;
            case RIGHT: dir = UP; break;
            case DOWN: dir = RIGHT; break;
            case LEFT: dir = DOWN; break;
            default:
                throw invalid_argument("not a cart character");
        }
    }

    void turnRight() {
        switch (dir) {
            case UP: dir = RIGHT; break;
            case RIGHT: dir = DOWN; break;
            case DOWN: dir = LEFT; break;
            case LEFT: dir = UP; break;
            default:
                throw invalid_argument("not a cart character");
        }
    }

    bool operator<(const Cart &other) const {
        if (y < other.y) return true;
        if (y > other.y) return false;
        return x < other.x;
    }
};

void dumpMap(const vector<string> &map, const vector<Cart> &carts) {
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            char c = '\0';
            for (const Cart &cart : carts) {
                if (cart.x == x && cart.y == y) {
                    if (c == '\0')
                        c = cart.dir;
                    else
                        c = 'X';
                }
            }

            if (c == '\0') {
                c = map[y][x];
            }

            cout << c;
        }
        cout << endl;
    }
}

void readInput(vector<string> &map, vector<Cart> &carts) {
    string line;
    int y = 0;

    while (getline(cin, line)) {
        for (int x = 0; x < line.size(); ++x) {
            if (Cart::isCart(line[x])) {
                carts.push_back(Cart(x, y, line[x]));
                line[x] = Cart::trackFromCart(line[x]);
            }
        }
        map.push_back(line);
        ++y;
    }
}

Cart solve(const vector<string> &map, vector<Cart> &carts) {
    set<Cart> uniqueCarts(carts.begin(), carts.end());

    while (true) {
        sort(carts.begin(), carts.end());

        for (Cart &cart: carts) {
            uniqueCarts.erase(cart);
            cart.move(map);
            if (!uniqueCarts.insert(cart).second) {
                return cart;
            }
        }
    }
}

int main() {
    vector<string> map;
    vector<Cart> carts;
    readInput(map, carts);
    Cart crashed = solve(map, carts);
    cout << crashed.x << "," << crashed.y << endl;
    return 0;
}