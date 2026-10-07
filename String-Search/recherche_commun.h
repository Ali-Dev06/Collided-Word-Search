#pragma once
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
using namespace std;

// Fonctions partagées par les 3 algorithmes.

// Met le texte en minuscules (pour l'option -i).
inline string minuscules(string s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
    return s;
}

// Transforme une position dans le texte en ligne et colonne (la 1re vaut 1).
// La colonne compte les caractères (les octets de suite UTF-8 sont ignorés).
inline void ligneColonne(const string& texte, size_t position, size_t& ligne, size_t& colonne) {
    ligne = 1;
    size_t debutLigne = 0;
    for (size_t i = 0; i < position; i++) {
        if (texte[i] == '\n') {
            ligne++;
            debutLigne = i + 1;
        }
    }
    colonne = 1;
    for (size_t c = debutLigne; c < position; c++)
        if ((texte[c] & 0xC0) != 0x80) colonne++;
}
