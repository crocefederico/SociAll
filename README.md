#Sociall
Titolo del progetto: Sociall- La piattaforma web di social sharing con servizio di riconoscimento facciale.

Studenti partecipanti:
Croce Federico - 1546488
Mucci Daniele - 1531141

Elenco del software consegnato:
SociAll-master
├── install.sh
├── README.md
└── sociall
    ├── CMakeLists.txt
    ├── config_db.php
    ├── createdb
    ├── include
    │   ├── detectObject.h
    │   ├── http.php
    │   ├── ImageUtils.h
    │   ├── oauth_client.php
    │   ├── oauth_configuration.json
    │   ├── preprocessFace.h
    │   └── recognition.h
    ├── index.php
    ├── inserisci_utente.php
    ├── inviaFoto.php
    ├── layout.css
    ├── lib
    │   ├── haarcascade_eye_tree_eyeglasses.xml
    │   ├── haarcascade_eye.xml
    │   └── lbpcascade_frontalface.xml
    ├── login_conID.php
    ├── login_con_webcam.php
    ├── login_manuale.php
    ├── login.php
    ├── logout.php
    ├── main.php
    ├── Makefile
    ├── registra_ok.php
    ├── registrazione.php
    ├── salvaFoto.php
    ├── shout.php
    ├── sociall.local.conf
    ├── src
    │   ├── detectObject.cpp
    │   ├── ImageUtils_0.7.cpp
    │   ├── main.cpp
    │   ├── preprocessFace.cpp
    │   ├── recognition.cpp
    ├── style
    │   ├── 2.jpg
    │   ├── avanti.png
    │   ├── Facebook.png
    │   ├── inserisci.png
    │   ├── Instagram.png
    │   ├── login_2.png
    │   ├── login3.png
    │   ├── login.png
    │   ├── login_tradizionale.png
    │   ├── password3.png
    │   ├── password.png
    │   ├── registrazione1.png
    │   ├── registrazione.png
    │   ├── riconoscimento_facciale.png
    │   ├── ripeti.png
    │   ├── scatta.png
    │   ├── shout.png
    │   ├── sociall_subtitle.png
    │   ├── sociall_title.png
    │   ├── submit2.png
    │   ├── submit.png
    │   ├── success.png
    │   ├── success_reg.png
    │   ├── Twitter.png
    │   └── upload.png
    ├── test.php
    └── utenti.sql

5 directories, 63 files

Istruzioni su come eseguire il software
~$cd /home/user/Downloads
~$unzip Sociall-master -d .
~$sudo sh install.sh
#inserire password di un utente MySql con privilegi di amministrazione

I file sorgenti non realizzati da noi sono quelli localizzati in /include e in /lib.
I file di configurazione sono layout.css, config_db.php , createdb, sociall.local.conf.
Il resto dei file sorgenti sono stati creati appositamente per offrire il servizio. 


La documentazione del progetto è reperibile nella cartella Doc/documentazione.pdf
