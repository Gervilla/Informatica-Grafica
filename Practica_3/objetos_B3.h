//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE=5000;
typedef enum{POINTS,PUNTICOS,EDGES,SOLID_CHESS,SOLID,RANDOM,FIESTA} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
  _puntos3D();
void  draw_puntos(float r, float g, float b, int grosor);
void  draw_punticos(int grosor);

void  asignar_colores_vertices();

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
void  draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void  draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void  draw_solido_colorines();
void  draw_FIESTA();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

void  asignar_colores_caras();

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


//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis: public _triangulos3D
{
public:
       _chasis();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;

protected:
_rotacion  rodamiento;
_cubo  base;
};

//************************************************************************

class _torreta: public _triangulos3D
{
public:
       _torreta();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;

protected:
_cubo  base;
_piramide parte_trasera;
};

//************************************************************************

class _tubo: public _triangulos3D
{
public:
       _tubo();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion canon; // caña del cañón
};

//************************************************************************

class _tanque: public _triangulos3D
{
public:
       _tanque();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_tubo;
float giro_torreta;

float giro_tubo_min;
float giro_tubo_max;

protected:
_chasis  chasis;
_torreta  torreta;
_tubo     tubo;
};









//************************************************************************
// objeto articulado: _robo_payaso
//************************************************************************

class _cuerpo: public _triangulos3D
{
public:
       _cuerpo();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, float longitud_tronco);

float altura;
float anchura;

protected:
_rotacion  cuello;
_cubo  tronco;
};

//************************************************************************

class _cabeza: public _triangulos3D
{
public:
       _cabeza();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;

protected:
_cubo  boca;
_rotacion cabeza;
_rotacion ojoI;
_rotacion ojoD;
_rotacion nariz;
_rotacion peloD;
_rotacion peloI;
_rotacion pelo;
};

//************************************************************************

class _brazo: public _triangulos3D
{
public:
       _brazo();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, float giro_brazos);

protected:
_rotacion antebrazo;
_rotacion brazo;
_rotacion codo;
_rotacion hombro;
_rotacion mano;
};

//************************************************************************

class _pierna: public _triangulos3D
{
public:
       _pierna();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, float giro_piernas);

protected:
_rotacion muslo;
_rotacion gemelo;
_rotacion rodilla;
_rotacion cadera;
_cubo pie;
};

//************************************************************************

class _robo_payaso: public _triangulos3D
{
public:
       _robo_payaso();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float longitud_tronco;
float longitud_tronco_min;
float longitud_tronco_max;

float giro_brazos;
float giro_brazos_max;
float giro_brazos_min;

float giro_piernas;
float giro_piernas_max;
float giro_piernas_min;


protected:
_cabeza cabeza;
_cuerpo tronco;
_brazo  brazoD;
_brazo  brazoI;
_pierna piernaD;
_pierna piernaI;
};