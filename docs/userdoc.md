# Encrypto 
Eine verschlüsselte Messenger-Applikation die Simplizität und Sicherheit zusammen ermöglicht.
## Anforderungen

*   Eine moderne Linux oder BSD distro mit Vernetzung
*   Xorg server mit GTK+
*   Libgcrypt
*   Pthread

## Installation
Um die Applikation zu installieren braucht man die source:
```
git clone https://github.com/leventeBajczi/encrypto-c.git
cd encrypto-c
make clean
```
Es gibt mehrere Möglichkeiten von hier an:

* Nur in diesem Folder die binäre Dateien herstellen:
    ```
    make encrypto
    ``` 
    Nach der Kompilierung kann eine neue Datei heißt `encrypto` in der `build` Folder gefunden werden.
* Nur in diesem Folder die binäre Dateien herstellen, und eine Server-Einheit laufen lassen: 
    ```
    make server
    ``` 
    Nach der Kompilierung kann eine neue Datei heißt `encrypto-server` in der `build` Folder gefunden werden, der auch laufen gelassen wird.
* Binäre Datei auch in /usr/bin/ herstellen, damit die Applikation systemweit benutzbar wird: 
    ```
    make install
    ``` 
    Nach der Kompilierung kann eine neue Datei heißt `encrypto` in der `build` Folder gefunden werden, der ins /usr/bin/ auch kopiert wird.

## Synopsys
Die Applikation kann durch CLI-Paramatern gestartet werden, welche je eine standarde Wert haben (falls nicht eingegeben):
```
encrypto [-m mode] [-c client] [-k keys] [-d directory] [-s server] [-n name] [-p port]
```
## Schaltern
* ### Mode
    * Entweder `server` oder `client` (default). 
    * In `server` Modus startet die Applikation sich als eine Server - Clients können sich zu dieser Einheit verbinden, Daten dadurch senden, und jeder, der sich über die Sicherheit des Programmes interessiert, kann die Logs checken. Nach der Anfang schreibt der Server zwei Zeile mit jede einer Portnummer aus: diese sind die Verbindungsporten, wozu Clients sich verbinden können. Zum Beispiel:
        ```
        Info available on port 45317
        Listening on port: 47709
        ```
        Diese beduetet, dass Clients können zu Port 47709 sich verbinden, und dass die 'Administration-Page' kann beim [http://serverip:45317]() gefunden.
        
        * Jeder Chat-Room braucht eine Server-Einheit. Diese sollte an inem solchen Maschine laufen gelassen werden, deren IP-Adresse bekannt und sichtbar (für die Clients) ist. Wenn ma dafür eine WAN benutzen möchtet, dann sollte er die Problem lösen, dass normalerweise die lokale IP-s sind nicht von außer sichtbar. In Allgeimein es beduetet, dass eine Weise Port-forwarding wird benötigt werden.
    * In `client` Modus verbindet sich die Applikation zu einem Server, und fängt an Messages zu senden. Vorsicht - dafür braucht man einen Partner, wegen der Verschlüsselung!
* ### Client
    * Entweder `gui` oder `cli` (default).
    * In `gui` Modus hat man eine auf GTK basierte graphische Oberfläche. Es verhindert den Benutz des Applikations nicht - jeder Operation kann auch von dem GUI durchgeführt werden.
* ### Keys
    * Die Folder spezifieren, wo die Keyfiles gespeichert werden können.
    * Die standarde Folder dafür ist `keys/` in dem aktuellen Folder.
    * Vorsicht - diese Folder muss existieren!
* ### Directory
    * Die Folder spezifieren, wo die Dateien gespeichert werden können.
    * Die standarde Folder dafür ist `messages/` in dem aktuellen Folder.
    * Vorsicht - diese Folder muss existieren!
* ### Server
    * Die IP-Addresse des Servers spezifieren.
    * Die standarde Addresse ist `localhost` (`127.0.0.1`)
* ### Name
    * Die Benutzername, die den Benutzer kennzeichnet.
    * Die standarde name ist `Anon`
* ### Port
    * Die Port spezifieren, die die Applikation benutzen sollten.
    * Diese Port muss leer sein!
    * Die standarde Port ist `0`, was bedeutet, dass die Kernel einen beliebigen Wert zuordnen wird in `server` Modus.
    * In `client` Modus muss diesen Wert spezifiert werden!

