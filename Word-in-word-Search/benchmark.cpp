#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "sous_sequence.h"
#include "sous_sequence2.h"
using namespace std;
using namespace chrono;

const int REPETITIONS = 5;

// Compte les mots qui contiennent le motif. Retourne le temps moyen en ms.
template <typename Fonction>
double mesurer(Fonction f, const vector<string>& mots, const string& motif, long& trouves) {
    long total = 0;
    auto debut = steady_clock::now();
    for (int r = 0; r < REPETITIONS; r++)
        for (const string& mot : mots)
            if (f(mot, motif)) total++;
    duration<double, milli> duree = steady_clock::now() - debut;
    trouves = total / REPETITIONS;
    return duree.count() / REPETITIONS;
}

int main(int argc, char* argv[]) {
    string fichier = argc > 1 ? argv[1] : "mots.txt";
    ifstream in(fichier);
    if (!in) {
        cout << "Fichier introuvable : " << fichier << endl;
        return 1;
    }

    vector<string> mots;
    string mot;
    while (in >> mot) mots.push_back(mot);

    vector<string> motifs;
    for (int i = 2; i < argc; i++) motifs.push_back(argv[i]);
    if (motifs.empty()) motifs = {"cote", "prg", "abc", "xyz", "compteur"};

    cout << mots.size() << " mots" << endl << endl;
    cout << left << setw(12) << "Motif" << setw(10) << "Trouves"
         << setw(14) << "Boucle ms" << "Find ms" << endl;

    double totalBoucle = 0, totalFind = 0;
    cout << fixed << setprecision(3);
    for (const string& motif : motifs) {
        long t1, t2;
        double ms1 = mesurer(estSousSequence, mots, motif, t1);
        double ms2 = mesurer(estSousSequenceFind, mots, motif, t2);
        totalBoucle += ms1;
        totalFind += ms2;
        cout << left << setw(12) << motif << setw(10) << t1
             << setw(14) << ms1 << ms2;
        if (t1 != t2) cout << " ERREUR";
        cout << endl;
    }
    cout << left << setw(22) << "Total" << setw(14) << totalBoucle << totalFind << endl;
    return 0;
}
