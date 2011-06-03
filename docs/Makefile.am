man_MANS = numaverage.1 numbound.1 numinterval.1 numnormalize.1 numgrep.1 numprocess.1 numrange.1 numrandom.1 numround.1 numsum.1 
EXTRA_DIST = $(man_MANS)
pdf: ps
	ps2pdf num-utils-ng.ps

num-utils-ng.dvi: num-utils-ng index references
	TEXINPUTS=$(srcdir):: latex $(srcdir)/num-utils-ng.tex
	TEXINPUTS=$(srcdir):: latex $(srcdir)/num-utils-ng.tex

num-utils-ng:$(srcdir)/num-utils-ng.tex
	TEXINPUTS=$(srcdir):: latex $(srcdir)/num-utils-ng.tex

index:num-utils-ng
	makeindex num-utils-ng.idx

references: num-utils-ng
	BSTINPUTS=$(srcdir):: bibtex num-utils-ng

ps: num-utils-ng.dvi
	dvips num-utils-ng.dvi




clean:
	$(RM) -f num-utils-ng.aux
	$(RM) -f num-utils-ng.dvi
	$(RM) -f num-utils-ng.ind
	$(RM) -f num-utils-ng.toc
	$(RM) -f num-utils-ng.bbl
	$(RM) -f num-utils-ng.idx
	$(RM) -f num-utils-ng.log
	$(RM) -f num-utils-ng.blg
	$(RM) -f num-utils-ng.ilg
	$(RM) -f num-utils-ng.ps
	$(RM) -f num-utils-ng.pdf
