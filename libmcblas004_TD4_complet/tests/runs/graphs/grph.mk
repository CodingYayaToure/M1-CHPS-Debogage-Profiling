datdir=../data/
basename=Rtst
GRALL=grall.data
GPLOT=gnuplot

all: allgr

allgr: grv1256789.pdf

# ALL_GRAPHS: O0_GRAPHS O1_GRAPHS O2_GRAPHS O3_GRAPHS
#ALLPLT: gplt001.plt gplt002.plt gplt001002.plt

grv1v2v3.pdf: gpltv1v2v3.plt
	$(GPLOT) $^ > $@

grv123456.pdf: gpltv123456.plt
	$(GPLOT) $^ > $@

grv12567.pdf: gpltv12567.plt
	$(GPLOT) $^ > $@

grv125678.pdf: gpltv125678.plt
	$(GPLOT) $^ > $@

grv1256789.pdf: gpltv1256789.plt
	$(GPLOT) $^ > $@

##############################################################################
# VERSION 001
##############################################################################
gplt001.plt: $(GRALL)
	@echo "set terminal pdf" > $@
	@echo "set multiplot" >> $@
	@echo "plot '$(GRALL)' u 1:2 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:4 w linespoints" >> $@

#	@echo "pause -1" >> $@

##############################################################################
# VERSION 002
##############################################################################
gplt002.plt: $(GRALL)
	@echo "set terminal pdf" > $@
	@echo "set multiplot" >> $@
	@echo "plot '$(GRALL)' u 1:6 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:8 w linespoints" >> $@

#	@echo "pause -1" >> $@

##############################################################################
# VERSION 001 vs VERSION 002
##############################################################################
gpltv123.plt: $(GRALL)
	@echo "set terminal pdf" > $@
	@echo "set xlabel 'Sizes'" >> $@
	@echo "set ylabel 'Cycles'" >> $@
	@echo "set multiplot" >> $@
	@echo "plot '$(GRALL)' u 1:2 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:3 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:4 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:5 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:6 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:7 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:8 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:9 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:10 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:11 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:12 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:13 w linespoints" >> $@

##############################################################################
# VERSION 001 vs VERSION 002
##############################################################################
gpltv1234.plt: $(GRALL)
	@echo "set terminal pdf" > $@
	@echo "set xlabel 'Sizes'" >> $@
	@echo "set ylabel 'Cycles'" >> $@
	@echo "set multiplot" >> $@
	@echo "plot '$(GRALL)' u 1:2 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:3 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:4 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:5 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:6 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:7 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:8 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:9 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:10 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:11 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:12 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:13 w linespoints" >> $@

#	@echo "pause -1" >> $@

#rgp001: gplt001.plt $(g001files)
#	gnuplot $<

##############################################################################
# VERSION 001 vs VERSION 002
##############################################################################
gpltv123456.plt: $(GRALL)
	@echo "set terminal pdf" > $@
	@echo "set xlabel 'Sizes'" >> $@
	@echo "set ylabel 'Cycles'" >> $@
	@echo "set multiplot" >> $@
	@echo "plot '$(GRALL)' u 1:2 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:3 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:4 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:5 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:6 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:7 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:8 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:9 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:10 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:11 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:12 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:13 w linespoints" >> $@

##############################################################################
# VERSION 001 vs VERSION 002
##############################################################################
gpltv12567.plt: $(GRALL)
	@echo "set terminal pdf" > $@
	@echo "set xlabel 'Sizes'" >> $@
	@echo "set ylabel 'Cycles'" >> $@
	@echo "set multiplot" >> $@
	@echo "plot '$(GRALL)' u 1:2 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:3 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:4 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:5 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:6 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:7 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:8 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:9 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:10 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:11 w linespoints" >> $@

##############################################################################
# VERSION 001 vs VERSION 002
##############################################################################
gpltv125678.plt: $(GRALL)
	@echo "set terminal pdf" > $@
	@echo "set xlabel 'Sizes'" >> $@
	@echo "set ylabel 'Cycles'" >> $@
	@echo "set multiplot" >> $@
	@echo "plot '$(GRALL)' u 1:2 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:3 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:4 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:5 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:6 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:7 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:8 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:9 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:10 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:11 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:12 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:13 w linespoints" >> $@

##############################################################################
# VERSION 001 vs VERSION 002
##############################################################################
gpltv1256789.plt: $(GRALL)
	@echo "set terminal pdf" > $@
	@echo "set xlabel 'Sizes'" >> $@
	@echo "set ylabel 'Cycles'" >> $@
	@echo "set multiplot" >> $@
	@echo "plot '$(GRALL)' u 1:2 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:3 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:4 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:5 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:6 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:7 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:8 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:9 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:10 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:11 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:12 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:13 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:14 w linespoints,\\" >> $@
	@echo "     '$(GRALL)' u 1:15 w linespoints" >> $@






#rgp001: gplt001.plt $(g001files)
#	gnuplot $<

clean:
	rm -f *.plt *.pdf
