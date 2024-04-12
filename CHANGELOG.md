# Changelog

## 10/04/2023

- prima consegna.

## 20/04/2023

- creato il file che contiene le dichiarazioni delle funzioni utili per il menù
  di gioco.

## 30/04/2023

- creati i file di gestione dei moduli handle_game, handle_leaderboard, handle_help
- documentati in modules.txt
- creata la cartella common/
- creato il modulo common/math che contiene funzioni matematiche di base
- creato il modulo common/string che contiene funzioni per manipolare le stringhe
- aggiunte varie costanti globali e spostato globals in common/
- aggiunti i record player, players, entry e entries

## 10/05/2023

- creati i file di interfaccia contenenti i menu, regole e manuale
- implementati i record in C
- creato un prototipo di inferfaccia

## 15/05/2023

- modularizzate le costanti (spostate da globals ai vari moduli)
- implementate le varie funzionalità (salvataggio, classifica, gioco, aiuto)
- creata cartella data/ che contiene i file binari
- creata la cartella menus/ che contiene i menu da stampare a video, manuale e regole
- rinominato common/ a library/
- aggiunto il modulo library/term che permette di interagire con il terminale

## 31/5/2023

- creati casi di test per il modulo handle_game

## Corrente

- rinominato library/ a common/
- creata la cartella res/
- spostato la cartella data/ in res/data/
- spostata la cartella menus/ in res/text/menus
- spostati res/text/menus/manual.txt e res/text/rules.txt in res/text
- aggiunto file che contiene gli errori da stampare a video
- nella cartella src/ è stato tradotto tutto lo pseudocodice
- ogni funzione in C è stata documentata dei file di interfaccia seguendo la
  sintassi doxygen.
