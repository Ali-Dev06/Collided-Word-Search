#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "recherche.h"
using namespace std;
using namespace chrono;

const int REPETITIONS = 10;

// Retourne le temps moyen en ms et le nombre d'occurrences trouvées.
template <typename Fonction>
double mesurer(Fonction f, const string& texte, const string& motif, size_t& trouves) {
    size_t total = 0;
    auto debut = steady_clock::now();
    for (int r = 0; r < REPETITIONS; r++)
        total += f(texte, motif).size();
    duration<double, milli> duree = steady_clock::now() - debut;
    trouves = total / REPETITIONS;
    return duree.count() / REPETITIONS;
}

int main(int argc, char* argv[]) {
    string fichier = argc > 1 ? argv[1] : "texte.txt";
    ifstream in(fichier, ios::binary);
    if (!in) {
        cout << "Fichier introuvable : " << fichier << endl;
        return 1;
    }
    stringstream buffer;
    buffer << in.rdbuf();
    string texte = buffer.str();

    vector<string> motifs;
    for (int i = 2; i < argc; i++) motifs.push_back(argv[i]);
    if (motifs.empty()) motifs = {"le", "chaine", "algorithme", "zzzzzz"};

    // Largeur de la première colonne : le motif le plus long
    size_t largeur = 8;
    for (const string& motif : motifs) largeur = max(largeur, motif.size() + 2);

    cout << texte.size() << " caracteres" << endl << endl;
    cout << left << setw(largeur) << "Motif" << setw(10) << "Trouves" << setw(12) << "Naive ms"
         << "Horspool ms" << endl;

    double total[2] = {0, 0};
    cout << fixed << setprecision(3);
    for (const string& motif : motifs) {
        size_t t[2];
        double ms[2] = {
            mesurer(rechercheNaive, texte, motif, t[0]),
            mesurer(rechercheHorspool, texte, motif, t[1]),
        };
        cout << left << setw(largeur) << motif << setw(10) << t[0];
        for (int i = 0; i < 2; i++) {
            total[i] += ms[i];
            cout << setw(12) << ms[i];
        }
        if (t[0] != t[1]) cout << "ERREUR";
        cout << endl;
    }
    cout << left << setw(largeur + 10) << "Total";
    for (int i = 0; i < 2; i++) cout << setw(12) << total[i];
    cout << endl;
    return 0;
}
