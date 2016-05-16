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


const int MAXLONG = 1000000;

void leelinea(char *s){
	do{
		cin.getline(s, MAXLONG);
	} while (s[0]=='\0');
}

int main(int argc, char * argv[]){
    char * ficheroGrises = argv[2];
    char * ficheroImagen= argv[1];
    Imagen origen;
    Lista celdas;
	
	if(argc!=2){
		cout << "Introduzca nombre de la imagen y fichero de grises por parametro."<<endl;
	}
	

    // Leer la imagen desde fichero
    if (!origen.leerImagen(ficheroImagen)){
		cerr << "Error leyendo imagen " << ficheroImagen << endl;
		return 1;
    }
	
	// Leer cadenas desde fichero
	if (celdas.leerLista(ficheroGrises)){	
		// realizar las conversiones
		if (origen.listaAArteASCII(celdas)){
			cerr << "Exito en la conversion." << endl;
			cerr << "Chequee los ficheros asciiX.txt" << endl;
			cerr << endl;
		}else{
			cerr << "La conversion no ha sido posible" << endl;
			cerr << endl;
		}
	}else{
		cerr << "Error lista de grises " << ficheroGrises << endl;
	}

}
