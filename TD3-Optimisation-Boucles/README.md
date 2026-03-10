# TD3 — Optimisation de boucles sur ssgemm

**Module :** Débogage, Profiling et Analyse de Performances  
**Auteur :** Yaya Toure — Master 1 CHPS, 2025-2026  

---

## Objectif

Analyser les dépendances du nid de boucles de la fonction ssgemm,
identifier la meilleure permutation et valider la légalité du blocage
de boucles (loop tiling).

---

## Versions implémentées

| Version | Ordre des boucles | Technique        |
|---------|-------------------|------------------|
| v001    | r, c, d           | Référence        |
| v002    | r, d, c           | Loop Interchange |
| v003    | rr,dd,cc,r,d,c    | Loop Tiling T=32 |

---

## Résultats (N=1024)
```
v001-O2    7 874 082 133 cycles    x1
v002-O2      744 359 166 cycles    x10.6
v003-O2      734 899 254 cycles    x10.7
```

## Conclusions

- Meilleure permutation : r -> d -> c (stride-1 sur B et C, A en registre)
- Taille de bloc optimale : T=32 (12 KiB, tient dans L1d=64 KiB)
- Le tiling devient bénéfique à partir de N=1024
- Référence : Bacon et al. 1994, Sections 5, 6.2.1, 6.2.4, 6.2.6
