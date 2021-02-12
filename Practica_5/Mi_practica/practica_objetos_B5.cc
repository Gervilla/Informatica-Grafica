//**************************************************************************
// Práctica 5 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B5.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, ICOSAEDRO, ESFERA, OBJETO_PLY, ROTACION, CONO, CILINDRO, ARTICULADO, TEXTURA, ICOSAEDRO_S} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;

int estadoRaton[3], xc, yc;
bool seleccion[6] = {0,0,0,0,0,0};
bool cara_selec_ico[20] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void pick_color(int x, int y);
//@@@
// objetos
_piramide piramide(0.85,1.3);
_cubo cubo(0.5);
_icosaedro icosaedro(0.53, 0.85);
_objeto_ply  ply; 
_esfera esfera_perfil(1.0, 45);
_rotacion rotacion;
_rotacion esfera;
_rotacion cono;
_rotacion cilindro;
_robo_payaso robo_payaso;
_textura textura;
_luz luz_fija;
_luz luz_dinamica;
bool se_mueve=false;
int sentido_brazos=1;
int sentido_tronco=1;
int sentido_piernas=1;
float velocidad=0.5;
bool ortogonal=0;
float zoom=1.0;
//int Ancho=450, Alto=450;
bool seleccionado=0;

//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

if(ortogonal){
	glOrtho(-2, 2, -2, 2, -100, 100);
	glScalef(zoom,zoom,1.0);
}else
	glFrustum(-Size_x, Size_x, -Size_x, Size_x, Front_plane, Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
//change_projection();@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//glViewport(0,0,Ancho,Alto);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//**************************************************************************

void draw_objects()
{

switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
    case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
    case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
    case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
    case CONO: cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
    case ESFERA: esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
    case ICOSAEDRO: icosaedro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
    case ICOSAEDRO_S: icosaedro.drawPick(1.0,0.0,0.0,0.0,1.0,0.0,cara_selec_ico);break;
    //case ARTICULADO: robo_payaso.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2);break;
    case ARTICULADO: robo_payaso.drawPick(modo,0.5,0.7,0.2,0.3,0.6,0.3,2,seleccion);break;
	case TEXTURA: textura.tablero_textura(4,4,4);break;
}
}

void draw_objects_seleccion(){
	if(t_objeto == ARTICULADO)
	  robo_payaso.draw_seleccion(100,100,100);
	if(t_objeto == ICOSAEDRO_S)
		icosaedro.draw_seleccion_color_cara(0,0,0);
}

//**************************************************************************
//
//**************************************************************************

void draw(void)
{

glDrawBuffer(GL_FRONT);
clean_window();
change_observer();
draw_axis();
draw_objects();
//glutSwapBuffers();
glDrawBuffer(GL_BACK);
clean_window();
change_observer();
draw_objects_seleccion();
glFlush();

luz_dinamica.transformar();
luz_fija.transformar();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_CHESS;break;
	case '5':modo=PUNTICOS;break;
	case '6':modo=RANDOM;break;
	case '7':modo=FIESTA;break;
	case '8':modo=SOLID_ILLUMINATED_FLAT;break;
	case '9':modo=SOLID_ILLUMINATED_GOURAUD;break;
	case '0':ortogonal=!ortogonal;change_projection();break;
        case 'P':t_objeto=PIRAMIDE;break;
        case 'C':t_objeto=CUBO;break;
        case 'O':t_objeto=OBJETO_PLY;break;	
        case 'R':t_objeto=ROTACION;break;
        case 'Z':t_objeto=CILINDRO;break;
        case 'K':t_objeto=CONO;break;
        case 'E':t_objeto=ESFERA;break;
        case 'I':t_objeto=ICOSAEDRO;break;
        case 'S':t_objeto=ICOSAEDRO_S;break;
        case 'A':t_objeto=ARTICULADO;break;
        case 'T':t_objeto=TEXTURA;break;
        case '*':velocidad+=0.1;break;
        case '/':velocidad-=0.1;break;
        case '+':zoom*=1.1;change_projection();break;
		case '-':zoom*=0.9;change_projection();break;
	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	case GLUT_KEY_F1:luz_dinamica.alpha+=5;break;
	case GLUT_KEY_F2:luz_dinamica.alpha-=5;break;
	case GLUT_KEY_F3:luz_dinamica.beta+=5;break;
	case GLUT_KEY_F4:luz_dinamica.beta-=5;break;
    case GLUT_KEY_F5:se_mueve =! se_mueve;break;
	}
glutPostRedisplay();
}

void clickRaton( int boton, int estado, int x, int y )
{
if(boton== GLUT_RIGHT_BUTTON) {
   if( estado == GLUT_DOWN) {
      estadoRaton[2] = 1;
      xc=x;
      yc=y;
     }
   else estadoRaton[2] = 1;
   }
if(boton== GLUT_LEFT_BUTTON) {
  if( estado == GLUT_DOWN) {
      estadoRaton[2] = 2;
      xc=x;
      yc=y;
      pick_color(xc, yc);
    }
  }
}

void getCamara (GLfloat *x, GLfloat *y)
{
*x=Observer_angle_x;
*y=Observer_angle_y;
}

void setCamara (GLfloat x, GLfloat y)
{
Observer_angle_x=x;
Observer_angle_y=y;
}

void RatonMovido( int x, int y )
{
float x0, y0, xn, yn;
if(estadoRaton[2]==1)
    {getCamara(&x0,&y0);
     yn=y0+(x-xc);
     xn=x0+(y-yc);
     setCamara(xn,yn);
     xc=x;
     yc=y;
     glutPostRedisplay();
    }
}

void procesar_color(unsigned char color[3])
{
 int i;

	if(t_objeto == ARTICULADO){
		switch (color[0])
	       {case 100:
	                  if (seleccion[0]==false)
	                       {seleccion[0]=true;
	                        seleccionado=1;
	                       }
	                   else
	                       {seleccion[0]=false;
	                        seleccionado=0;
	                       }
	                   break;
	         case 120:
	                   if (seleccion[1]==false)
	                        {seleccion[1]=true;
	                         seleccionado=1;
	                        }
	                   else
	                        {seleccion[1]=false;
	                         seleccionado=0;
	                        }
	                   break;
	         case 140:
	                   if (seleccion[2]==false)
	                        {seleccion[2]=true;
	                         seleccionado=1;
	                        }
	                   else
	                        {seleccion[2]=false;
	                         seleccionado=0;
	                        }
	                   break;
	         case 160:
	                   if (seleccion[3]==false)
	                        {seleccion[3]=true;
	                         seleccionado=1;
	                        }
	                   else
	                        {seleccion[3]=false;
	                         seleccionado=0;
	                        }
	                   break;
	         case 180:
	                   if (seleccion[4]==false)
	                        {seleccion[4]=true;
	                         seleccionado=1;
	                        }
	                   else
	                        {seleccion[4]=false;
	                         seleccionado=0;
	                        }
	                   break;
	         case 200:
	                   if (seleccion[5]==false)
	                        {seleccion[5]=true;
	                         seleccionado=1;
	                        }
	                   else
	                        {seleccion[5]=false;
	                         seleccionado=0;
	                        }
	                   break;
	                 }
	}else if(t_objeto == ICOSAEDRO_S){
		if(cara_selec_ico[color[0]] == false){
			cara_selec_ico[color[0]] = true;
			seleccionado= 1;
		}else{
			cara_selec_ico[color[0]] = false;
			seleccionado= 0;
		}
	}
 }

void pick_color(int x, int y)
{
GLint viewport[4];
unsigned char pixel[3];

glGetIntegerv(GL_VIEWPORT, viewport);
glReadBuffer(GL_BACK);
glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

procesar_color(pixel);
glutPostRedisplay();
}

//***********************************************************************************

void animacion() {
	if (se_mueve) {
		robo_payaso.giro_brazos+=velocidad*sentido_brazos;
		if(robo_payaso.giro_brazos > robo_payaso.giro_brazos_max){
			robo_payaso.giro_brazos = robo_payaso.giro_brazos_max;
			sentido_brazos*=-1;
		}
		if(robo_payaso.giro_brazos < robo_payaso.giro_brazos_min){
			robo_payaso.giro_brazos = robo_payaso.giro_brazos_min;
			sentido_brazos*=-1;
		}

		robo_payaso.giro_piernas+=velocidad*sentido_piernas;
		if(robo_payaso.giro_piernas > robo_payaso.giro_piernas_max){
			robo_payaso.giro_piernas = robo_payaso.giro_piernas_max;
			sentido_piernas*=-1;
		}
		if(robo_payaso.giro_piernas < robo_payaso.giro_piernas_min){
			robo_payaso.giro_piernas = robo_payaso.giro_piernas_min;
			sentido_piernas*=-1;
		}

		robo_payaso.longitud_tronco+=(velocidad/50)*sentido_tronco;
		if(robo_payaso.longitud_tronco > robo_payaso.longitud_tronco_max){
			robo_payaso.longitud_tronco = robo_payaso.longitud_tronco_max;
			sentido_tronco*=-1;
		}
		if(robo_payaso.longitud_tronco < robo_payaso.longitud_tronco_min){
			robo_payaso.longitud_tronco = robo_payaso.longitud_tronco_min;
			sentido_tronco*=-1;
		}
		draw();
	}
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);

luz_fija.encender(GL_LIGHT0);
luz_dinamica.encender(GL_LIGHT1);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char **argv)
{

// perfil 

vector<_vertex3f> perfil_cilindro;

perfil_cilindro.push_back( _vertex3f(1.0, -1.0, 0.0) );
perfil_cilindro.push_back( _vertex3f(1.0, 1.0, 0.0) );


vector<_vertex3f> perfil_cono;

perfil_cono.push_back( _vertex3f(1.0, -0.5, 0.0) );


cono.parametros(perfil_cono,10,1.5);
cilindro.parametros(perfil_cilindro,10,0.0);
esfera.parametros(esfera_perfil.perfil,20,0.0);
rotacion.rotacion_ply("Plys/arbolito",10,2.0);

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 5");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);
// eventos ratón
glutMouseFunc(clickRaton);
glutMotionFunc(RatonMovido);

glutIdleFunc(animacion);

// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros("Plys/armadillo");

// inicio del bucle de eventos
glutMainLoop();
return 0;
}