//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B5.h"
#include "CImg.h"


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
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 
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
  ambiente_difusa = {0.022, 0.17, 0.02, 1.0};
  especular = {0.63, 0.73, 0.63, 1.0};
  brillo = 10;
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);
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
	if (i%2==0) glColor3f(r1,g1,b1);
	else glColor3f(r2,g2,b2);
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
  	case SOLID_ILLUMINATED_FLAT: draw_iluminacion_plana(); break;
  	case SOLID_ILLUMINATED_GOURAUD: draw_iluminacion_suave(); break;
	}
}
//*************************************************************************
// Calcular normales caras
//*************************************************************************

void _triangulos3D::calcular_normales_caras()
{
    normales_caras.resize(caras.size());

    for(unsigned long i=0; i<caras.size(); ++i)
    {
        _vertex3f a1 = vertices[caras[i]._1] - vertices[caras[i]._0];
        _vertex3f a2 = vertices[caras[i]._2] - vertices[caras[i]._0];
        _vertex3f n = a1.cross_product(a2);

        normales_caras[i] = _vertex3f(n.x, n.y, n.z);
        normales_caras[i].normalize();
    }

}

//*************************************************************************
// Calcular normales caras
//*************************************************************************
void _triangulos3D::calcular_normales_vertices()
{
    calcular_normales_caras();

    normales_vertices.resize(vertices.size());

    for(unsigned long i=0; i<vertices.size(); ++i)
        {normales_vertices[i].x=0;
         normales_vertices[i].y=0;
         normales_vertices[i].z=0;
       }

    for(unsigned long i=0; i<caras.size(); ++i)
    {
        normales_vertices[caras[i]._0] += normales_caras[i];
        normales_vertices[caras[i]._1] += normales_caras[i];
        normales_vertices[caras[i]._2] += normales_caras[i];
    }
    for(unsigned long i=0; i<vertices.size(); ++i)
        normales_vertices[i].normalize();

}

//*************************************************************************
// Iluminación plana
//*************************************************************************

void _triangulos3D::draw_iluminacion_plana()
{
    if(normales_caras.empty())
        calcular_normales_caras();

    //glEnable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);


    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat *) &brillo);


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    for(int i=0; i<caras.size(); ++i)
    {
        glNormal3f(normales_caras[i].x, normales_caras[i].y, normales_caras[i].z);
        glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y, vertices[caras[i]._0].z);
        glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y, vertices[caras[i]._1].z);
        glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y, vertices[caras[i]._2].z);
    }

    glEnd();
    glDisable(GL_LIGHTING);
    //glDisable(GL_CULL_FACE);
}

//*************************************************************************
// Iluminación suave
//*************************************************************************

void _triangulos3D::draw_iluminacion_suave()
{

    if(normales_vertices.empty())
        calcular_normales_vertices();

    //glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);


    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat *) &brillo);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    for(int i=0; i<caras.size(); ++i)
    {
        glNormal3f(normales_vertices[caras[i]._0].x, normales_vertices[caras[i]._0].y, normales_vertices[caras[i]._0].z);
        glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y, vertices[caras[i]._0].z);
        glNormal3f(normales_vertices[caras[i]._1].x, normales_vertices[caras[i]._1].y, normales_vertices[caras[i]._1].z);
        glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y, vertices[caras[i]._1].z);
        glNormal3f(normales_vertices[caras[i]._2].x, normales_vertices[caras[i]._2].y, normales_vertices[caras[i]._2].z);
        glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y, vertices[caras[i]._2].z);
    }

    glEnd();
    glDisable(GL_LIGHTING);
    //glDisable(GL_CULL_FACE);
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void _triangulos3D::draw_seleccion_color(int r, int g, int b){
  int i;

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glColor3ub(r,g,b);
  glBegin(GL_TRIANGLES);

  for (i=0;i<caras.size();i++){
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();
}

void _triangulos3D::draw_seleccion_color_cara(int r, int g, int b){
  int i;
  int inc =0;

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glColor3ub(r,g,b);
  glBegin(GL_TRIANGLES);

  for (i=0;i<caras.size();i++){
    glColor3ub(r+inc,g+inc,b+inc);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    inc++;
  }
  glEnd();
}

void _triangulos3D::drawPick(float r1, float g1, float b1, float r2, float g2, float b2, bool cara_selec_ico[20])
{
  int i;

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);

  for (i=0;i<caras.size();i++){
    if(!cara_selec_ico[i])glColor3f(r1,g1,b1);
    else glColor3f(r2,g2,b2);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// Clase luz
//*************************************************************************
_luz::_luz(){}
void _luz::encender(GLenum indice)
{
    this->indice = indice;
    glEnable(indice);
    if(indice != GL_LIGHT0){
      GLfloat light_ambient[] = {0.2, 0.2, 0.2, 0.2};
      GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};//{1.0, 0.0, 0.0, 1.0};
      GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};//{1.0, 0.0, 0.0, 1.0};
      GLfloat light_position[] = {this->x, this->y, this->z, 1.0};
      glLightfv(indice, GL_AMBIENT, light_ambient);
      glLightfv(indice, GL_DIFFUSE, light_diffuse);
      glLightfv(indice, GL_SPECULAR, light_specular);
      glLightfv(indice, GL_POSITION, light_position);
    }
}
void _luz::transformar(){
  GLfloat light_position[] = {x, y, z, 1.0};
  if (alpha > 360)
      alpha -= 360;
  if (alpha < -360)
      alpha += 360;

  if (beta > 360)
      beta -= 360;
  if (beta < -360)
      beta += 360;

  glPushMatrix();
      //glTranslatef(x,y,z);
      glRotatef(alpha,0,1,0);
      glRotatef(beta,1,0,0);
      glLightfv(this->indice, GL_POSITION, light_position);
  glPopMatrix();
}

//*************************************************************************
// Clase textura
//*************************************************************************
_textura::_textura()
{
    logo.load("./unnamed.jpg");


    // empaquetamos bien los datos
    for (long y = 0; y < logo.height(); y ++)
        for (long x = 0; x < logo.width(); x ++)
        {
          unsigned char *r = logo.data(x, y, 0, 0);
          unsigned char *g = logo.data(x, y, 0, 1);
          unsigned char *b = logo.data(x, y, 0, 2);
          data.push_back(*r);
          data.push_back(*g);
          data.push_back(*b);
        }

    glGenTextures(1, &textura_id);
}

//*************************************************************************
// Textura del tablero
//*************************************************************************
void _textura::tablero_textura(float tam, int n, int m)
{

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textura_id);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, logo.width(), logo.height(),
        0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);

    glColor3f(1,1,1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glPushMatrix();

  glTranslatef(-tam/2, -tam/2, 0.0);

    for(int i=0; i<n; ++i)
    {

        for(int j=0; j<m; ++j)
        {

      glBegin(GL_QUADS);

      glTexCoord2d(0.0,1.0);
            glVertex3f(j*tam/(1.0*n),i*tam/(1.0*n),0.0);

      glTexCoord2f(1.0, 1.0);
            glVertex3f((j+1)*tam/(1.0*n),i*tam/(1.0*n),0.0);

       glTexCoord2f(1.0, 0.0);
            glVertex3f((j+1)*tam/(1.0*n),(i+1.0)*tam/(1.0*n),0.0);

      glTexCoord2f(0.0, 0.0);
            glVertex3f(j*tam/(1.0*n),(i+1.0)*tam/(1.0*n),0.0);

            glEnd();

        }
    }
glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;  
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

    for (int i = 1; i < rev; i++){
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

//if (n_ver<3 || n_car<1){
//	printf("Error %d %d\n",__FILE__,__LINE__);
//	exit(-1);
//	}

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

void _rotacion::parametros(vector<_vertex3f> perfil, int num, float eje_en_y)
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
  if (eje_en_y != 0.0){
	 vertices.push_back( _vertex3f(0.0, eje_en_y, 0.0) );
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
	  if (eje_en_y != 0.0){
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

//************************************************************************
// objeto articulado: _robo_payaso
//************************************************************************

_cuerpo::_cuerpo()
{
// perfil para un cilindro, el cuello
vector<_vertex3f> perfil;
_vertex3f aux;

aux.x=0.107;aux.y=-0.5;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.107;aux.y=0.5;aux.z=0.0;
perfil.push_back(aux);

cuello.parametros(perfil,12,0.0);
altura=2.5;
anchura=1.5;
};

void _cuerpo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, float longitud_tronco)
{
glPushMatrix();
glScalef(anchura,altura+longitud_tronco,0.5);
tronco.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.0,(altura+longitud_tronco)/1.5,0.0);
glScalef(1.0,altura/2-longitud_tronco,1.0);
cuello.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

void _cuerpo::draw_seleccion_color(int r, int g, int b, float longitud_tronco)
{
glPushMatrix();
glScalef(anchura,altura+longitud_tronco,0.5);
tronco.draw_seleccion_color(r,g,b);
glPopMatrix();

glPushMatrix();
glTranslatef(0.0,(altura+longitud_tronco)/1.5,0.0);
glScalef(1.0,altura/2-longitud_tronco,1.0);
cuello.draw_seleccion_color(r,g,b);
glPopMatrix();
}

//************************************************************************

_cabeza::_cabeza()
{
	vector<_vertex3f> perfil;
	_vertex3f aux;
	altura=0.5;

	aux.x=0.1;aux.y=-0.2;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0.1;aux.y=0.2;aux.z=0.0;
	perfil.push_back(aux);

	_esfera nariz_perfil(0.15,10);
	_esfera peloDyI_perfil(0.5, 25);
	_esfera pelo_perfil(0.75, 25);

	cabeza.parametros(perfil,15,0.0);
	ojoD.parametros(perfil,12,0.0);
	ojoI.parametros(perfil,12,0.0);
	nariz.parametros(nariz_perfil.perfil,10,0.0);
	peloD.parametros(peloDyI_perfil.perfil,25,0.0);
	peloI.parametros(peloDyI_perfil.perfil,25,0.0);
	pelo.parametros(pelo_perfil.perfil,25,0.0);
};

void _cabeza::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glTranslatef(0,0.08,0);
glScalef(5.0,3.2,5.0);
cabeza.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0,-0.3,0.3);
glScalef(0.3,0.1,0.5);
boca.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.2,0.35,0.3);
glRotatef(90.0,1,0,0);
ojoD.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.2,0.35,0.3);
glRotatef(90.0,1,0,0);
ojoI.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0,0.1,0.55);
nariz.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,0.8,0);
peloD.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.5,0.8,0);
peloI.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0,0.8,-0.4);
pelo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

void _cabeza::draw_seleccion_color(int r, int g, int b)
{
glPushMatrix();
glTranslatef(0,0.08,0);
glScalef(5.0,3.2,5.0);
cabeza.draw_seleccion_color(r,g,b);
glPopMatrix();

glPushMatrix();
glTranslatef(0,-0.3,0.3);
glScalef(0.3,0.1,0.5);
boca.draw_seleccion_color(r,g,b);
glPopMatrix();

glPushMatrix();
glTranslatef(0.2,0.35,0.3);
glRotatef(90.0,1,0,0);
ojoD.draw_seleccion_color(r,g,b);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.2,0.35,0.3);
glRotatef(90.0,1,0,0);
ojoI.draw_seleccion_color(r,g,b);
glPopMatrix();

glPushMatrix();
glTranslatef(0,0.1,0.55);
nariz.draw_seleccion_color(r,g,b);
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,0.8,0);
peloD.draw_seleccion_color(r,g,b);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.5,0.8,0);
peloI.draw_seleccion_color(r,g,b);
glPopMatrix();

glPushMatrix();
glTranslatef(0,0.8,-0.4);
pelo.draw_seleccion_color(r,g,b);
glPopMatrix();
}

//************************************************************************

_brazo::_brazo()
{
	vector<_vertex3f> perfil;
	_vertex3f aux;

	aux.x=0.1;aux.y=-0.4;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0.1;aux.y=0.4;aux.z=0.0;
	perfil.push_back(aux);

	_esfera hombro_perfil(0.15,10);
	_esfera codo_perfil(0.12,10);
	_esfera mano_perfil(0.15,10);

	antebrazo.parametros(perfil,12,0.0);
	brazo.parametros(perfil,12,0.0);
	hombro.parametros(hombro_perfil.perfil,10,0.0);
	codo.parametros(codo_perfil.perfil,10,0.0);
	mano.parametros(mano_perfil.perfil,10,0.0);

};

void _brazo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, float giro_brazos)
{

hombro.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

glPushMatrix();
glTranslatef(0.45,0,0);
glRotatef(90.0,0,0,1);
brazo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.905,0,0);
codo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glRotatef(-giro_brazos*1.85,0,0,1);

	glPushMatrix();
	glTranslatef(0.4,0,0);
	glRotatef(90.0,0,0,1);
	antebrazo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.855/2,0,0);
	mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
glPopMatrix();
}

void _brazo::draw_seleccion_color(int r, int g, int b, float giro_brazos)
{

hombro.draw_seleccion_color(r,g,b);

glPushMatrix();
glTranslatef(0.45,0,0);
glRotatef(90.0,0,0,1);
brazo.draw_seleccion_color(r,g,b);
glPopMatrix();

glPushMatrix();
glTranslatef(0.905,0,0);
codo.draw_seleccion_color(r,g,b);
glRotatef(-giro_brazos*1.85,0,0,1);

  glPushMatrix();
  glTranslatef(0.4,0,0);
  glRotatef(90.0,0,0,1);
  antebrazo.draw_seleccion_color(r,g,b);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.855/2,0,0);
  mano.draw_seleccion_color(r,g,b);
  glPopMatrix();
glPopMatrix();
}

//************************************************************************

_pierna::_pierna()
{
	vector<_vertex3f> perfil;
	_vertex3f aux;

	aux.x=0.1;aux.y=-0.4;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0.1;aux.y=0.4;aux.z=0.0;
	perfil.push_back(aux);

	_esfera cadera_perfil(0.15,10);
	_esfera rodilla_perfil(0.12,10);

	gemelo.parametros(perfil,12,0.0);
	muslo.parametros(perfil,12,0.0);
	cadera.parametros(cadera_perfil.perfil,10,0.0);
	rodilla.parametros(rodilla_perfil.perfil,10,0.0);

};

void _pierna::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, float giro_piernas)
{

cadera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

glPushMatrix();
glTranslatef(0.45,0,0);
glRotatef(90.0,0,0,1);
muslo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.905,0,0);
rodilla.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glRotatef(-giro_piernas,0,0,1);

	glPushMatrix();
	glTranslatef(0.4,0,0);
	glRotatef(90.0,0,0,1);
	gemelo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.855/2,0.15,0);
	glScalef(0.2,0.5,0.35);
	pie.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
glPopMatrix();
}

void _pierna::draw_seleccion_color(int r, int g, int b, float giro_piernas)
{

cadera.draw_seleccion_color(r,g,b);

glPushMatrix();
glTranslatef(0.45,0,0);
glRotatef(90.0,0,0,1);
muslo.draw_seleccion_color(r,g,b);
glPopMatrix();

glPushMatrix();
glTranslatef(0.905,0,0);
rodilla.draw_seleccion_color(r,g,b);
glRotatef(-giro_piernas,0,0,1);

  glPushMatrix();
  glTranslatef(0.4,0,0);
  glRotatef(90.0,0,0,1);
  gemelo.draw_seleccion_color(r,g,b);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.855/2,0.15,0);
  glScalef(0.2,0.5,0.35);
  pie.draw_seleccion_color(r,g,b);
  glPopMatrix();
glPopMatrix();
}

//************************************************************************

_robo_payaso::_robo_payaso()
{
giro_brazos=0.0;
giro_brazos_max=95.0;
giro_brazos_min=0.0;

giro_piernas=0.0;
giro_piernas_max=95.0;
giro_piernas_min=0.0;

longitud_tronco=0.0;
longitud_tronco_min=-0.8;
longitud_tronco_max=0.8;
};

/*void _robo_payaso::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

tronco.draw(modo, r1, g1, b1, r2, g2, b2, grosor, longitud_tronco);

glPushMatrix();
glTranslatef(0.0,(tronco.altura+cabeza.altura-longitud_tronco)/1.4,0.0);
cabeza.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(tronco.anchura/2.0,(tronco.altura+longitud_tronco)/2.1,0.0);
glRotatef(giro_brazos,0,0,1);
glRotatef(275.0,0,0,1);
glScalef(1.5,1.5,1.5);
brazoD.draw(modo, r1, g1, b1, r2, g2, b2, grosor, giro_brazos);
glPopMatrix();

glPushMatrix();
glTranslatef(-tronco.anchura/2.0,(tronco.altura+longitud_tronco)/2.1,0.0);
glRotatef(360-giro_brazos,0,0,1);
glRotatef(180.0,0,1,0);
glRotatef(275.0,0,0,1);
glScalef(1.5,1.5,1.5);
brazoI.draw(modo, r1, g1, b1, r2, g2, b2, grosor, giro_brazos);
glPopMatrix();

glPushMatrix();
glTranslatef(tronco.anchura/2.0,(-tronco.altura-longitud_tronco)/2.0,0.0);
glRotatef(giro_piernas,0,0,1);
glRotatef(-90.0,0,0,1);
glScalef(1.5,1.5,1.5);
piernaD.draw(modo, r1, g1, b1, r2, g2, b2, grosor, giro_piernas);
glPopMatrix();

glPushMatrix();
glTranslatef(-tronco.anchura/2.0,(-tronco.altura-longitud_tronco)/2.0,0.0);
glRotatef(360-giro_piernas,0,0,1);
glRotatef(90.0,0,0,1);
glRotatef(180.0,0,1,0);
glScalef(1.5,1.5,1.5);
piernaI.draw(modo, r1, g1, b1, r2, g2, b2, grosor, giro_piernas);
glPopMatrix();
};*/

void _robo_payaso::draw_seleccion(int r, int g, int b)
{
  int inc = 20;
  tronco.draw_seleccion_color(r,g,b, longitud_tronco);

  glPushMatrix();
  glTranslatef(0.0,(tronco.altura+cabeza.altura-longitud_tronco)/1.4,0.0);
  cabeza.draw_seleccion_color(r+inc,g+inc,b+inc);
  glPopMatrix();
  inc+=20;

  glPushMatrix();
  glTranslatef(tronco.anchura/2.0,(tronco.altura+longitud_tronco)/2.1,0.0);
  glRotatef(giro_brazos,0,0,1);
  glRotatef(275.0,0,0,1);
  glScalef(1.5,1.5,1.5);
  brazoD.draw_seleccion_color(r+inc,g+inc,b+inc, giro_brazos);
  glPopMatrix();
  inc+=20;

  glPushMatrix();
  glTranslatef(-tronco.anchura/2.0,(tronco.altura+longitud_tronco)/2.1,0.0);
  glRotatef(360-giro_brazos,0,0,1);
  glRotatef(180.0,0,1,0);
  glRotatef(275.0,0,0,1);
  glScalef(1.5,1.5,1.5);
  brazoI.draw_seleccion_color(r+inc,g+inc,b+inc, giro_brazos);
  glPopMatrix();
  inc+=20;

  glPushMatrix();
  glTranslatef(tronco.anchura/2.0,(-tronco.altura-longitud_tronco)/2.0,0.0);
  glRotatef(giro_piernas,0,0,1);
  glRotatef(-90.0,0,0,1);
  glScalef(1.5,1.5,1.5);
  piernaD.draw_seleccion_color(r+inc,g+inc,b+inc, giro_piernas);
  glPopMatrix();
  inc+=20;

  glPushMatrix();
  glTranslatef(-tronco.anchura/2.0,(-tronco.altura-longitud_tronco)/2.0,0.0);
  glRotatef(360-giro_piernas,0,0,1);
  glRotatef(90.0,0,0,1);
  glRotatef(180.0,0,1,0);
  glScalef(1.5,1.5,1.5);
  piernaI.draw_seleccion_color(r+inc,g+inc,b+inc, giro_piernas);
  glPopMatrix();
};

void _robo_payaso::drawPick(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, bool seleccion[6])
{

  glPushMatrix();
  glTranslatef(0.0,(tronco.altura+cabeza.altura-longitud_tronco)/1.4,0.0);
  if(!seleccion[1]) cabeza.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
      else cabeza.draw(modo, 0.5, 0.2, 0.8, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(tronco.anchura/2.0,(tronco.altura+longitud_tronco)/2.1,0.0);
  glRotatef(giro_brazos,0,0,1);
  glRotatef(275.0,0,0,1);
  glScalef(1.5,1.5,1.5);

  if(!seleccion[2]) brazoD.draw(modo, r1, g1, b1, r2, g2, b2, grosor, giro_brazos);
      else brazoD.draw(modo, 0.5, 0.2, 0.8, r2, g2, b2, grosor, giro_brazos);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-tronco.anchura/2.0,(tronco.altura+longitud_tronco)/2.1,0.0);
  glRotatef(360-giro_brazos,0,0,1);
  glRotatef(180.0,0,1,0);
  glRotatef(275.0,0,0,1);
  glScalef(1.5,1.5,1.5);

  if(!seleccion[3]) brazoI.draw(modo, r1, g1, b1, r2, g2, b2, grosor, giro_brazos);
      else brazoI.draw(modo, 0.5, 0.2, 0.8, r2, g2, b2, grosor, giro_brazos);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(tronco.anchura/2.0,(-tronco.altura-longitud_tronco)/2.0,0.0);
  glRotatef(giro_piernas,0,0,1);
  glRotatef(-90.0,0,0,1);
  glScalef(1.5,1.5,1.5);

  if(!seleccion[4]) piernaD.draw(modo, r1, g1, b1, r2, g2, b2, grosor, giro_piernas);
      else piernaD.draw(modo, 0.5, 0.2, 0.8, r2, g2, b2, grosor, giro_piernas);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-tronco.anchura/2.0,(-tronco.altura-longitud_tronco)/2.0,0.0);
  glRotatef(360-giro_piernas,0,0,1);
  glRotatef(90.0,0,0,1);
  glRotatef(180.0,0,1,0);
  glScalef(1.5,1.5,1.5);

  if(!seleccion[5]) piernaI.draw(modo, r1, g1, b1, r2, g2, b2, grosor, giro_piernas);
      else piernaI.draw(modo, 0.5, 0.2, 0.8, r2, g2, b2, grosor, giro_piernas);
  glPopMatrix();

  if(!seleccion[0]) tronco.draw(modo, r1, g1, b1, r2, g2, b2, grosor, longitud_tronco);
      else tronco.draw(modo, 0.5, 0.2, 0.8, r2, g2, b2, grosor, longitud_tronco);
};