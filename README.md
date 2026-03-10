# M1 CHPS — Débogage, Profiling et Analyse de Performances

![License](https://img.shields.io/badge/License-MIT-yellow.svg)
![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)
![Compiler](https://img.shields.io/badge/Compiler-GCC%2011.2-blue.svg)
![SIMD](https://img.shields.io/badge/SIMD-AVX%20256bit-orange.svg)
![Perf](https://img.shields.io/badge/Profiling-Linux%20perf-red.svg)
![University](https://img.shields.io/badge/Université-Perpignan-darkgreen.svg)

**Auteur :** Yaya Toure  
**Formation :** Master 1 Calcul Haute Performance et Simulation (CHPS)  
**Université :** Université de Perpignan Via Domitia  
**Année universitaire :** 2025-2026  
**Licence :** MIT  
---

## Description

Ce dépôt contient l'ensemble des travaux pratiques du module
Débogage, Profiling et Analyse de Performances du Master 1 CHPS.
Chaque TD comprend le code source complet, un rapport scientifique
détaillé produit en LaTeX, et les résultats de benchmarks sur
architecture Intel Core i7 (Latitude 7480).

Le dépôt est mis à jour progressivement au fil des séances et
constitue une archive complète du parcours d'optimisation HPC.

---

## Travaux réalisés

| TD  | Thème                            | Technique principale           | Gain mesuré |
|-----|----------------------------------|--------------------------------|-------------|
| TD3 | Optimisation de boucles (ssgemm) | Loop Interchange + Loop Tiling | x11         |
| TD4 | Profiling et vectorisation AVX   | perf stat/record + AVX 256bit  | x19.9       |

---

## Prérequis
```bash
# Compilateur
gcc --version       # GCC >= 11.2.0

# Outils de build
cmake --version     # CMake >= 3.16

# Profiling (TD4)
perf --version      # Linux perf (kernel >= 5.15)

# Visualisation
gnuplot --version   # gnuplot >= 5.4
```

---

## Compilation et exécution rapide
```bash
# Cloner le dépôt
git clone git@github.com:CodingYayaToure/M1-CHPS-Debogage-Profiling.git
cd M1-CHPS-Debogage-Profiling

# TD4 — compiler et exécuter tous les benchmarks
cd TD4-Profiling-Vectorisation/libmcblas004
mkdir build && cd build
cmake ../ && make RALL

# Générer les graphiques
make GALL
```

---

## Architecture cible

| Composant    | Valeur                          |
|--------------|---------------------------------|
| CPU          | Intel Core i7 (Latitude 7480)   |
| Cache L1d    | 64 KiB                          |
| Cache L2     | 512 KiB                         |
| Cache L3     | 3 MiB                           |
| SIMD         | AVX2 — YMM 256 bits (8 floats)  |
| Compilateur  | GCC 11.2.0, -O2/-O3 -march=native |
| OS           | Ubuntu 24, Linux perf           |

---

## Résultats principaux (N=1000)
```
Version    Technique                 Cycles            Gain
----------------------------------------------------------------
v001-O2    Reference r,c,d           21 063 671 922    x1
v002-O2    Loop Interchange r,d,c     1 896 422 768    x11.1
v009-O2    Tiling + buffer B          1 870 859 146    x11.3
v010-O2    Tiling + AVX 256 bits      1 059 085 932    x19.9
```

---

## Structure du dépôt
```
M1-CHPS-Debogage-Profiling/
├── README.md
├── LICENSE
├── CHANGELOG.md
├── CONTRIBUTING.md
├── .gitignore
├── TD3-Optimisation-Boucles/
│   ├── README.md
│   ├── rapport_TD3_YAYA_TOURE.pdf
│   ├── libmcblas002/
│   └── results/
│       └── grv123456.pdf
└── TD4-Profiling-Vectorisation/
    ├── README.md
    ├── rapport_TD4_YAYA_TOURE.pdf
    ├── libmcblas004/
    └── results/
        └── pdfall.pdf
```

---

## Référence théorique

Bacon D., Graham S., Sharp O.  
*Compiler Transformations for High-Performance Computing*  
ACM Computing Surveys, Vol. 26, No. 4, December 1994.

---

## Licence

Ce projet est distribué sous licence MIT.  
Voir le fichier [LICENSE](./LICENSE) pour les détails.
