# SWO3-Übungen - WS 2023/24 - Übung 6

 Erstellen Sie für die Aufgabe eine entsprechende `CMakeLists.txt`-Datei und stellen Sie sicher, dass Sie keine Dateien aus Ihrer Entwicklungsumgebung dem Repository hinzufügen.
 Erstellen Sie ihre Visual-Studio Solution wie in den Übungen:

```shell
# open Devloper PowerShell for VS 2022
cd src
mkdir build
cd build
cmake ..
# open generated .sln with Visual Studio
```

## 1. Schach (src/chess/)

Erstellen Sie mit Hilfe der Vererbungsmöglichkeiten in C++ Klasse ein erweiterbares Schachsystem. Dabei gibt es eine gemeinsame Basisklasse, z.B. `Chessman` für alle Spielfiguren. Jede Spielfigur muss mindestens folgende Funktionalität bieten:

* die Farbe der Mannschaft liefern können
* eine symbolische Darstellung, z.B. in Form eines ASCII Zeichens liefern können
* die Frage beantworten können, ob es sich um eine „essentielle“ Figur handelt, deren Verlust das Ende des Spiels bedeuten würde
* ob sich die Figur von Position ($x_0$, $y_0$) auf Position ($x_1$, $y_1$) auf einem gegebenen Schachbrett bewegen könnte

Alle konkreten Spielfiguren sollen dann insbesondere für die letzte Funktionalität eigene Implementierungen haben. Erstellen Sie dazu abgeleitete Klassen für die typischen Schachfiguren:

* König („King“ – K) kann sich jeweils auf ein direkt oder diagonal liegendes benachbartes Feld bewegen, wenn dieses frei oder von einer gegnerischen (nicht aber von einer eigenen) Figur besetzt ist. Außerdem ist diese Figur essentiell.

* Die Dame („Queen“ – Q) kann sich beliebig weit diagonal oder rechtwinkelig auf dem Brett bewegen, solange keine andere Figur im Weg ist.

* Der Läufer („Bishop“ – B) kann ähnlich wie die Dame nur diagonal beliebig weit bis zur nächsten Figur bewegen.

* Der Turm („Rook“ – R) kann sich ähnlich wie die Dame nur horizontal oder vertikal beliebig weit bis zur nächsten Figur bewegen.

* Der Springer („Knight“ – N) kann sich um jeweils zwei Felder in eine Dimension und gleichzeitig um ein Feld in die andere Dimension bewegen. Dabei kann er beliebige andere Figuren überspringen.

Alle Figuren können auf einer feindlichen Figur landen, was diese aus dem Spiel befördert und zum eigenen Sieg beitragen kann. Die Figuren befinden sich auf einem Spielbrett welches z.B. in einer Klasse `Chessboard` implementiert werden kann. Dieses Spielfeld muss mindestens folgende Funktionalität aufweisen:

* Es soll prinzipiell vorgesehen sein, ein beliebig großes Spielbrett anlegen zu können (jedoch mit einer sinnvollen Mindestgröße).

* Es muss erkannt werden, wann das Spiel beendet ist (nämlich, wenn einer der Spieler eine essentielle Figur verloren hat).

* Für jede Position muss die darauf befindliche Figur ermittelt werden können. Dazu kann z.B. der Funktionsaufruf-Operator (`operator() (int, int)`) sozusagen als zweidimensionaler Indexoperator missbraucht werden.

* Der aktuelle Spieler sowie die Größe des Spielfeldes müssen ebenfalls abgefragt werden können.

* Folgende Fragen sollen pro Spielfeld gestellt werden können:
  * Kann es „befahren“ werden bzw. ist es frei?
  * Kann auf diesem Feld von einer bestimmten Farbe eine Figur geschlagen werden?
  * Kann eine Spielfigur einer bestimmten Farbe darauf landen? Ist es also frei oder kann dort eine andere Figur geschlagen werden?
  * Kann man auf diesem Feld eine Figur momentan „in die Hand nehmen“? Also ist dort eine Figur und wenn ja von der aktuell am Zug befindlichen Farbe?
  * Kann man die aktuell aktive („in der Hand befindliche“) Figur an diesem Feld abstellen? Darf die Figur also von ihrem aktuellen Startpunkt aus dort hinfahren und kann dort bleiben?
  * Kann man von einem Feld ($x_0$, $y_0$) auf ein Feld ($x_1$, $y_1$) fahren?

* Folgende aktive Aktionen sollen außerdem möglich sein:
  * Die Figur an einer bestimmten Stelle aktivieren, also „in die Hand nehmen“.
  * Die aktive Figur auf ein bestimmtes Feld wieder abstellen (sofern das erlaubt ist).

* Der aktuelle Spielstand soll möglichst anschaulich, zumindest aber in ASCII-Grafik dargestellt werden.

Die Schnittstellen einer möglichen Implementierung könnten in etwa folgendermaßen aussehen:

```c
class Chessman {

private: /* ... */

public:
  Chessman(char symbol, bool is_white);
  virtual ~Chessman() {}

  char get_symbol() const;
  char get_color() const;
  bool is_white() const;

  virtual bool is_essential() const { return false; }
  virtual bool can_move(
    int from_row, int from_col,
    int to_row, int to_col,
    const Chessboard &cb) const = 0;
};
```

```c
class Chessboard {

private: /* ... */

public:
  Chessboard(int size = 8);
  ~Chessboard();
  bool is_whites_turn() const;
  bool is_game_over() const;
  int get_size() const { return size; }
  const Chessman* operator() (int row, int col) const;

  bool can_pass_over(int row, int col) const;
  bool can_land_on(int row, int col, bool is_white) const;
  bool can_capture_on(int row, int col, bool is_white) const;

  bool can_select_piece(int row, int col) const;
  bool can_move_selection_to(int row, int col) const;
  bool can_move(int from_row, int from_col,
                int to_row, int to_col) const;

  void select_piece(int row, int col);
  void move_selection_to(int row, int col);
  void show() const;
};
```

**a.** Implementieren Sie alle klassischen Schachfiguren und testen Sie die einzelnen „Bewegungsmuster“ ausführlich. Gehen Sie in der Lösungsidee auch darauf ein, wieviel Speicher pro Spielfigur und pro Klasse verbraucht wird, insbesondere im Hinblick auf deren Datenkomponenten und die `vtable`.

**b.** Schreiben Sie ein Hauptprogramm, wo interaktiv von zwei Spielern Schach gespielt werden kann. Dazu sollen für die aktive Figur immer die möglichen Züge angezeigt werden, beispielsweise so wie im Folgenden dargestellt. Hier ist der weiße Springer (N) in Zeile 7, Spalte 1 aktiv, bzw. die weiße Dame (Q) in Zeile 7, Spalte 4, die einen gegnerischen Bauern in Zeile 4 Spalte 3 schlagen könnte. Die unterschiedlichen „Farben“ sind hier als Groß- oder Kleinbuchstaben dargestellt, die Zeilen und Spalten, der Einfachheit halber mit Null beginnend.

```text
Beispiel 1:                     Beispiel 2:
    0  1  2  3  4  5  6  7         0  1  2  3  4  5  6  7 
 0  r  n  b  q  k  b  n  r      0  r  n  b  q  k  b  n  r 
 1  p  p  p  p  p  p  p  p      1  p  p  p  p  .  p  p  p 
 2  .  .  .  .  .  .  .  .      2  .  .  .  .  .  .  .  . 
 3  .  .  .  .  .  .  .  .      3  .  .  .  .  .  .  . [.]
 4  .  .  .  .  .  .  .  .      4 [.] .  . [p] .  . [.] . 
 5 [.] . [.] .  .  .  .  .      5  . [.] P [.] P [.] .  . 
 6  P  P  P  P  P  P  P  P      6  P  P [.][.][.] P  P  P 
 7  R (N) B  Q  K  B  N  R      7  R  N  B (Q) K  B  N  R
```

**c.** Schreiben Sie ein alternatives Hauptprogramm oder eine über die Kommandozeile auswählbare Variante, die es erlaubt, ein zufälliges Spiel zu generieren, bei dem aber nur gültige Züge gemacht werden.

**d.** Entwickeln Sie zwei neue Schachfiguren, die andere Züge erlauben und testen Sie das Spiel auch mit anderen Schachbrettgrößen als 8x8.
