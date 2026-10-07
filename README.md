# Collided-Word-Search

Recherche de chaînes de caractères en C++ (ILISI 2, cours PO + Design Patterns).
Le dépôt contient 2 projets, un rapport et un guide.

## Structure

| Dossier | Contenu |
|---|---|
| `Word-in-word-Search/` | **Projet 1.** Un mot est-il dans un autre, dans l'ordre mais pas forcément côte à côte ? (`Compteur` contient `Cote`) |
| `String-Search/` | **Projet 2.** Un mot est-il dans un fichier texte ? 3 algorithmes comparés : naïf, Horspool et `find` |
| `Rapport/` | Rapport LaTeX et PDF : algorithmes, code, tableaux de benchmark |
| `GUIDE.md` | Quel programme pour quoi, et les commandes pour compiler et lancer |

## Projet 1 : mot dans un mot

- 2 versions de la même fonction : une boucle à 2 pointeurs (`sous_sequence.h`) et une version `find` (`sous_sequence2.h`).
- La boucle est environ 2 fois plus rapide que `find` (127 419 mots testés).
- `main.cpp` teste 10 cas. `benchmark.cpp` compare les 2 versions.
- Explications : `ALGORITHME.md` et `ALGO2.md`.

## Projet 2 : mot dans un fichier

- Un fichier par algorithme : `recherche_naive_file.h`, `recherche_horspool_file.h`, `recherche_find_file.h`.
- `recherche_fichier.cpp` lance les 3 sur le même mot et affiche la ligne, la colonne et le temps de chacun.
- `test.cpp` vérifie que les 3 donnent les mêmes résultats. `benchmark.cpp` compare leur vitesse.
- Textes d'essai : `texte.txt`, `texte_riche.txt` (0,7 Mo) et `Roman.txt` (1 000 000 de mots).
- Explications : `ALGOSEARCHFILE.md`.

Résultat principal sur un texte de 14,8 Mo : `find` est le plus rapide presque partout, et Horspool gagne sur les motifs très longs. Le détail est dans le rapport.

## Lancer

Il faut `g++` (C++17). Exemple pour le projet 2 :
```
cd String-Search
g++ -O2 -std=c++17 -o recherche_fichier recherche_fichier.cpp
.\recherche_fichier texte_riche.txt france
```
Toutes les commandes (test, benchmark, projet 1) sont dans `GUIDE.md`.

## Auteur

Ali Zouhdi, ILISI, FST Mohammedia.
