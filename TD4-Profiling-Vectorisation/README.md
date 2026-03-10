# TD4 — Profiling et Vectorisation AVX de ssgemm

**Module :** Débogage, Profiling et Analyse de Performances  
**Auteur :** Yaya Toure — Master 1 CHPS, 2025-2026  

---

## Objectif

Utiliser les outils de profiling Linux (perf) pour identifier les
goulots d'étranglement, puis concevoir une version vectorisée AVX
256 bits (mcblas010).

---

## Versions implémentées

| Version | Technique                        |
|---------|----------------------------------|
| v001    | Référence r,c,d                  |
| v002    | Loop Interchange r,d,c           |
| v007    | Tiling + unroll 2rx4c            |
| v008    | Tiling + variables locales Ar/Bd |
| v009    | Tiling + buffer Bbuffer          |
| v010    | Tiling T=64 + AVX 256 bits       |

---

## Résultats perf stat (N=1000)
```
Métrique          v002-O2        v009-O2        v010-O3 (AVX)
--------------------------------------------------------------
Temps (s)         1.093          0.999          0.407
Cycles            869 M          945 M          410 M
Instructions    2 330 M        3 022 M          773 M
Cache-misses       64 M           28 M            3 M  (x21)
dTLB-misses       227 K          654 K           26 K  (x9)
```

## Résultats benchmarks (N=1000)
```
v001-O2    21 063 671 922 cycles    x1
v002-O2     1 896 422 768 cycles    x11.1
v009-O2     1 870 859 146 cycles    x11.3
v010-O2     1 059 085 932 cycles    x19.9
```

## Contribution principale : mcblas010

Placer c en boucle interne (stride-1 sur B et C) et extraire A(r,d)
comme invariant mis en registre permet la vectorisation automatique AVX.
Confirmé par -fopt-info-vec-optimized :

    mcblas3.cpp:31: optimized: loop vectorized using 32 byte vectors

Taille de bloc optimale : T=64 (49 152 octets, tient dans L1d=64 KiB).
