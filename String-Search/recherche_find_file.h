#pragma once
#include "recherche_commun.h"

inline vector<size_t> rechercheFind(const string& texte, const string& motif,
                                    bool premierSeulement = false) {
    vector<size_t> res;
    if (motif.empty()) return res;
    size_t pos = texte.find(motif);
    while (pos != string::npos) {
        res.push_back(pos);
        if (premierSeulement) return res;
        pos = texte.find(motif, pos + 1);  // pos + 1 garde les occurrences qui se chevauchent
    }
    return res;
}
