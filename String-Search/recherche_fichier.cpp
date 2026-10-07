#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "recherche_find_file.h"
#include "recherche_horspool_file.h"
#include "recherche_naive_file.h"
using namespace std;
using namespace chrono;

const int REPETITIONS = 50;

template <typename Fonction>
double mesurer(Fonction f, const string& texte, const string& mot, bool premierSeulement,
               vector<size_t>& positions) {
    auto debut = steady_clock::now();
    for (int r = 0; r < REPETITIONS; r++) positions = f(texte, mot, premierSeulement);
    duration<double, milli> duree = steady_clock::now() - debut;
    return duree.count() / REPETITIONS;
}

void afficher(const string& nom, const string& texte, const vector<size_t>& positions,
              bool tous, double ms) {
    cout << left << setw(10) << nom;
    if (positions.empty()) {
        cout << setw(24) << "Non";
    } else {
        size_t ligne, colonne;
        ligneColonne(texte, positions[0], ligne, colonne);
        string debut = tous ? to_string(positions.size()) + " occ., 1re : " : "Oui, ";
        cout << debut << "ligne " << ligne << " col " << colonne << "  ";
    }
    cout << fixed << setprecision(4) << ms << " ms" << endl;
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

    bool premier = !tous;
    vector<size_t> p1, p2, p3;
    double t1 = mesurer(rechercheNaive, texte, mot, premier, p1);
    double t2 = mesurer(rechercheHorspool, texte, mot, premier, p2);
    double t3 = mesurer(rechercheFind, texte, mot, premier, p3);

    afficher("Naive", texte, p1, tous, t1);
    afficher("Horspool", texte, p2, tous, t2);
    afficher("Find", texte, p3, tous, t3);
    return 0;
}
