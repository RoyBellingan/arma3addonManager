# arma3addonManager
ennesimo tentativo a fixare una situazione disastrosa

Partendo da https://github.com/SecMeyo/WorkshopManager

Provare a scaricare qualche addon e ricreare la struttura 

C:\GAME_SERVER\arma3server

che contiene 

1)arma3server
2)gli addon come LINK con il NOME (steamcmd li scarica in C:\GAME_SERVER\steamcmd\steamapps\workshop\content\107410)

e sarebbero inusabili solo con l'id.

# Step 1
Installare steamcmd https://steamcdn-a.akamaihd.net/client/installer/steamcmd.zip 

https://www.python.org/

click primo link (latest python 3 release)

in fondo click su  Windows installer (64-bit)

IMPORTANTE fare click su add python.exe to PATH

Install now va benissimo

Cliccare per estendere il path oltre 260 caratteri.

# Step 2
https://github.com/SecMeyo/WorkshopManager/blob/master/requirements.txt

pip install joblib
pip install beautifulsoup4

Creare la cartella WorkshopManager (anche sul desktop va benisismo) e scaricarci dentro https://raw.githubusercontent.com/SecMeyo/WorkshopManager/master/wm.py

entrare con cmd dentro la cartella appena creata e provare che funzioni il tutto con 

python wm.py -h

si dovrebbe leggere l'help del programma

# Step 3
Configurare per l'uso di arma3 server (solo una volta)

python wm.py set appid 233780

configurare la cartella dove salvare gli addon
python wm.py set install_dir C:\Users\Arma3_9GU\Desktop\prova

configurare login per steam non necessario in quanto è tutto libero quel che viene scaricato, importante il "" che sarebbe la password vuota
python wm.py set login anonymous ""

Provare ad installare CBA (probabilmente l'addon più piccolo)

python wm.py install 450814997
