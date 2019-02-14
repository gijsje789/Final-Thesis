% ----------------
% LaTeX Class to generate weekly report 
%
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{include/RaM/RaM-Weekly}[2013/06/26 Robotics and Mechatronics Weekly class v1.0]

%% Pass given options to derived class 
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{include/RaM/RaMReport}}
\ProcessOptions

% Derive RaM-Weekly from the RaMReport class
\LoadClass{include/RaM/RaMReport}

%% Packages required by RaM-Weekly

%% RaM-Weekly specific settings
