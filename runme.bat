REM MIKTEX_PATH=E:\Programs\MiKTeX\miktex\bin
REM PATH=%MIKTEX_PATH%;%PATH%

mkdir tmp
pdflatex -aux-directory=tmp --enable-write18 -interaction=nonstopmode document.tex
bibtex -include-directory=tmp tmp/document
pdflatex -aux-directory=tmp --enable-write18 -interaction=nonstopmode document.tex
pdflatex -aux-directory=tmp --enable-write18 -interaction=nonstopmode document.tex
acrord32 document.tex

buildRRO
acrord32 RichReportOutline.pdf