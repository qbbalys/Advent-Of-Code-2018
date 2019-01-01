#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getDigits(int n) {
    vector<int> digits;
    
    while (n > 9) {
        digits.push_back(n % 10);
        n /= 10;
    }
    
    digits.push_back(n);
    reverse(digits.begin(), digits.end());
    return digits;
}

int main() {
    vector<int> scores = { 3, 7 };
    int recipeCount, a, b;
    a = 0;
    b = 1;
    cin >> recipeCount;
    
    while (scores.size() < recipeCount + 10) {
        vector<int> digits = getDigits(scores[a] + scores[b]);
        scores.insert(scores.end(), digits.begin(), digits.end());
        a = (a + scores[a] + 1) % scores.size();
        b = (b + scores[b] + 1) % scores.size();
    }
    
    for (int i = recipeCount; i < recipeCount + 10; ++i) {
        cout << scores[i];
    }
    
    cout << endl;
    
    return 0;
}
