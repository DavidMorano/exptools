% \iffalse meta-comment
%
% Copyright 1994 the LaTeX3 project and the individual authors.
% All rights reserved. For further copyright information see the file
% legal.txt, and any other copyright indicated in this file.
% 
% This file is part of the LaTeX2e system.
% ----------------------------------------
% 
%  This system is distributed in the hope that it will be useful,
%  but WITHOUT ANY WARRANTY; without even the implied warranty of
%  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
% 
% 
% IMPORTANT NOTICE:
% 
% For error reports in case of UNCHANGED versions see bugs.txt.
% 
% Please do not request updates from us directly.  Distribution is
% done through Mail-Servers and TeX organizations.
% 
% You are not allowed to change this file.
% 
% You are allowed to distribute this file under the condition that
% it is distributed together with all files mentioned in manifest.txt.
% 
% If you receive only some of these files from someone, complain!
% 
% You are NOT ALLOWED to distribute this file alone.  You are NOT
% ALLOWED to take money for the distribution or use of either this
% file or a changed version, except for a nominal charge for copying
% etc.
% \fi
% Filename: ltxguide.cls
% Author: Alan Jeffrey
% Version: 0.05
 
% This is the document class for the LaTeX guides `LaTeX2e for authors'
% and `LaTeX2e for class and package writers'.  The changes log is at the
% end of the file.
 
% Copyright 1994 Alan Jeffrey and the LaTeX3 project.  All rights reserved.
 
% This is a LaTeX2e document class.
 
\NeedsTeXFormat{LaTeX2e}[1994/06/01]
\ProvidesClass{ltxguide}[1994/06/01 Standard LaTeX class]
 
% Input any local configuration file.
 
\InputIfFileExists{ltxguide.cfg}{
   \ClassInfo{ltxguide}{Local configuration file used.}
}{
   \ClassInfo{ltxguide}{Local configuration file not found.}
}
 
% All options are passed to the article class.
 
\DeclareOption*{\PassOptionsToPackage{\CurrentOption}{article}}
\ProcessOptions
\LoadClass{article}
 
% No paragraph indentation, space between paragraphs.
 
\setlength{\parindent}{0pt}
\setlength{\parskip}{\medskipamount}
 
% The names of some documents:
 
\newcommand{\clsguide}{\LaTeXe{} for Class and Package Writers}
\newcommand{\usrguide}{\LaTeXe{} for Authors}
\newcommand{\fntguide}{\LaTeXe{} Font Selection}
\newcommand{\sourcecode}{\LaTeX: the program}
\newcommand{\LaTeXbook}{\LaTeX: A Document Preparation System}
\newcommand{\LaTeXcomp}{The \LaTeX{} Companion}
 
% The SliTeX logo:
 
\newcommand{\SLiTeX}{\textsc{Sli}\TeX}
 
% A declaration of a command, in a box, set out into the margin.
 
\newenvironment{decl}%
    {\par\small\addvspace{4.5ex plus 1ex}%
     \vskip -\parskip
     \noindent\hspace{-\leftmargini}%
     \begin{tabular}{|l|}\hline\ignorespaces}%
    {\\\hline\end{tabular}\par\nopagebreak\addvspace{2.3ex}%
     \vskip -\parskip}
 
\newcommand{\declline}[1]{\\\multicolumn1{|r|}{\small#1}}

% Run the toc tighter:

\def\@starttoc#1{\begingroup
  \makeatletter
  \parskip\z@\@plus\p@\relax         % <----
  \@input{\jobname.#1}\if@filesw 
  \expandafter\newwrite\csname tf@#1\endcsname
             \immediate\openout
                 \csname tf@#1\endcsname \jobname.#1\relax
  \fi \global\@nobreakfalse \endgroup}
 
% Some hacks with verbatim... NB: this would be better done with the
% verbatim package, but this document has to run on any LaTeX
% installation.
%
% Set verbatim small.
 
\let\nverbatim\verbatim
\def\verbatim{\ifhmode\unskip\fi\nopagebreak\small\nverbatim}

% Make |...| a synonym for \verb|...|
 
\catcode`\|=\active
\def|{\verb|}
 
% Make <...> produce italics surrounded by angle brackets, even in
% verbatim.  << produces a less-than, and >> produces a greater-than.
 
\catcode`\<=\active
\catcode`\>=\active
\def<{\@ifnextchar<\@lt\@meta}
\def>{\@ifnextchar>\@gt\@gtr@err}
\def\@lt<{\char`\<}
\def\@gt>{\char`\>}
\def\@meta#1>{{\normalfont\itshape$\langle$#1\/$\rangle$}}
\def\@gtr@err{%
   \ClassError{ltxguide}{%
      Isolated \protect>%
   }{%
      In this document class, \protect<...\protect> 
      is used to indicate a parameter.\MessageBreak
      I've just found a \protect> on its own.
      Perhaps you meant to type \protect>\protect>?
   }%
}
\def\verbatim@nolig@list{\do\`\do\,\do\'\do\-}
 
% Various forms of argument:
 
\newcommand{\m}[1]{\mbox{$\langle$\itshape#1\/$\rangle$}}
\renewcommand{\arg}[1]{{\tt\string{}\m{#1}{\tt\string}}}
\newcommand{\oarg}[1]{{\tt[}\m{#1}{\tt]}}
 
% Logos.
 
\newcommand{\NFSS}{\textsf{NFSS}}
 
\newcommand{\AmS}{$${\protect\the\textfont2 A}\kern-.1667em\lower
         .5ex\hbox{\protect\the\textfont2 M}\kern
         -.125em{\protect\the\textfont2 S}}
 
\newcommand{\AmSLaTeX}{\mbox{\AmS-\LaTeX}}
 
% Table of contents is two deep.
 
\setcounter{tocdepth}{2}
 
% Allow more flexibility about bad paragraphs.
 
\tolerance500
 
% That's it!
 
\endinput
 
% CHANGELOG
%
% 24 May 1994, ASAJ: Turned the collection of macros used by
%       usrguide and clsguide into a class.
%
% 27 May 1994, ASAJ: Added the SliTeX logo.
%
% 28 May 1994, ASAJ: Made << and >> produce < and > inside verbatim.  
%    Added ltxguide.cfg.
%
% 29 May 1994, ASAJ: Added italic correction to <...>.
%    Added \sourcecode.
%
% 1 Jun 1994, ASAJ: Made toc run tighter, corrected bug with verbatim.
