#pragma once
#include <cctype>
#include <string>
using namespace std;

inline bool estSousSequence(const string& m1, const string& m2) {
    size_t j = 0;
    for (size_t i = 0; i < m1.size() && j < m2.size(); i++) {
        if (tolower((unsigned char)m1[i]) == tolower((unsigned char)m2[j]))
            j++;
    }
    return j == m2.size();
}
