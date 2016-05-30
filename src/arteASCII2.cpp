/**
 * lee cualquier imagen indicada por el usuario y un fichero con cadenas 
 * de caracteres y crea ficheros de imagen transformadas, una por cadena
*/
#include<iostream>
#include<fstream>
#include<cstring>
#include "imagen.h"
#include "lista.h"

using namespace std;

int main(int argc, char * argv[]){
    char * ficheroGrises = argv[2];
    char * ficheroImagen= argv[1];
    Imagen origen;
    Lista celdas, cel, c;
	
	if(argc!=3){
		cout << "Introduzca nombre de la imagen y fichero de grises por parametro."<<endl;
		return 1;
	}
	

    // Leer la imagen desde fichero
    if (!origen.leerImagen(ficheroImagen)){
		cerr << "Error leyendo imagen " << ficheroImagen << endl;
		return 1;
    }

	// Leer cadenas desde fichero
	if (celdas.leerLista(ficheroGrises)){	
		// realizar las conversiones 
		cerr << "Exito en la conversion." << endl;
		Lista l(celdas);
		cerr << "Exito en la conversion." << endl;
		c=l;
		cerr << "Exito en la conversion." << endl;
		if (origen.listaAArteASCII(c)){
			cerr << "Exito en la conversion." << endl;
			cerr << "Chequee los ficheros asciiX.txt" << endl;
		}else{
			cerr << "La conversion no ha sido posible" << endl;
			cerr << endl;
			return 1;
		}
	}else{
		cerr << "Error lista de grises " << ficheroGrises << endl;
		return 1;
	}

}
