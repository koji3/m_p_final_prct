#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<imagen.h>
#include <stdlib.h> 
#include <cstring>

using namespace std;

int main(){
	char archivo_grises[255];
	char archivo_salida[255];
	char grises[100];
	
	const int TAM=100000;
	
    char arteASCII[TAM]; 
       
    Imagen origen;
    char nombre_imagen[255];
	
	cout << "Introduce el nombre de la imagen .pgm: " << endl;  
	cin >> nombre_imagen;
	
	cout << "Introduce el fichero de grises: " << endl;  
	cin >> archivo_grises;
	
	cout << "Introduce el fichero de salida: " << endl;  
	cin >> archivo_salida;
	
	if (!origen.leerImagen(nombre_imagen)){
	   cerr << "error leyendo " << nombre_imagen << " \n";
	   return 1;
    }
	
	string linea;
	int num_grises;
	ifstream fentrada;
	ofstream fsalida;
	fentrada.open(archivo_grises);
	if(fentrada){
		getline(fentrada,linea);				//Ignorar primera linea
		fentrada >> num_grises;
		for(int x=1; x<=num_grises; x++){
			fentrada>>grises;
		    if(origen.aArteASCII(grises, arteASCII, TAM)){
		    	char nombre_aux[255];
		    	//strcpy(nombre_aux,archivo_salida);
		    	sprintf(nombre_aux, "%s%d%s", archivo_salida,x,".txt");
		    	//strcat(nombre_aux,".txt");
				fsalida.open(nombre_aux);
				fsalida << arteASCII;
				fsalida.close();
			}else{
				cout << "La conversión " << x << " no ha sido posible" << endl;  
			}
		}
		fentrada.close();
	}else{
		cerr << "error de apertura del fichero\n";
	}
	
}
