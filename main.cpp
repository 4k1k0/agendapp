#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<iomanip>
#include<fstream>
using namespace std;
#include "akko.h"
#include "agenda.h"

class Loop{
public:
    void agregar(){
        Akko::limpiarVentana();
        /*
         * Primero checa los datos, en caso de no ser válidos los pide otra vez.
         * Si los tres datos son válidos, entonces se agregan a la agenda.
         */
        cin.ignore();
        anombre();
        atelefono();
        acorreo();
        agenda.agregar(nombre, telefono, correo);
    }
    void ver(){
        Akko::limpiarVentana();
        /*
         * noancho y coancho es el nombre más largo
         * y el correo más largo. Se usan para darle
         * formato al texto.
         * 
         * Teléfono no necesita esto porque la agenda
         * sólo acepta teléfonos de 8 dígitos.
         * 
         * Se deja el espacio de las funciones + 2
         * 
         * Todos los datos van a la izquierda (left)
         */
        int a = agenda.noancho() + 2;
        int b = 8 + 2;
        int c = agenda.coancho() + 2;
        
        cout << setw(a) << left << "Contacto" << setw(b) << "Telefono" << setw(c) << "Correo" << endl;
        for(int i = 0; i < agenda.tamano(); ++i)
            cout << setw(a) << agenda.mnombre(i) << setw(b) << agenda.mnumero(i) << setw(c) << agenda.mcorreo(i) << endl;
        
        cin.ignore();
        Akko::pausa("");
    }
    void archivo(){
        ofstream as{"_Agenda.txt"};
        if(!as) cout << "Error al crear Agenda.txt" << endl;
        
        int a = agenda.noancho() + 2;
        int b = 10;
        int c = agenda.coancho() + 2;
        
        as << setw(a) << left << "Contacto" << setw(b) << "Telefono" << setw(c) << "Correo" << endl;
        for(int i = 0; i < agenda.tamano(); ++i)
            as << setw(a) << agenda.mnombre(i) << setw(b) << agenda.mnumero(i) << setw(c) << agenda.mcorreo(i) << endl;
        as.close();
        
    }
    void menu(){
        Akko::limpiarVentana();
        cout << "1) Agregar contacto" << endl
             << "2) Ver agenda" << endl
             << "3) Salir" << endl
             << "> ";
        char m[2];
        cin >> m;
        if(strlen(m) > 1) m[0] = '0';
        switch(m[0]){
            case '1':
                agregar();
                break;
            case '2':
                ver();
                break;
            case '3':
            case 'q':
            case 'Q':
                archivo();
                exit(1);
                break;
            default:
                Akko::limpiarVentana();
                break;
        }
    }
    void loop(){
        while(true)
            menu();
    }
private:
    /*
     * anombre()
     * atelefono()
     * acorreo()
     * Se volverá a pedir el dato
     * en caso que esté repetido.
     */
    void anombre(){
        cin.ignore(numeric_limits<size_t>::max());
        do{
            cout << "Nombre: ";
            getline(cin, nombre);
        } while(!agenda.vnombre(nombre));
    }
    void atelefono(){
        cout << "Telefono (8 digitos): ";
        cin >> telefono;
        if(!agenda.vnumero(telefono))
            atelefono();
    }
    void acorreo(){
        cout << "Correo: ";
        cin >> correo;
        if(!agenda.vcorreo(correo))
            acorreo();
    }
    /*
     * Se crea la Agenda agenda
     * y se declaran los datos que
     * se pedirán desde la consola.
     */
    Agenda agenda;
    
    string nombre;
    string telefono;
    string correo;
};

int main(){
    Akko::nombreVentana("Agenda");
    
    Loop Kumiko;
    Kumiko.loop();
    
    return 0;
}
