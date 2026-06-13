#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_ESTUDIANTES = 100;
const int MAX_NOTAS = 500;

class Estudiante
{
private:
    string carnet;
    string nombre;
    string estado;

public:

    void setCarnet(string c)
    {
        carnet = c;
    }

    void setNombre(string n)
    {
        nombre = n;
    }

    void setEstado(string e)
    {
        estado = e;
    }

    string getCarnet()
    {
        return carnet;
    }

    string getNombre()
    {
        return nombre;
    }

    string getEstado()
    {
        return estado;
    }
};

class Nota
{
private:
    string carnet;
    string curso;
    int nota;

public:

    void setCarnet(string c)
    {
        carnet = c;
    }

    void setCurso(string c)
    {
        curso = c;
    }

    void setNota(int n)
    {
        nota = n;
    }

    string getCarnet()
    {
        return carnet;
    }

    string getCurso()
    {
        return curso;
    }

    int getNota()
    {
        return nota;
    }
};

Estudiante estudiantes[MAX_ESTUDIANTES];
Nota notas[MAX_NOTAS];

int totalEstudiantes = 0;
int totalNotas = 0;

bool existeArchivo(string nombreArchivo)
{
    ifstream archivo(nombreArchivo.c_str());

    if(archivo)
    {
        archivo.close();
        return true;
    }

    return false;
}

bool archivoVacio(string nombreArchivo)
{
    ifstream archivo(nombreArchivo.c_str());

    archivo.seekg(0, ios::end);

    bool vacio = (archivo.tellg() == 0);

    archivo.close();

    return vacio;
}

bool esNumeroValido(string texto)
{
    if(texto.length() == 0)
    {
        return false;
    }

    for(int i = 0; i < texto.length(); i++)
    {
        if(texto[i] < '0' || texto[i] > '9')
        {
            return false;
        }
    }

    return true;
}

int convertirNumero(string texto)
{
    int numero = 0;

    for(int i = 0; i < texto.length(); i++)
    {
        numero = numero * 10 + (texto[i] - '0');
    }

    return numero;
}

void cargarEstudiantes()
{
    ifstream archivo("estudiantes.txt");

    string carnet;
    string estado;

    while(getline(archivo, carnet, ',') &&
          getline(archivo, estado))
    {
        if(totalEstudiantes < MAX_ESTUDIANTES)
        {
            estudiantes[totalEstudiantes].setCarnet(carnet);
            estudiantes[totalEstudiantes].setEstado(estado);

            totalEstudiantes++;
        }
        else
        {
            cout << "Aviso: se alcanzo el limite maximo de estudiantes ("
                 << MAX_ESTUDIANTES
                 << "). Registros adicionales ignorados.\n";
            break;
        }
    }

    archivo.close();
}

void cargarNombres()
{
    ifstream archivo("nombres.txt");

    string carnet;
    string nombre;

    while(getline(archivo, carnet, ',') &&
          getline(archivo, nombre))
    {
        for(int i = 0; i < totalEstudiantes; i++)
        {
            if(estudiantes[i].getCarnet() == carnet)
            {
                estudiantes[i].setNombre(nombre);
            }
        }
    }

    archivo.close();
}

void cargarNotas()
{
    ifstream archivo("notas.txt");

    string carnet;
    string curso;
    string notaTexto;

    while(getline(archivo, carnet, ',') &&
          getline(archivo, curso, ',') &&
          getline(archivo, notaTexto))
    {
        if(!esNumeroValido(notaTexto))
        {
            cout << "Aviso: nota invalida para el carnet "
                 << carnet
                 << " en el curso "
                 << curso
                 << " (\""
                 << notaTexto
                 << "\"). Registro omitido.\n";
            continue;
        }

        if(totalNotas < MAX_NOTAS)
        {
            notas[totalNotas].setCarnet(carnet);
            notas[totalNotas].setCurso(curso);
            notas[totalNotas].setNota(convertirNumero(notaTexto));

            totalNotas++;
        }
        else
        {
            cout << "Aviso: se alcanzo el limite maximo de notas ("
                 << MAX_NOTAS
                 << "). Registros adicionales ignorados.\n";
            break;
        }
    }

    archivo.close();
}

float calcularPromedio(string carnet)
{
    int suma = 0;
    int cantidad = 0;

    for(int i = 0; i < totalNotas; i++)
    {
        if(notas[i].getCarnet() == carnet)
        {
            suma += notas[i].getNota();
            cantidad++;
        }
    }

    if(cantidad == 0)
    {
        return 0;
    }

    return (float)suma / cantidad;
}

void mostrarCursosDeEstudiante(string carnet)
{
    bool tieneCursos = false;

    for(int j = 0; j < totalNotas; j++)
    {
        if(notas[j].getCarnet() == carnet)
        {
            cout << notas[j].getCurso()
                 << " -> "
                 << notas[j].getNota()
                 << endl;

            tieneCursos = true;
        }
    }

    if(!tieneCursos)
    {
        cout << "No tiene cursos registrados.\n";
    }
}

void mostrarEstudiantes()
{
    for(int i = 0; i < totalEstudiantes; i++)
    {
        cout << "\n----------------------\n";

        cout << "Carnet: "
             << estudiantes[i].getCarnet()
             << endl;

        cout << "Nombre: "
             << estudiantes[i].getNombre()
             << endl;

        cout << "Estado: "
             << estudiantes[i].getEstado()
             << endl;

        cout << "Cursos:\n";

        mostrarCursosDeEstudiante(estudiantes[i].getCarnet());
    }
}

void buscarEstudiante()
{
    string carnet;
    bool encontrado = false;

    cout << "Ingrese carnet: ";
    cin >> carnet;

    for(int i = 0; i < totalEstudiantes; i++)
    {
        if(estudiantes[i].getCarnet() == carnet)
        {
            encontrado = true;

            cout << "\nNombre: "
                 << estudiantes[i].getNombre()
                 << endl;

            cout << "Estado: "
                 << estudiantes[i].getEstado()
                 << endl;

            cout << "Cursos:\n";

            mostrarCursosDeEstudiante(carnet);

            cout << "Promedio: "
                 << calcularPromedio(carnet)
                 << endl;
        }
    }

    if(!encontrado)
    {
        cout << "Estudiante no encontrado.\n";
    }
}

void reporteAprobados()
{
    cout << "\nAPROBADOS\n";

    for(int i = 0; i < totalEstudiantes; i++)
    {
        float promedio =
            calcularPromedio(
                estudiantes[i].getCarnet());

        if(promedio >= 61)
        {
            cout << estudiantes[i].getNombre()
                 << " -> "
                 << promedio
                 << endl;
        }
    }
}

void mayorPromedio()
{
    float mayor = -1;
    int posicion = -1;

    for(int i = 0; i < totalEstudiantes; i++)
    {
        float promedio =
            calcularPromedio(
                estudiantes[i].getCarnet());

        if(promedio > mayor)
        {
            mayor = promedio;
            posicion = i;
        }
    }

    if(posicion != -1)
    {
        cout << "\nMayor promedio:\n";

        cout << estudiantes[posicion].getNombre()
             << " -> "
             << mayor
             << endl;
    }
}

void cantidadActivos()
{
    int contador = 0;

    for(int i = 0; i < totalEstudiantes; i++)
    {
        if(estudiantes[i].getEstado() == "Activo")
        {
            contador++;
        }
    }

    cout << "Cantidad de activos: "
         << contador
         << endl;
}

void reporteOrdenadoPorPromedio()
{
    int orden[MAX_ESTUDIANTES];
    float promedios[MAX_ESTUDIANTES];

    for(int i = 0; i < totalEstudiantes; i++)
    {
        orden[i] = i;
        promedios[i] = calcularPromedio(estudiantes[i].getCarnet());
    }

    // Bubble Sort ascendente por promedio
    for(int i = 0; i < totalEstudiantes - 1; i++)
    {
        for(int j = 0; j < totalEstudiantes - 1 - i; j++)
        {
            if(promedios[orden[j]] > promedios[orden[j + 1]])
            {
                int temp = orden[j];
                orden[j] = orden[j + 1];
                orden[j + 1] = temp;
            }
        }
    }

    cout << "\nESTUDIANTES ORDENADOS ASCENDENTEMENTE POR PROMEDIO (Bubble Sort)\n";

    for(int i = 0; i < totalEstudiantes; i++)
    {
        int pos = orden[i];

        cout << (i + 1) << ". "
             << estudiantes[pos].getNombre()
             << " -> "
             << promedios[pos]
             << endl;
    }
}

void calcularPromedioEstudiante()
{
    string carnet;
    bool encontrado = false;

    cout << "Ingrese carnet: ";
    cin >> carnet;

    for(int i = 0; i < totalEstudiantes; i++)
    {
        if(estudiantes[i].getCarnet() == carnet)
        {
            encontrado = true;

            cout << "\nNombre: "
                 << estudiantes[i].getNombre()
                 << endl;

            cout << "Promedio: "
                 << calcularPromedio(carnet)
                 << endl;
        }
    }

    if(!encontrado)
    {
        cout << "Estudiante no encontrado.\n";
    }
}

string escapeSQL(string texto)
{
    string resultado = "";

    for(int i = 0; i < texto.length(); i++)
    {
        if(texto[i] == '\'')
        {
            resultado += "''";
        }
        else
        {
            resultado += texto[i];
        }
    }

    return resultado;
}

void insertarActivosBD()
{
    ofstream archivo("insert_estudiantes_activos.sql");

    if(!archivo)
    {
        cout << "No se pudo crear el archivo SQL.\n";
        return;
    }

    int contador = 0;

    archivo << "USE Academ;\n\n";

    for(int i = 0; i < totalEstudiantes; i++)
    {
        if(estudiantes[i].getEstado() == "Activo")
        {
            float promedio = calcularPromedio(estudiantes[i].getCarnet());

            archivo << "INSERT INTO estudiantes_activos (carnet, nombre, promedio) VALUES ('"
                    << escapeSQL(estudiantes[i].getCarnet())
                    << "', '"
                    << escapeSQL(estudiantes[i].getNombre())
                    << "', "
                    << promedio
                    << ");\n";

            contador++;
        }
    }

    archivo.close();

    cout << "\nSe generaron " << contador
         << " sentencias INSERT en el archivo 'insert_estudiantes_activos.sql'.\n";
    cout << "Ejecute ese archivo en su base de datos\n";
}

void menuReportes()
{
    int opcion;

    do
    {
        cout << "\n===== REPORTES =====\n";
        cout << "1. Aprobados\n";
        cout << "2. Mayor promedio\n";
        cout << "3. Cantidad activos\n";
        cout << "4. Estudiantes ordenados por promedio\n";
        cout << "5. Regresar\n";

        cin >> opcion;

        switch(opcion)
        {
            case 1:
                reporteAprobados();
                break;

            case 2:
                mayorPromedio();
                break;

            case 3:
                cantidadActivos();
                break;

            case 4:
                reporteOrdenadoPorPromedio();
                break;

            case 5:
                break;

            default:
                cout << "Opcion invalida\n";
        }

    }while(opcion != 5);
}

int main()
{
    if(!existeArchivo("estudiantes.txt"))
    {
        cout << "No existe estudiantes.txt";
        return 0;
    }

    if(!existeArchivo("nombres.txt"))
    {
        cout << "No existe nombres.txt";
        return 0;
    }

    if(!existeArchivo("notas.txt"))
    {
        cout << "No existe notas.txt";
        return 0;
    }

    if(archivoVacio("estudiantes.txt"))
    {
        cout << "estudiantes.txt esta vacio";
        return 0;
    }

    if(archivoVacio("nombres.txt"))
    {
        cout << "nombres.txt esta vacio";
        return 0;
    }

    if(archivoVacio("notas.txt"))
    {
        cout << "notas.txt esta vacio";
        return 0;
    }

    cargarEstudiantes();
    cargarNombres();
    cargarNotas();

    int opcion;

    do
    {
        cout << "\n===== CONTROL ACADEMICO =====\n";
        cout << "1. Mostrar estudiantes\n";
        cout << "2. Buscar estudiante (carnet)\n";
        cout << "3. Calcular promedio de estudiante\n";
        cout << "4. Insertar estudiantes activos en base de datos\n";
        cout << "5. Reportes\n";
        cout << "6. Salir\n";

        cin >> opcion;

        switch(opcion)
        {
            case 1:
                mostrarEstudiantes();
                break;

            case 2:
                buscarEstudiante();
                break;

            case 3:
                calcularPromedioEstudiante();
                break;

            case 4:
                insertarActivosBD();
                break;

            case 5:
                menuReportes();
                break;

            case 6:
                cout << "Fin del programa\n";
                break;

            default:
                cout << "Opcion invalida\n";
        }

    }while(opcion != 6);

    return 0;
}