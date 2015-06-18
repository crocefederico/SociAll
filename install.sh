#!bin/bash

#creazione delle cartelle
mkdir sociall/utenti
mkdir sociall/modelli
mkdir sociall/uploads
mkdir sociall/log

#Copia della cartella di installazione
cp -R sociall /var/www/html

#Modifica dei permessi delle cartelle
cd /var/www/html
chmod 777 /var/www/html/sociall
chmod 777 /var/www/html/sociall/utenti
chmod 777 /var/www/html/sociall/modelli
chmod 777 /var/www/html/sociall/uploads

#Compilazione del modulo C++
cmake /var/www/html/sociall/CMakeLists.txt
cd sociall
make

#Attivazione del virtual host "sociall.local"
cp /var/www/html/sociall/sociall.local.conf /etc/apache2/sites-available
cd /etc/apache2/sites-available
a2ensite sociall.local.conf
service apache2 reload

#Creazione ed inizializzazione del DB
chmod 755 /var/www/html/sociall/createdb
/var/www/html/sociall/createdb sociAll sito aSLJAPALGwqPav6r
mysql sociAll -usito -paSLJAPALGwqPav6r < /var/www/html/sociall/utenti.sql
