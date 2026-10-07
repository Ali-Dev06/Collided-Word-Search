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
- La boucle est environ 2 fois plus rapide que `find` (10 paires de mots testées).
- `main.cpp` teste 10 cas. `benchmark.cpp` compare les 2 versions.
- Explications : `ALGORITHME.md` et `ALGO2.md`.

## Projet 2 : mot dans un fichier

- Un fichier par algorithme : `recherche_naive_file.h`, `recherche_horspool_file.h`, `recherche_find_file.h`.
- `recherche_fichier.cpp` lance les 3 sur le même mot et affiche la ligne, la colonne et le temps de chacun.
- `test.cpp` vérifie que les 3 donnent les mêmes résultats. `benchmark.cpp` compare leur vitesse.
- Textes d'essai : `texte.txt`, `texte_riche.txt` (0,7 Mo) et `Roman.txt` (1 000 000 de mots).
- Explications : `ALGOSEARCHFILE.md`.

Résultat principal sur `Roman.txt` : `find` est le plus rapide presque partout, et Horspool gagne sur les motifs très longs. Le détail est dans le rapport.

## Benchmarks

Temps mesurés avec `chrono`, médiane de 5 exécutions (Intel Core Ultra 5 125H, Linux, g++ 11.4, `-O2`). Sur une autre machine, les valeurs changent mais le classement reste le même.

**Projet 1** : temps d'un appel en ns, sur les 10 paires de `main.cpp` (1 000 000 d'appels par paire).

| Mot1 | Mot2 | Résultat | Boucle | Find | Plus rapide |
|---|---|---|---:|---:|---|
| `Compteur` | `Cote` | Oui | **66,0** | 96,5 | boucle ×1,5 |
| `Compteur` | `COTE` | Oui | **64,8** | 91,9 | boucle ×1,4 |
| `Compteur` | `cMpR` | Oui | **44,6** | 90,0 | boucle ×2,0 |
| `Compteur` | `compteur` | Oui | **42,8** | 176,4 | boucle ×4,1 |
| `aabbcc` | `abc` | Oui | **26,0** | 77,7 | boucle ×3,0 |
| `Compteur` | `Cotte` | Non | **45,1** | 91,1 | boucle ×2,0 |
| `Compteur` | `Cetop` | Non | **43,2** | 81,6 | boucle ×1,9 |
| `Compteur` | `Z` | Non | **42,4** | 49,6 | boucle ×1,2 |
| `Cot` | `Cote` | Non | **17,5** | 75,3 | boucle ×4,3 |
| `abc` | `ACB` | Non | **17,6** | 62,3 | boucle ×3,5 |
| **Total** | | | **410,0** | 892,4 | boucle ×2,2 |

**Projet 2** : recherche dans `Roman.txt` (5,85 Mo, 999 923 mots).

| Motif | Occurrences | Naïf | Horspool | Find | Plus rapide |
|---|---:|---:|---:|---:|---|
| `le` | 85 449 | 12,86 | 25,65 | **6,28** | find ×2,0 |
| `de` | 84 265 | 10,97 | 26,02 | **5,70** | find ×1,9 |
| `pour` | 11 670 | 10,09 | 10,28 | **3,88** | find ×2,6 |
| `france` | 994 | 7,57 | 8,98 | **1,71** | find ×4,4 |
| `ment` | 14 949 | 9,98 | 11,58 | **3,88** | find ×2,6 |
| `abracadabra` | 1 | 14,36 | **4,07** | 4,78 | Horspool ×3,5 |
| `constitutionnellement` | 3 | 10,97 | **3,09** | 3,72 | Horspool ×3,6 |
| `zzzzzz` | 0 | 6,69 | 4,70 | **0,56** | find ×11,8 |
| **Total** | | 83,50 | 94,36 | **30,51** | find ×2,7 |

- `find` est le plus rapide presque partout.
- Horspool gagne sur les motifs très longs, mais il est le plus lent sur les motifs de 2 lettres.
- Le détail et l'explication des algorithmes sont dans `Rapport/Rapport.pdf`.

## Lancer

Il faut `g++` (C++17). Exemple pour le projet 2 :
```
cd String-Search
g++ -O2 -std=c++17 -o recherche_fichier recherche_fichier.cpp
.\recherche_fichier Roman.txt france
```
