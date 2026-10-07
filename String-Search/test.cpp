#include <iostream>
#include "recherche_find_file.h"
#include "recherche_horspool_file.h"
#include "recherche_naive_file.h"
using namespace std;

struct Test { string texte, motif; size_t attendu; };

int main() {
    Test tests[] = {
        {"mississippi",             "issi",  2},
        {"abababa",                 "aba",   3},  // chevauchement
        {"aaaa",                    "aa",    3},  // chevauchement
        {"hello world",             "o w",   1},
        {"hello",                   "xyz",   0},
        {"abc",                     "abcd",  0},  // motif plus long
        {"Hello",                   "hello", 0},  // casse différente
        {"aezbc",                   "bc",    1},  // fin du texte
        {"le chat est sur la table", "le",   2},  // dans table aussi
    };

    for (const Test& t : tests) {
        vector<size_t> naif = rechercheNaive(t.texte, t.motif);
        vector<size_t> horspool = rechercheHorspool(t.texte, t.motif);
        vector<size_t> find = rechercheFind(t.texte, t.motif);
        bool ok = naif.size() == t.attendu && naif == horspool && naif == find;

        size_t unique = t.attendu > 0 ? 1 : 0;
        vector<size_t> a = rechercheNaive(t.texte, t.motif, true);
        vector<size_t> b = rechercheHorspool(t.texte, t.motif, true);
        vector<size_t> c = rechercheFind(t.texte, t.motif, true);
        ok = ok && a.size() == unique && b.size() == unique && c.size() == unique
             && (unique == 0 || (a[0] == naif[0] && b[0] == naif[0] && c[0] == naif[0]));

        cout << t.texte << " | " << t.motif << " : " << naif.size() << (ok ? "" : " ERREUR") << endl;
    }
    return 0;
}
