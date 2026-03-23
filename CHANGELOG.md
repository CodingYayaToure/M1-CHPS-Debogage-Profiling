# Changelog

Toutes les modifications notables de ce dépôt sont documentées ici.
Format inspiré de [Keep a Changelog](https://keepachangelog.com).

---

## [0.2.0] - 2026-03-10

### Ajouté
- TD4 : Profiling avec perf stat et perf record
- TD4 : Vectorisation AVX 256 bits (mcblas010, gain x19.9)
- TD4 : Rapport complet 11 pages (LaTeX)
- TD4 : Graphique gnuplot pdfall.pdf (12 courbes v001-v010)

---

## [0.1.0] - 2026-02-27

### Ajouté
- TD3 : Analyse de dépendances et permutations de boucles
- TD3 : Loop tiling sur ssgemm (T=32, gain x10.7)
- TD3 : Rapport complet 14 pages (LaTeX)
- TD3 : Graphique gnuplot grv123456.pdf

---

## [0.3.0] - 2026-03-23

### Ajouté
- TD4-BIS : analyse perf stat sur 11 versions (v001-v011)
- TD4-BIS : perf record + perf annotate sur v009-O2
- TD4-BIS : vectorisation AVX 256 bits automatique (v006, Q-4.1)
- TD4-BIS : AVX2 + FMA intrinsèques explicites (v010)
- TD4-BIS : parallélisation OpenMP 4.5 (v011, 3.54 CPUs utilisés)
- TD4-BIS : Analyse Top-Down de Yasin (Frontend/Backend/Retiring/Bad Spec)
- TD4-BIS : dashboard HTML interactif (make GUI)
- TD4-BIS : 5 graphiques gnuplot (overview, zoom, gains, O2vsO3)
- TD4-BIS : programme C++ plot_results générant les graphiques automatiquement
