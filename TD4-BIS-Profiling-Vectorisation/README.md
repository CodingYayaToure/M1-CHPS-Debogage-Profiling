# TD4-BIS — Profiling, Vectorisation AVX et Analyse Top-Down

**Module :** Débogage, Profiling et Analyse de Performances
**Auteur :** Yaya Toure — Master 1 CHPS, 2025-2026
**Référence :** Yasin A., "A Top-Down Method for Performance Analysis
and Counters Architecture", Intel, 2014

---

## Versions implémentées

| Version | Technique | Cycles O2 (N=1000) | Gain |
|---------|-----------|-------------------|------|
| v001 | Référence r,c,d | 15 528 M | ×1 |
| v002 | Loop Interchange r,d,c | 1 368 M | ×11.3 |
| v003 | Tiling T=16 mauvais ordre | 4 621 M | ×3.4 |
| v004 | Tiling asymétrique | 5 590 M | ×2.8 |
| v005 | 1D macros r,d,c | 1 455 M | ×10.7 |
| v006 | Tiling T=64 + AVX 256 bits | 823 M | ×18.9 |
| v007 | Tiling + unroll | 2 123 M | ×7.3 |
| v008 | Tiling + vars locales | 1 931 M | ×8.0 |
| v009 | Tiling + buffer B | 1 551 M | ×10.0 |
| v010 | AVX2 + FMA intrinsèques | 794 M | ×19.6 |
| v011 | AVX2 + FMA + OpenMP | 815 M | ×19.0 |

---

## Compilation et exécution
```bash
mkdir build && cd build
cmake ../libmcblas004
make RALL    # benchmarks
make GALL    # graphiques gnuplot
make GUI     # dashboard HTML + graphiques PDF
```

---

## Résultats

- results/pdfall.pdf : toutes les versions O2/O3
- results/plot_overview.pdf : vue d'ensemble O2
- results/plot_zoom.pdf : zoom versions optimisées
- results/plot_gains.pdf : gains vs v001
- results/plot_o2vso3.pdf : comparaison O2 vs O3
- results/dashboard.html : dashboard interactif complet

---

## Analyse Top-Down de Yasin

| Version | Bottleneck principal |
|---------|---------------------|
| v001-O2 | Backend Bound (43.6%) — cache-misses stride-n |
| v002-O2 | Retiring (100%) — exécution efficace |
| v006-O2 | Frontend Bound (20%) — décodage AVX |
| v011-O2 | Retiring + Backend (OpenMP sync) |
