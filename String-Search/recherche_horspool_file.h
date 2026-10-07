#pragma once
#include "recherche_commun.h"

inline vector<size_t> rechercheHorspool(const string& texte, const string& motif,
                                        bool premierSeulement = false) {
    vector<size_t> res;
    size_t n = texte.size(), p = motif.size();
    if (p == 0 || p > n) return res;

    // distance de chaque lettre à la fin du motif, dernière lettre exclue
    size_t saut[256];
    for (size_t& s : saut) s = p;
    for (size_t i = 0; i + 1 < p; i++) saut[(unsigned char)motif[i]] = p - 1 - i;

    size_t i = 0;
    while (i + p <= n) {
        size_t j = p;
        while (j > 0 && texte[i + j - 1] == motif[j - 1]) j--;
        if (j == 0) {
            res.push_back(i);
            if (premierSeulement) return res;
        }
        i += saut[(unsigned char)texte[i + p - 1]];
    }
    return res;
}
