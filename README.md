# OpenGL

Ejemplos escritos en C++ utilizando OpenGL y la librería  freeglut (http://freeglut.sourceforge.net).

## GCO_Practica1

### Iman

Cuerpo creado utilizando una malla por revolución. Los polos han sido creados mediante dos mallas cuyas caras han sido dibujadas e iluminadas manualmente.

![Iman](/GCO_Practica1/screenshots/magnet.PNG?raw=true "Iman")

### Hipotrocoide

Malla por revolución creada utilizando el marco de Frenet. La ecuación paramétrica que define la curva es la siguiente:

C(t) = ( (a-b)*cos(t) + c*cos(A), 0, (a-b)*sen(t) - c*sen(A)  siendo A = ((a-b)/b)*t ), con a,b,c,t > 0

![Hipotrocoide](/GCO_Practica1/screenshots/hypotrochoid.PNG?raw=true "Hipotrocoide")

### Bosque

Creado utilizando posicionamiento relativo y figuras simples.

![Bosque](/GCO_Practica1/screenshots/forest.PNG?raw=true "Bosque")

### Coche

Ejemplo de malla con animación. El coche avanza con las teclas f/v a lo largo del eje X (en rojo.)

![Coche](/GCO_Practica1/screenshots/car.PNG?raw=true "coche")

## GCO_Practica2

### Movimientos de cámara

* Rotaciones alrededor  de los ejes X, Y y Z utilizando las teclas 1, 2 y 3.
* Visualización lateral, frontal, cenital y rincón de la escena con las teclas 4, 5, 6 y 7.
* Proyección perpectiva u ortogonal. Tecla p.
* Rotaciones respecto de los tres ejes con las teclas q, w y e

### Modelo jerárquico

Usado para la creación y optimización del pintado de una escena. Hace uso de Objetos compuestos y objetos simples que contienen las transformaciones afines necesarias para colocarlos en una posición determinada.

### Iluminación

* Faros del coche: focos. Se enciende y apaga con las teclas t/g.
* Farola: emite luz rosa. Se enciende y apaga con las teclas r/f.
* Luz direccional de color verde. Entra formando un ángulo de 45º con el plano XZ. Se enciende y apaga con las teclas y/h.
* Luz ambiente global. Se enciende y apaga con las teclas u/j.

![snapshot1](/GCO_Practica2/snapshots/snapshot1.PNG?raw=true "snapshot1")

![snapshot2](/GCO_Practica2/snapshots/snapshot2.PNG?raw=true "snapshot2")

![snapshot3](/GCO_Practica2/snapshots/snapshot3.PNG?raw=true "snapshot3")

## Autores

* Jorge Casas Hernan (https://github.com/JorgeKsas)
* Mariano Hernandez Garcia (https://github.com/mariano2AA3)


