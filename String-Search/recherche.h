#pragma once
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
using namespace std;

// Chaque fonction retourne la position de toutes les occurrences
// de motif dans texte (chevauchements inclus). Motif vide : aucune.

inline string minuscules(string s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
    return s;
}

// Compare le motif à chaque position du texte.
inline vector<size_t> rechercheNaive(const string& texte, const string& motif) {
    vector<size_t> res;
    if (motif.empty() || motif.size() > texte.size()) return res;
    for (size_t i = 0; i + motif.size() <= texte.size(); i++) {
        size_t j = 0;
        while (j < motif.size() && texte[i + j] == motif[j]) j++;
        if (j == motif.size()) res.push_back(i);
    }
    return res;
}

// Lettre, chiffre, _ ou accent (UTF-8) : fait partie d'un mot.
inline bool estCaractereDeMot(char c) {
    unsigned char u = c;
    return isalnum(u) || u == '_' || u >= 128;
}

// Horspool : compare à partir de la fin du motif et saute plusieurs lettres.
// motEntier : ignore les occurrences collées à d'autres lettres (le dans table).
// premierSeulement : s'arrête à la première occurrence trouvée.
inline vector<size_t> horspool(const string& texte, const string& motif,
                               bool motEntier, bool premierSeulement) {
    vector<size_t> res;
    size_t n = texte.size(), p = motif.size();
    if (p == 0 || p > n) return res;

    size_t saut[256];
    for (size_t& s : saut) s = p;
    for (size_t i = 0; i + 1 < p; i++) saut[(unsigned char)motif[i]] = p - 1 - i;

    size_t i = 0;
    while (i + p <= n) {
        size_t j = p;
        while (j > 0 && texte[i + j - 1] == motif[j - 1]) j--;
        if (j == 0) {
            bool avant = i == 0 || !estCaractereDeMot(texte[i - 1]);
            bool apres = i + p == n || !estCaractereDeMot(texte[i + p]);
            if (!motEntier || (avant && apres)) {
                res.push_back(i);
                if (premierSeulement) return res;
            }
        }
        i += saut[(unsigned char)texte[i + p - 1]];
    }
    return res;
}

inline vector<size_t> rechercheHorspool(const string& texte, const string& motif) {
    return horspool(texte, motif, false, false);
}
