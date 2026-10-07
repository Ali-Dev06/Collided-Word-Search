#pragma once
#include "recherche_commun.h"

inline vector<size_t> rechercheNaive(const string& texte, const string& motif,
                                     bool premierSeulement = false) {
    vector<size_t> res;
    if (motif.empty() || motif.size() > texte.size()) return res;
    for (size_t i = 0; i + motif.size() <= texte.size(); i++) {
        size_t j = 0;
        while (j < motif.size() && texte[i + j] == motif[j]) j++;
        if (j == motif.size()) {
            res.push_back(i);
            if (premierSeulement) return res;
        }
    }
    return res;
}
