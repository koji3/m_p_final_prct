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
    ptrfilas=0;
    matriz=0;
}

Imagen::Imagen(int filas, int columnas){
    datos=0;
    ptrfilas=0;
    matriz=0;
    crear(filas,columnas);
}

Imagen::Imagen(const Imagen& img){
    this->datos=0;
    this->ptrfilas=0;
    this->matriz=0;
    this->crear(img.filas(),img.columnas());
    for(int x=0; x<nfilas*ncolumnas; x++){
    	this->setPos(x, img.getPos(x));
    }
}

Imagen &Imagen::operator=(const Imagen &img){
	destruir();
	crear(img.filas(),img.columnas());
    for(int x=0; x<nfilas*ncolumnas; x++){
    	setPos(x, img.getPos(x));
    }
    return *this;
}

Imagen Imagen::operator+(Imagen b){
	Imagen *nueva= new Imagen(max(this->filas(),b.filas()),this->columnas()+b.columnas());
	for(int f=0; f<this->filas(); f++){
		for(int c=0; c<this->columnas(); c++){
			nueva->set(f,c,this->get(f,c));
		}
	}

	for(int f=0; f<b.filas(); f++){
		for(int c=0; c<b.columnas(); c++){
			nueva->set(f,c+this->columnas(),b.get(f,c));
		}
	}
	return *nueva;
}

int Imagen::filas()const{
    return nfilas;
}

int Imagen::columnas()const{
    return ncolumnas;
}

void Imagen::set(int y, int x, byte v){
    ptrfilas[y][x]=v;
}

byte Imagen::get(int y, int x){

    return ptrfilas[y][x];
}

void Imagen::setPos(int i, byte v){
    datos[i]=v;
}

byte Imagen::getPos(int i)const{
    return datos[i];
}

void Imagen::crear(int filas, int columnas){
    if(datos!=0){ destruir(); }
    this->nfilas = filas;
    this->ncolumnas = columnas;
    ptrfilas=new byte*[filas];
    matriz=&ptrfilas[0];
    datos=new byte[filas*columnas];
    for(int f=0; f<filas;f++){
    	ptrfilas[f]=&datos[ncolumnas*f];
    }
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
	if(datos!=0){ delete [] datos; delete [] ptrfilas; }
	ncolumnas=0;
	datos=0;
	nfilas=0;
    ptrfilas=0;
    matriz=0;
}

Imagen::~Imagen(){
	destruir();
}




