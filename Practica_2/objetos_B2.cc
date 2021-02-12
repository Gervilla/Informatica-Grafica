//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}

//*************************************************************************
// dibujar puntos de colores
//*************************************************************************

void _puntos3D::draw_punticos(int grosor)
{
int i;
glPointSize(grosor);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glColor3fv((GLfloat *) &colores_vertices[i]);
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{

int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();

}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if (i%2 == 0)
		glColor3f(r1,g1,b1);
	else
		glColor3f(r2,g2,b2);
	
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido con caras de colores aleatorios
//*************************************************************************

void _triangulos3D::draw_solido_colorines()
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glColor3fv((GLfloat *) &colores_caras[i]);
	
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

void _triangulos3D::draw_FIESTA()
{
int i;
asignar_colores_caras();
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glColor3fv((GLfloat *) &colores_caras[i]);
	
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// asignar colores a las caras y vertices
//*************************************************************************

void _triangulos3D::asignar_colores_caras(){
	colores_caras.resize(caras.size());
	for(int i=0; i<caras.size();i++){
		colores_caras[i].r = rand()%255/255.0;
		colores_caras[i].g = rand()%255/255.0;
		colores_caras[i].b = rand()%255/255.0;
	}
}

void _puntos3D::asignar_colores_vertices(){
	colores_vertices.resize(vertices.size());
	for(int i=0; i<vertices.size();i++){
		colores_vertices[i].r = rand()%255/255.0;
		colores_vertices[i].g = rand()%255/255.0;
		colores_vertices[i].b = rand()%255/255.0;
	}
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case PUNTICOS:draw_punticos(grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	case RANDOM:draw_solido_colorines();break;
	case FIESTA:draw_FIESTA();break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices 
vertices.resize(8);
vertices[0].x=-tam; vertices[0].y=-tam; vertices[0].z=-tam;
vertices[1].x=tam; vertices[1].y=-tam; vertices[1].z=-tam;
vertices[2].x=-tam; vertices[2].y=-tam; vertices[2].z=tam;
vertices[3].x=tam; vertices[3].y=-tam; vertices[3].z=tam;
vertices[4].x=-tam; vertices[4].y=tam; vertices[4].z=-tam;
vertices[5].x=tam; vertices[5].y=tam; vertices[5].z=-tam;
vertices[6].x=-tam; vertices[6].y=tam; vertices[6].z=tam;
vertices[7].x=tam; vertices[7].y=tam; vertices[7].z=tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=5;caras[0]._2=1;
caras[1]._0=0;caras[1]._1=4;caras[1]._2=5;
caras[2]._0=1;caras[2]._1=7;caras[2]._2=3;
caras[3]._0=1;caras[3]._1=5;caras[3]._2=7;
caras[4]._0=3;caras[4]._1=6;caras[4]._2=2;
caras[5]._0=3;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=2;caras[6]._1=4;caras[6]._2=0;
caras[7]._0=2;caras[7]._1=6;caras[7]._2=4;
caras[8]._0=1;caras[8]._1=2;caras[8]._2=0;
caras[9]._0=1;caras[9]._1=3;caras[9]._2=2;
caras[10]._0=7;caras[10]._1=4;caras[10]._2=6;
caras[11]._0=7;caras[11]._1=5;caras[11]._2=4;
asignar_colores_vertices();
asignar_colores_caras();
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
asignar_colores_vertices();
asignar_colores_caras();
}

_icosaedro::_icosaedro(float tam, float tam1)
{
//vertices 
vertices.resize(12);
vertices[0].x=-tam; vertices[0].y=0.0; vertices[0].z=tam1;
vertices[1].x=tam; vertices[1].y=0.0; vertices[1].z=tam1;
vertices[2].x=-tam; vertices[2].y=0.0; vertices[2].z=-tam1;
vertices[3].x=tam; vertices[3].y=0.0; vertices[3].z=-tam1;

vertices[4].x=0.0; vertices[4].y=tam1; vertices[4].z=tam;
vertices[5].x=0.0; vertices[5].y=tam1; vertices[5].z=-tam;
vertices[6].x=0.0; vertices[6].y=-tam1; vertices[6].z=tam;
vertices[7].x=0.0; vertices[7].y=-tam1; vertices[7].z=-tam;

vertices[8].x=tam1; vertices[8].y=tam; vertices[8].z=0.0;
vertices[9].x=-tam1; vertices[9].y=tam; vertices[9].z=0.0;
vertices[10].x=tam1; vertices[10].y=-tam; vertices[10].z=0.0;
vertices[11].x=-tam1; vertices[11].y=-tam; vertices[11].z=0.0;

// triangulos
caras.resize(20);
caras[0]._0=1;caras[0]._1=4;caras[0]._2=0;
caras[1]._0=4;caras[1]._1=9;caras[1]._2=0;
caras[2]._0=4;caras[2]._1=5;caras[2]._2=9;
caras[3]._0=8;caras[3]._1=5;caras[3]._2=4;
caras[4]._0=1;caras[4]._1=8;caras[4]._2=4;
caras[5]._0=1;caras[5]._1=10;caras[5]._2=8;
caras[6]._0=10;caras[6]._1=3;caras[6]._2=8;
caras[7]._0=8;caras[7]._1=3;caras[7]._2=5;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=5;
caras[9]._0=3;caras[9]._1=7;caras[9]._2=2;
caras[10]._0=3;caras[10]._1=10;caras[10]._2=7;
caras[11]._0=10;caras[11]._1=6;caras[11]._2=7;
caras[12]._0=6;caras[12]._1=11;caras[12]._2=7;
caras[13]._0=6;caras[13]._1=0;caras[13]._2=11;
caras[14]._0=6;caras[14]._1=1;caras[14]._2=0;
caras[15]._0=10;caras[15]._1=1;caras[15]._2=6;
caras[16]._0=11;caras[16]._1=0;caras[16]._2=9;
caras[17]._0=2;caras[17]._1=11;caras[17]._2=9;
caras[18]._0=5;caras[18]._1=2;caras[18]._2=9;
caras[19]._0=11;caras[19]._1=2;caras[19]._2=7;
asignar_colores_vertices();
asignar_colores_caras();
}

//*************************************************************************
// clase esfera
//*************************************************************************

_esfera::_esfera(float radio, int rev){
    float angulo, x, y;

    for (int i = 0; i <= rev; i++){
        angulo = i*(180/rev);

        angulo += 270;        

        x = radio * cos(angulo * M_PI/180);
        y = radio * sin(angulo * M_PI/180);

        perfil.push_back( _vertex3f(x, y, 0.0) );
    }
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);
caras.resize(n_car);

int i,j;
j=0;
for(i=0; i<vertices.size()*3;i+=3, j++){
	vertices[j].x = ver_ply[i];
	vertices[j].y = ver_ply[i+1];
	vertices[j].z = ver_ply[i+2];
}

j=0;
for(i=0; i<caras.size()*3;i+=3,j++){
	caras[j]._0 = car_ply[i];
	caras[j]._1 = car_ply[i+1];
	caras[j]._2 = car_ply[i+2];
}

asignar_colores_vertices();
asignar_colores_caras();

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{
}

void _rotacion::rotacion_ply(char *archivo, int num, float eje){

	vector<float> ver_ply ;
	vector<int>   car_ply ;
	vector<_vertex3f> ply_rot;

	_file_ply::read(archivo, ver_ply, car_ply);
	ply_rot.resize(ver_ply.size()/3);
	int tam=ver_ply.size();

	int i,j;
	for(i=0,j=0; i<tam;i+=3,j++) {
		ply_rot[j].x = ver_ply[i];
		ply_rot[j].y = ver_ply[i+1];
		ply_rot[j].z = ver_ply[i+2];
	}

	parametros(ply_rot,num,eje);
}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, float eje)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértices
num_aux=perfil.size();
vertices.resize(num_aux*num);

for (j=0;j<num;j++) {
	for (i=0;i<num_aux;i++) {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }
  if (eje != 0.0){
	vertices.push_back( _vertex3f(0.0, eje, 0.0) );
  }
// tratamiento de las caras 

for (j=0;j<num;j++) {
	for (i=0;i<num_aux-1;i++) {
      cara_aux._0 = i + ((j+1)%num)*num_aux;
      cara_aux._1 = i + 1 +((j+1)%num)*num_aux;
      cara_aux._2 = i + 1 + j*num_aux;
      caras.push_back(cara_aux);

      cara_aux._0 = i + 1 + j*num_aux;
      cara_aux._1 = i + j*num_aux;
      cara_aux._2 = i + ((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }
    
 // tapa inferior
	if (fabs(perfil[0].x)>0.0) {
	  vertice_aux.x=0.0;
	  if (eje != 0.0){
		vertice_aux.y=perfil[num_aux-1].y;
  	  }
	  else{
	  	vertice_aux.y=perfil[0].y;
	  }
	  vertice_aux.z=0.0;
	  vertices.push_back(vertice_aux);

	  cara_aux._0=num*num_aux;

	  for(i=0; i<num;i++){
	   cara_aux._1=i*num_aux;
	   cara_aux._2=((i+1)%num)*num_aux;
	   caras.push_back(cara_aux);

	  }
	}
 
 // tapa superior
 	if (fabs(perfil[0].x)>0.0) {
	  vertice_aux.x=0.0;
	  vertice_aux.y=perfil[num_aux-1].y;
	  vertice_aux.z=0.0;
	  vertices.push_back(vertice_aux);

	  cara_aux._0=num*num_aux + 1;

	  for(i=0; i<num;i++){
	   cara_aux._1=(i + 1) * num_aux - 1;
	   cara_aux._2=((i+1)%num)*num_aux + num_aux - 1;
	   caras.push_back(cara_aux);

	  }
	}
	asignar_colores_vertices();
	asignar_colores_caras();
}
