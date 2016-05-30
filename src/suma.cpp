// guarda degradado.pgm y trozo.pgm en formato texto. Lee lena.pgm en texto
#include<iostream>
#include<imagen.h>

using namespace std;

int main(int argc, char * argv[]){
	
	if(argc!=5){
		cerr << "Uso: " << argv[0] << " imagen1.pgm imagen2.pgm img_out.pgm (t|b)" << endl ;
		return 1;
	}
	
	bool esBinario;
	if(*argv[4]=='b')
		esBinario=true;
	else
		esBinario=false;
	
    Imagen origen;
    Imagen destino;
    
	if (!destino.leerImagen(argv[1])){
		cerr << "error leyendo  "<< argv[1] << "\n";
		return 1;
	}
	
	if (!origen.leerImagen(argv[2])){
		cerr << "error leyendo  "<< argv[2] << "\n";
		return 1;
	}
	


//	Imagen gato;
//	gato.leerImagen("imagenes/gato.pgm");
	//Imagen destino2(destino+origen);//+gato+origen+origen+destino;
	// Guardar la imagen destino en el fichero 
	if ((destino+origen).escribirImagen(argv[3], esBinario)){
		// si todo va bien
		cout << argv[3] << " guardado correctamente \n";
	} else { // si error
		cerr << "Error guardando la imagen " << argv[3] << "\n";
		return 1;
	}	

	return 0;
}
