
UNIVERSIDAD MARIANO GÁLVEZ
Ingeniería en Sistemas de Información
PROGRAMACION 1



PROGRAMA DE CONTROL ACADEMICO
 







Alan Secundino Chan Batz

Guatemala — Junio 2026 

MANUAL TÉCNICO
El presente sistema fue desarrollado en lenguaje C++ con el objetivo de administrar información académica de estudiantes mediante el procesamiento de archivos de texto. El programa permite almacenar y consultar datos relacionados con estudiantes, cursos y calificaciones, facilitando la generación de reportes académicos y la preparación de información para su posterior inserción en una base de datos.
El sistema trabaja a partir de tres archivos de entrada: estudiantes, nombres y notas. A partir de estos datos se realizan diversas operaciones como búsqueda de estudiantes, cálculo de promedios, generación de reportes y creación de sentencias SQL para el registro de estudiantes activos.
La aplicación fue diseñada utilizando programación orientada a objetos, lo que permite una organización más clara del código y facilita futuras mejoras o ampliaciones.

Funciones Principales

Mostrar estudiantes
Permite visualizar la información completa de cada estudiante registrado en el sistema. Se muestran el carnet, nombre, estado académico y los cursos asociados junto con sus respectivas notas.

Buscar estudiante
Realiza una búsqueda utilizando el número de carnet como criterio principal. Una vez localizado el estudiante, se muestran sus datos generales, cursos registrados y promedio académico.

Calcular promedio
Calcula el promedio general de un estudiante tomando en cuenta todas las notas registradas en los diferentes cursos asociados a su carnet.

Generación de reportes
El sistema genera distintos reportes académicos:
•	Listado de estudiantes aprobados.
•	Estudiante con el mayor promedio.
•	Cantidad de estudiantes activos.
•	Ordenamiento de estudiantes según su promedio utilizando el algoritmo Bubble Sort.

Generación de archivo SQL
Permite crear automáticamente un archivo con sentencias SQL de inserción para los estudiantes que se encuentran en estado activo. Este archivo puede ejecutarse posteriormente en una base de datos para registrar la información correspondiente.

Estructuras Utilizadas

Clase Estudiante
La clase Estudiante representa la información básica de cada alumno registrado en el sistema.

Atributos:
•	carnet
•	nombre
•	estado

Métodos:
•	setCarnet()
•	setNombre()
•	setEstado()
•	getCarnet()
•	getNombre()
•	getEstado()
Esta clase encapsula la información de los estudiantes y permite acceder a ella mediante métodos de lectura y escritura.

Clase Nota
La clase Nota almacena la información relacionada con las calificaciones obtenidas por los estudiantes.
Atributos:
•	carnet
•	curso
•	nota
Métodos:
•	setCarnet()
•	setCurso()
•	setNota()
•	getCarnet()
•	getCurso()
•	getNota()
Su función principal es relacionar un estudiante con un curso específico y la nota obtenida.

Arreglos Utilizados
Para el almacenamiento temporal de datos se utilizan arreglos estáticos, e arreglo estudiantes posee una capacidad máxima de 100 registros, mientras que el arreglo notas permite almacenar hasta 500 registros. Estos límites son definidos mediante las constantes MAX_ESTUDIANTES y MAX_NOTAS, garantizando un control sobre la cantidad máxima de datos procesados por la aplicación.:
Estudiante estudiantes[MAX_ESTUDIANTES];
Nota notas[MAX_NOTAS];
Estos arreglos permiten guardar la información cargada desde los archivos de texto durante la ejecución del programa.
Además, se utilizan variables contadoras para controlar la cantidad de registros almacenados:
int totalEstudiantes;
int totalNotas;

Explicación de Archivos

estudiantes.txt
Contiene la información relacionada con el carnet y estado de cada estudiante.
Formato:
2024001,Activo
2024002,Inactivo
2024003,Activo

nombres.txt
Almacena la relación entre el carnet y el nombre del estudiante.
Formato:
2024001,Juan Pérez
2024002,Ana López
2024003,Carlos García

notas.txt
Contiene las notas obtenidas por los estudiantes en cada curso.
Formato:
2024001,Matemática,85
2024001,Programación,90
2024002,Física,70

insert_estudiantes_activos.sql
Es un archivo generado automáticamente por el sistema. Contiene instrucciones SQL para insertar en una base de datos los estudiantes que poseen estado activo.
Ejemplo:
INSERT INTO estudiantes_activos
(carnet,nombre,promedio)
VALUES
('2024001','Juan Pérez',87.5);


Explicación de la Conexión a Base de Datos
El sistema no establece una conexión directa con una base de datos mediante librerías o controladores específicos. En lugar de ello, implementa una estrategia de integración mediante la generación automática de un archivo SQL.
Cuando el usuario selecciona la opción correspondiente del menú principal, el programa identifica a los estudiantes con estado activo, calcula su promedio académico y genera sentencias INSERT dentro del archivo denominado:
insert_estudiantes_activos.sql
Posteriormente, dicho archivo puede ejecutarse en un gestor de bases de datos como MySQL Workbench para insertar los registros en la tabla correspondiente.
Esta metodología permite separar el procesamiento de datos de la administración de la base de datos, simplificando el desarrollo y facilitando las pruebas del sistema.
Durante el desarrollo del proyecto se intentó trabajar directamente con MySQL Workbench desde Visual Studio Code. Sin embargo, el programa requería otros datos de configuración que no se tenían disponibles en ese momento. Como alternativa, se generó un archivo SQL que posteriormente fue ejecutado en MySQL Workbench para ingresar los registros a la base de datos. De esta manera se logró cumplir con el objetivo del proyecto. También se perdieron lamentablemente capturas de la base de datos ejecutado ya que la maquina virtual no permite la capturas de pantalla.

Conclusión
El sistema de control académico desarrollado en C++ permite gestionar información estudiantil de forma sencilla y organizada mediante archivos de texto. Su diseño orientado a objetos facilita el mantenimiento del código y mejora la comprensión de su funcionamiento. Además, la generación automática de sentencias SQL constituye una herramienta útil para trasladar la información procesada hacia una base de datos, integrando de manera eficiente el manejo de archivos con los procesos de almacenamiento de información académica.

