#include <string>
#include <fstream>
#include<iostream>
#include "lista.h"

using namespace std;


Lista::Lista(){
	cabecera = 0;
	num_elementos = 0;
}
//CONSTRUCTOR DE COPIA
Lista::Lista(const Lista& otra){
	cabecera = 0;
	num_elementos = 0;
	Celda *aux = otra.cabecera;
	while(aux != 0){
		this->insertar(aux->datos);
		aux = aux->siguiente;
	}
}

Lista::~Lista(){
	destruir();
}
   
Lista::Lista(string valor){
	cabecera=new Celda;
	cabecera->datos = valor;
	cabecera->siguiente = 0;
	num_elementos=1;
}
//SOBRECARGA OPERADOR =

Lista &Lista::operator=(const Lista &otra){
	if(&otra!=this){
		destruir();
		Celda *aux = otra.cabecera;
		while(aux != 0){
			this->insertar(aux->datos);
			aux = aux->siguiente;
		}
	}
	return *this;
}


//SOBRECARGA OPERADOR +
	
Lista& Lista::operator +(const string &s1)
{
	Lista *nueva = this;
	nueva->insertar(s1);
	return *nueva;
}

void Lista::destruir(){
	if(cabecera!=0){
		Celda * actual = cabecera;
		while(actual!=0){
			Celda * aux = actual->siguiente;
			delete actual;
			actual = aux;
		}
	}
	this->cabecera = 0;
	this->num_elementos = 0;
}

void Lista::insertar(string valor){
	Celda *nueva=new Celda;
	Celda *ultima=cabecera;
	nueva->datos=valor;
	nueva->siguiente=0;
	if(ultima==0){
		cabecera=nueva;
	}else{
		while(ultima->siguiente!=0){
			ultima=ultima->siguiente;
		}
		ultima->siguiente=nueva;
	}
	num_elementos++;
}

string Lista::getCelda(int pos) const{
	if(pos<num_elementos){
		Celda *actual=cabecera;
		int contador=0;
		while(contador<pos){
			actual=actual->siguiente;
			contador++;
		}
		return actual->datos;
	}else{
		cerr << "Acceso a celda errónea" << endl;
		exit(1);
		return "";
	}
}

int Lista::longitud() const{
	return num_elementos;
}

/**
 * @brief Construye una lista de celdas enlazadas a partir de la informacion 
 * contenida en un fichero.
 * @param nombreFichero ruta del fichero de texto con el contenido de las datoss
 * a insertar en la lista
 * @retval true si ha tenido éxito en la lectura y el formato es el correcto
 * @retval false si se ha producido algún error en la lectura 
 * 
 * Lee desde disco los elementos almacenados en @a nombreFichero y los guarda 
 * en la lista. La función debe asegurarse de que la estructura sigue un patron 
 * determinado, y se ha de crear la lista con el numero de elementos que contenga. 
 */
bool Lista::leerLista(const char nombrefichero[]){
	ifstream fin;
	fin.open(nombrefichero);
	if(!fin){
		return false;
	}else{
		string grises;
		int lineas;
		getline(fin,grises); //la primera linea se ignora
		fin >> lineas; //leo el numero de datos de grises
		getline(fin,grises); //leer salto de linea
		if (!fin){
			return false;
		}else {
			int i = 0;
			getline(fin,grises); //leer cadena de caracteres
			while ((i < lineas)&&(fin)){
				if (grises != ""){
					insertar(grises);
					i++;
				}
				getline(fin,grises); //leer cadena de caracteres
			}
		}
		fin.close();
	}
	return true;
}

