#include "byte.h"

using namespace std;
namespace bytaso{
	void on(byte &b, int pos){
		unsigned char mascara=1<<pos;	//Creamos una máscara con un solo bit a 1, aquel que queremos encender.
		b=b|mascara;					//Aplicamos la máscara al bloque de led con un OR, para que el bit correspondiente quede a 1
	}

	void off(byte &b, int pos){
		unsigned char mascara=1<<pos;	//Creamos una máscara con un solo bit a 1, aquel que queremos apagar.
		mascara= ~mascara;				//Negamos la máscara para que queden todos los bits a 1 salvo uno.
		b=b&mascara;					//Aplicamos la máscara al bloque de led con un AND, para que el bit correspondiente quede a 0
	}

	bool get(byte b, int pos){	
		unsigned char mascara=1<<pos;	//Creamos una máscara con un solo bit a 1, aquel que queremos consultar.
		return b&mascara;				//Aplicamos la máscara al bloque de led con un AND. Devolvemos el resultado que será distinto de 0 solo si el led estaba encendido
	}

	string byteToString ( byte b ) {
		string resultado;
	   
		for(int i=7;i>=0;i--){
			if(get(b,i)){				//comprobamos el valor de cada led y añadimos 1 o 0 al string resultado según el valor que tuviese
				resultado+='1';
			}else{
				resultado+='0';        	
			}
			
		}
		return resultado;
	}

	void apagar(byte &b){
		unsigned int mascara = 0;	//Creamos una máscara con todos los bits a 0
	   
		b=b & mascara;				//Aplicamos la máscara al bloque de led con un AND para apagar todos los leds
	   
	}

	void encender(byte &b){
		unsigned int mascara = 0; 	//Creamos una máscara con todos los bits a 0
	   
		b=b | ~mascara;				//Aplicamos la máscara negada al bloque de led con un OR para encender todos los leds
	   
	}

	void asignar(byte &b, const bool v[]){
		unsigned int mascara = 1;	//Creamos una máscara con un solo bit a 1
	   
	   
		for(int i=7; i>=0; i--){
			if(v[i]){				//Si tenemos un true en la posicion actual aplicamos la máscara con un OR para encenderlo
			    b=b | mascara;
			}
			else{					//Si tenemos un false en la posicion actual aplicamos la máscara negada con un AND para apagarlo
			    b=b & ~mascara;
			}
			mascara=mascara<<1;
		}
	}

	void volcar(byte b, bool v[]){
		for(int i=0;i<8;i++){
			if(get(b,i)==0){		//Si el led de la posicion actual está apagado guardamos un 0 en el vector
			    v[i]=0;
			}
			else{					//Si el led de la posicion actual está encendido guardamos un 1 en el vector
			    v[i]=1;
			}
		}
	}

	void encendidos(byte b, int posic[], int &cuantos){
		bool v[8];
		volcar(b, v);				// Volcamos en v el estado de los leds de b
		cuantos=0;					// Inicializamos el contador de encendidos a 0
		for(int x=7; x>=0; x--){
			if( v[x] ){				// Si la posición del vector está a 1, el led está encendido. Entonces lo guardamos en posic y aumentamos el contador de encendidos
				posic[cuantos]=x;
				cuantos++;
			}
		}
	}
}

