#include <iostream>
#include "recherche.h"
using namespace std;

struct Test { string texte, motif; size_t attendu; };

int main() {
    Test tests[] = {
        {"mississippi", "issi",  2},
        {"abababa",     "aba",   3},  // chevauchement
        {"aaaa",        "aa",    3},  // chevauchement
        {"hello world", "o w",   1},
        {"hello",       "xyz",   0},
        {"abc",         "abcd",  0},  // motif plus long
        {"Hello",       "hello", 0},  // casse différente
    };

    cout << "Blocs de lettres" << endl;
    for (const Test& t : tests) {
        vector<size_t> ref = rechercheNaive(t.texte, t.motif);
        bool ok = ref.size() == t.attendu
               && ref == rechercheHorspool(t.texte, t.motif);
        cout << t.texte << " " << t.motif << " : " << ref.size() << (ok ? "" : " ERREUR") << endl;
    }

    Test motsEntiers[] = {
        {"le chat est sur la table", "le",  1},  // pas dans table
        {"un mot, un autre mot.",    "mot", 2},  // la ponctuation sépare les mots
        {"motmot",                   "mot", 0},
        {"mot",                      "mot", 1},
        {"a_b a",                    "a",   1},  // _ fait partie du mot
        {"cafe café",                "caf", 0},  // un accent fait partie du mot
    };

    cout << endl << "Mot entier" << endl;
    for (const Test& t : motsEntiers) {
        vector<size_t> tous = horspool(t.texte, t.motif, true, false);
        vector<size_t> premier = horspool(t.texte, t.motif, true, true);
        bool ok = tous.size() == t.attendu
               && premier.size() == (t.attendu > 0 ? 1 : 0)
               && (tous.empty() || premier[0] == tous[0]);
        cout << t.texte << " " << t.motif << " : " << tous.size() << (ok ? "" : " ERREUR") << endl;
    }
    return 0;
}
