\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{mathese}[]
% version 1.0 Olivier Pothier 1999/09/15
% version 1.1 Catherine Lamy 2000/04/18
% version 1.2 Gregoire Pau 2005/07/06

%---------------------------------------
%---- on se base sur la classe book ----
%---- sur papier a4, 2 faces, 1 col ----  
%---------------------------------------
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{book}}
\ProcessOptions
\LoadClass{book}

%----------------------
%---- les packages ----
%----------------------


%------------------------------
%---- la taille de la page ----
%------------------------------
\voffset 0.0cm
\hoffset 0.0cm
\textheight 23cm
\textwidth 15cm
\topmargin 0.0cm
\oddsidemargin 0.0cm
\evensidemargin 0.0cm

%----------------------------------------------------------------
%---- pour la sombre histoire que \chapter* ne fait pas appel
%---- à chaptermark, on a toujours \leftmark qui est en 
%---- majuscules (chiant au possible, on remarque au passage
%---- que T. Oetiker, dans ``The Not So Short Introduction to
%---- Latex 2e'' a laissé tombé...). On definit donc un ersazt
%---- de \chapter*, \chapternonum, qui fait appel à \markboth
%---- avec deux arguments identiques (notons au passage que 
%---- \chapter, lui, comme un con, ne passe qu'un argument, le
%---- premier, à markboth au traver de \chaptermark. Il faudrait
%---- aussi réécrire \chapter, demain peut-être :-))
%----------------------------------------------------------------
\newcommand{\chapternonum}[1]{\chapter*{#1\markboth{#1}{#1}}}

\usepackage{fancyhdr}

%-----------------------------------
%---- on se charge des headings ----
%-----------------------------------
\pagestyle{fancy}
%\bibliographystyle{fancy}
%---- on doit redefinir \chaptermark et \sectionmark pour qu'ils
%---- ne mettent pas tout en majuscule. On vire au passage tous les
%---- tests débiles fait dans leur version originale, et on corrige
%---- le fait que \chaptermark ne passait qu'un seul argument à
%---- markboth, ce qui posait problème dans certains cas, rares il est
%---- vrai.
%---- Je ne veux pas afficher \chaptername dans le header, et on
%---- laisse tout dans la casse voulue par l'auteur... L'argument
%---- passé par \chapter à \chaptermark est son argument propre (à
%---- savoir le nom du chapitre. On fait de même pour section.
\renewcommand{\chaptermark}[1]{\markboth {\thechapter.\ #1}{\thechapter.\ #1}}
\renewcommand{\sectionmark}[1]{\markright{\thesection. \ #1}}
\fancyhf{}
%----       le numéro de la page       ----
%---- à gauche sur les pages de gauche ----
%---- à droite sur les pages de droite ----
\fancyhead[LE,RO]{\thepage}
%---- \leftmark, cad le chapitre, à droite des pages de gauche
\fancyhead[RE]{\textsc{\leftmark}}
%---- \rightmark, cad la section, à gauche des pages de droite
%\fancyhead[LO]{\textsc{\rightmark}}
%---- les initiales ----%
%\fancyfoot[RE,LO]{\footnotesize C.L.}
%---- la version ----%
%\fancyfoot[CE,CO]{\footnotesize version finale}
%---- la date ----%
%\fancyfoot[LE,RO]{\tiny 2000}
%---- les barres ----%
\renewcommand{\headrulewidth}{1pt}
\renewcommand{\footrulewidth}{1pt}
\addtolength{\headheight}{1pt}
%---- on redefinit le style plain (\chapter le force pour la
%---- première page de tout chapitre
\fancypagestyle{plain}{
  \fancyhead[RE]{}
  \fancyhead[LO]{}
}

% nouveaux environements de theoreme
%----------------------
\newtheorem{proposition}{Proposition}
%\newtheorem{lemme}{Lemme}
\newtheorem{exemple}{Exemple}
%\newcommand{\mydefinition}[2]{\begin{definition}{\bf #1:} #2$\diamond$\end{definition}}
%\newcommand{\mydefinition}[1]{\begin{definition}#1\end{definitio
\newtheorem{theorem}{Théorème}
\newcommand{\deftitle}[1]{\begin{definition}{\bf (#1)}}


\newcommand{\chapterw}[1]{\chapter*{#1}\addcontentsline{toc}{chapter}{#1}}

%% choix des profondeurs de section pour la table des matières
\setcounter{secnumdepth}{3}  %% Avec un numero.
\setcounter{tocdepth}{3}     %% Visibles dans la table des matieres
