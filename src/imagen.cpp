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
    if(filas>=0 && columnas>=0){
	    crear(filas,columnas);
	}
}

Imagen::Imagen(const Imagen& img){
    this->datos=0;
    this->crear(img.filas(),img.columnas());
    for(int x=0; x<nfilas*ncolumnas; x++){
    	this->setPos(x, img.getPos(x));
    }
}

Imagen &Imagen::operator=(const Imagen &img){
	if(&img!=this){
		if(datos!=0){ destruir(); }
		crear(img.filas(),img.columnas());
		for(int x=0; x<nfilas*ncolumnas; x++){
			setPos(x, img.getPos(x));
		}
    }
    return *this;
}

Imagen Imagen::operator+(const Imagen b) const{
	Imagen nueva(max(this->filas(),b.filas()),this->columnas()+b.columnas());
	for(int f=0; f<this->filas(); f++){
		for(int c=0; c<this->columnas(); c++){
			nueva.set(f,c,this->get(f,c));
		}
	}

	for(int f=0; f<b.filas(); f++){
		for(int c=0; c<b.columnas(); c++){
			nueva.set(f,c+this->columnas(),b.get(f,c));
		}
	}
	return nueva;
}

int Imagen::filas()const{
    return nfilas;
}

int Imagen::columnas()const{
    return ncolumnas;
}

void Imagen::set(int y, int x, byte v){
	if(y<filas() && x<columnas()){
		datos[y][x]=v;
	}else{
		cerr << "Acceso fuera de los límites del vector" << endl;
		exit(1);
	}
}

byte Imagen::get(int y, int x) const{
	if(y<filas() && x<columnas()){
		return datos[y][x];
	}else{
		cerr << "Acceso fuera de los límites del vector" << endl;
		exit(1);
	}
}

void Imagen::setPos(int i, byte v){
	if(i<filas()*columnas()){
		datos[0][i]=v;
	}else{
		cerr << "Acceso fuera de los límites del vector" << endl;
		exit(1);
	}
}

byte Imagen::getPos(int i)const{
	if(i<filas()*columnas()){
		return datos[0][i];
	}else{
		cerr << "Acceso fuera de los límites del vector" << endl;
		exit(1);
	}
}

void Imagen::crear(int filas, int columnas){
    if(datos!=0){ destruir(); }
    this->nfilas = filas;
    this->ncolumnas = columnas;
    datos=new byte*[filas];
    datos[0]=new byte[filas*columnas];
    for(int f=0; f<filas;f++){
    	datos[f]=&datos[0][(f*ncolumnas)];
    }
    for(int f=0;f<filas;f++){ 
        for(int c=0;c<columnas;c++){ 
	        datos[f][c] = 0;
    	}
    }
}

bool Imagen::leerImagen(const char nombreFichero[]){
	int f, c;
	bool exito=false;
	TipoImagen tipo = infoPGM(nombreFichero,f,c);
	switch ( tipo ){
		case IMG_PGM_BINARIO: 
			this->crear(f,c); 
			leerPGMBinario(nombreFichero,datos[0],f,c);
			exito=true;
			break;

		case IMG_PGM_TEXTO: 
			this->crear(f,c); 
			leerPGMTexto(nombreFichero,datos[0],f,c);
			exito=true;
			break;
		
		case IMG_DESCONOCIDO:
			exito=false;
			break;
		
		default: 
			exito=false;
			break;
	}
	return exito;
}

 
bool Imagen::escribirImagen(const char nombreFichero[], bool esBinario){
	if(esBinario){
    	return escribirPGMBinario(nombreFichero, datos[0], nfilas, ncolumnas);
    }else{
    	return escribirPGMTexto(nombreFichero, datos[0], nfilas, ncolumnas);
    }
}

Imagen *Imagen::plano ( int k ){
    Imagen *aux= new Imagen(nfilas,ncolumnas);
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
				arteASCII[indice]=grises[(datos[0][(y*ncolumnas)+x]*ncaracteres)/256];
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
    char * arteASCII= new char[nfilas*(ncolumnas+1)]; 
    bool exito=true;
	for(int x=0; x<celdas.longitud(); x++){
		string gris = celdas.getCelda(x);
		const char *gris_char = gris.c_str();
		if(this->aArteASCII(gris_char, arteASCII, nfilas*(ncolumnas+1))){
		    	char nombre_aux[255]="";
				ofstream fsalida;
		    	sprintf(nombre_aux, "%s%d%s", "ascii",x,".txt");
				fsalida.open(nombre_aux);
				fsalida << arteASCII;
				fsalida.close();
			}else{
				//cout << "La conversión " << x << " no ha sido posible" << endl;  
				exito= false;
			}
	}
	delete []arteASCII;
	return exito;
}

void Imagen::destruir(){
	if(datos!=0){ 
		delete [] datos[0];
		delete [] datos;
	}
	ncolumnas=0;
	datos=0;
	nfilas=0;
}

Imagen::~Imagen(){
	destruir();
}




