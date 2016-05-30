/**
@file imagen.h
@brief Clase imagen blanco y negro.
*/

#ifndef _IMAGEN_H_
#define _IMAGEN_H_
#include"lista.h"
typedef unsigned char byte; ///< byte = 8bits almacenado en un unsigned char

/**
@brief Una imagen en blanco y negro. Cada píxel es un byte
*/
class Imagen{
private:
   byte ** datos; ///< puntero a los punteros de las filas 
   int nfilas; 			///< número de filas de la imagen
   int ncolumnas;		///< número de columnsa de la imagen
public:
	/**
	@brief Constructor por defecto. Crea un Imagen vacía de 0 filas x 0 columnas.
	*/
    Imagen(); 
    
    /**
    @brief Libera la memoria reservada para una imagen   
    */
	~Imagen();
	
	/**
	@brief Contructor de copia de la clase Imagen.
	@param Imagen a copiar
	*/
	
	Imagen(const Imagen&);
	
	/**
	@brief Operador de asignación de la clase imagen. Si la imagen a asignar es la misma que la actual no hace nada. Si la imagen ya estaba creada, se destruye.
	@param img	imagen a copiar
	@return imagen nueva copiada
	*/
	Imagen& operator=(const Imagen &img);
	
	/**
	@brief Operador + de la clase imagen. Devuelve una nueva imagen compuesta por los dos sumandos colocados uno al lado del otro y con el 
	espacio que quede en negro.
	@param img	imagen a sumar
	@return imagen suma
	*/
	Imagen operator+(const Imagen img) const;
	
	/**
	@brief Construye una imagen negra de tamaño @a filas x @a columnas
	@param filas 	número de filas de la imagen
	@param columnas	número de columnas de la imagen

	Construye una imagen de tamaño @a filas x @a columnas y pone todos 
	sus elementos a 0.
	*/
   Imagen(int filas, int columnas);
   
   
	/**
	@brief Crea una imagen negra de tamaño @a filas x @a columnas
	@param filas 	número de filas de la imagen
	@param columnas	número de columnas de la imagen

	Dimensiona la imagen a tamaño @a filas x @a columnas y pone todos 
	sus elementos a 0.
	*/
   void crear(int filas, int columnas);
   
   
	/**
	@brief Devuelve el número de filas de las imagen
	@return el número de filas de la imagen
	*/
   int filas() const; 

   
	/**
	@brief Devuelve el número de columnas de las imagen
	@return el número de columnas de la imagen
	*/
   int columnas() const; 
   

	/**
	@brief Asigna el valor @a v a la posición (@a x,@a y) de la imagen
	@param y 	fila de la imagen
	@param x 	columna de la imagen 
	@param v 	valor a asignar

	Asigna el valor @a v a la posición (@a x,@a y) de la imagen. Dado que la imagen se guarda
	como un vector, la posición (@a x,@a y) corresponde a la posición @a y * @c ncolumnas + @a x 
	del vector.    
	*/
   void set(int y, int x, byte v); 
   
   
	/**
	@brief Devuelve el valor de la posición (@a x,@a y) de la imagen
	@param y	 fila de la imagen
	@param x	 columna de la imagen 
	@return el valor de la posición (@a x,@a y) de la imagen

	Devuelve el valor de la posición (@a x,@a y) de la imagen. Dado que la imagen se guarda
	como un vector, la posición (@a x,@a y) corresponde a la posición @a y * @c ncolumnas + @a x 
	del vector.    
	*/
   byte get(int y, int x) const; 
   
   
	/**
	@brief Asigna el valor @a v a la posición @a i de la imagen considerada como vector
	@param i 	posición de la imagen considerada como vector
	@param v 	valor a asignar

	Asigna el valor @a v a la posición @a i de la imagen considerada como vector. La posición @a i 
	corresponde con la posición @c y * @c ncolumnas + @c x de la imagen donde @c y representa la 
	fila y @c x representa la columna.    
	*/
   void setPos(int i, byte v); 
   
	 
	/**
	@brief Devuelve el valor de la posición @a i de la imagen considerada como vector
	@param i 	posición de la imagen considerada como vector

	Devuelve el valor de la posición @a i de la imagen considerada como vector. La posición @a i 
	corresponde con la posición @c y * @c ncolumnas + @c x de la imagen donde @c y representa la 
	fila y @c x representa la columna.    
	*/
   byte getPos(int i) const;

   
	/**
	@brief Carga una imagen desde un fichero 
	@param nombreFichero nombre del fichero que contiene la imagen
	@retval true 	si ha tenido éxito en la lectura
	@retval false 	si se ha producido algún error en la lectura

	Lee desde disco los datos de la imagen llamada @a nombreFichero y la guarda en la memoria. La función debe asegurarse de que la imagen es de un tipo de imagen conocido.
	*/
   bool leerImagen(const char nombreFichero[]);
   

	/**
	@brief Guarda una imagen desde un fichero 
	@param nombreFichero nombre del fichero que contiene la imagen
	@param esBinario toma el valor @c true si el fichero se escribe en formato binario o @c false en caso contrario.
	@retval true 	si ha tenido éxito en la escritura
	@retval false 	si se ha producido algún error en la escritura
	*/
   bool escribirImagen(const char nombreFichero[], bool esBinario); 
   
   
	/**
	@brief Extrae de la imagen el plano del bit del vector indicado por @a k 
	@param k 	Numero del bit del que extraer el plano

	Extrae de la imagen el plano de la imagen del bit indicado por @a k, despues devuelve como una nueva imagen el plano resultante.    
	*/
   Imagen *plano(int k);
   
	/**
	@brief Dada una imagen, se convierte equivalente utilizando caracteres ASCII
	@param grises caracteres que se utilizarán en el arte ASCII
	@param arteASCII vector resultante con la cadena ASCII que representa la imagen
	@param maxlong longitud máxima
	@retval true 	la imagen cabe en el vector resultante
	@retval false 	la imagen no cabe en el vector resultante
	*/
   bool aArteASCII(const char grises[], char arteASCII[], int maxlong);
   
   	/**
	@brief Dada una lista de strings que representan niveles de gris, se ejecuta la función @f aArteASCII con cada string. El resultado de 
	pasar la imagen a arte ASCII con cada grupo de grises se guarda en archivos con nombre ascii1.txt, ascii2.txt,...
	@param celdas Lista de strings de niveles de gris
	@retval true 	todas las conversiones fueron posibles
	@retval false 	alguna conversión falló
	*/
	bool listaAArteASCII(const Lista &celdas);
	
	
   	/**
	@brief Libera la memoria de una imagen. Esta función es llamada por el destructor.
	*/
	void destruir();
};

#endif
