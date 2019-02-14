% RaM-BScReport.cls
% ----------------
% LaTeX Class to generate reports for BSc reports
% with a proper title page for the University of Twente
%TODO Make proper title page...
%
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{include/RaM/RaM-BScReport}[2013/06/26 Robotics and Mechatronics Bachelor Report document class v1.0]

%% Pass given options to derived class 
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{include/RaM/RaMReport}}
\ProcessOptions

% Derive the BScReport from the RaMReport class
\LoadClass{include/RaM/RaMReport}

%% Packages required by RaM-BScReports

%% RaM-BScReport specific settings
