//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,PUNTICOS,EDGES,SOLID_CHESS,SOLID,RANDOM,FIESTA} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);
void	draw_punticos(int grosor);

void	asignar_colores_vertices();

vector<_vertex3f> vertices;
vector<_vertex3f> colores_vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void	draw_solido_colorines();
void	draw_FIESTA();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

void	asignar_colores_caras();

vector<_vertex3i> caras;
vector<_vertex3f> colores_caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase icosaedro
//*************************************************************************

class _icosaedro: public _triangulos3D
{
public:

	_icosaedro(float tam=0.53, float tam1=0.85);
};


//*************************************************************************
// clase esfera
//*************************************************************************

class _esfera: public _triangulos3D
{
public:

	_esfera(float radio, int rev);
	vector<_vertex3f> perfil;
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, float eje);
void  rotacion_ply(char *archivo, int num, float eje);

vector<_vertex3f> perfil; 
int num;
};

