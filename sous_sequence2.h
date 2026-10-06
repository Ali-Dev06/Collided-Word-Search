#pragma once
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

inline string minuscules(string s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
    return s;
}

// Version avec find : chaque lettre de mot2 est cherchée après la précédente.
inline bool estSousSequenceFind(const string& mot1, const string& mot2) {
    string m1 = minuscules(mot1);
    string m2 = minuscules(mot2);
    size_t pos = 0;
    for (char c : m2) {
        pos = m1.find(c, pos);
        if (pos == string::npos) return false;
        pos++;
    }
    return true;
}
