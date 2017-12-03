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
    1. void send_clicked() - wenn ENTER oder Send gedrückt wird, speichern wir die Eingabe in i_miso.
    1. void* handler(void* params) - falls i_mosi nicht leer ist, schreiben wir seine Daten aus.
### **misomosi** - Für memory
1. **memory.c**
    1. void allocate_str_array(char*** array, int size, int piece_size) - eine zweidimensionellen Char-Array allokieren aus einem char***
    1. void free_str_array(char*** array, int size) - die oben allokierten array freilassen.
    1. void shift(char*** array, int size) - Die ganze FIFO nach links schiften.
1. **misomosi.c**
    1. void write_comm(char*** ch, char* in) - eine der FIFOs mit Daten schreiben.
    1. int read_comm(char*** ch, char** out) - eine der FIFOs auslesen, falls es Daten innerhalb gibt, true zurücktreten, und diese Element löschen (durch schiften).
### **networking** - Für Server- und Clientoperationen
1. **networking.c**
    1. void networking(char* param) - abhängig von dem CLI-parametern entweder Server oder Client-Thread starten, und auch eine Router-Thread:
    1. void* router(void* param) - die FIFO-s handeln
1. **server.c**
    1. void* server(void* params) - Eintrittspunkt für den Server, fängt an zu listen-en (auf dem spezifierten Port), started andere Threads(callback, serverread).
    1. void* host_info(void* params) - Eintrittspunkt für den Information-server (der ermöglicht den Admin-Oberfläche).
    1. void* serverread(void* params) - Für einkommene Daten (-> n_miso)
    1. void s_handle_input(char* in) - Für einkommene Daten (Hilfsfunktion)
    1. void* callback(void* params) - Verteilung des einkommenden Daten (nach jede verbundene Client)
1. **client.c**
    
    Sehr ähnlic zu server, aber:
    1. void handle_input(char* in) - parsieren den einkommenden Daten - message, status, key request, key response, key negotiation -> entsprechende Hilfsfunktionen, sehr trivial (sehen Sie den Grafikonen unten).
