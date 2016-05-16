#include"imagen.h"
#include"lista.h"
#include"pgm.h"
#include"byte.h"
#include <stdlib.h> 
#include<stdio.h>
#include<iostream>
#include<fstream>
#include <cstring> 
#include <string.h> 

using namespace std;

Imagen::Imagen(){
    ncolumnas=0;
    nfilas=0;
    datos=0;
}

Imagen::Imagen(int filas, int columnas){
    datos=0;
    crear(filas,columnas);
}


int Imagen::filas(){
    return nfilas;
}

int Imagen::columnas(){
    return ncolumnas;
}

void Imagen::set(int y, int x, byte v){
    datos[(y*ncolumnas)+x]=v;
}

byte Imagen::get(int y, int x){
    return datos[(y*ncolumnas)+x];
}

void Imagen::setPos(int i, byte v){
    datos[i]=v;
}

byte Imagen::getPos(int i){
    return datos[i];
}

void Imagen::crear(int filas, int columnas){
    if(datos!=0){ destruir(); }
    this->nfilas = filas;
    this->ncolumnas = columnas;
    datos=new byte[filas*columnas];
    for(int i=0;i<filas*columnas;i++){ 
        datos[i] = 0;
    }
}

 bool Imagen::leerImagen(const char nombreFichero[]){
     int f, c;
     TipoImagen tipo = infoPGM(nombreFichero,f,c);
     this->crear(f,c); 
     if(tipo==IMG_PGM_BINARIO){
         leerPGMBinario(nombreFichero,datos,this->nfilas,this->ncolumnas);
         return true;
     }else{
     	 if(tipo==IMG_PGM_TEXTO){
		     leerPGMTexto(nombreFichero,datos,f,c);
		     return true;
	     }
     }
	
	return false;
     
 }
 
bool Imagen::escribirImagen(const char nombreFichero[], bool esBinario){
	if(esBinario){
    	return escribirPGMBinario(nombreFichero, datos, nfilas, ncolumnas);
    }else{
    	return escribirPGMTexto(nombreFichero, datos, nfilas, ncolumnas);
    }
}

Imagen *Imagen::plano ( int k ){
    Imagen *aux= new Imagen(nfilas,ncolumnas);
    //aux.crear;
    for(int y=0; y<nfilas*ncolumnas; y++){
    	bytaso::byte nuevo;
    	bytaso::apagar(nuevo);
        if(bytaso::get(getPos(y),k)){
            bytaso::on(nuevo,7);
            
        }
        aux->setPos(y,nuevo);

    }
    return aux;
}

bool Imagen::aArteASCII(const char grises[], char arteASCII[], int maxlong){
	bool exito=false;
	if(ncolumnas*nfilas < maxlong){
		int ncaracteres=strlen(grises);
		int indice=0;
		for(int y=0; y<nfilas; y++){
			for(int x=0; x<ncolumnas; x++){
				arteASCII[indice]=grises[(datos[(y*ncolumnas)+x]*ncaracteres)/256];
				indice++;
			}
			arteASCII[indice]='\n';
			indice++;
		}
		exito=true;
	}
	
	return exito;
}

bool Imagen::listaAArteASCII(const Lista &celdas){
	//const int TAM=100000;
    char * arteASCII= new char[nfilas*(ncolumnas+1)]; 
    bool exito=true;
	for(int x=0; x<celdas.longitud(); x++){
		string gris = celdas.getCelda(x);
		const char *gris_char = gris.c_str();
		//strcpy(gris_char, gris.c_str());
		
		if(this->aArteASCII(gris_char, arteASCII, nfilas*(ncolumnas+1))){
		    	char nombre_aux[255]="";
	    		ofstream fsalida;
		    	sprintf(nombre_aux, "%s%d%s", "ascii",x,".txt");
				fsalida.open(nombre_aux);
				fsalida << arteASCII;
				fsalida.close();
			}else{
				cout << "La conversión " << x << " no ha sido posible" << endl;  
				exito= false;
			}
	}
	delete []arteASCII;
	return exito;
}

void Imagen::destruir(){
	if(datos!=0){ delete [] datos; }
	ncolumnas=0;
	datos=0;
	nfilas=0;
}

Imagen::~Imagen(){
	destruir();
}




