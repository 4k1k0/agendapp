#ifndef AGENDA_H
#define AGENDA_H

struct Contacto{
    /*
     * El primer constructor es para crear
     * vector<Contacto> contactos
     * de la clase Agenda.
     * 
     * El segundo es para crear los contactos
     * con sus respectivos datos.
     * 
     * Cada Contacto se compone de 3 datos:
     *     nombre
     *     numero
     *     correo
     */
    Contacto(){}
    Contacto(string no, string nu, string co): nombre{no}, numero{nu}, correo{co} {}
    string nombre;
    string numero;
    string correo;
};

class Agenda: Contacto{
public:
    /*
     * Para obtener el número
     * de contactos en la agenda.
     */
    int tamano() const{
        return contactos.size();
    }
    /*
     * Para obtener el valor del
     * nombre y el correo más
     * largo, para poder darle
     * estilo a la agenda.
     */
    int noancho() const{
        int min = 8;
        for(int i = 0; i < tamano(); ++i){
            if(min < contactos[i].nombre.length())
                min = contactos[i].nombre.length();
        }
        return min;
    }
    int coancho() const{
        int min = 6;
        for(int i = 0; i < tamano(); ++i){
            if(min < contactos[i].correo.length())
                min = contactos[i].correo.length();
        }
        return min;
    }
    /*
     * v(alido)nombre
     * v(alido)numero
     * v(alido)correo
     * Comprueban si el dato ya existe
     * en la agenda. En caso de que ya exista
     * el dato no es válido (false).
     * Los números deben tener 8 dígitos.
     */
    bool vnombre(string& n){
        for(int i = 0; i < tamano(); ++i){
            if(n == contactos[i].nombre) return false;
        }
        return true;
    }
    bool vnumero(string& n){
        if(n.length() != 8) return false;
        for(int i = 0; i < tamano(); ++i){
            if(n == contactos[i].numero) return false;
        }
        return true;
    }
    bool vcorreo(string& n){
        for(int i = 0; i < tamano(); ++i){
            if(n == contactos[i].correo) return false;
        }
        return true;
    }
    /*
     * Agrega un contacto
     * a la agenda y la ordena.
     */
    void agregar(string no, string nu, string co){
        contactos.push_back({no, nu, co});
        ordenar();
    }
    /*
     * m(ostrar)nombre
     * m(ostrar)numero
     * m(ostrar)correo
     * 
     * Retorna el valor n
     * de la información de
     * contacto.
     * Al hacerlo de esta manera
     * se protege la información
     * del contacto para que no
     * sea alterada. Son utilizadas
     * en las funciones ver() y archivo()
     * para poder imprimir la información.
     * 
     */
    string mnombre(int n) const{
        return contactos[n].nombre;
    }
    string mnumero(int n) const{
        return contactos[n].numero;
    }
    string mcorreo(int n) const{
        return contactos[n].correo;
    }
    
private:
    /*
     * ** NO UTILIZAR LA FUNCION ordenarNoUsar **
     * 
     * Crea una copia de los nombres
     * de contactos en la agenda.
     * 
     * Ordena la copia alfabéticamente.
     * 
     * Llena los vectores num y cor
     * con sus respectivos datos de
     * contacto. (Cada contacto conserva
     * su número y correo)
     * 
     * Ordena los datos de la agenda.
     * 
     */
    
    /*
    void ordenarNoUsar(){
        vector<string> nom;
        vector<string> num;
        vector<string> cor;
        
        for(int i = 0; i < tamano(); ++i){
            nom.push_back(contactos[i].nombre);
        }
        
        sort(nom.begin(), nom.end());
        
        for(int i = 0; i < tamano(); ++i){
            for(int j = 0; j < tamano(); ++j){
                if(nom[i] == contactos[j].nombre){
                    num.push_back(contactos[j].numero);
                    cor.push_back(contactos[j].correo);
                }
            }
        }
        
        for(int i = 0; i < tamano(); ++i){
            contactos[i].nombre = nom[i];
            contactos[i].numero = num[i];
            contactos[i].correo = cor[i];
        }
        
        
    }
    */
    
    
    /*
     * ordenar() Hace uso de una expresión lambda
     *     [](){}
     * Para ordenar los contactos de la agenda alfabéticamente, conservando la relación entre sus datos.
     * 
     * Se redujo la función ordenarNoUsar() de 26 líneas a la función ordenar() de 3 líneas,
     * aunque pudo haber quedado en una sola línea:
     *     sort(contactos.begin(), contactos.end(), [](const Contacto& a, const Contacto& b){ return a.nombre < b.nombre; } );
     * quedó en 3 para ser más legíble.
     */
    void ordenar(){
        sort(contactos.begin(), contactos.end(),
            [](const Contacto& a, const Contacto& b){ return a.nombre < b.nombre; }
        );
    }
    /*
     * Cada agenda tiene un vector de contactos.
     */
    vector<Contacto> contactos;
};

#endif
