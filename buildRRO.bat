@echo off
pdflatex -aux-directory=tmp  --enable-write18 -interaction=nonstopmode include/RichReportOutline.tex
bibtex -include-directory=tmp  tmp/RichReportOutline
pdflatex -aux-directory=tmp  --enable-write18 -interaction=nonstopmode include/RichReportOutline.tex
pdflatex -aux-directory=tmp --enable-write18 -interaction=nonstopmode include/RichReportOutline.tex

pause