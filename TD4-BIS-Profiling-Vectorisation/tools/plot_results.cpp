#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

struct VersionData {
    std::string name;
    std::string tech;
    std::string cat;
    std::vector<long long> cycles;
};

int main(int argc, char* argv[]) {
    std::string datafile = "tests/runs/data/grall.data";
    std::string outdir   = "tests/runs/graphs";
    if (argc > 1) datafile = argv[1];
    if (argc > 2) outdir   = argv[2];

    // Lire grall.data
    std::vector<int> sizes;
    std::vector<std::vector<long long>> cols;
    std::ifstream f(datafile);
    if (!f) { std::cerr << "Cannot open " << datafile << std::endl; return 1; }

    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        int sz; ss >> sz;
        sizes.push_back(sz);
        long long v; int i = 0;
        while (ss >> v) {
            if ((int)cols.size() <= i) cols.push_back({});
            cols[i++].push_back(v);
        }
    }
    f.close();

    // Versions
    std::vector<VersionData> versions = {
        {"001-O2","Référence r,c,d",        "ref"},
        {"001-O3","Référence r,c,d",        "ref"},
        {"002-O2","Loop Interchange r,d,c", "good"},
        {"002-O3","Loop Interchange r,d,c", "good"},
        {"003-O2","Tiling T=16",            "base"},
        {"003-O3","Tiling T=16",            "base"},
        {"004-O2","Tiling asymétrique",     "base"},
        {"004-O3","Tiling asymétrique",     "base"},
        {"005-O2","1D macros r,d,c",        "good"},
        {"005-O3","1D macros r,d,c",        "good"},
        {"006-O2","Tiling T=64 + AVX",      "best"},
        {"006-O3","Tiling T=64 + AVX",      "best"},
        {"007-O2","Tiling + unroll",        "base"},
        {"007-O3","Tiling + unroll",        "base"},
        {"008-O2","Tiling + vars locales",  "base"},
        {"008-O3","Tiling + vars locales",  "base"},
        {"009-O2","Tiling + buffer B",      "base"},
        {"009-O3","Tiling + buffer B",      "base"},
        {"010-O2","AVX2 + FMA",             "best"},
        {"010-O3","AVX2 + FMA",             "best"},
        {"011-O2","AVX2+FMA+OpenMP",        "best"},
        {"011-O3","AVX2+FMA+OpenMP",        "best"},
    };
    for (int i = 0; i < (int)versions.size() && i < (int)cols.size(); ++i)
        versions[i].cycles = cols[i];

    long long ref_val = versions[0].cycles.back();

    // ─── Graphique 1 : Vue d'ensemble O2 ──────────────────────────────
    {
        std::string plt = outdir + "/plot_overview.plt";
        std::string pdf = outdir + "/plot_overview.pdf";
        std::ofstream p(plt);
        p << "set terminal pdfcairo enhanced size 16cm,10cm\n";
        p << "set output '" << pdf << "'\n";
        p << "set title 'ssgemm — Vue d ensemble toutes versions (O2)'\n";
        p << "set xlabel 'Taille N'\n";
        p << "set ylabel 'Cycles'\n";
        p << "set key top left\n";
        p << "set grid\n";
        p << "plot ";
        bool first = true;
        for (int i = 0; i < (int)versions.size(); i += 2) {
            if (!first) p << ", \\\n     ";
            p << "'" << datafile << "' u 1:" << (i+2)
              << " w lp pt " << (i/2+1)
              << " title '" << versions[i].name << " (" << versions[i].tech << ")'";
            first = false;
        }
        p << "\n";
        p.close();
        std::string cmd = "gnuplot " + plt;
        system(cmd.c_str());
        std::cout << "Generated: " << pdf << std::endl;
    }

    // ─── Graphique 2 : Zoom versions optimisées (sans v001) ───────────
    {
        std::string plt = outdir + "/plot_zoom.plt";
        std::string pdf = outdir + "/plot_zoom.pdf";
        std::ofstream p(plt);
        p << "set terminal pdfcairo enhanced size 16cm,10cm\n";
        p << "set output '" << pdf << "'\n";
        p << "set title 'ssgemm — Zoom versions optimisees (O2, sans reference)'\n";
        p << "set xlabel 'Taille N'\n";
        p << "set ylabel 'Cycles'\n";
        p << "set key top left\n";
        p << "set grid\n";
        p << "plot ";
        bool first = true;
        for (int i = 2; i < (int)versions.size(); i += 2) {
            if (!first) p << ", \\\n     ";
            p << "'" << datafile << "' u 1:" << (i+2)
              << " w lp pt " << (i/2+1)
              << " title '" << versions[i].name << " (" << versions[i].tech << ")'";
            first = false;
        }
        p << "\n";
        p.close();
        std::string cmd = "gnuplot " + plt;
        system(cmd.c_str());
        std::cout << "Generated: " << pdf << std::endl;
    }

    // ─── Graphique 3 : Gains vs v001 ──────────────────────────────────
    {
        std::string dat = outdir + "/gains.dat";
        std::string plt = outdir + "/plot_gains.plt";
        std::string pdf = outdir + "/plot_gains.pdf";

        // Écrire fichier données gains
        std::ofstream d(dat);
        d << "# Version Gain\n";
        for (int i = 0; i < (int)versions.size(); i += 2) {
            double gain = (double)ref_val / versions[i].cycles.back();
            d << i/2+1 << " " << gain
              << " \"" << versions[i].name << "\"\n";
        }
        d.close();

        std::ofstream p(plt);
        p << "set terminal pdfcairo enhanced size 16cm,9cm\n";
        p << "set output '" << pdf << "'\n";
        p << "set title 'ssgemm — Gain vs v001-O2 (N=" << sizes.back() << ")'\n";
        p << "set ylabel 'Facteur de gain (x)'\n";
        p << "set xlabel 'Version'\n";
        p << "set style fill solid 0.8\n";
        p << "set boxwidth 0.7\n";
        p << "set grid y\n";
        p << "set xtics rotate by -30\n";
        p << "set yrange [0:*]\n";
        p << "set key off\n";
        // Colorer les barres selon la valeur
        p << "plot '" << dat << "' u 1:2:($2 > 15 ? '#27ae60' : $2 > 8 ? '#2980b9' : '#95a5a6')"
          << " with boxes lc rgb variable, \\\n";
        p << "     '" << dat << "' u 1:2:(sprintf('x%.1f',$2))"
          << " with labels offset 0,0.5 font ',9'\n";
        p.close();
        std::string cmd = "gnuplot " + plt;
        system(cmd.c_str());
        std::cout << "Generated: " << pdf << std::endl;
    }

    // ─── Graphique 4 : O2 vs O3 comparaison ───────────────────────────
    {
        std::string plt = outdir + "/plot_o2vso3.plt";
        std::string pdf = outdir + "/plot_o2vso3.pdf";
        std::ofstream p(plt);
        p << "set terminal pdfcairo enhanced size 16cm,10cm\n";
        p << "set output '" << pdf << "'\n";
        p << "set title 'ssgemm — Comparaison O2 vs O3 (N=" << sizes.back() << ")'\n";
        p << "set ylabel 'Cycles'\n";
        p << "set xlabel 'Version'\n";
        p << "set style data histograms\n";
        p << "set style histogram clustered gap 1\n";
        p << "set style fill solid 0.8 border -1\n";
        p << "set boxwidth 0.9\n";
        p << "set grid y\n";
        p << "set xtics rotate by -30\n";
        p << "set key top right\n";

        // Écrire données O2 vs O3
        std::string dat = outdir + "/o2vso3.dat";
        std::ofstream d(dat);
        d << "# Version O2 O3\n";
        for (int i = 0; i < (int)versions.size(); i += 2) {
            long long o2 = versions[i].cycles.back();
            long long o3 = (i+1 < (int)versions.size()) ? versions[i+1].cycles.back() : 0;
            d << "\"" << versions[i].name << "\" " << o2 << " " << o3 << "\n";
        }
        d.close();

        p << "plot '" << dat << "' u 2:xtic(1) title 'O2' lc rgb '#2980b9', \\\n";
        p << "     '" << dat << "' u 3 title 'O3' lc rgb '#e74c3c'\n";
        p.close();
        std::string cmd = "gnuplot " + plt;
        system(cmd.c_str());
        std::cout << "Generated: " << pdf << std::endl;
    }

    // ─── Résumé console ───────────────────────────────────────────────
    std::cout << "\n=== RESUME DES PERFORMANCES (N=" << sizes.back() << ") ===\n";
    std::cout << std::string(60, '-') << "\n";
    printf("%-12s %-28s %14s %8s\n", "Version", "Technique", "Cycles O2", "Gain");
    std::cout << std::string(60, '-') << "\n";
    for (int i = 0; i < (int)versions.size(); i += 2) {
        double gain = (double)ref_val / versions[i].cycles.back();
        printf("%-12s %-28s %14lld %7.1fx\n",
               versions[i].name.c_str(),
               versions[i].tech.c_str(),
               versions[i].cycles.back(),
               gain);
    }
    std::cout << std::string(60, '-') << "\n";
    std::cout << "Graphiques generes dans: " << outdir << "/\n";

    return 0;
}
