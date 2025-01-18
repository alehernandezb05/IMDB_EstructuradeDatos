#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Calificacion {
    string nombre; 
    string ID;   
    float puntuacion; 
    Calificacion* siguiente; 
};
struct Reseña {
    string nombre;
    string ID;
    string texto;
    Reseña* siguiente;
};
struct Pelicula {
    string ID;
    string nombre;
    string anio;
    string genero;
    string duracion;
    Pelicula* siguiente;
};
struct Usuario {
    string nombre;
    string email;
    int edad;
    string pais;
    Usuario* siguiente;
};
struct Capitulo {
    string IDCap;
    string nombre;
    int anioEstreno;
    int duracionSerie;
    int numero;
    string ID_Temporada;
    Capitulo* siguiente;
};
struct Temporada {
    string IDTemp;
    string nombre;
    int anioEstreno;
    string ID_Serie;
    Temporada* siguiente;
    Capitulo* capitulos;
};
struct Serie {
    string ID;
    string nombre;
    int anioEstreno;
    string generoSerie;
    Serie* siguiente;
    Temporada* temporadas;
};

struct ConteoReseñas {
    string nombrePelicula;
    int cantidadReseñas;
};

struct ConteoReseñasSeries {
    string nombreSerie;
    int cantidadReseñas;
};

struct ConteoReseñasTemporadas {
    string nombreTemporada;
    int cantidadReseñas;
};

struct ConteoReseñasCapitulos {
    string nombreCapitulo;
    int cantidadReseñas;
};

//Función para validar si la película ya existe en la lista
string aMinusculas(string str) {
    string resultado = str;
    for(char& c : resultado) {
        c = tolower(c);
    }
    return resultado;
}

bool validarPelicula(Pelicula* cabeza, string ID, string nombre) {
    Pelicula* aux = cabeza;
    string nombreBuscar = aMinusculas(nombre);
    string IDBuscar = ID;

    while (aux != nullptr) {
        if (aux->ID == IDBuscar || aMinusculas(aux->nombre) == nombreBuscar) {
            return true; 
        }
        aux = aux->siguiente;
    }
    return false;
}

void guardarPeliculas(Pelicula* cabeza) {
    ofstream archivo("peliculas.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar las películas.\n";
        return;
    }
    Pelicula* actual = cabeza;
    while (actual != nullptr) {
        archivo << actual->ID << "," << actual->nombre << "," << actual->anio << "," << actual->genero << "," << actual->duracion << '\n';
        actual = actual->siguiente;
    }
}

// Función para agregar una película a la lista
void agregarPelicula(Pelicula*& cabeza, string ID, string nombre, string anio, string genero, string duracion) {
    // Validar si el ID o el nombre ya existen
    if (validarPelicula(cabeza, ID, nombre)) {
        cout << "La película con ID '" << ID << "' o nombre '" << nombre << "' ya existe en la lista.\n";
        return;
    }
    Pelicula* nuevaPelicula = new Pelicula{ID, nombre, anio, genero, duracion, cabeza};
    cabeza = nuevaPelicula;
    guardarPeliculas(cabeza); // Guardar en archivo
}

// Función para eliminar una película de la lista
void eliminarPelicula(Pelicula*& cabeza, string ID, string nombre) {
    Pelicula* actual = cabeza;
    Pelicula* anterior = nullptr;

    while (actual != nullptr && actual->ID != ID && actual->nombre != nombre) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        cout << "Película no encontrada.\n";
        return;
    }

    if (anterior == nullptr) {
        cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
    guardarPeliculas(cabeza);
}

// Función para mostrar todas las películas de la lista
void mostrarPeliculas(Pelicula* cabeza) {
    Pelicula* actual = cabeza;
    while (actual != nullptr) {
        cout << "--------------------------" << endl;
        cout << "ID: " << actual->ID << endl;
        cout << "Nombre: " << actual->nombre << endl;
        cout << "Año: " << actual->anio << endl;
        cout << "Género: " << actual->genero << endl;
        cout << "Duración: " << actual->duracion << " minutos" << endl;
        cout << "--------------------------" << endl;
        actual = actual->siguiente;
    }
}

void cargarPeliculas(Pelicula*& cabeza) {
    ifstream archivo("peliculas.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para cargar las películas.\n";
        return;
    }
    
    string linea;
    while (getline(archivo, linea)) {
        string ID, nombre, anio, genero, duracion;
        size_t pos = 0;

        // Obtener el ID
        pos = linea.find(',');
        if (pos == string::npos) continue; 
        ID = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        // Obtener el nombre
        pos = linea.find(',');
        if (pos == string::npos) continue; 
        nombre = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        // Obtener el año
        pos = linea.find(',');
        if (pos == string::npos) continue; 
        anio = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        // Obtener el género
        pos = linea.find(',');
        if (pos == string::npos) continue; 
        genero = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        // El resto es la duración
        duracion = linea; 

        agregarPelicula(cabeza, ID, nombre, anio, genero, duracion);
    }
}

bool validarUsuario(Usuario* cabeza, string email) {
    Usuario* aux = cabeza;
    string emailBuscar = aMinusculas(email);

    while (aux != nullptr) {
        if (aMinusculas(aux->email) == emailBuscar) {
            return true; // El usuario ya existe
        }
        aux = aux->siguiente;
    }
    return false;
}

// Función para guardar usuarios en archivo
void guardarUsuarios(Usuario* cabeza) {
    ofstream archivo("usuarios.txt");
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        archivo << actual->nombre << " " << actual->email << " " << actual->edad << " " << actual->pais << endl;
        actual = actual->siguiente;
    }
}

// Función para agregar un usuario
void agregarUsuario(Usuario*& cabeza, string nombre, string email, int edad, string pais) {
    if (validarUsuario(cabeza, email)) {
        cout << "Ya existe un usuario con ese email.\n";
        return;
    }

    Usuario* nuevoUsuario = new Usuario{nombre, email, edad, pais, cabeza};
    cabeza = nuevoUsuario;
    guardarUsuarios(cabeza);
}

void eliminarUsuario(Usuario*& cabeza, string email) {
    Usuario* actual = cabeza;
    Usuario* anterior = nullptr;

    while (actual != nullptr && aMinusculas(actual->email) != aMinusculas(email)) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        cout << "Usuario no encontrado.\n";
        return;
    }

    if (anterior == nullptr) {
        cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    cout << "Usuario " << actual->nombre << " eliminado exitosamente.\n";
    delete actual;
    guardarUsuarios(cabeza);
}

void mostrarUsuarios(Usuario* cabeza) {
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        cout << "--------------------------" << endl;
        cout << "ID: " << actual->nombre << endl;
        cout << "Email: " << actual->email << endl;
        cout << "Edad: " << actual->edad << endl;
        cout << "País: " << actual->pais << endl;
        cout << "--------------------------" << endl;
        actual = actual->siguiente;
    }
}

void cargarUsuarios(Usuario*& cabeza) {
    ifstream archivo("usuarios.txt");
    string nombre, email, pais;
    int edad;
    while (archivo >> nombre >> email >> edad >> pais) {
        agregarUsuario(cabeza, nombre, email, edad, pais);
    }
}

//SERIES
bool validarSerie(Serie* cabeza, string nombre) {
    Serie* aux = cabeza;
    string nombreBuscar = aMinusculas(nombre); // Convertir el nombre a buscar a minúsculas

    while (aux != nullptr) {
        if (aMinusculas(aux->nombre) == nombreBuscar) {
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

void guardarSeries(Serie* cabeza) {
    ofstream archivo("series.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar las series.\n";
        return;
    }
    Serie* actual = cabeza;
    while (actual != nullptr) {
        archivo << actual->ID << "," << actual->nombre << "," << actual->anioEstreno << "," << actual->generoSerie << '\n';
        actual = actual->siguiente;
    }
    archivo.close();
}

void agregarSerie(Serie*& cabeza, string ID, string nombre, int anioEstreno, string generoSerie) {
    if (validarSerie(cabeza, nombre)) {
        cout << "La serie '" << nombre << "' ya existe en la lista.\n";
        return;
    }
    Serie* nuevaSerie = new Serie{ID, nombre, anioEstreno, generoSerie, cabeza, nullptr};
    cabeza = nuevaSerie;
    guardarSeries(cabeza); // Guarda las series en el archivo
}

void eliminarSerie(Serie*& cabeza, string ID, string nombre) {
    Serie* actual = cabeza;
    Serie* anterior = nullptr;

    while (actual != nullptr && actual->ID != ID && actual->nombre != nombre) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        cout << "Serie no encontrada.\n";
        return;
    }

    if (anterior == nullptr) {
        cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
    guardarSeries(cabeza);
}

void mostrarSeries(Serie* cabeza) {
    Serie* actual = cabeza;
    while (actual != nullptr) {
        cout << "--------------------------" << endl;
        cout << "ID: " << actual->ID << endl;
        cout << "Nombre: " << actual->nombre << endl;
        cout << "Año de estreno: " << actual->anioEstreno << endl;
        cout << "Género: " << actual->generoSerie << endl;
        cout << "--------------------------" << endl;
        actual = actual->siguiente;
    }
}

void cargarSeries(Serie*& cabeza) {
    ifstream archivo("series.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para cargar las series.\n";
        return;
    }
    string linea;
    while (getline(archivo, linea)) {
        string ID, nombre, generoSerie, anioStr;
        int anioEstreno;
        size_t pos = 0;

        // Obtener el ID
        pos = linea.find(',');
        if (pos == string::npos) continue; 
        ID = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        // Obtener el nombre
        pos = linea.find(',');
        if (pos == string::npos) continue; 
        nombre = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        // Obtener el año
        pos = linea.find(',');
        if (pos == string::npos) continue; 
        anioStr = linea.substr(0, pos);
        anioEstreno = stoi(anioStr);
        linea.erase(0, pos + 1);

        generoSerie = linea;

        agregarSerie(cabeza, ID, nombre, anioEstreno, generoSerie);
    }
    archivo.close();
}


//TEMPORADAS
bool validarTemporada(Temporada* cabeza, string ID, string nombre) {
    Temporada* aux = cabeza;
    while (aux != nullptr) {
        if (aux->IDTemp == ID || aux->nombre == nombre) {
            return true; // La temporada ya existe
        }
        aux = aux->siguiente;
    }
    return false;
}

void guardarTemporadas(Temporada* cabeza) {
    ofstream archivo("temporadas.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar las temporadas.\n";
        return;
    }
    Temporada* actual = cabeza;
    while (actual != nullptr) {
        archivo << actual->IDTemp << "," << actual->nombre << "," << actual->anioEstreno << '\n';
        actual = actual->siguiente;
    }
}

void agregarTemporada(Serie*& cabeza, string IDSerie, string ID, string nombreTemporada, int anioEstreno) {
    Serie* serie = cabeza;
    while (serie != nullptr && serie->ID != IDSerie) {
        serie = serie->siguiente;
    }

    if (serie == nullptr) {
        cout << "Serie con ID " << IDSerie << " no encontrada.\n";
        return;
    }

    // Validar si el ID o el nombre ya existen
    if (validarTemporada(serie->temporadas, ID, nombreTemporada)) {
        cout << "La temporada con ID '" << ID << "' o nombre '" << nombreTemporada << "' ya existe en la serie.\n";
        return;
    }

    // Crear la nueva temporada
    Temporada* nuevaTemporada = new Temporada{ID, nombreTemporada, anioEstreno, IDSerie, serie->temporadas, nullptr};
    serie->temporadas = nuevaTemporada; // Asignar la nueva temporada a la lista de temporadas de la serie
    guardarTemporadas(serie->temporadas); // Guardar en archivo
}

void eliminarTemporada(Serie*& cabeza, string nombreSerie, string ID, string nombreTemporada) {
    Serie* serie = cabeza;
    while (serie != nullptr && serie->nombre != nombreSerie) {
        serie = serie->siguiente;
    }

    if (serie == nullptr) {
        cout << "Serie no encontrada.\n";
        return;
    }

    Temporada* actual = serie->temporadas;
    Temporada* anterior = nullptr;

    while (actual != nullptr && actual->IDTemp != ID && actual->nombre != nombreTemporada) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        cout << "Temporada no encontrada.\n";
        return;
    }

    if (anterior == nullptr) {
        serie->temporadas = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
    guardarTemporadas(serie->temporadas);
}

void mostrarTemporadas(Serie* cabeza, string nombreSerie) {
    Serie* serie = cabeza;
    while (serie != nullptr && serie->nombre != nombreSerie) {
        serie = serie->siguiente;
    }

    if (serie == nullptr) {
        cout << "Serie no encontrada.\n";
        return;
    }

    Temporada* actual = serie->temporadas;
    while (actual != nullptr) {
        cout << "--------------------------" << endl;
        cout << "ID: " << actual->IDTemp << endl;
        cout << "Nombre: " << actual->nombre << endl;
        cout << "ID Serie: " << actual->ID_Serie << endl;
        cout << "Año de estreno: " << actual->anioEstreno << endl;
        cout << "--------------------------" << endl;
        actual = actual->siguiente;
    }
}

void cargarTemporadas(Serie* listaSeries) {
    if (listaSeries == nullptr) {
        cerr << "Error: La lista de series está vacía.\n";
        return;
    }
    ifstream archivo("temporadas.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para cargar las temporadas.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        string IDTemp, nombre, ID_Serie, anioStr;
        int anioEstreno;
        size_t pos = 0;

        // Obtener el ID de la temporada
        pos = linea.find(',');
        if (pos == string::npos) continue; 
        IDTemp = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        // Obtener el nombre de la temporada
        pos = linea.find(',');
        if (pos == string::npos) continue; 
        nombre = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        // Obtener el año de estreno
        pos = linea.find(',');
        if (pos == string::npos) continue; 
        anioStr = linea.substr(0, pos);
        anioEstreno = stoi(anioStr);
        linea.erase(0, pos + 1);

        // El resto es el ID de la serie
        ID_Serie = linea;

        // Buscar la serie correspondiente
        Serie* serieActual = listaSeries;
        while (serieActual != nullptr && serieActual->ID != ID_Serie) {
            serieActual = serieActual->siguiente;
        }

        // Si se encontró la serie, agregar la temporada
        if (serieActual != nullptr) {
            Temporada* nuevaTemporada = new Temporada{IDTemp, nombre, anioEstreno, ID_Serie, serieActual->temporadas, nullptr};
            serieActual->temporadas = nuevaTemporada;
        } else {
            cerr << "Serie con ID " << ID_Serie << " no encontrada para la temporada " << nombre << ".\n";
        }
    }
    archivo.close();
}

bool validarCapitulo(Capitulo* cabeza, string ID, string nombre) {
    Capitulo* aux = cabeza;
    string nombreBuscar = aMinusculas(nombre);
    string IDBuscar = ID;

    while (aux != nullptr) {
        if (aux->IDCap == IDBuscar || aMinusculas(aux->nombre) == nombreBuscar) {
            return true; // El capítulo ya existe
        }
        aux = aux->siguiente;
    }
    return false;
}

void guardarCapitulos(Capitulo* cabeza) {
    ofstream archivo("capitulos.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar los capítulos.\n";
        return;
    }
    Capitulo* actual = cabeza;
    while (actual != nullptr) {
        archivo << actual->IDCap << "," << actual->nombre << "," << actual->anioEstreno << "," << actual->duracionSerie << "," << actual->numero << '\n';
        actual = actual->siguiente;
    }
}

void agregarCapitulo(Serie*& cabeza, string nombreSerie, string nombreTemporada, string ID, string nombreCapitulo, int anioEstreno, int duracionSerie, int numero) {
    Serie* serie = cabeza;
    while (serie != nullptr && serie->nombre != nombreSerie) {
        serie = serie->siguiente;    
    }

    if (serie == nullptr) {
        cout << "Serie no encontrada.\n";
        return;
    }

    Temporada* temporadaActual = serie->temporadas;
    while (temporadaActual != nullptr && temporadaActual->nombre != nombreTemporada) {
        temporadaActual = temporadaActual->siguiente;
    }

    if (temporadaActual == nullptr) {
        cout << "Temporada no encontrada.\n";
        return;
    }

    if (validarCapitulo(temporadaActual->capitulos, ID, nombreCapitulo)) {
        cout << "El capítulo con ID '" << ID << "' o nombre '" << nombreCapitulo << "' ya existe en la temporada.\n";
        return;
    }

    Capitulo* nuevoCapitulo = new Capitulo{ID, nombreCapitulo, anioEstreno, duracionSerie, numero};
    temporadaActual->capitulos = nuevoCapitulo; // Asignar el nuevo capítulo a la lista de capítulos de la temporada
    guardarCapitulos(temporadaActual->capitulos); // Guardar en archivo
    cout << "Capítulo agregado exitosamente.\n";
}

void eliminarCapitulo(Serie*& cabeza, string nombreSerie, string nombreTemporada, string ID, string nombreCapitulo) {
    Serie* serie = cabeza;
    while (serie != nullptr && serie->nombre != nombreSerie) {
        serie = serie->siguiente;
    }

    if (serie == nullptr) {
        cout << "Serie no encontrada.\n";
        return;
    }

    Temporada* temporada = serie->temporadas;
    while (temporada != nullptr && temporada->nombre != nombreTemporada) {
        temporada = temporada->siguiente;
    }

    if (temporada == nullptr) {
        cout << "Temporada no encontrada.\n";
        return;
    }

    Capitulo* actual = temporada->capitulos;
    Capitulo* anterior = nullptr;

    while (actual != nullptr && actual->IDCap != ID && actual->nombre != nombreCapitulo) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        cout << "Capítulo no encontrado.\n";
        return;
    }

    if (anterior == nullptr) {
        temporada->capitulos = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
    guardarCapitulos(temporada->capitulos);
}

void mostrarCapitulos(Serie* cabeza, string IDTemp) {
    // Recorrer todas las series
    Serie* serieActual = cabeza;
    bool temporadaEncontrada = false;

    while (serieActual != nullptr) {
        // Buscar la temporada correspondiente dentro de la serie
        Temporada* temporadaActual = serieActual->temporadas;
        while (temporadaActual != nullptr) {
            if (temporadaActual->IDTemp == IDTemp) {
                temporadaEncontrada = true;

                // Mostrar los capítulos de la temporada
                Capitulo* capituloActual = temporadaActual->capitulos;
                if (capituloActual == nullptr) {
                    cout << "No hay capítulos en esta temporada.\n";
                } else {
                    cout << "Capítulos de la temporada " << temporadaActual->nombre << ":\n";
                    while (capituloActual != nullptr) {
                        cout << "--------------------------" << endl;
                        cout << "ID: " << capituloActual->IDCap << endl;
                        cout << "Nombre: " << capituloActual->nombre << endl;
                        cout << "Año de estreno: " << capituloActual->anioEstreno << endl;
                        cout << "Duración: " << capituloActual->duracionSerie << " minutos" << endl;
                        cout << "Número: " << capituloActual->numero << endl;
                        cout << "--------------------------" << endl;
                        capituloActual = capituloActual->siguiente;
                    }
                }
                break;
            }
            temporadaActual = temporadaActual->siguiente;
        }
        if (temporadaEncontrada) {
            break;
        }
        serieActual = serieActual->siguiente;
    }

    if (!temporadaEncontrada) {
        cout << "Temporada con ID " << IDTemp << " no encontrada.\n";
    }

    cout << "\nPresione ENTER para volver al menu\n";
    cin.ignore();
}

void cargarCapitulos(Serie* listaSeries) {
    ifstream archivo("capitulos.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para cargar los capítulos.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        string IDCap, nombre, anioStr, duracionStr, numeroStr, IDTemp;
        int anioEstreno, duracionSerie, numero;
        size_t pos = 0;

        // Obtener el ID del capítulo
        pos = linea.find(',');
        if (pos == string::npos) continue;
        IDCap = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        // Obtener el nombre del capítulo
        pos = linea.find(',');
        if (pos == string::npos) continue;
        nombre = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        // Obtener el año de estreno
        pos = linea.find(',');
        if (pos == string::npos) continue;
        anioStr = linea.substr(0, pos);
        anioEstreno = stoi(anioStr);
        linea.erase(0, pos + 1);

        // Obtener la duración
        pos = linea.find(',');
        if (pos == string::npos) continue;
        duracionStr = linea.substr(0, pos);
        duracionSerie = stoi(duracionStr);
        linea.erase(0, pos + 1);

        // Obtener el número del capítulo
        pos = linea.find(',');
        if (pos == string::npos) continue;
        numeroStr = linea.substr(0, pos);
        numero = stoi(numeroStr);
        linea.erase(0, pos + 1);

        // Obtener el ID de la temporada
        IDTemp = linea;

        // Buscar la temporada correspondiente en la lista de series
        Serie* serieActual = listaSeries;
        while (serieActual != nullptr) {
            Temporada* temporadaActual = serieActual->temporadas;
            while (temporadaActual != nullptr) {
                if (temporadaActual->IDTemp == IDTemp) {
                    // Agregar el capítulo a la temporada correcta
                    Capitulo* nuevoCapitulo = new Capitulo{IDCap, nombre, anioEstreno, duracionSerie, numero};
                    if (temporadaActual->capitulos == nullptr) {
                        temporadaActual->capitulos = nuevoCapitulo;
                    } else {
                        Capitulo* capituloActual = temporadaActual->capitulos;
                        while (capituloActual->siguiente != nullptr) {
                            capituloActual = capituloActual->siguiente;
                        }
                        capituloActual->siguiente = nuevoCapitulo;
                    }
                    break;
                }
                temporadaActual = temporadaActual->siguiente;
            }
            if (temporadaActual != nullptr) break;
            serieActual = serieActual->siguiente;
        }
    }

    archivo.close();
}
//Funciones de verificación para CALIFICACIONES Y RESENAS
bool verificarPelicula(Pelicula* cabeza, const string& nombre) {
    Pelicula* actual = cabeza;
    while (actual != nullptr) {
        if (aMinusculas(actual->nombre) == aMinusculas(nombre)) {
            return true; 
        }
        actual = actual->siguiente;
    }
    return false; 
}

bool verificarSerie(Serie* cabeza, const string& nombre) {
    Serie* actual = cabeza;
    while (actual != nullptr) {
        if (aMinusculas(actual->nombre) == aMinusculas(nombre)) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

bool verificarUsuario(Usuario* cabeza, const string& ID) {
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        if (aMinusculas(actual->nombre) == aMinusculas(ID)) {
            return true; // El usuario existe
        }
        actual = actual->siguiente;
    }
    return false; // El usuario no existe
}

//Funciones para buscar en CALIFICACIONES Y RESENAS
void buscarCalificacionesPorPelicula(Calificacion* cabeza, const string& nombrePelicula) {
    Calificacion* actual = cabeza;
    bool encontrado = false;

    while (actual != nullptr) {
        if (aMinusculas(actual->nombre) == aMinusculas(nombrePelicula)) {
            cout << "Nombre: " << actual->nombre 
                 << ", ID: " << actual->ID 
                 << ", Puntuación: " << actual->puntuacion << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron calificaciones para la película '" << nombrePelicula << "'.\n";
    }
}

void buscarResenasPorPelicula(Reseña* cabeza, const string& nombrePelicula) {
    Reseña* actual = cabeza;
    bool encontrado = false;

    while (actual != nullptr) {
        if (aMinusculas(actual->nombre) == aMinusculas(nombrePelicula)) {
            cout << "Nombre: " << actual->nombre 
                 << ", ID: " << actual->ID 
                 << ", Reseña: " << actual->texto << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron reseñas para '" << nombrePelicula << "'.\n";
    }
}

//CALIFICACIONES
void guardarCalificaciones(Calificacion* cabeza) {
    ofstream archivo("calificaciones.txt");
    Calificacion* actual = cabeza;

    while (actual != nullptr) {
        archivo << actual->nombre << "," << actual->ID << "," << actual->puntuacion << endl;
        actual = actual->siguiente;
    }
}

void agregarCalificacion(Calificacion*& cabeza, const string& nombre, const string& ID, float puntuacion, Pelicula* listaPeliculas, Serie* listaSeries, Usuario* listaUsuarios) {
    if (puntuacion < 0.0 || puntuacion > 5.0) {
        cout << "La puntuación debe estar entre 0.0 y 5.0.\n";
        return;
    }
    // Verificar si la película o serie existe
    if (!verificarPelicula(listaPeliculas, nombre) && !verificarSerie(listaSeries, nombre)) {
        cout << "La película o serie '" << nombre << "' no existe.\n";
        return;
    }

    if (!verificarUsuario(listaUsuarios, ID)){
        cout << "El ID '" << ID << "' no existe.\n";
        return;
    }

    Calificacion* nuevaCalificacion = new Calificacion{nombre, ID, puntuacion, cabeza};
    cabeza = nuevaCalificacion;
    guardarCalificaciones(cabeza); // Guardar en archivo
}

void mostrarCalificacionesSeries(Calificacion* cabeza, Serie* listaSeries) {
    Calificacion* actual = cabeza;
    bool encontrado = false;

    while (actual != nullptr) {
        // Verificamos si la serie existe en la lista de series
        if (verificarSerie(listaSeries, actual->nombre)) {
            cout << "Nombre: " << actual->nombre 
                 << ", ID: " << actual->ID 
                 << ", Puntuación: " << actual->puntuacion << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron calificaciones para series.\n";
    }
}

void mostrarCalificacionesPeliculas(Calificacion* cabeza, Pelicula* listaPeliculas) {
    Calificacion* actual = cabeza;
    bool encontrado = false;

    while (actual != nullptr) {
        // Verificamos si la película existe en la lista de películas
        if (verificarPelicula(listaPeliculas, actual->nombre)) {
            cout << "Nombre: " << actual->nombre 
                 << ", ID: " << actual->ID 
                 << ", Puntuación: " << actual->puntuacion << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron calificaciones para películas.\n";
    }
}

void cargarCalificaciones(Calificacion*& cabeza, Pelicula* listaPeliculas, Serie* listaSeries, Usuario* listaUsuarios) {
    ifstream archivo("calificaciones.txt");
    string linea;

    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(','); // Encuentra la primera coma
        if (pos1 == string::npos) continue; 
        string nombre = linea.substr(0, pos1);

        size_t pos2 = linea.find(',', pos1 + 1); // Encuentra la segunda coma
        if (pos2 == string::npos) continue; 
        string ID = linea.substr(pos1 + 1, pos2 - pos1 - 1);

        float puntuacion = stof(linea.substr(pos2 + 1)); // Obtener la puntuación

        agregarCalificacion(cabeza, nombre, ID, puntuacion, listaPeliculas, listaSeries, listaUsuarios);
    }
    archivo.close();
}

//RESENAS
void guardarResenas(Reseña* cabeza) {
    ofstream archivo("resenas.txt");
    Reseña* actual = cabeza;

    while (actual != nullptr) {
        archivo << actual->nombre << "|" << actual->ID << "|" << actual->texto << endl;
        actual = actual->siguiente;
    }
}

void agregarResenaTemporadaCapitulo(Reseña*& cabeza, const string& nombreContenido, const string& ID, const string& texto, Serie* listaSeries, Usuario* listaUsuarios) {
    // Verificar si la reseña tiene más de 250 caracteres
    if (texto.length() > 250) {
        cout << "La reseña no puede tener más de 250 caracteres.\n";
        return;
    }

    // Verificar si la temporada o capítulo existe
    bool existe = false;
    Serie* serieActual = listaSeries;
    while (serieActual != nullptr) {
        Temporada* temporadaActual = serieActual->temporadas;
        while (temporadaActual != nullptr) {
            if (aMinusculas(temporadaActual->nombre) == aMinusculas(nombreContenido)) {
                existe = true;
                break;
            }
            Capitulo* capituloActual = temporadaActual->capitulos;
            while (capituloActual != nullptr) {
                if (aMinusculas(capituloActual->nombre) == aMinusculas(nombreContenido)) {
                    existe = true;
                    break;
                }
                capituloActual = capituloActual->siguiente;
            }
            if (existe) break;
            temporadaActual = temporadaActual->siguiente;
        }
        if (existe) break;
        serieActual = serieActual->siguiente;
    }

    if (!existe) {
        cout << "La temporada o capítulo '" << nombreContenido << "' no existe.\n";
        return;
    }

    // Verificar si el usuario existe
    if (!verificarUsuario(listaUsuarios, ID)) {
        cout << "El ID '" << ID << "' no existe.\n";
        return;
    }

    // Crear una nueva reseña
    Reseña* nuevaResena = new Reseña{nombreContenido, ID, texto, cabeza};
    cabeza = nuevaResena;

    // Guardar las reseñas en un archivo (opcional)
    guardarResenas(cabeza);
}

void agregarResena(Reseña*& cabeza, const string& nombre, const string& ID, const string& texto, Pelicula* listaPeliculas, Serie* listaSeries, Usuario* listaUsuarios) {
    if (texto.length() > 250) {
        cout << "La reseña no puede tener más de 250 caracteres.\n";
        return;
    }

    // Verificar si la película o serie existe
    if (!verificarPelicula(listaPeliculas, nombre) && !verificarSerie(listaSeries, nombre)) {
        agregarResenaTemporadaCapitulo(cabeza, nombre, ID, texto, listaSeries, listaUsuarios);
        return;
    }

    if (!verificarUsuario(listaUsuarios, ID)) {
        cout << "El ID '" << ID << "' no existe.\n";
        return;
    }

    Reseña* nuevaResena = new Reseña{nombre, ID, texto, cabeza};
    cabeza = nuevaResena;
    guardarResenas(cabeza);
}

void mostrarResenasPeliculas(Reseña* cabeza, Pelicula* listaPeliculas) {
    Reseña* actual = cabeza;
    bool encontrado = false;

    while (actual != nullptr) {
        // Verificamos si la película existe en la lista de películas
        if (verificarPelicula(listaPeliculas, actual->nombre)) {
            cout << "Nombre: " << actual->nombre 
                 << ", ID: " << actual->ID 
                 << ", Reseña: " << actual->texto << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron reseñas para películas.\n";
    }
}

void mostrarResenasSeries(Reseña* cabeza, Serie* listaSeries) {
    Reseña* actual = cabeza;
    bool encontrado = false;

    while (actual != nullptr) {
        // Verificamos si la serie existe en la lista de series
        if (verificarSerie(listaSeries, actual->nombre)) {
            cout << "Nombre: " << actual->nombre 
                 << ", ID: " << actual->ID 
                 << ", Reseña: " << actual->texto << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron reseñas para series.\n";
    }
}

void cargarResenas(Reseña*& cabeza, Pelicula* listaPeliculas, Serie* listaSeries, Usuario* listaUsuarios) {
    ifstream archivo("resenas.txt");
    string linea;

    while (getline(archivo, linea)) {
        size_t pos1 = linea.find('|');
        if (pos1 == string::npos) continue; 
        string nombre = linea.substr(0, pos1);

        size_t pos2 = linea.find('|', pos1 + 1);
        if (pos2 == string::npos) continue; 
        string ID = linea.substr(pos1 + 1, pos2 - pos1 - 1);

        string texto = linea.substr(pos2 + 1); 
        agregarResena(cabeza, nombre, ID, texto, listaPeliculas, listaSeries, listaUsuarios);
    }
}

void mostrarResenasTemporadaCapitulo(Reseña* cabeza, const string& nombreContenido) {
    Reseña* actual = cabeza;
    bool encontrado = false;

    while (actual != nullptr) {
        if (aMinusculas(actual->nombre) == aMinusculas(nombreContenido)) {
            cout << "Nombre: " << actual->nombre 
                 << ", ID: " << actual->ID 
                 << ", Reseña: " << actual->texto << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron reseñas para la temporada o capítulo '" << nombreContenido << "'.\n";
    }
}


//TOPSSSSS
void top5PeliculasGenerales(Calificacion* cabezaCalificaciones, Pelicula* cabezaPeliculas) {
    // Crear un arreglo para almacenar las películas y sus promedios
    const int MAX_PELICULAS = 1000; // Ajusta este valor según sea necesario
    struct PeliculaPromedio {
        string nombre;
        float promedio;
    };
    PeliculaPromedio peliculas[MAX_PELICULAS];
    int totalPeliculas = 0;

    // Recorrer todas las calificaciones
    Calificacion* actualCalificacion = cabezaCalificaciones;
    while (actualCalificacion != nullptr) {
        // Verificar si la calificación es para una película
        Pelicula* peliculaActual = cabezaPeliculas;
        while (peliculaActual != nullptr && peliculaActual->nombre != actualCalificacion->nombre) {
            peliculaActual = peliculaActual->siguiente;
        }

        // Si es una película, procesar la calificación
        if (peliculaActual != nullptr) {
            bool encontrada = false;
            for (int i = 0; i < totalPeliculas; i++) {
                if (peliculas[i].nombre == actualCalificacion->nombre) {
                    peliculas[i].promedio += actualCalificacion->puntuacion;
                    encontrada = true;
                    break;
                }
            }
            if (!encontrada) {
                peliculas[totalPeliculas].nombre = actualCalificacion->nombre;
                peliculas[totalPeliculas].promedio = actualCalificacion->puntuacion;
                totalPeliculas++;
            }
        }

        actualCalificacion = actualCalificacion->siguiente;
    }

    // Calcular el promedio para cada película
    for (int i = 0; i < totalPeliculas; i++) {
        int contador = 0;
        Calificacion* temp = cabezaCalificaciones;
        while (temp != nullptr) {
            if (temp->nombre == peliculas[i].nombre) {
                contador++;
            }
            temp = temp->siguiente;
        }
        peliculas[i].promedio /= contador;
    }

    // Ordenar las películas por promedio (de mayor a menor)
    for (int i = 0; i < totalPeliculas - 1; i++) {
        for (int j = i + 1; j < totalPeliculas; j++) {
            if (peliculas[i].promedio < peliculas[j].promedio) {
                PeliculaPromedio temp = peliculas[i];
                peliculas[i] = peliculas[j];
                peliculas[j] = temp;
            }
        }
    }

    // Mostrar el Top 5
    cout << "Top 5 Películas Mejor Calificadas (General):\n";
    for (int i = 0; i < min(5, totalPeliculas); i++) {
        cout << i + 1 << ". " << peliculas[i].nombre << " - Puntuación: " << peliculas[i].promedio << endl;
    }
}

void top5PeliculasPorPais(Calificacion* cabezaCalificaciones, Usuario* cabezaUsuarios, const string& pais) {
    // Crear un arreglo para almacenar las películas y sus promedios
    const int MAX_PELICULAS = 1000; // Ajusta este valor según sea necesario
    struct PeliculaPromedio {
        string nombre;
        float promedio;
    };
    PeliculaPromedio peliculas[MAX_PELICULAS];
    int totalPeliculas = 0;
    // Recorrer todas las calificaciones
    Calificacion* actualCalificacion = cabezaCalificaciones;
    while (actualCalificacion != nullptr) {
        // Buscar el usuario que hizo la calificación
        Usuario* usuarioActual = cabezaUsuarios;
        while (usuarioActual != nullptr && usuarioActual->nombre != actualCalificacion->ID) {
            usuarioActual = usuarioActual->siguiente;
        }
        // Si el usuario es del país especificado, procesar la calificación
        if (usuarioActual != nullptr && usuarioActual->pais == pais) {
            // Buscar si la película ya está
                        // Buscar si la película ya está en el arreglo
            bool encontrada = false;
            for (int i = 0; i < totalPeliculas; i++) {
                if (peliculas[i].nombre == actualCalificacion->nombre) {
                    peliculas[i].promedio += actualCalificacion->puntuacion;
                    encontrada = true;
                    break;
                }
            }
            // Si no está en el arreglo, agregarla
            if (!encontrada) {
                peliculas[totalPeliculas].nombre = actualCalificacion->nombre;
                peliculas[totalPeliculas].promedio = actualCalificacion->puntuacion;
                totalPeliculas++;
            }
        }

        actualCalificacion = actualCalificacion->siguiente;
    }
    // Calcular el promedio para cada película
    for (int i = 0; i < totalPeliculas; i++) {
        int contador = 0;
        Calificacion* temp = cabezaCalificaciones;
        while (temp != nullptr) {
            if (temp->nombre == peliculas[i].nombre) {
                contador++;
            }
            temp = temp->siguiente;
        }
        peliculas[i].promedio /= contador;
    }
    // Ordenar las películas por promedio (de mayor a menor)
    for (int i = 0; i < totalPeliculas - 1; i++) {
        for (int j = i + 1; j < totalPeliculas; j++) {
            if (peliculas[i].promedio < peliculas[j].promedio) {
                PeliculaPromedio temp = peliculas[i];
                peliculas[i] = peliculas[j];
                peliculas[j] = temp;
            }
        }
    }
    // Mostrar el Top 5
    cout << "Top 5 Películas Mejor Calificadas (País: " << pais << "):\n";
    for (int i = 0; i < min(5, totalPeliculas); i++) {
        cout << i + 1 << ". " << peliculas[i].nombre << " - Puntuación: " << peliculas[i].promedio << endl;
    }
}

void top5PeliculasPorGenero(Calificacion* cabezaCalificaciones, Pelicula* cabezaPeliculas, const string& genero) {
    // Crear un arreglo para almacenar las películas y sus promedios
    const int MAX_PELICULAS = 1000; // Ajusta este valor según sea necesario
    struct PeliculaPromedio {
        string nombre;
        float promedio;
    };
    PeliculaPromedio peliculas[MAX_PELICULAS];
    int totalPeliculas = 0;

    // Recorrer todas las calificaciones
    Calificacion* actualCalificacion = cabezaCalificaciones;
    while (actualCalificacion != nullptr) {
        // Buscar la película correspondiente a la calificación
        Pelicula* peliculaActual = cabezaPeliculas;
        while (peliculaActual != nullptr && peliculaActual->nombre != actualCalificacion->nombre) {
            peliculaActual = peliculaActual->siguiente;
        }

        // Si la película es del género especificado, procesar la calificación
        if (peliculaActual != nullptr && peliculaActual->genero == genero) {
            // Buscar si la película ya está en el arreglo
            bool encontrada = false;
            for (int i = 0; i < totalPeliculas; i++) {
                if (peliculas[i].nombre == actualCalificacion->nombre) {
                    peliculas[i].promedio += actualCalificacion->puntuacion;
                    encontrada = true;
                    break;
                }
            }

            // Si no está en el arreglo, agregarla
            if (!encontrada) {
                peliculas[totalPeliculas].nombre = actualCalificacion->nombre;
                peliculas[totalPeliculas].promedio =                 peliculas[totalPeliculas].promedio = actualCalificacion->puntuacion;
                totalPeliculas++;
            }
        }

        actualCalificacion = actualCalificacion->siguiente;
    }

    // Calcular el promedio para cada película
    for (int i = 0; i < totalPeliculas; i++) {
        int contador = 0;
        Calificacion* temp = cabezaCalificaciones;
        while (temp != nullptr) {
            if (temp->nombre == peliculas[i].nombre) {
                contador++;
            }
            temp = temp->siguiente;
        }
        peliculas[i].promedio /= contador;
    }

    // Ordenar las películas por promedio (de mayor a menor)
    for (int i = 0; i < totalPeliculas - 1; i++) {
        for (int j = i + 1; j < totalPeliculas; j++) {
            if (peliculas[i].promedio < peliculas[j].promedio) {
                PeliculaPromedio temp = peliculas[i];
                peliculas[i] = peliculas[j];
                peliculas[j] = temp;
            }
        }
    }

    // Mostrar el Top 5
    cout << "Top 5 Películas Mejor Calificadas (Género: " << genero << "):\n";
    for (int i = 0; i < min(5, totalPeliculas); i++) {
        cout << i + 1 << ". " << peliculas[i].nombre << " - Puntuación: " << peliculas[i].promedio << endl;
    }
}

void top5SeriesGenerales(Calificacion* cabezaCalificaciones, Serie* cabezaSeries) {
    const int MAX_SERIES = 1000; // Ajusta según sea necesario
    struct SeriePromedio {
        string nombre;
        float promedio;
    };
    SeriePromedio series[MAX_SERIES];
    int totalSeries = 0;
    // Recorrer todas las calificaciones
    Calificacion* actualCalificacion = cabezaCalificaciones;
    while (actualCalificacion != nullptr) {
        // Verificar si la calificación es para una serie
        Serie* serieActual = cabezaSeries;
        while (serieActual != nullptr && serieActual->nombre != actualCalificacion->nombre) {
            serieActual = serieActual->siguiente;
        }
        // Si es una serie, procesar la calificación
        if (serieActual != nullptr) {
            bool encontrada = false;
            for (int i = 0; i < totalSeries; i++) {
                if (series[i].nombre == actualCalificacion->nombre) {
                    series[i].promedio += actualCalificacion->puntuacion;
                    encontrada = true;
                    break;
                }
            }
            if (!encontrada) {
                series[totalSeries].nombre = actualCalificacion->nombre;
                series[totalSeries].promedio = actualCalificacion->puntuacion;
                totalSeries++;
            }
        }
        actualCalificacion = actualCalificacion->siguiente;
    }
    // Calcular el promedio para cada serie
    for (int i = 0; i < totalSeries; i++) {
        int contador = 0;
        Calificacion* temp = cabezaCalificaciones;
        while (temp != nullptr) {
            if (temp->nombre == series[i].nombre) {
                contador++;
            }
            temp = temp->siguiente;
        }
        series[i].promedio /= contador;
    }
    // Ordenar las series por promedio (de mayor a menor)
    for (int i = 0; i < totalSeries - 1; i++) {
        for (int j = i + 1; j < totalSeries; j++) {
            if (series[i].promedio < series[j].promedio) {
                SeriePromedio temp = series[i];
                series[i] = series[j];
                series[j] = temp;
            }
        }
    }

    // Mostrar el Top 5
    cout << "Top 5 Series Mejor Calificadas (General):\n";
    for (int i = 0; i < min(5, totalSeries); i++) {
        cout << i + 1 << ". " << series[i].nombre << " - Puntuación: " << series[i].promedio << endl;
    }
}

void top5SeriesPorPais(Calificacion* cabezaCalificaciones, Serie* cabezaSeries, Usuario* cabezaUsuarios, const string& pais) {
    const int MAX_SERIES = 1000; // Ajusta según sea necesario
    struct SeriePromedio {
        string nombre;
        float promedio;
    };
    SeriePromedio series[MAX_SERIES];
    int totalSeries = 0;

    // Recorrer todas las calificaciones
    Calificacion* actualCalificacion = cabezaCalificaciones;
    while (actualCalificacion != nullptr) {
        // Buscar el usuario que hizo la calificación
        Usuario* usuarioActual = cabezaUsuarios;
        while (usuarioActual != nullptr && usuarioActual->nombre != actualCalificacion->ID) {
            usuarioActual = usuarioActual->siguiente;
        }

        // Si el usuario es del país especificado, procesar la calificación
        if (usuarioActual != nullptr && usuarioActual->pais == pais) {
            // Verificar si la calificación es para una serie
            Serie* serieActual = cabezaSeries;
            while (serieActual != nullptr && serieActual->nombre != actualCalificacion->nombre) {
                serieActual = serieActual->siguiente;
            }

            // Si es una serie, procesar la calificación
            if (serieActual != nullptr) {
                                bool encontrada = false;
                for (int i = 0; i < totalSeries; i++) {
                    if (series[i].nombre == actualCalificacion->nombre) {
                        series[i].promedio += actualCalificacion->puntuacion;
                        encontrada = true;
                        break;
                    }
                }
                if (!encontrada) {
                    series[totalSeries].nombre = actualCalificacion->nombre;
                    series[totalSeries].promedio = actualCalificacion->puntuacion;
                    totalSeries++;
                }
            }
        }
        actualCalificacion = actualCalificacion->siguiente;
    }

    // Calcular el promedio para cada serie
    for (int i = 0; i < totalSeries; i++) {
        int contador = 0;
        Calificacion* temp = cabezaCalificaciones;
        while (temp != nullptr) {
            if (temp->nombre == series[i].nombre) {
                contador++;
            }
            temp = temp->siguiente;
        }
        series[i].promedio /= contador;
    }

    // Ordenar las series por promedio (de mayor a menor)
    for (int i = 0; i < totalSeries - 1; i++) {
        for (int j = i + 1; j < totalSeries; j++) {
            if (series[i].promedio < series[j].promedio) {
                SeriePromedio temp = series[i];
                series[i] = series[j];
                series[j] = temp;
            }
        }
    }

    // Mostrar el Top 5
    cout << "Top 5 Series Mejor Calificadas (País: " << pais << "):\n";
    for (int i = 0; i < min(5, totalSeries); i++) {
        cout << i + 1 << ". " << series[i].nombre << " - Puntuación: " << series[i].promedio << endl;
    }
}

void top5SeriesPorGenero(Calificacion* cabezaCalificaciones, Serie* cabezaSeries, const string& genero) {
    const int MAX_SERIES = 1000; // Ajusta según sea necesario
    struct SeriePromedio {
        string nombre;
        float promedio;
    };
    SeriePromedio series[MAX_SERIES];
    int totalSeries = 0;

    // Recorrer todas las calificaciones
    Calificacion* actualCalificacion = cabezaCalificaciones;
    while (actualCalificacion != nullptr) {
        // Buscar la serie correspondiente a la calificación
        Serie* serieActual = cabezaSeries;
        while (serieActual != nullptr && serieActual->nombre != actualCalificacion->nombre) {
            serieActual = serieActual->siguiente;
        }

        // Si la serie es del género especificado, procesar la calificación
        if (serieActual != nullptr && serieActual->generoSerie == genero) {
            bool encontrada = false;
            for (int i = 0; i < totalSeries; i++) {
                if (series[i].nombre == actualCalificacion->nombre) {
                    series[i].promedio += actualCalificacion->puntuacion;
                    encontrada = true;
                    break;
                }
            }
            if (!encontrada) {
                series[totalSeries].nombre = actualCalificacion->nombre;
                series[totalSeries].promedio = actualCalificacion->puntuacion;
                totalSeries++;
            }
        }
        actualCalificacion = actualCalificacion->siguiente;
    }
    // Calcular el promedio para cada serie
    for (int i = 0; i < totalSeries; i++) {
        int contador = 0;
        Calificacion* temp = cabezaCalificaciones;
        while (temp != nullptr) {
            if (temp->nombre == series[i].nombre) {
                contador++;
            }
            temp = temp->siguiente;
        }
        series[i].promedio /= contador;
    }
    // Ordenar las series por promedio (de mayor a menor)
    for (int i = 0; i < totalSeries - 1; i++) {
        for (int j = i + 1; j < totalSeries; j++) {
            if (series[i].promedio < series[j].promedio) {
                SeriePromedio temp = series[i];
                series[i] = series[j];
                series[j] = temp;
            }
        }
    }
    // Mostrar el Top 5
    cout << "Top 5 Series Mejor Calificadas (Género: " << genero << "):\n";
    for (int i = 0; i < min(5, totalSeries); i++) {
        cout << i + 1 << ". " << series[i].nombre << " - Puntuación: " << series[i].promedio << endl;
    }
}

void contarReseñasPorPelicula(Reseña* cabezaReseñas, ConteoReseñas conteo[], int& totalPeliculas) {
    Reseña* actual = cabezaReseñas;
    while (actual != nullptr) {
        bool encontrada = false;
        // Buscar si la película ya está en el arreglo
        for (int i = 0; i < totalPeliculas; i++) {
            if (conteo[i].nombrePelicula == actual->nombre) {
                conteo[i].cantidadReseñas++;
                encontrada = true;
                break;
            }
        }
        // Si no está en el arreglo, agregarla
        if (!encontrada) {
            conteo[totalPeliculas].nombrePelicula = actual->nombre;
            conteo[totalPeliculas].cantidadReseñas = 1;
            totalPeliculas++;
        }
        actual = actual->siguiente;
    }
}

void contarReseñasPorPeliculaYPais(Reseña* cabezaReseñas, Usuario* cabezaUsuarios, const string& pais, ConteoReseñas conteo[], int& totalPeliculas) {
    Reseña* actualReseña = cabezaReseñas;
    while (actualReseña != nullptr) {
        // Buscar el usuario que hizo la reseña
        Usuario* usuarioActual = cabezaUsuarios;
        while (usuarioActual != nullptr && usuarioActual->nombre != actualReseña->ID) {
            usuarioActual = usuarioActual->siguiente;
        }
        // Si el usuario es del país especificado, contar la reseña
        if (usuarioActual != nullptr && usuarioActual->pais == pais) {
            bool encontrada = false;
            // Buscar si la película ya está en el arreglo
            for (int i = 0; i < totalPeliculas; i++) {
                if (conteo[i].nombrePelicula == actualReseña->nombre) {
                    conteo[i].cantidadReseñas++;
                    encontrada = true;
                    break;
                }
            }
            // Si no está en el arreglo, agregarla
            if (!encontrada) {
                conteo[totalPeliculas].nombrePelicula = actualReseña->nombre;
                conteo[totalPeliculas].cantidadReseñas = 1;
                totalPeliculas++;
            }
        }
        actualReseña = actualReseña->siguiente;
    }
}

void obtenerTop5Peliculas(ConteoReseñas conteo[], int totalPeliculas) {
    const int TOP = 5;
    string topPeliculas[TOP];
    int topReseñas[TOP] = {0};

    // Recorrer el arreglo de conteo de reseñas
    for (int i = 0; i < totalPeliculas; i++) {
        string nombrePelicula = conteo[i].nombrePelicula;
        int cantidadReseñas = conteo[i].cantidadReseñas;

        // Verificar si la película debe estar en el Top 5
        for (int j = 0; j < TOP; j++) {
            if (cantidadReseñas > topReseñas[j]) {
                // Desplazar las películas en el Top 5
                for (int k = TOP - 1; k > j; k--) {
                    topPeliculas[k] = topPeliculas[k - 1];
                    topReseñas[k] = topReseñas[k - 1];
                }
                // Insertar la nueva película en la posición correcta
                topPeliculas[j] = nombrePelicula;
                topReseñas[j] = cantidadReseñas;
                break;
            }
        }
    }
    // Mostrar el Top 5
    cout << "Top 5 Películas con Más Reseñas:\n";
    for (int i = 0; i < TOP; i++) {
        if (topReseñas[i] > 0) {
            cout << i + 1 << ". " << topPeliculas[i] << " - Reseñas: " << topReseñas[i] << endl;
        }
    }
}

void top5PeliculasConMasReseñasPorPais(Reseña* cabezaReseñas, Usuario* cabezaUsuarios, const string& pais) {
    const int MAX_PELICULAS = 1000; // Ajusta este valor según sea necesario
    ConteoReseñas conteo[MAX_PELICULAS];
    int totalPeliculas = 0;

    contarReseñasPorPeliculaYPais(cabezaReseñas, cabezaUsuarios, pais, conteo, totalPeliculas);
    obtenerTop5Peliculas(conteo, totalPeliculas);
}

void top5PeliculasConMasReseñas(Reseña* cabezaReseñas) {
    const int MAX_PELICULAS = 1000; // Ajusta este valor según sea necesario
    ConteoReseñas conteo[MAX_PELICULAS];
    int totalPeliculas = 0;

    contarReseñasPorPelicula(cabezaReseñas, conteo, totalPeliculas);
    obtenerTop5Peliculas(conteo, totalPeliculas);
}

void contarReseñasPorSerie(Reseña* cabezaReseñas, ConteoReseñasSeries conteo[], int& totalSeries) {
    Reseña* actual = cabezaReseñas;
    while (actual != nullptr) {
        bool encontrada = false;
        // Buscar si la serie ya está en el arreglo
        for (int i = 0; i < totalSeries; i++) {
            if (conteo[i].nombreSerie == actual->nombre) {
                conteo[i].cantidadReseñas++;
                encontrada = true;
                break;
            }
        }
        // Si no está en el arreglo, agregarla
        if (!encontrada) {
            conteo[totalSeries].nombreSerie = actual->nombre;
            conteo[totalSeries].cantidadReseñas = 1;
            totalSeries++;
        }
        actual = actual->siguiente;
    }
}

void contarReseñasPorSerieYPais(Reseña* cabezaReseñas, Usuario* cabezaUsuarios, const string& pais, ConteoReseñasSeries conteo[], int& totalSeries) {
    Reseña* actualReseña = cabezaReseñas;
    while (actualReseña != nullptr) {
        // Buscar el usuario que hizo la reseña
        Usuario* usuarioActual = cabezaUsuarios;
        while (usuarioActual != nullptr && usuarioActual->nombre != actualReseña->ID) {
            usuarioActual = usuarioActual->siguiente;
        }
        // Si el usuario es del país especificado, contar la reseña
        if (usuarioActual != nullptr && usuarioActual->pais == pais) {
            bool encontrada = false;
            // Buscar si la serie ya está en el arreglo
            for (int i = 0; i < totalSeries; i++) {
                if (conteo[i].nombreSerie == actualReseña->nombre) {
                    conteo[i].cantidadReseñas++;
                    encontrada = true;
                    break;
                }
            }
            // Si no está en el arreglo, agregarla
            if (!encontrada) {
                conteo[totalSeries].nombreSerie = actualReseña->nombre;
                conteo[totalSeries].cantidadReseñas = 1;
                totalSeries++;
            }
        }
        actualReseña = actualReseña->siguiente;
    }
}


void obtenerTop5Series(ConteoReseñasSeries conteo[], int totalSeries) {
    const int TOP = 5;
    string topSeries[TOP];
    int topReseñas[TOP] = {0};

    // Recorrer el arreglo de conteo de reseñas
    for (int i = 0; i < totalSeries; i++) {
        string nombreSerie = conteo[i].nombreSerie;
        int cantidadReseñas = conteo[i].cantidadReseñas;

        // Verificar si la serie debe estar en el Top 5
        for (int j = 0; j < TOP; j++) {
            if (cantidadReseñas > topReseñas[j]) {
                // Desplazar las series en el Top 5
                for (int k = TOP - 1; k > j; k--) {
                    topSeries[k] = topSeries[k - 1];
                    topReseñas[k] = topReseñas[k - 1];
                }
                // Insertar la nueva serie en la posición correcta
                topSeries[j] = nombreSerie;
                topReseñas[j] = cantidadReseñas;
                break;
            }
        }
    }
    // Mostrar el Top 5
    cout << "Top 5 Series con Más Reseñas:\n";
    for (int i = 0; i < TOP; i++) {
        if (topReseñas[i] > 0) {
            cout << i + 1 << ". " << topSeries[i] << " - Reseñas: " << topReseñas[i] << endl;
        }
    }
}

void top5SeriesConMasReseñas(Reseña* cabezaReseñas) {
    const int MAX_SERIES = 1000; // Ajusta este valor según sea necesario
    ConteoReseñasSeries conteo[MAX_SERIES];
    int totalSeries = 0;

    contarReseñasPorSerie(cabezaReseñas, conteo, totalSeries);
    obtenerTop5Series(conteo, totalSeries);
}

// Función para el Top 5 de series con más reseñas por país
void top5SeriesConMasReseñasPorPais(Reseña* cabezaReseñas, Usuario* cabezaUsuarios, const string& pais) {
    const int MAX_SERIES = 1000; // Ajusta este valor según sea necesario
    ConteoReseñasSeries conteo[MAX_SERIES];
    int totalSeries = 0;

    contarReseñasPorSerieYPais(cabezaReseñas, cabezaUsuarios, pais, conteo, totalSeries);
    obtenerTop5Series(conteo, totalSeries);
}

void mostrarCalificacionesPorUsuario(Calificacion* cabezaCalificaciones, const string& IDUsuario) {
    Calificacion* actual = cabezaCalificaciones;
    bool encontrado = false;

    cout << "Calificaciones dadas por el usuario con ID '" << IDUsuario << "':\n";

    while (actual != nullptr) {
        if (actual->ID == IDUsuario) {
            cout << "--------------------------" << endl;
            cout << "Nombre: " << actual->nombre << endl;
            cout << "Puntuación: " << actual->puntuacion << endl;
            cout << "--------------------------" << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron calificaciones para el usuario con ID '" << IDUsuario << "'.\n";
    }
}

void contarReseñasPorTemporada(Reseña* cabezaReseñas, ConteoReseñasTemporadas conteo[], int& totalTemporadas) {
    Reseña* actual = cabezaReseñas;
    while (actual != nullptr) {
        bool encontrada = false;
        // Buscar si la temporada ya está en el arreglo
        for (int i = 0; i < totalTemporadas; i++) {
            if (conteo[i].nombreTemporada == actual->nombre) {
                conteo[i].cantidadReseñas++;
                encontrada = true;
                break;
            }
        }
        // Si no está en el arreglo, agregarla
        if (!encontrada) {
            conteo[totalTemporadas].nombreTemporada = actual->nombre;
            conteo[totalTemporadas].cantidadReseñas = 1;
            totalTemporadas++;
        }
        actual = actual->siguiente;
    }
}

void contarReseñasPorTemporadaYPais(Reseña* cabezaReseñas, Usuario* cabezaUsuarios, const string& pais, ConteoReseñasTemporadas conteo[], int& totalTemporadas) {
    Reseña* actualReseña = cabezaReseñas;
    while (actualReseña != nullptr) {
        // Buscar el usuario que hizo la reseña
        Usuario* usuarioActual = cabezaUsuarios;
        while (usuarioActual != nullptr && usuarioActual->nombre != actualReseña->ID) {
            usuarioActual = usuarioActual->siguiente;
        }
        // Si el usuario es del país especificado, contar la reseña
        if (usuarioActual != nullptr && usuarioActual->pais == pais) {
            bool encontrada = false;
            // Buscar si la temporada ya está en el arreglo
            for (int i = 0; i < totalTemporadas; i++) {
                if (conteo[i].nombreTemporada == actualReseña->nombre) {
                    conteo[i].cantidadReseñas++;
                    encontrada = true;
                    break;
                }
            }
            // Si no está en el arreglo, agregarla
            if (!encontrada) {
                conteo[totalTemporadas].nombreTemporada = actualReseña->nombre;
                conteo[totalTemporadas].cantidadReseñas = 1;
                totalTemporadas++;
            }
        }
        actualReseña = actualReseña->siguiente;
    }
}

void obtenerTop5Temporadas(ConteoReseñasTemporadas conteo[], int totalTemporadas) {
    const int TOP = 5;
    string topTemporadas[TOP];
    int topReseñas[TOP] = {0};
    int encontradas = 0;

    // Recorrer el arreglo de conteo de reseñas
    for (int i = 0; i < totalTemporadas; i++) {
        string nombreTemporada = conteo[i].nombreTemporada;
        int cantidadReseñas = conteo[i].cantidadReseñas;

        // Verificar si la temporada debe estar en el Top 5
        for (int j = 0; j < TOP; j++) {
            if (cantidadReseñas > topReseñas[j]) {
                // Desplazar las temporadas en el Top 5
                for (int k = TOP - 1; k > j; k--) {
                    topTemporadas[k] = topTemporadas[k - 1];
                    topReseñas[k] = topReseñas[k - 1];
                }
                // Insertar la nueva temporada en la posición correcta
                topTemporadas[j] = nombreTemporada;
                topReseñas[j] = cantidadReseñas;
                break;
            }
        }
        if (encontradas == TOP) break;
    }
    // Mostrar el Top 5
    cout << "Top 5 Temporadas con Más Reseñas:\n";
    for (int i = 0; i < TOP; i) {
        if (topReseñas[i] > 0) {
            cout << i + 1 << ". " << topTemporadas[i] << " - Reseñas: " << topReseñas[i] << endl;
        }
    }
}

void contarReseñasPorCapitulo(Reseña* cabezaReseñas, ConteoReseñasCapitulos conteo[], int& totalCapitulos) {
    Reseña* actual = cabezaReseñas;
    while (actual != nullptr) {
        bool encontrada = false;
        // Buscar si el capítulo ya está en el arreglo
        for (int i = 0; i < totalCapitulos; i++) {
            if (conteo[i].nombreCapitulo == actual->nombre) {
                conteo[i].cantidadReseñas++;
                encontrada = true;
                break;
            }
        }
        // Si no está en el arreglo, agregarla
        if (!encontrada) {
            conteo[totalCapitulos].nombreCapitulo = actual->nombre;
            conteo[totalCapitulos].cantidadReseñas = 1;
            totalCapitulos++;
        }
        actual = actual->siguiente;
    }
}

// Función para contar reseñas por capítulo y país
void contarReseñasPorCapituloYPais(Reseña* cabezaReseñas, Usuario* cabezaUsuarios, const string& pais, ConteoReseñasCapitulos conteo[], int& totalCapitulos) {
    Reseña* actualReseña = cabezaReseñas;
    while (actualReseña != nullptr) {
        // Buscar el usuario que hizo la reseña
        Usuario* usuarioActual = cabezaUsuarios;
        while (usuarioActual != nullptr && usuarioActual->nombre != actualReseña->ID) {
            usuarioActual = usuarioActual->siguiente;
        }
        // Si el usuario es del país especificado, contar la reseña
        if (usuarioActual != nullptr && usuarioActual->pais == pais) {
            bool encontrada = false;
            // Buscar si el capítulo ya está en el arreglo
            for (int i = 0; i < totalCapitulos; i++) {
                if (conteo[i].nombreCapitulo == actualReseña->nombre) {
                    conteo[i].cantidadReseñas++;
                    encontrada = true;
                    break;
                }
            }
            // Si no está en el arreglo, agregarla
            if (!encontrada) {
                conteo[totalCapitulos].nombreCapitulo = actualReseña->nombre;
                conteo[totalCapitulos].cantidadReseñas = 1;
                totalCapitulos++;
            }
        }
        actualReseña = actualReseña->siguiente;
    }
}

// Función para obtener el Top 5 de capítulos con más reseñas
void obtenerTop5Capitulos(ConteoReseñasCapitulos conteo[], int totalCapitulos) {
    const int TOP = 5;
    string topCapitulos[TOP];
    int topReseñas[TOP] = {0};

    // Recorrer el arreglo de conteo de reseñas
    for (int i = 0; i < totalCapitulos; i++) {
        string nombreCapitulo = conteo[i].nombreCapitulo;
        int cantidadReseñas = conteo[i].cantidadReseñas;

        // Verificar si el capítulo debe estar en el Top 5
        for (int j = 0; j < TOP; j++) {
            if (cantidadReseñas > topReseñas[j]) {
                // Desplazar los capítulos en el Top 5
                for (int k = TOP - 1; k > j; k--) {
                    topCapitulos[k] = topCapitulos[k - 1];
                    topReseñas[k] = topReseñas[k - 1];
                }
                // Insertar el nuevo capítulo en la posición correcta
                topCapitulos[j] = nombreCapitulo;
                topReseñas[j] = cantidadReseñas;
                break;
            }
        }
    }
    // Mostrar el Top 5
    cout << "Top 5 Capítulos con Más Reseñas:\n";
    for (int i = 0; i < TOP; i++) {
        if (topReseñas[i] > 0) {
            cout << i + 1 << ". " << topCapitulos[i] << " - Reseñas: " << topReseñas[i] << endl;
        }
    }
}

void top5CapitulosConMasReseñas(Reseña* cabezaReseñas) {
    const int MAX_CAPITULOS = 1000; // Ajusta este valor según sea necesario
    ConteoReseñasCapitulos conteo[MAX_CAPITULOS];
    int totalCapitulos = 0;

    contarReseñasPorCapitulo(cabezaReseñas, conteo, totalCapitulos);
    obtenerTop5Capitulos(conteo, totalCapitulos);
}

// Función para el Top 5 de capítulos con más reseñas por país
void top5CapitulosConMasReseñasPorPais(Reseña* cabezaReseñas, Usuario* cabezaUsuarios, const string& pais) {
    const int MAX_CAPITULOS = 1000; // Ajusta este valor según sea necesario
    ConteoReseñasCapitulos conteo[MAX_CAPITULOS];
    int totalCapitulos = 0;

    contarReseñasPorCapituloYPais(cabezaReseñas, cabezaUsuarios, pais, conteo, totalCapitulos);
    obtenerTop5Capitulos(conteo, totalCapitulos);
}

// Función para mostrar todas las reseñas dadas por un usuario
void mostrarResenasPorUsuario(Reseña* cabezaReseñas, const string& IDUsuario) {
    Reseña* actual = cabezaReseñas;
    bool encontrado = false;

    cout << "Reseñas dadas por el usuario con ID '" << IDUsuario << "':\n";

    while (actual != nullptr) {
        if (actual->ID == IDUsuario) {
            cout << "--------------------------" << endl;
            cout << "Nombre: " << actual->nombre << endl;
            cout << "Reseña: " << actual->texto << endl;
            cout << "--------------------------" << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron reseñas para el usuario con ID '" << IDUsuario << "'.\n";
    }
}

// Función para buscar una serie por su ID
Serie* buscar_serie_por_id(Serie* cabeza, const string& id_serie) {
    Serie* actual = cabeza;  // Puntero para recorrer la lista de series
    while (actual != nullptr) {
        if (actual->ID == id_serie) {  // Compara el ID de la serie con el ID buscado
            return actual;  // Retorna la serie si la encuentra
        }
        actual = actual->siguiente;  // Avanza al siguiente nodo
    }
    return nullptr;  // Retorna nullptr si no encuentra la serie
}

int main() {
    Pelicula* listaPeliculas = nullptr;
    Usuario* listaUsuarios = nullptr;
    Serie* listaSeries = nullptr;
    Temporada* listaTemporadas = nullptr;
    Capitulo* listaCapitulos = nullptr;
    Calificacion* listaCalificaciones = nullptr;
    Reseña* listaResenas = nullptr;

    cargarPeliculas(listaPeliculas);
    cargarUsuarios(listaUsuarios);
    cargarSeries(listaSeries);
    cargarTemporadas(listaSeries);
    cargarCapitulos(listaSeries);
    cargarCalificaciones(listaCalificaciones, listaPeliculas, listaSeries, listaUsuarios);
    cargarResenas(listaResenas, listaPeliculas, listaSeries, listaUsuarios);

    int opcion, opcion2doMenu, opcionTop, opcionTopResenas;
    string nombre, anio, duracion, genero, email, pais;
    string nombreSerie, nombreTemporada, nombreCapitulo, generoSerie;
    int edad, anioEstreno, duracionSerie, numero;
    float puntuacion; 
    string ID, IDTemp, textoResena, nombreContenido; 
    int opcionEliminar; 

    do {
        cout << "\nMENU PRINCIPAL\n";
        cout << "1. Agregar usuario\n";
        cout << "2. Eliminar usuario\n";
        cout << "3. Mostrar usuarios\n";
        cout << "4. Agregar película\n";
        cout << "5. Eliminar película\n";
        cout << "6. Mostrar películas\n"; 
        cout << "7. Agregar serie\n";
        cout << "8. Mostrar series\n";
        cout << "9. Eliminar serie\n";
        cout << "10. Agregar temporada\n";
        cout << "11. Mostrar temporadas\n";
        cout << "12. Eliminar temporada\n";
        cout << "13. Agregar capítulo\n";
        cout << "14. Mostrar capítulos\n";
        cout << "15. Eliminar capítulo\n";
        cout << "16. Agregar calificación\n";
        cout << "17. Mostrar calificaciones\n"; 
        cout << "18. Agregar reseña\n"; 
        cout << "19. Mostrar reseñas\n";
        cout << "20. Agregar resena de temporada o capitulo\n";
        cout << "21. Mostrar resenas de temporada o capitulo\n";
        cout << "22. Top 5 Películas Mejor Calificadas\n";
        cout << "23. Top 5 Series Mejor Calificadas\n";
        cout << "24. Top 5 Películas con mas Reseñas\n";
        cout << "25. Todas calificaciones dadas por un usuario\n";
        cout << "26. Top 5 Series con mas Reseñas\n";
        cout << "27. Top 5 Capitulos con mas Reseñas\n";
        cout << "28. Todas las Resenas dadas por un usuario\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: 
                cout << "Ingrese el nombre del usuario: ";
                getline(cin, nombre);
                cout << "Ingrese el email: ";
                getline(cin, email);
                cout << "Ingrese la edad: ";
                cin >> edad;
                cin.ignore();
                cout << "Ingrese el país: ";
                getline(cin, pais);
                agregarUsuario(listaUsuarios, nombre, email, edad, pais);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;
            
            case 2:
                cout << "Ingrese el email del usuario a eliminar: ";
                getline(cin, email);
                eliminarUsuario(listaUsuarios, email);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;
            
            case 3:
                mostrarUsuarios(listaUsuarios);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;
                
            case 4:
                cout << "Ingrese el ID de la película: ";
                getline(cin, ID);
                cout << "Ingrese el nombre de la película: ";
                getline(cin, nombre);
                cout << "Ingrese el año de estreno: ";
                cin >> anio;
                cin.ignore();
                cout << "Ingrese el género: ";
                getline(cin, genero);
                cout << "Ingrese la duración (en minutos): ";
                cin >> duracion;
                cin.ignore();
                agregarPelicula(listaPeliculas, ID, nombre, anio, genero, duracion);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;
                
            case 5:
                cout << "¿Desea eliminar por ID (1) o por nombre (2)? ";
                int opcionEliminar;
                cin >> opcionEliminar;
                cin.ignore();

                if (opcionEliminar == 1) {
                    cout << "Ingrese el ID de la película a eliminar: ";
                    getline(cin, ID);
                    eliminarPelicula(listaPeliculas, ID, ""); // Busca solo por ID
                } else if (opcionEliminar == 2) {
                    cout << "Ingrese el nombre de la película a eliminar: ";
                    getline(cin, nombre);
                    eliminarPelicula(listaPeliculas, "", nombre); // Busca solo por nombre
                } else {
                    cout << "Opción no válida.\n";
                }
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;

            case 6:
                mostrarPeliculas(listaPeliculas);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;

            case 7:
                cout << "Ingrese el ID de la serie: ";
                getline(cin, ID);
                cout << "Ingrese el nombre de la serie: ";
                getline(cin, nombreSerie);
                cout << "Ingrese el año de estreno de la serie: ";
                cin >> anioEstreno;
                cin.ignore();
                cout << "Ingrese el género de la serie: ";
                getline(cin, generoSerie);
                agregarSerie(listaSeries, ID, nombreSerie, anioEstreno, generoSerie);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;

            case 8:
                mostrarSeries(listaSeries);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;

            case 9:
                cout << "¿Desea eliminar por ID (1) o por nombre (2)? ";
                cin >> opcionEliminar;
                cin.ignore();

                if (opcionEliminar == 1) {
                cout << "Ingrese el ID de la serie a eliminar: ";
                getline(cin, ID);
                eliminarSerie(listaSeries, ID, ""); // Busca solo por ID
                } else if (opcionEliminar == 2) {
                cout << "Ingrese el nombre de la serie a eliminar: ";
                getline(cin, nombre);
                eliminarSerie(listaSeries, "", nombre); // Busca solo por nombre
                } else {
                cout << "Opción no válida.\n";
                }
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;

            case 10:
                cout << "Ingrese el nombre de la serie: ";
                getline(cin, nombreSerie);
                cout << "Ingrese el ID de la temporada: ";
                getline(cin, ID);
                cout << "Ingrese el nombre de la temporada: ";
                getline(cin, nombreTemporada);
                cout << "Ingrese el año de estreno de la temporada: ";
                cin >> anioEstreno;
                cin.ignore();
                agregarTemporada(listaSeries, nombreSerie, ID, nombreTemporada, anioEstreno);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;

            case 11: {
                cout << "Ingrese el ID de la serie: ";
                string idSerie;
                getline(cin, idSerie);  // Solicita el ID de la serie al usuario

                // Busca la serie por ID
                Serie* serieEncontrada = buscar_serie_por_id(listaSeries, idSerie);

                if (serieEncontrada != nullptr) {
                    // Si la serie existe, muestra sus temporadas
                    cout << "Temporadas de la serie '" << serieEncontrada->nombre << "':\n";
                    Temporada* temporadaActual = serieEncontrada->temporadas;
                    while (temporadaActual != nullptr) {
                        cout << "--------------------------" << endl;
                        cout << "ID: " << temporadaActual->IDTemp << endl;
                        cout << "Nombre: " << temporadaActual->nombre << endl;
                        cout << "Año de estreno: " << temporadaActual->anioEstreno << endl;
                        cout << "--------------------------" << endl;
                        temporadaActual = temporadaActual->siguiente;
                    }
                } else {
                    // Si no se encuentra la serie, muestra un mensaje de error
                    cout << "Serie no encontrada.\n";
                }

                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;
            };

            case 12:
                cout << "Ingrese el nombre de la serie: ";
                getline(cin, nombreSerie);
                cout << "¿Desea eliminar por ID (1) o por nombre (2)? ";
                cin >> opcionEliminar;
                cin.ignore();

                if (opcionEliminar == 1) {
                    cout << "Ingrese el ID de la temporada a eliminar: ";
                    getline(cin, ID);
                    eliminarTemporada(listaSeries, nombreSerie, ID, "");
                } else if (opcionEliminar == 2) {
                    cout << "Ingrese el nombre de la temporada a eliminar: ";
                    getline(cin, nombreTemporada);
                    eliminarTemporada(listaSeries, nombreSerie, "", nombreTemporada);
                } else {
                    cout << "Opción no válida.\n";
                }
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;

            case 13:
                cout << "Ingrese el nombre de la serie: ";
                getline(cin, nombreSerie);
                cout << "Ingrese el nombre de la temporada: ";
                getline(cin, nombreTemporada);
                cout << "Ingrese el ID del capítulo: ";
                getline(cin, ID);
                cout << "Ingrese el nombre del capítulo: ";
                getline(cin, nombreCapitulo);
                cout << "Ingrese el año de estreno del capítulo: ";
                cin >> anioEstreno;
                cin.ignore();
                cout << "Ingrese la duración del capítulo (en minutos): ";
                cin >> duracionSerie;
                cin.ignore();
                cout << "Ingrese el número del capítulo: ";
                cin >> numero;
                cin.ignore();
                agregarCapitulo(listaSeries, nombreSerie, nombreTemporada, ID, nombreCapitulo, anioEstreno, duracionSerie, numero);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;

            case 14: 
                cout << "Ingrese el ID de la temporada: ";
                getline(cin, IDTemp);
                mostrarCapitulos(listaSeries, IDTemp);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;

            case 15:
                cout << "Ingrese el nombre de la serie: ";
                getline(cin, nombreSerie);
                cout << "Ingrese el nombre de la temporada: ";
                getline(cin, nombreTemporada);
                cout << "¿Desea eliminar por ID (1) o por nombre (2)? ";                
                cin >> opcionEliminar;
                cin.ignore();

                if (opcionEliminar == 1) {
                    cout << "Ingrese el ID del capítulo a eliminar: ";
                    getline(cin, ID);
                    eliminarCapitulo(listaSeries, nombreSerie, nombreTemporada, ID, ""); // Busca solo por ID
                } else if (opcionEliminar == 2) {
                    cout << "Ingrese el nombre del capítulo a eliminar: ";
                    getline(cin, nombreCapitulo);
                    eliminarCapitulo(listaSeries, nombreSerie, nombreTemporada, "", nombreCapitulo); // Busca solo por nombre
                } else {
                    cout << "Opción no válida.\n";
                }
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;

            case 16:
                cout << "Ingrese el nombre de la película o serie: ";
                getline(cin, nombre);
                cout << "Ingrese el ID Ingrese el ID del usuario que califica: ";
                getline(cin, ID);
                cout << "Ingrese la puntuación (0.0 a 5.0): ";
                cin >> puntuacion;
                cin.ignore();
                agregarCalificacion(listaCalificaciones, nombre, ID, puntuacion, listaPeliculas, listaSeries, listaUsuarios);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;

            case 17:
                cout << "\nOPCIONES\n";
                cout << "1. Todas las peliculas\n";
                cout << "2. Todas las series\n";
                cout << "3. Calificaciones de una película o serie\n";
                cout << "Seleccione una opción: ";
                cin >> opcion2doMenu;

                switch (opcion2doMenu) {
                    case 1:
                        cout<<" ";
                        cin.ignore();
                        mostrarCalificacionesPeliculas(listaCalificaciones, listaPeliculas);
                        cout << "\nPresione ENTER para volver al menu\n";
                        cin.ignore();
                        break;

                    case 2:
                        cout<<" ";
                        cin.ignore();
                        mostrarCalificacionesSeries(listaCalificaciones, listaSeries);
                        cout << "\nPresione ENTER para volver al menu\n";
                        cin.ignore();
                        break;

                    case 3: 
                        cout << "Ingrese el nombre de la película, serie, temporada o capítulo: ";
                        cin.ignore();
                        getline(cin, nombreContenido);
                        buscarCalificacionesPorPelicula(listaCalificaciones, nombreContenido);
                        cout << "\nPresione ENTER para volver al menu\n";
                        cin.ignore();
                        break;
                        
                    default:
                        cout << "Opción no válida.\n";
                        break;
                }
                break;

            case 18:
                cout << "Ingrese el nombre de la película o serie: ";
                getline(cin, nombre);
                cout << "Ingrese el ID del usuario que reseña: ";
                getline(cin, ID);
                cout << "Ingrese la reseña (máximo 250 caracteres): ";
                getline(cin, textoResena);
                agregarResena(listaResenas, nombre, ID, textoResena, listaPeliculas, listaSeries, listaUsuarios);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;

            case 19: 
                cout << "\nOPCIONES\n";
                cout << "1. Todas las peliculas\n";
                cout << "2. Todas las series\n";
                cout << "3. Reseñas de una película o serie específica\n";
                cout << "Seleccione una opción: ";
                cin >> opcion2doMenu;

                switch (opcion2doMenu) {
                    case 1:
                        cout<<" ";
                        cin.ignore();
                        mostrarResenasPeliculas(listaResenas, listaPeliculas);
                        cout << "\nPresione ENTER para volver al menu\n";
                        cin.ignore();
                        break;

                    case 2:
                        cout<<" ";
                        cin.ignore();
                        mostrarResenasSeries(listaResenas, listaSeries);
                        cout << "\nPresione ENTER para volver al menu\n";
                        cin.ignore();
                        break;

                    case 3: 
                        cout << "Ingrese el nombre de la película o serie: ";
                        cin.ignore();
                        getline(cin, nombreContenido);
                        buscarResenasPorPelicula(listaResenas, nombreContenido);
                        cout << "\nPresione ENTER para volver al menu\n";
                        cin.ignore();
                        break;
                        
                    default:
                        cout << "Opción no válida. Intente de nuevo.\n";
                        break;
                }
                break;

            case 20:
                cout << "Ingrese el nombre de la temporada o capítulo: ";
                getline(cin, nombreContenido);
                cout << "Ingrese el ID del usuario que reseña: ";
                getline(cin, ID);
                cout << "Ingrese la reseña (máximo 250 caracteres): ";
                getline(cin, textoResena);
                agregarResenaTemporadaCapitulo(listaResenas, nombreContenido, ID, textoResena, listaSeries, listaUsuarios);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();
                break;

            case 21:
                cout << "Ingrese el nombre de la temporada o capítulo: ";
                getline(cin, nombreContenido);
                mostrarResenasTemporadaCapitulo(listaResenas, nombreContenido);
                cout << "\nPresione ENTER para volver al menu\n";
                cin.ignore();

            case 22:
                cout << "\nOPCIONES DE TOP 5\n";
                cout << "1. Top 5 General\n";
                cout << "2. Top 5 por País\n";
                cout << "3. Top 5 por Género\n";
                cout << "Seleccione una opción: ";
                cin >> opcionTop;
                cin.ignore();

                switch (opcionTop) {
                    case 1:
                        cout << " ";
                        cin.ignore();
                        top5PeliculasGenerales(listaCalificaciones, listaPeliculas);
                        cout << "\nPresione ENTER para volver al menu\n";
                        cin.ignore();
                        break;
                    case 2:
                        cout << "Ingrese el país: ";
                        getline(cin, pais);
                        top5PeliculasPorPais(listaCalificaciones, listaUsuarios, pais);
                        cout << "\nPresione ENTER para volver al menu\n";
                        cin.ignore();
                        break;
                    case 3:
                        cout << "Ingrese el género: ";
                        getline(cin, genero);
                        top5PeliculasPorGenero(listaCalificaciones, listaPeliculas, genero);
                        cout << "\nPresione ENTER para volver al menu\n";
                        cin.ignore();
                        break;
                    default:
                        cout << "Opción no válida.\n";
                        break;
                }
                break;

            case 23:
                cout << "\nOPCIONES DE TOP 5 SERIES\n";
                cout << "1. Top 5 General\n";
                cout << "2. Top 5 por País\n";
                cout << "3. Top 5 por Género\n";
                cout << "Seleccione una opción: ";
                cin >> opcionTop;
                cin.ignore();
                switch (opcionTop) {
                    case 1:
                        cout << " ";
                        cin.ignore();
                        top5SeriesGenerales(listaCalificaciones, listaSeries);
                        cout << "\nPresione ENTER para volver al menu\n";
                        cin.ignore();
                        break;
                    case 2:
                        cout << "Ingrese el país: ";
                        getline(cin, pais);
                        top5SeriesPorPais(listaCalificaciones, listaSeries, listaUsuarios, pais);
                        cout << "\nPresione ENTER para volver al menu\n";
                        cin.ignore();
                        break;
                    case 3:
                        cout << "Ingrese el género: ";
                        getline(cin, genero);
                        top5SeriesPorGenero(listaCalificaciones, listaSeries, genero);
                        cout << "\nPresione ENTER para volver al menu\n";
                        cin.ignore();
                        break;
                    default:
                        cout << "Opción no válida.\n";
                        break;
                }
                break;

            case 24:
                cout << "\nOPCIONES DE TOP 5 PELÍCULAS CON MÁS RESEÑAS\n";
                cout << "1. Top 5 General\n";
                cout << "2. Top 5 por País\n";
                cout << "0. Volver al menú principal\n";
                cout << "Seleccione una opción: ";
                cin >> opcionTopResenas;
                cin.ignore();
                switch (opcionTopResenas) {
                    case 1:
                        cout << " ";
                        cin.ignore();
                        top5PeliculasConMasReseñas(listaResenas);
                        cout << "\nPresione ENTER para continuar\n";
                        cin.ignore();
                        break;

                    case 2:
                        cout << "Ingrese el país: ";
                        getline(cin, pais);
                        top5PeliculasConMasReseñasPorPais(listaResenas, listaUsuarios, pais);
                        cout << "\nPresione ENTER para continuar\n";
                        cin.ignore();
                        break;
                        
                    default:
                        cout << "Opción no válida.\n";
                        break;
                }
                break;

            case 25: 
                cout << "Ingrese el ID del usuario: ";
                getline(cin, ID);
                mostrarCalificacionesPorUsuario(listaCalificaciones, ID);
                cout << "\nPresione ENTER para volver al menú\n";
                cin.ignore();
                break;

            case 26:
                cout << "\nOPCIONES DE TOP 5 SERIES CON MÁS RESEÑAS\n";
                cout << "1. Top 5 General\n";
                cout << "2. Top 5 por País\n";
                cout << "Seleccione una opción: ";
                cin >> opcionTopResenas;
                cin.ignore();

                switch (opcionTopResenas) {
                    case 1:
                        cout << " ";
                        cin.ignore();
                        top5SeriesConMasReseñas(listaResenas);
                        cout << "\nPresione ENTER para continuar\n";
                        cin.ignore();
                        break;
                    case 2:
                        cout << "Ingrese el país: ";
                        getline(cin, pais);
                        top5SeriesConMasReseñasPorPais(listaResenas, listaUsuarios, pais);
                        cout << "\nPresione ENTER para continuar\n";
                        cin.ignore();
                        break;
                    default:
                        cout << "Opción no válida.\n";
                        break;
                }
                break;

            case 27:    
                cout << "\nOPCIONES DE TOP 5 CAPÍTULOS CON MÁS RESEÑAS\n";
                cout << "1. Top 5 General\n";
                cout << "2. Top 5 por País\n";
                cout << "Seleccione una opción: ";
                cin >> opcionTopResenas;
                cin.ignore();
                switch (opcionTopResenas) {
                    case 1:
                        cout << " ";   
                        cin.ignore();
                        top5CapitulosConMasReseñas(listaResenas);
                        cout << "\nPresione ENTER para continuar\n";
                        cin.ignore();
                        break;
                    case 2:
                        cout << "Ingrese el país: ";
                        getline(cin, pais);
                        top5CapitulosConMasReseñasPorPais(listaResenas, listaUsuarios, pais);
                        cout << "\nPresione ENTER para continuar\n";
                        cin.ignore();
                        break;
                    default:
                        cout << "Opción no válida.\n";
                        break;
                }
                break;
            
            case 28:
                cout << "Ingrese el ID del usuario: ";
                getline(cin, ID);
                mostrarResenasPorUsuario(listaResenas, ID);
                cout << "\nPresione ENTER para volver al menú\n";
                cin.ignore();
                break;
                
            case 0:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
 
    return 0;
}