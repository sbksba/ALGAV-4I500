#*******************************************************************************
# Makefile for LaTeX documents
#
# Provided under the terms of
# GNU General Public License <http://www.gnu.org/licenses/gpl.html>
#
#*******************************************************************************

#*******************************************************************************
# Document base name that we want to build
DOC = algav_Projet

#*******************************************************************************
# Directory where are stored all used images .eps and .png format
IMAGEDIR = images

#*******************************************************************************
# Final directory where we want to save the final results
FINALDIR = $(DOC)

#*******************************************************************************
# Language (fr, gb)
# If set, html will use the corresponding language
# If set and run final, files will be in the corresponding language directory
LNG = fr

#*******************************************************************************
# NO CHANGE NEEDED BELOW THAT LINE
#*******************************************************************************

#*******************************************************************************
# Processor
LATEX = latex
MAKEINDEX = makeindex
DVIPS = dvips
PDF = pdflatex
BIB = bibtex
READPDF= evince
DIAPO= presentation

#*******************************************************************************
# Error message
BADREF = "get cross-references right"

#*******************************************************************************
# Default values
MODE = --interaction batchmode

#*******************************************************************************
# Check what we have to do

.PHONY: help usage dvi ps pdf clean all final

help: usage

usage:
	clear
	@echo ""
	@echo "Makefile for latex document"
	@echo "USAGE: "
	@echo ""
	@echo "help     - That usage information"
	@echo "usage    - That usage information"
	@echo "dvi      - Build the dvi file"
	@echo "ps       - Build the postscript file to be print"
	@echo "img      - Build the pdf with pictures"
	@echo "final    - Build all output files (dvi, ps, pdf) and move them to the final directory"
	@echo "clean    - Remove all intermediate files"
	@echo ""
	@echo "dossier : "$(DOC)""

dvi: $(DOC).tex
	@echo ""
	@echo "***************************************************************************"
	@echo "creation du fichier dvi"
	@echo "***************************************************************************"
	$(LATEX) $(DOC).tex

ps: $(DOC).tex
	make dvi
	@echo ""
	@echo "***************************************************************************"
	@echo "creation du fichier ps"
	@echo "***************************************************************************"
	$(DVIPS) -o $(DOC$).ps $(DOC).dvi

pdf: $(DOC).tex
	make ps
	@echo ""
	@echo "***************************************************************************"
	@echo "creation du fichier pdf"
	@echo "***************************************************************************"
	$(PDF) $(DOC).tex

img: $(DOC).tex
	@echo "***************************************************************************"
	@echo "creation du dossier"
	@echo "***************************************************************************"
	mkdir -p $(FINALDIR)
	@echo "***************************************************************************"
	@echo "creation du fichier pdf avec des images"
	@echo "***************************************************************************"
	$(PDF) $(DOC).tex
	$(PDF) $(DOC).tex
	@echo ""
	@echo "***************************************************************************"
	@echo "deplacement des fichiers dvi, ps et pdf dans le dossier"
	@echo "***************************************************************************"
	mv $(DOC).pdf $(FINALDIR)
	@echo ""
	@echo "***************************************************************************"
	@echo "suppression des fichiers temporaires"
	@echo "***************************************************************************"
	rm -f $(DOC).log
	rm -f $(DOC).aux
	rm -f $(DOC).toc
	rm -f $(DOC).lot
	rm -f $(DOC).lof
	@echo ""
	@echo "***************************************************************************"
	@echo "affichage du pdf"
	@echo "***************************************************************************"
	$(READPDF) $(DOC)/$(DOC).pdf

dia:
	@echo "***************************************************************************"
	@echo "creation du fichier pdf avec des images"
	@echo "***************************************************************************"
	$(PDF) $(DIAPO).tex
	$(PDF) $(DIAPO).tex
	rm -f *.aux *.glo *.gls *.idx *.ilg *.ind *.lof *.log *.lot *.out *.toc *.nav *.snm

final: $(DOC).tex
	@echo "###########################################################################"
	@echo "lancement de la compilation"
	@echo "###########################################################################"
	@echo ""
	@echo "***************************************************************************"
	@echo "creation du dossier"
	@echo "***************************************************************************"
	mkdir -p $(FINALDIR)
	make pdf
	@echo ""
	@echo "***************************************************************************"
	@echo "deplacement des fichiers dvi, ps et pdf dans le dossier"
	@echo "***************************************************************************"
	mv $(DOC).dvi $(FINALDIR)
	mv $(DOC).ps $(FINALDIR)
	mv $(DOC).pdf $(FINALDIR)
	@echo ""
	@echo "***************************************************************************"
	@echo "suppression des fichiers temporaires"
	@echo "***************************************************************************"
	rm -f $(DOC).log
	rm -f $(DOC).aux
	rm -f $(DOC).toc
	rm -f $(DOC).lot
	rm -f $(DOC).lof
	@echo ""
	@echo "***************************************************************************"
	@echo "affichage du pdf"
	@echo "***************************************************************************"
	$(READPDF) $(DOC)/$(DOC).pdf

clean:
	clear
	@echo "***************************************************************************"
	@echo "nettoyage complet"
	@echo "***************************************************************************"
	rm -f *~ *.aux *.glo *.gls *.idx *.ilg *.ind *.lof *.log *.lot *.out *.toc *.nav *.snm *.pdf
	rm -f $(DOC).haux $(DOC).hind $(DOC).htoc $(DOC).image.tex $(DOC).dvi $(DOC)*.ps $(DOC).pdf $(DOC).b* *.gif
	rm -rf $(DOC) $(DOC).pgf-plot.gnuplot
