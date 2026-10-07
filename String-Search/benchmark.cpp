#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "recherche_find_file.h"
#include "recherche_horspool_file.h"
#include "recherche_naive_file.h"
using namespace std;
using namespace chrono;

const int REPETITIONS = 10;
const int LARGEURS[3] = {12, 14, 0};

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

    size_t largeur = 8;
    for (const string& motif : motifs) largeur = max(largeur, motif.size() + 2);

    cout << texte.size() << " caracteres" << endl << endl;
    cout << left << setw(largeur) << "Motif" << setw(10) << "Trouves" << setw(LARGEURS[0]) << "Naive ms"
         << setw(LARGEURS[1]) << "Horspool ms" << "Find ms" << endl;

    auto naive = [](const string& t, const string& m) { return rechercheNaive(t, m); };
    auto horspool = [](const string& t, const string& m) { return rechercheHorspool(t, m); };
    auto find = [](const string& t, const string& m) { return rechercheFind(t, m); };

    double total[3] = {0, 0, 0};
    cout << fixed << setprecision(3);
    for (const string& motif : motifs) {
        size_t t[3];
        double ms[3] = {
            mesurer(naive, texte, motif, t[0]),
            mesurer(horspool, texte, motif, t[1]),
            mesurer(find, texte, motif, t[2]),
        };
        cout << left << setw(largeur) << motif << setw(10) << t[0];
        for (int i = 0; i < 3; i++) {
            total[i] += ms[i];
            cout << setw(LARGEURS[i]) << ms[i];
        }
        if (t[0] != t[1] || t[0] != t[2]) cout << " ERREUR";
        cout << endl;
    }
    cout << left << setw(largeur + 10) << "Total";
    for (int i = 0; i < 3; i++) cout << setw(LARGEURS[i]) << total[i];
    cout << endl;
    return 0;
}
