% RaMReport.cls
% ------------
% LaTeX Class to generate reports for RaM reports
% This file is included in the class definitions and should contain class specific settings
% ie settings which defines the document type (margins, headers, footers, etc
%
% Keep content generic for RaM reports!
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{include/RaM/RaMReport}[2013/06/26 Robotics and Mechatronics Report document class v1.0]

%% Pass given options to derived class 
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{include/files/Report}}
\ProcessOptions

% Derive the RaMReport from the Report class
\LoadClass{include/files/Report}

%% Packages required by RaMReports
\RequirePackage{fancyhdr}		% Advanced header manipulation

%%Setup the headers and footers (for RaM templates)
\pagestyle{fancy} %use the fancy style
\fancyhf{} %clear headers and footers

%%Change the header and footerstyle of normal pages 
\fancyhead[RO,LE]{\thepage}
\fancyhead[RE]{\doctitle}
\fancyhead[LO]{\leftmark}
\fancyfoot[RE]{University of Twente}
\fancyfoot[LO]{Robotics and Mechatronics}

\iffinalversion
	\fancyfoot[CO,CE]{\docauthor}
\else
	% Add current date, and if datetime package is present, apply a nice formatting
	\fancyfoot[CO,CE]{\docauthor, \ifthenelse{\isundefined{\ddmmyyyydate} }{%
	\today
	}{ %else
	% Use day-month-year (numerical) and only make the changes temporary
	% using {} so the document date type is not influenced!
	{\def\dateseparator{-}\ddmmyyyydate\today}}%
	}
\fi	

%%Change the header and footerstyle of chapter pages (1st page chapter + frontmatter)
\fancypagestyle{plain}{%
	\fancyhf{} %clear headers and footers
	\fancyhead[RO,LE]{\thepage}
	\fancyhead[RE]{\doctitle}
	\fancyfoot[RE]{University of Twente}
	\fancyfoot[LO]{Robotics and Mechatronics}
	\iffinalversion
		\fancyfoot[CO,CE]{\docauthor}
	\else
		% Add current date, and if datetime package is present, apply a nice formatting
		\fancyfoot[CO,CE]{\docauthor, \ifthenelse{\isundefined{\ddmmyyyydate} }{%
		\today
		}{ %else
		% Use day-month-year (numerical) and only make the changes temporary
		% using {} so the document date type is not influenced!
		{\def\dateseparator{-}\ddmmyyyydate\today}}%
		}
		
		% Add (Draft) to pages containing the start of a new chapter, normally they have an empty header
		\fancyhead[RO]{(Draft)}
	\fi	
}%

\ifpdf
	\RequirePackage{pdfpages}
	\pdfminorversion=6 % Don't show warnings like: ``PDF inclusion: found PDF version <1.x>, but at most version <1.4> allowed
\fi	

%%Set header and footer sizes
\renewcommand{\headrulewidth}{0.4pt}
\renewcommand{\footrulewidth}{0.4pt}
