# Encrypto
Programmer's guide
## Allgeimeine Aufbau

Die Code des Applikations ist in logische Einheiten (und anhand diesen Foldern) verteilt. Für jede *.c File gehört eine *.h File mit gleichem Name, die die Include-Sachen enthalten, und die Funktionen des Files deklarieren. Außer diesen Foldern findet man nur drei Dateien:
### main (.c und .h)
Diese beschreiben die Anfangspunkt des Applikations. Aus dem Terminal die CLI-parametern werden zuerst in einem Datenstruktur (viele char* -s) eingeladet. Einige müssen aus Äußerem erreichbar sein, diese sind globale Variablen (und später mit Keyword `extern` erreicht), andere brauchen wir nur Lokal. 

Hier installieren wir auch einem Signalhandler für Signal `SIGINT`, mithilfe von wem wir `^C` korrekt behandeln können, um die Applikation zum Halt kommen zu lassen.

Im Funktion `start` allokieren wir 5 FIFO-s, je für eine spezifizierten Task - n_miso ist für Netwerk Master-In-Slave-Out, i_mosi ist für Interface Master-Out-Slave-In, usw. Diese sind je `N`x`L` groß, also `N` unterschiedliche Dateien können gespeichert werden, je `L` lang. 

Auch hier werden zwei Funktionen angerufen, eine für den Initialisation des Interfaces, andere für des Netzwerkes.
### defines (.h)
Diese ist die "Settings" file des Programmes. Jede #define Direktiv ist hier angegeben.

## Folders
### **file** - Für Fileoperationen
1. **io.c**
    1. void log_file(char* tag, char* client, char* message) -  Screibt eine Zeile in die Logfile aus.
    1. char* load_log() - Ladet die ausgeschriebene Zeilen aus der Logfile ein in einem neu allokierten char*.
    1. void write_pem(const char* type, char* data, const char* file) - schreibt eine PEM-formattiert File aus.
    1. char* read_key(char* file) - Ladet eine PEM-formattiert Datei ein.
### **interfaces** - Für Benutzeroberflächen
1. **interfaces.c**
    1. void interfaces(char* param) - eine 'switch' für CLI oder GUI. Jede nicht `cli` Eingabe werden als `gui` behandelt. Die neue Threads werden gestartet, und diese Thread wird zu eineim Halt gebracht - bis einem SIGINT.
1. **cli.c**
    1. void *cli(void* params) - wenn es Daten in dem i_mosi gibt, diese Daten ausschreiben (formel: carriage return, eine Zeile nach oben, löschen diese Zeile, ausscreiben, zurück nach unten). Startet auch eine neues Thread:
    1. void *listener(void* params) - wenn der Benutzer aus dem Tastatur Daten eingeben, speichern in i_miso.
1. **gui.c**
    1. static void start(GtkApplication* app, gpointer user_data) - Für den Aussicht des GUIs
    1. void* gui(void* params) - Eintrittspunkt des GUI-kodes.
    1. void send_clicked() - wenn ENTER oder Send gedrückt wird, specihern wir die Eingabe in i_miso.
    1. void* handler(void* params) - falls i_mosi nicht leer ist, schreiben wir seine Daten aus.
1. 