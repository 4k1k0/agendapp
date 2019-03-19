# Crear ejecutable Agenda:
#     $ make
# Ejecutar el programa:
#     $ ./Agenda
# Eliminar el ejecutable
#     $ make clean

Agenda: main.cpp
	g++ -std=c++14 main.cpp -o Agenda
clean:
	rm -r Agenda


