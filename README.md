# IMDB_EstructuradeDatos
Proyecto final para la materia Estructura de datos, 2do semestre, UCAB. C++

Intrucciones:
Implementación de una aplicación que almacenará datos de películas, series y opiniones que tengan
distintos usuarios acerca de estas.
Los datos que su aplicación deberá manejar serán los siguientes:
● Películas: Nombre, año de estreno, género, duración (en minutos).
● Series: Nombre, Año de estreno, género. Las series tienen una particularidad con
respecto a las películas, y es que están compuestas por temporadas, y las
temporadas, a su vez, están compuestas por capítulos. Los datos a almacenar por
cada uno son los siguientes:
- Temporadas: Nombre, año de estreno.
- Capítulos: Nombre, año de estreno, duración (en minutos), número del
capítulo.
● Usuarios: Correo electrónico, edad y el país al que pertenece. Además, el usuario
puede calificar una serie o película, o dejar una reseña corta de una película, serie
en general, temporada en particular de una serie o un capítulo. De cada una se
necesitan guardar los siguientes datos:
● Calificaciones: Datos de la película o serie calificada y puntuación dada
(número decimal desde 0.0 a 5.0).
● Reseñas: Datos de la película, serie, temporada o capítulo en especifico de
la reseña y la reseña corta (no más de 250 carácteres).
Estos datos deben estar almacenados en archivos de texto plano. Su aplicación
leerá los archivos y permitirá el manejo y la visualización de los datos que se encuentren
guardados en estos. Además, permitirá agregar o eliminar películas, series, temporadas,
capítulos y usuarios. Los cambios que se hagan a los datos desde su aplicación deben
quedar guardados en los mismos archivos de texto plano que usan para obtenerlos.

Además de esto, su aplicación debe ser capaz de generar reportes basados en los
datos que se almacenen. Los reportes que se piden son los siguientes:
● Top 5 películas mejor calificadas por los usuarios (por país, por género y en general)
● Top 5 series mejor calificadas por los usuarios (por país, por género y en general)
● Top 5 películas con más reseñas por los usuarios (por país y en general)
● Top 5 series con más reseñas por los usuarios (por país y en general)
● Top 5 temporadas con más reseñas por los usuarios (por país y en general)
● Top 5 capítulos con más reseñas por los usuarios (por país y en general)
● Todas las reseñas dadas por un usuario
● Todas las calificaciones dadas por un usuario
