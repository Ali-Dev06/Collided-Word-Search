#include <iostream>
#include "sous_sequence.h"
using namespace std;

struct Test { string m1, m2; bool attendu; };

int main() {
    Test tests[] = {
        {"Compteur", "Cote",     true},
        {"Compteur", "COTE",     true},
        {"Compteur", "cMpR",     true},
        {"Compteur", "compteur", true},
        {"aabbcc",   "abc",      true},
        {"Compteur", "Cotte",    false},  // un seul 't'
        {"Compteur", "Cetop",    false},  // mauvais ordre
        {"Compteur", "Z",        false},  // lettre absente
        {"Cot",      "Cote",     false},  // m2 plus long
        {"abc",      "ACB",      false},  // ordre inversé
    };

    for (const Test& t : tests) {
        bool res = estSousSequence(t.m1, t.m2);
        cout << t.m1 << " " << t.m2 << " : " << (res ? "Oui" : "Non");
        if (res != t.attendu) cout << " ERREUR";
        cout << endl;
    }
    return 0;
}
