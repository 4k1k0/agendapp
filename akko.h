/*
 * Akko.h tiene funciones básicas y repetitivas,
 * de una manera que funcionen tanto en Windows
 * como en GNU/Linux.
 * 
 * Funciones:
 * 
 *     nombreVentana     Cambia el título de la consola. Utiliza una string como parámetro.
 * 
 *     limpiarVentana    Limpia la consola. No tiene parámetro.
 * 
 *     esperar           Pausa el programa por x segundos. Admite 0.5 como medio segundo.
 *                       Si se utiliza en GNU y se quiere imprimir un mensaje en horizontal. E.g.
 *                           "Esperando"
 *                           "Esperando."
 *                           "Esperando.."
 *                           "Esperando..."
 *                       Donde hay una función pausa(x) entre cada punto:
 *                           cout << "Esperando"; pausa(x); cout << "."; pausa(x); cout << "."; pausa(x); cout << "."; pausa(x);
 *                       El mensaje "Esperando..." tardaría 3 veces X para poderse visualizar, sin notarse la animación, esto debido
 *                       a que se tiene que limpiar el buffer antes de la función pausa(x). Para esto se utiliza *flush*
 *                             cout << "Esperando" << flush; pausa(x); cout << "." << flush;
 *                             pausa(x); cout << "." << flush; pausa(x); cout << "." << flush; pausa(x);
 *                       De esta manera se puede ejecuta la función pausa(x) entre cada cout, creando una pequeña animación en el texto.
 *                       Si lo que se desea es mostrar texto de manera vertical dejando una pausa(x) entre cada cout
 *                       la función no tiene problemas, ya que al utilizar *endl* entre cada *cout* se limpia el buffer. E.g.
 *                           for(int i = 0; i < 3; ++i){
 *                               cout << i << endl;
 *                               pausa(x);
 *                           }
 *                       Esto funciona correctamente y no hay necesidad de utilizar *flush*.
 *                       *Este problema es sólo de GNU, en Windows no hay necesidad de utilizar flush*
 * 
 *     pausa             Pausa la consola hasta que se presione Enter. Utiliza una string como parámetro,
 *                       pero si el parámetro es "" se utiliza el mensaje por defecto.
 * 
 *     listaArchivos     Muestra una lista de los archivos del directorio indicado.
 *                       Donde los parámetro son *directorio* y *extensión de los archivos (sin el punto)*.
 *                       Si el primer parámetro se deja como "" se mostrará la carpeta raíz del ejecutable.
 *                       Si el segundo parámetro se deja como "" se mostrarán todos los archivos.
 * 
 *     mostrarArchivo    Muestra el contenido de un archivo en la consola.
 *                       El primer parámetro es el nombre del archivo y el segundo el tiempo de animación.
 *                       El tiempo se ingresa de la misma manera que en la función pausa() y el tiempo es
 *                       por caracter. 
 *                       Pensé en esto como una manera de mostrar arte ASCII pero funciona bien con cualquier
 *                       tipo de archivo de texto plano.
 * 
 * Librerías:
 *      
 *     fstream           Necesaria para la función mostrarArchivo()
 * 
 *     time.h            Necesaria para la funcion esperar()
 *     
 *     windows.h         *Sólo en Windows* Necesaria para la función nombreVentana()
 * 
 *     unistd.h          *Sólo en GNU* Necesaria para la función esperar()
 * 
 * Akko(https://myanimelist.net/character/15658/Akiko_Oohashi)
 */
#ifndef AKKO_H
#define AKKO_H

#include<fstream>
#include<time.h>
#ifdef _WIN32
#include<windows.h>
#else
#include<unistd.h>
#endif

namespace Akko{
    
    void nombreVentana(string nombre){
        #ifdef _WIN32
        const char* n = nombre.c_str();
            SetConsoleTitle(n);
        #else
            char esc_start[] = { 0x1b, ']', '0', ';', 0 };
            char esc_end[] = { 0x07, 0 };
            cout << esc_start << nombre << esc_end;
        #endif
    }
    void limpiarVentana(){
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    void esperar(double segundos){
        if(segundos <= 0) return;
        #ifdef _WIN32
            segundos *= 1000;
            int goal = (int) segundos + clock();
            while(goal > clock());
        #else
            segundos *= 1000000;
            int goal = (int) segundos;
            usleep(goal);
        #endif
    }
    void pausa(string msj){
        if(msj == "") msj = "Presiona Enter para continuar";
        cout << msj << endl;
        cin.get();
        cin.clear();
    }
    void listaArchivos(string directorio, string extension){
        string cd;
        (directorio == "") ? cd = "" : cd = "cd " + directorio + " && ";
        if(extension != "") extension = " *" + extension;
        #ifdef _WIN32
            cd += "dir /b" + extension;
            const char* a = cd.c_str();
            system(a);
        #else
            cd += "ls --color" + extension;
            const char* a = cd.c_str();
            system(a);
        #endif
    }
    void mostrarArchivo(string n, double t){
        ifstream archivo {n};
        if(!archivo) cout << "Error al abrir el archivo " << n << "\n";
        char c;
        while(archivo.get(c)){
            cout << c << flush;
            esperar(t);
        }
        archivo.close();
    }
    
}

#endif
