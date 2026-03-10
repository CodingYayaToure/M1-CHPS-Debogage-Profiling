# M1 CHPS — Débogage, Profiling et Analyse de Performances

**Auteur :** Yaya Toure  
**Formation :** Master 1 Calcul Haute Performance et Simulation (CHPS)  
**Université :** Université de Perpignan Via Domitia  
**Année universitaire :** 2025-2026  
**Module :** Débogage, Profiling et Analyse de Performances  

---

## Description

Ce dépôt contient les travaux pratiques du module Débogage, Profiling et
Analyse de Performances du Master 1 CHPS. Chaque TD comprend le code source,
le rapport et les résultats de benchmarks. Le dépôt est mis à jour
progressivement au fil des séances.

---

## Travaux réalisés

| TD  | Thème                            | Technique principale           | Gain mesuré |
|-----|----------------------------------|--------------------------------|-------------|
| TD3 | Optimisation de boucles (ssgemm) | Loop Interchange + Loop Tiling | x11         |
| TD4 | Profiling et vectorisation AVX   | perf stat/record + AVX 256bit  | x19.9       |

---

## Architecture cible

- CPU : Intel Core i7 (Latitude 7480)
- Cache L1d : 64 KiB / L2 : 512 KiB / L3 : 3 MiB
- SIMD : AVX2, registres YMM 256 bits (8 floats)
- Compilateur : GCC 11.2.0 avec -O2/-O3 et -march=native
- Référence théorique : Bacon, Graham & Sharp,
  "Compiler Transformations for High-Performance Computing",
  ACM Computing Surveys, 1994

---

## Compilation
```bash
git clone https://github.com/CodingYayaToure/M1-CHPS-Debogage-Profiling.git
cd M1-CHPS-Debogage-Profiling/TD4-Profiling-Vectorisation/libmcblas004
mkdir build && cd build
cmake ../ && make RALL
```

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
├── TD3-Optimisation-Boucles/
│   ├── README.md
│   ├── rapport_TD3_YAYA_TOURE.pdf
│   ├── libmcblas002/
│   └── results/
└── TD4-Profiling-Vectorisation/
    ├── README.md
    ├── rapport_TD4_YAYA_TOURE.pdf
    ├── libmcblas004/
    └── results/
```

---

*Ce dépôt est mis à jour progressivement au fil des séances.*
