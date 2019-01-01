#include <iostream>

using namespace std;

int main() {
    string scores = "37";
    string pattern;
    int a, b;
    size_t patternIndex = string::npos;
    
    a = 0;
    b = 1;
    cin >> pattern;
    
    while (patternIndex == string::npos) {
        int scoreA = static_cast<int>(scores[a] - '0');
        int scoreB = static_cast<int>(scores[b] - '0');
        string suffix = to_string(scoreA + scoreB);
        scores += suffix;
        patternIndex = scores.find(pattern, max<size_t>(0, scores.size() - pattern.size() - suffix.size() + 1));
        a = (a + scoreA + 1) % scores.size();
        b = (b + scoreB + 1) % scores.size();
    }
    
    cout << patternIndex << endl;
    
    return 0;
}
