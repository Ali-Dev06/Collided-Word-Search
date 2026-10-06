#include <fstream>
#include <iostream>
#include "recherche.h"
using namespace std;

const size_t MAX_AFFICHE = 10;

// Affiche la ligne et la colonne des premières positions.
// La colonne compte les caractères (les octets de suite UTF-8 sont ignorés).
void afficher(const string& texte, const vector<size_t>& positions) {
    size_t ligne = 1, debutLigne = 0, i = 0;
    for (size_t k = 0; k < positions.size() && k < MAX_AFFICHE; k++) {
        for (; i < positions[k]; i++) {
            if (texte[i] == '\n') {
                ligne++;
                debutLigne = i + 1;
            }
        }
        size_t colonne = 1;
        for (size_t c = debutLigne; c < positions[k]; c++)
            if ((texte[c] & 0xC0) != 0x80) colonne++;
        cout << "ligne " << ligne << " colonne " << colonne << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage : recherche_fichier fichier mot [-i] [-tous]" << endl;
        return 1;
    }
    string fichier = argv[1];
    string mot = argv[2];
    bool ignorerCasse = false, tous = false;
    for (int k = 3; k < argc; k++) {
        string option = argv[k];
        if (option == "-i") ignorerCasse = true;
        else if (option == "-tous") tous = true;
        else {
            cout << "Option inconnue : " << option << endl;
            return 1;
        }
    }

    ifstream in(fichier, ios::binary);
    if (!in) {
        cout << "Fichier introuvable : " << fichier << endl;
        return 1;
    }
    in.seekg(0, ios::end);
    size_t taille = in.tellg();
    string texte(taille, '\0');
    in.seekg(0);
    in.read(&texte[0], taille);

    if (ignorerCasse) {
        texte = minuscules(texte);
        mot = minuscules(mot);
    }

    // Sans -tous, la recherche s'arrête au premier mot trouvé.
    vector<size_t> positions = horspool(texte, mot, true, !tous);

    if (!tous) {
        if (positions.empty()) {
            cout << "Non" << endl;
        } else {
            cout << "Oui" << endl;
            afficher(texte, positions);
        }
    } else {
        cout << positions.size() << " occurrence(s)" << endl;
        afficher(texte, positions);
        if (positions.size() > MAX_AFFICHE)
            cout << "et " << positions.size() - MAX_AFFICHE << " autres" << endl;
    }
    return 0;
}
