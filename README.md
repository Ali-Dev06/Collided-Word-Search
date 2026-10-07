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

## Benchmarks

Temps mesurés avec `chrono`, en ms, médiane de 5 exécutions (Intel Core Ultra 5 125H, Linux, g++ 11.4, `-O2`). Sur une autre machine, les valeurs changent mais le classement reste le même.

**Projet 1** : test des 127 419 mots de `texte_riche.txt`.

| Motif | Mots trouvés | Boucle | Find | Plus rapide |
|---|---:|---:|---:|---|
| `cote` | 1 035 | **2,59** | 5,26 | boucle ×2,0 |
| `prg` | 152 | **2,65** | 4,91 | boucle ×1,9 |
| `abc` | 40 | **2,58** | 5,43 | boucle ×2,1 |
| `xyz` | 0 | **2,60** | 4,48 | boucle ×1,7 |
| `compteur` | 5 | **2,59** | 6,07 | boucle ×2,3 |
| `tion` | 2 046 | **2,52** | 5,39 | boucle ×2,1 |
| `aaa` | 279 | **2,49** | 5,77 | boucle ×2,3 |
| **Total** | | **18,03** | 37,31 | boucle ×2,1 |

**Projet 2** : recherche dans un texte de 14 811 920 caractères.

| Motif | Occurrences | Naïf | Horspool | Find | Plus rapide |
|---|---:|---:|---:|---:|---|
| `le` | 217 500 | 18,27 | 43,69 | **9,53** | find ×1,9 |
| `de` | 223 460 | 17,64 | 40,29 | **7,33** | find ×2,4 |
| `pour` | 25 880 | 13,69 | 16,53 | **5,15** | find ×2,7 |
| `france` | 2 080 | 11,26 | 14,18 | **2,53** | find ×4,4 |
| `ment` | 35 440 | 14,98 | 19,14 | **5,16** | find ×2,9 |
| `abracadabra` | 20 | 22,35 | **6,22** | 7,40 | Horspool ×3,6 |
| `constitutionnellement` | 0 | 15,51 | **4,59** | 5,27 | Horspool ×3,4 |
| `zzzzzz` | 0 | 8,94 | 7,91 | **0,67** | find ×13,3 |
| **Total** | | 122,63 | 152,54 | **43,04** | find ×2,8 |

- `find` est le plus rapide presque partout.
- Horspool gagne sur les motifs très longs, mais il est le plus lent sur les motifs de 2 lettres.
- Les tableaux complets (aussi sur le petit texte de 0,7 Mo) sont dans `Rapport/Rapport.pdf`.

## Lancer

Il faut `g++` (C++17). Exemple pour le projet 2 :
```
cd String-Search
g++ -O2 -std=c++17 -o recherche_fichier recherche_fichier.cpp
.\recherche_fichier texte_riche.txt france
```
Toutes les commandes (test, benchmark, projet 1) sont dans `GUIDE.md`.


