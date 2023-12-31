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
% Filename: ltnews.cls
% Author: Alan Jeffrey
% Version: 0.05
 
% This is the LaTeX2e document class for the `LaTeX News' information 
% sheet which comes with every LaTeX release.  It may be useful for 
% newsletters, or as an example of how simple newsletters can be set with 
% LaTeX.  The changes log is at the end of the file.
 
% Copyright 1994 Alan Jeffrey and the LaTeX3 project.  All rights reserved.
 
% This is a LaTeX2e document class.
 
\NeedsTeXFormat{LaTeX2e}
 
\ProvidesClass{ltnews}[1994/05/31 Standard LaTeX class]

% The configuration file, used for passing options.

\InputIfFileExists{ltnews.cfg}{%
   \ClassInfo{ltnews}{Using local configuration file}%
}{%
   \ClassInfo{ltnews}{No local configuration file}%
}

% The lw35fonts option uses the fonts:
%
%    Adobe Palatino          (main text)
%    Adobe Helvetica Bold    (headings)
%    Courier                 (program listings)
%    Mathptm math italic     (2e logo)
%    Mathptm symbol font     (AMS logo)
%
% The type1fonts option uses the fonts:
% 
%    Adobe Utopia            (main text)
%    URW Grotesk-T Bold      (headings)
%    Lucida Sans typewriter  (program listings)
%    Mathptm math italic     (2e logo)
%    Mathptm symbol font     (AMS logo)

% The Adobe Palatino fonts:

\DeclareFontFamily{OT1}{ppl}{}
\DeclareFontShape{OT1}{ppl}{m}{n}{<-> pplr7t}{}
\DeclareFontShape{OT1}{ppl}{m}{sc}{<-> pplrc7t}{}
\DeclareFontShape{OT1}{ppl}{m}{it}{<-> pplri7t}{}

% The Adobe Helvetica fonts:

\DeclareFontFamily{OT1}{phv}{}
\DeclareFontShape{OT1}{phv}{b}{n}{<-> phvb7t}{}

% The Adobe Courier fonts:

\DeclareFontFamily{OT1}{pcr}{\hyphenchar\font=-1}
\DeclareFontShape{OT1}{pcr}{m}{n}{<-> pcrr7t}{}
 
% The Utopia fonts:

\DeclareFontFamily{OT1}{put}{}
\DeclareFontShape{OT1}{put}{m}{n}{<-> putr7t}{}
\DeclareFontShape{OT1}{put}{m}{sc}{<-> putrc7t}{}
\DeclareFontShape{OT1}{put}{m}{it}{<-> putri7t}{}

% The URW Grotesk fonts:

\DeclareFontFamily{OT1}{ugq}{}
\DeclareFontShape{OT1}{ugq}{b}{n}{<-> ugqb7t}{}

% The Lucida Sans Typewriter fonts:

\DeclareFontFamily{OT1}{hlct}{\hyphenchar\font=-1}
\DeclareFontShape{OT1}{hlct}{m}{n}{<-> hlct7t}{}

% The mathptm math italic:

\DeclareFontFamily{OML}{ptmcm}{\skewchar\font=127}
\DeclareFontShape{OML}{ptmcm}{m}{it}{<-> zptmcmrm}{}

% The mathptm symbol font:

\DeclareFontFamily{OMS}{pzccm}{}
\DeclareFontShape{OMS}{pzccm}{m}{n}{<-> zpzccmry}{}

% The TeX logo for use with Palatino.

\def\pplTeX{T\kern-.15em\lower.4ex\hbox{E}\kern-.1emX\@}

% The LaTeX logo for use with Palatino.

\DeclareRobustCommand{\pplLaTeX}{L\kern-.3em
        {\setbox0\hbox{T}%
         \vbox to\ht0{\hbox{%
                            \csname S@\f@size\endcsname
                            \fontsize\sf@size\z@
                            \math@fontsfalse\selectfont
                            A}%
                      \vss}%
        }%
        \kern-.07em
        \TeX}

% The TeX logo for use with Utopia.

\def\putTeX{T\kern-.1667em\lower.4ex\hbox{E}\kern-.075emX\@}

% The LaTeX logo for use with Utopia.

\DeclareRobustCommand{\putLaTeX}{L\kern-.2em
        {\setbox0\hbox{T}%
         \vbox to\ht0{\hbox{%
                            \csname S@\f@size\endcsname
                            \fontsize\sf@size\z@
                            \math@fontsfalse\selectfont
                            A}%
                      \vss}%
        }%
        \kern-.05em
        \TeX}

% The TeX logo for use with Helvetica.

\def\phvTeX{T\kern-.1em\lower.4ex\hbox{E}\kern-.05emX\@}

% The LaTeX logo for use with Helvetica.

\DeclareRobustCommand{\phvLaTeX}{L\kern-.3em
        {\calculate@math@sizes
         \setbox0\hbox{T}%
         \vbox to\ht0{\hbox{%
                            \csname S@\f@size\endcsname
                            \fontsize\sf@size\z@
                            \math@fontsfalse\selectfont
                            A}%
                      \vss}%
        }%
        \kern-.05em
        \TeX}

% The TeX logo for use with Grotesk.

\def\ugqTeX{T\kern-.1em\lower.4ex\hbox{E}\kern-.05emX\@}

% The LaTeX logo for use with Grotesk.

\DeclareRobustCommand{\ugqLaTeX}{L\kern-.15em
        {\calculate@math@sizes
         \setbox0\hbox{T}%
         \vbox to\ht0{\hbox{%
                            \csname S@\f@size\endcsname
                            \fontsize\sf@size\z@
                            \math@fontsfalse\selectfont
                            A}%
                      \vss}%
        }%
        \kern-.01em
        \TeX}

% The TeX logo for use with CMSS.

\def\cmssTeX{T\kern-.2em\lower.4ex\hbox{E}\kern-.05emX\@}

% The LaTeX logo for use with CMSS.

\DeclareRobustCommand{\cmssLaTeX}{L\kern-.22em
        {\setbox0\hbox{T}%
         \vbox to\ht0{\hbox{%
                            \csname S@\f@size\endcsname
                            \fontsize\sf@size\z@
                            \math@fontsfalse\selectfont
                            A}%
                      \vss}%
        }%
        \kern-.17em
        \TeX}

% Switch off some of the article options.
 
\DeclareOption{a4paper}{\OptionNotUsed}
\DeclareOption{a5paper}{\OptionNotUsed}
\DeclareOption{b5paper}{\OptionNotUsed}
\DeclareOption{letterpaper}{\OptionNotUsed}
\DeclareOption{legalpaper}{\OptionNotUsed}
\DeclareOption{executivepaper}{\OptionNotUsed}
\DeclareOption{landscape}{\OptionNotUsed}
\DeclareOption{twoside}{\OptionNotUsed}
\DeclareOption{titlepage}{\OptionNotUsed}
\DeclareOption{onecolumn}{\OptionNotUsed}

% The CM fonts

\newcommand{\@titlefont}{\normalfont\Huge}
\newcommand{\@indiciafont}{\normalfont\footnotesize}
\newcommand{\@headingfont}{%
   \large\sffamily\slshape
   \let\LaTeX\cmssLaTeX\let\TeX\cmssTeX
}

% The LW 35 fonts option

\DeclareOption{lw35fonts}{%
   \renewcommand{\rmdefault}{ppl}%
   \renewcommand{\ttdefault}{pcr}%
   \renewcommand{\sfdefault}{phv}%
   \renewcommand{\@titlefont}{%
      \fontsize{50}{60}\fontfamily{phv}\fontseries{b}\selectfont
      \let\LaTeX\phvLaTeX\let\TeX\phvTeX
   }%
   \renewcommand{\@indiciafont}{%
      \fontsize{8}{10}\fontfamily{ppl}\fontshape{it}\selectfont
   }%
   \renewcommand{\@headingfont}{%
      \fontsize{12}{14}\fontfamily{phv}\fontseries{b}\selectfont
      \let\LaTeX\phvLaTeX\let\TeX\phvTeX
   }%
   \DeclareSymbolFont{letters}{OML}{ptmcm}{m}{it}%
   \DeclareSymbolFont{symbols}{OMS}{pzccm}{m}{n}%
   \let\LaTeX\pplLaTeX
   \let\TeX\pplTeX
}

% The type 1 fonts option

\DeclareOption{type1fonts}{%
   \renewcommand{\rmdefault}{put}%
   \renewcommand{\ttdefault}{hlct}%
   \renewcommand{\sfdefault}{ugq}%
   \renewcommand{\@titlefont}{%
      \fontsize{50}{60}\fontfamily{ugq}\fontseries{b}\selectfont
      \let\LaTeX\ugqLaTeX\let\TeX\ugqTeX
   }%
   \renewcommand{\@indiciafont}{%
      \fontsize{8}{10}\fontfamily{put}\fontshape{it}\selectfont
   }%
   \renewcommand{\@headingfont}{%
      \fontsize{12}{14}\fontfamily{ugq}\fontseries{b}\selectfont
      \let\LaTeX\ugqLaTeX\let\TeX\ugqTeX
   }%
   \renewcommand{\verbatim@font}{%
      \fontsize{9}{12}\fontfamily{hlct}\selectfont
   }%
   \DeclareSymbolFont{letters}{OML}{ptmcm}{m}{it}%
   \DeclareSymbolFont{symbols}{OMS}{pzccm}{m}{n}%
   \let\LaTeX\putLaTeX
   \let\TeX\putTeX
}

% The default action for any option is to pass it to the article
% class.
 
\DeclareOption*{\PassOptionToClass{\CurrentOption}{article}}
 
% Execute the options.
 
\ProcessOptions
 
% Load the article class.
 
\LoadClass[twocolumn,oneside]{article}

% The page style.
 
\pagestyle{empty}
\setlength{\parindent}{1em}
\setlength{\rightskip}{0pt plus \textwidth}
\setlength{\@rightskip}{\rightskip}
\setlength{\parfillskip}{0pt plus 2\textwidth}
\setlength{\columnsep}{2em}

% The text size, which tries to work with both A4 and letter paper sizes. 
 
\setlength{\textheight}{230mm}
\setlength{\topmargin}{-10mm}
 
\setlength{\textwidth}{180mm}
\setlength{\oddsidemargin}{-10mm}
 
% \maketitle parameters.
 
\newcommand{\publicationmonth}{\renewcommand{\@month}}
\newcommand{\@month}{\ClassError{ltnews}
   {No \protect\publicationmonth~given}\@eha}
 
\newcommand{\publicationyear}{\renewcommand{\@year}}
\newcommand{\@year}{\ClassError{ltnews}
   {No \protect\publicationyear~given}\@eha}
 
\newcommand{\publicationissue}{\renewcommand{\@issue}}
\newcommand{\@issue}{\ClassError{ltnews}
   {No \protect\publicationissue~given}\@eha}
\newcommand{\issuename}{Issue}
 
\newcommand{\indicia}{\renewcommand{\@indicia}}
\newcommand{\@indicia}{%
   \LaTeXNews, and the \LaTeX{} software,
   is brought to you by the \LaTeX3 project team;
   Copyright \@year, all rights reserved.
}
 
\title{\LaTeXNews}
 
% The \maketitle for the LaTeX News.
 
\renewcommand{\maketitle}{%
   \twocolumn[{%
      \parbox[t][7\baselineskip]{\textwidth}{%
         \@titlefont\@title\\[\medskipamount]
         \normalfont\normalsize\issuename~\@issue, \@month~\@year
      }%
   }]%
   \thispagestyle{titlepage}
}
 
\newcommand{\ps@titlepage}{%
   \renewcommand{\@oddhead}{\hfill}%
   \renewcommand{\@evenhead}{\hfill}%
   \renewcommand{\@oddfoot}{\@indiciafont\@indicia\hfill}%
   \renewcommand{\@evenfoot}{\@indiciafont\@indicia\hfill}%
}
 
% Sectioning commands.
 
\renewcommand{\section}{%
   \@startsection
      {section}{1}{\z@}{-1.5ex \@plus -1ex \@minus -.2ex}%
      {1ex \@plus.2ex}{\@headingfont}%
}
 
% No section numbers.
 
\setcounter{secnumdepth}{0}
 
% Set lists tighter, but brought in by 1em (otherwise the first line 
% always looks very wide).
 
\renewcommand{\@listI}{%
   \setlength{\parsep}{0pt}%
   \setlength{\topsep}{\medskipamount}%
   \setlength{\itemsep}{0pt}%
   \setlength{\listparindent}{1em}%
   \setlength{\rightskip}{1em}%
}
 
\newenvironment{citations}{%
   \list{}{%
      \renewcommand{\makelabel}[1]{\itshape{##1},}%
   }%
}{%
   \endlist
}
 
% Some logos.
 
\newcommand{\NFSS}{NFSS}
\newcommand{\LaTeXNews}{\LaTeX~News}
\newcommand{\AW}{Addison Wesley}
\newcommand{\SLiTeX}{\textsc{Sli}\TeX}
\newcommand{\AmS}{$${\protect\the\textfont2 A}\kern-.1667em\lower
         .5ex\hbox{\protect\the\textfont2 M}\kern
         -.125em{\protect\the\textfont2 S}}
\newcommand{\AmSLaTeX}{\mbox{\AmS-\LaTeX}}

% Hacking to make <...> produce italics in verbatim.  NB: this can be 
% done more cleanly using the verbatim package.  But the ltnews class has 
% to run on any LaTeX installation, even those without the verbatim 
% package.  
 
\catcode`\<=\active
\def<#1>{{\reset@font\normalsize\itshape#1\/}}
\def\verbatim@nolig@list{\do\`\do\,\do\'\do\-}
 
% That's it!
 
\endinput
 
% CHANGELOG
%
% 20 May 1994, v0.01: Created file.
%
% 21 May 1994, v0.02: Made <...> produce italics inside verbatim.  Added 
%    the indicia, \publicationyear, \publicationmonth and 
%    \publicationissue.  Added the citations environment.  Switched off 
%    some of the article class options.
% 
% 21 May 1994, v0.03: Fixed a bug with ragged right.  Fixed a bug
%    which was causing underfull hbox messages.
% 
% 27 May 1994, v0.04: Added SliTeX logo, and proper AMS LaTeX logo.
%    Added angle brackets to <...>.
%
% 31 May 1994, v0.05: Added downloaded PS fonts options.  Removed
%    angle brackets from <...> since these were the last remaining
%    bitmaps!  Added variants of the LaTeX logo.  Added the ltnews.cfg
%    file.  Added the lw35fonts option.

% BUGS
%
% Switching between logos like this is a mess.
%
% The last column should be set flush bottom.
 
