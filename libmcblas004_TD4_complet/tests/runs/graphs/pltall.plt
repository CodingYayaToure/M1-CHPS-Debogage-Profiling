set terminal pdf
set xlabel "Sizes"
set ylabel "Cycles"
set title "Comparaison ssgemm v001-v010 (O2/O3) - TD4"
set key top left
set multiplot
plot 	"data/grall.data" u 1:2 w lp title "001-O2", 	"data/grall.data" u 1:3 w lp title "001-O3", 	"data/grall.data" u 1:4 w lp title "002-O2", 	"data/grall.data" u 1:5 w lp title "002-O3", 	"data/grall.data" u 1:6 w lp title "007-O2", 	"data/grall.data" u 1:7 w lp title "007-O3", 	"data/grall.data" u 1:8 w lp title "008-O2", 	"data/grall.data" u 1:9 w lp title "008-O3", 	"data/grall.data" u 1:10 w lp title "009-O2", 	"data/grall.data" u 1:11 w lp title "009-O3", 	"data/grall.data" u 1:12 w lp title "010-O2", 	"data/grall.data" u 1:13 w lp title "010-O3"
