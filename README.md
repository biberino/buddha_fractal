## Fraktal renderer nach der Buddhabrot Methode
Rendert Fraktale nach der Buddhabrot Methode, unterstützt Multithread und gibt Zwischenergebnisse aus. Sollte mit jedem c++11 fähigen Compiler auf jeder Plattform compilieren, getestet bisher nur auf Linux. 
Erwartet eine Datei conf.json im selben Verzeichnis (ansonsten wird mit Defaultwerten gerechnet) mit folgenden Einträgen:

conf.json:
- pixel_width: Pixelbreite des Ausgabebildes
- pixel_height: Pixelhöhe des Ausgabebildes
- x_axis_min: linker Rand der X-Achse
- x_axis_max: rechter Rand der X-Achse
- y_axis_min: unterer Rand der Y-Achse
- y_axis_max: oberer Rand der Y-Achse
- real_min: untere Grenze für die Zufallszahlen, Realanteil
- real_max: obere Grenze für die Zufallszahlen, Realanteil
- im_min: untere Grenze für die Zufallszahlen, Imaginäranteil
- im_max: obere Grenze für die Zufallszahlen, Imaginäranteil
- max_iter: Maximale Anzahl an Iterationen pro Punkt
- bailout_squared: das Quadrat des Abstandes zum Ursprung, ab dem ein Punkt sicher divergiert
- func_indentifier: Wählt das Fraktal aus. Siehe Tabelle unten
- zwilling: ob das Zwillingsverfahren (Gabi Müller) angewendet werden soll. NOCH NICHT IMPLEMENTIERT
- koppl: Kopplungskonstante für das Zwillingsverfahren
- chunck_min_points: Anzahl Punkte pro Thread, nach denen die Zeit überprüft wird (wegen Performance gründen wird nicht nach jedem Punkt geprüft).
- chunck_time_seconds: Anzahl Sekunden nach denen ein Bild generiert und das aktuelle Ergebniss als Rohdatei (wenn angegeben) ausgegeben wird.
- seconds: Minimale laufzeit des Programms in Sekunden.
- num_threads: Anzahl Threads
- save_raw_result: Ob (Zwischen)Ergebnisse gespeichert werden sollen. Dazu muss eine Datei als Parameter übergeben werden.

(Zwischen)Ergebnisse werden als ein Graustufenbild (pgm) exportert. Dabei werden die Punkte zunächst logarithmisch Skaliert und dann linear zwischen 0-255 Skaliert.

Wird eine Datei mit angegeben, wird zusätzlich diese Datei eingelesen (falls vorhanden) und (Zwischen)Ergebnisse werden darin komplett gespeichert. DIESE DATEI KANN GROß WERDEN! (pixel_width * pixel_height * 4 Bytes)

## Beispiel:

Das folgende Beispiel berechnet das Buddhafraktal für 60 Sekunden, wobei alle 25 Sekunden ein aktuelles Bild exportiert und das Ergeniss in my_mandelbrot.bin gespeichert wird.

```json
{
    "pixel_width": 14400,
    "pixel_height": 9000,
    "x_axis_min": -2.0,
    "x_axis_max": 2.0,
    "y_axis_min": -2.0,
    "y_axis_max": 2.0,
    "real_min": -4.0,
    "real_max": 4.0,
    "im_min": -4.0,
    "im_max": 4.0,
    "max_iter": 500000,
    "bailout_squared": 4,
    "func_indentifier": 0,
    "zwilling": false,
    "koppl": 0.5,
    "chunck_min_points": 50,
    "chunck_time_seconds": 25,
    "seconds": 60,
    "num_threads": 3,
    "save_raw_result": true
}
```

```
./buddha my_mandelbrot.bin
```

Die Berechnung kann jederzeit mit 
```
./buddha my_mandelbrot.bin
```
fortgesetzt werden. Wird lange genug gerechnet, sollte folgendes Bild erscheinen:
![Mandelbrot](img/mandelbrot.png?raw=true "Mandelbrot")

## Warnung
Die generierten Zwischenergebnisse und der RAM bedarf kann je nach gewählter Größe des Bildes recht groß ausfallen.


## Implementierte Fraktale

| Identifier        | Formel 
| ------------- |:-------------:
| 0     | z*z+c 
| 1     | z*z-c  
| 2     | z* (*z)+c 
| 3     | z*(*z)-c 
| 4     | (z+c) / (1 + c*z^3) 
| 5     | (z+c) / (1 + c*z^2)  
| 6     | z^z + c 
| 7     | z^z -c    
| 8     | abs(z*(*z)) * abs(c) * ((sqrt((z * (*z)^2)+1) / abs(z * (*z)+c))) -1