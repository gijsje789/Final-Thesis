# Makefile to build the LaTeX document and its RRO

# Name of the main TeX file
DOCUMENT?=document

# List of bibliography files (separated by spaces)
BIBLIOGRAPHIES?=bibliography.bib

# Name of the Rich Report Outline document
RRO?=RichReportOutline

# Generate index? (non-empty means yes)
# Uncomment for default index generation
#GENINDEX?=1


BIBTEX=bibtex
DVITEX=latex -interaction=nonstopmode
PDFTEX=pdflatex -interaction=nonstopmode
MAKEINDEX=makeindex

ifeq ($(V),)
  NON_VERBOSE=> /dev/null
endif

.PHONY: clean dvi pdf all rro help

define runlatex
	@echo "Processing $(1) for $(3) output"
	@while $(2) $(1).tex $(NON_VERBOSE); grep -q "Rerun to get \|has been referenced but does not exist" $(notdir $(1).log); do \
	  echo "  Rerunning for cross references and citations..."; \
	done
endef

define generateaux
	@echo "Preprocessing $(1)"
	@$(PDFTEX) -draftmode $(1).tex $(NON_VERBOSE)
endef

define runbibtex
	@echo "Bibtex processing $(1)"
	@$(BIBTEX) $(1) $(NON_VERBOSE)
endef

define runmakeindex
	@echo "Makeindex processing $(1)"
	@$(MAKEINDEX) $(if $(V),,-q) $(1).idx
endef

default: help

all: dvi pdf rro

define usage
Usage:
  make <target(s)> [variable]

  Suitable targets are:
    all       Same as adding these targets: dvi pdf rro
    dvi       Build dvi document
    pdf       Build PDF document
    rro       Build Rich Report Outline
    dvips     Create a postscript (ps) document, using the dvi document
              The dvi document is (re)build first when it is outdated
    dvipsdpf  Create a PDF document, using the postscript document
              The postscript document is (re)build first when it is outdated
    help      Shows this message
    clean     Clean all intermediate files (leaving the input files and the final results)
    distclean Clean all derived files (leaving only the input files)
  Note that it is allowed to provide multiple targets

  Accepted/Used variable/value pairs are:
    BIBLIOGRAPHIES  List of bibliography files (Default: bibliography.bib)
                    This list is space separated, so use quotes
    DOCUMENT        Name of the main TeX file (Default: document)
    GENINDEX        When value is not empty generate index files (to support an index in the document)
                    Note: You need to make sure to add the makeidx package and properly use it
    RRO             Name of the Rich Report Outlien file
    V               When value is not empty verbose building information is shown

  Examples:
    make pdf V=1    This build the pdf document showing verbose build information
    make clean pdf  This first cleans the derived files and then build a fresh PDF document
endef
export usage

help:
	@echo "$$usage"

clean:
	@-rm -rf tmp/*
	@-find . -type f -name '*.aux' -delete 2> /dev/null
	@-rm -f $(DOCUMENT).bbl $(DOCUMENT).blg $(DOCUMENT).log $(DOCUMENT).toc $(DOCUMENT).out texput.log
	@-rm -f $(DOCUMENT).idx $(DOCUMENT).ind $(DOCUMENT).ilg
	@-rm -f $(RRO).rro $(RRO).log $(RRO).out $(RRO).bbl $(RRO).blg

distclean: clean
	@-rm -f $(DOCUMENT).dvi $(DOCUMENT).pdf $(DOCUMENT).ps
	@-rm -f $(RRO).pdf

$(RRO).rro $(DOCUMENT).aux: $(DOCUMENT).tex $(BIBLIOGRAPHIES)
	$(call generateaux,$(DOCUMENT))

$(DOCUMENT).bbl: $(BIBLIOGRAPHIES) | $(DOCUMENT).aux
	$(call runbibtex,$(DOCUMENT))

# Unfortunately, $(DOCUMENT).idx keeps on getting updated, so the index is always regenerated...
$(DOCUMENT).ind: $(DOCUMENT).idx | $(DOCUMENT).aux
	$(call runmakeindex,$(DOCUMENT))

$(DOCUMENT).dvi: $(DOCUMENT).bbl $(if $(GENINDEX),$(DOCUMENT).ind,)
	$(call runlatex,$(DOCUMENT),$(DVITEX),DVI)

$(DOCUMENT).pdf: $(DOCUMENT).aux $(DOCUMENT).bbl $(if $(GENINDEX),$(DOCUMENT).ind,)
	$(call runlatex,$(DOCUMENT),$(PDFTEX),PDF)
	
$(DOCUMENT).ps: $(DOCUMENT).dvi
	dvips $< $(NON_VERBOSE)

$(RRO).aux: $(RRO).rro include/$(RRO).tex $(BIBLIOGRAPHIES)
	$(call generateaux,include/$(RRO),$(PDFTEX))

$(RRO).bbl: $(BIBLIOGRAPHIES) | $(RRO.aux)
	$(call runbibtex,$(RRO))

$(RRO).pdf: $(RRO).aux $(RRO).bbl
	$(call runlatex,include/$(RRO),$(PDFTEX),PDF)

pdf: $(DOCUMENT).pdf

rro: $(RRO).pdf

dvi: $(DOCUMENT).dvi
	
dvips: $(DOCUMENT).ps

dvipspdf: $(DOCUMENT).ps
	ps2pdf -dCompatibilityLevel=1.4 -dEmbedAllFonts=true -dOptimize=false -dPDFSETTINGS=/prepress $(DOCUMENT).ps $(NON_VERBOSE)
