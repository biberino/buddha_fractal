### Fraktal renderer nach der Buddhabrot Methode
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
- chunck_size: Anzahl Punkte pro Thread, nach der ein Zwischenergebniss ausgegeben wird.
- seconds: Minimale laufzeit des Programms ins Sekunden.
- num_threads: Anzahl Threads


(Zwischen)Ergebnisse werden als ein Graustufenbild (pgm) exportert. Dabei werden die Punkte zunächst logarithmisch Skaliert und dann linear zwischen 0-255 Skaliert.

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