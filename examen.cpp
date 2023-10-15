#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

//----------------------------------------VARIABLES-----------------------------------------

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Angulo;

int ancho = 800;
int alto = 800;
int speed = 50;
Angulo anguloBrazo = {0.0f, 0.0f, 0.0f};
Angulo anguloCabina = {0.0f, 0.0f, 0.0f};
bool bajando = false;
int sentido = 0;
int hazPerspectiva = 0;

//-------------------------------------MOVIMIENTO NORIA--------------------------------------

void timerRotation(int value){
    if (sentido)
    {
        if (fmod(anguloBrazo.z, 360.0) > 90 && fmod(anguloBrazo.z, 360.0) < 270) {
            bajando = true;
        } else {
            bajando = false;
        }
        
        if (bajando) {
            anguloBrazo.z += 2.0f;
            anguloCabina.z -= 2.0f;
        } else {
            anguloBrazo.z += 1.0f;
            anguloCabina.z -= 1.0f;
        }
    } else {
        if(anguloBrazo.z < 0) {
            anguloBrazo.z += 360;
        }
        if (fmod(anguloBrazo.z, 360.0) < 90 || fmod(anguloBrazo.z, 360.0) > 270) {
            bajando = true;
        } else {
            bajando = false;
        }
        
        if (bajando) {
            anguloBrazo.z -= 2.0f;
            anguloCabina.z += 2.0f;
        } else {
            anguloBrazo.z -= 1.0f;
            anguloCabina.z += 1.0f;
        }
    }
    glutTimerFunc(speed, timerRotation, value); 
}

//------------------------------------CONTROL CAMARAS--------------------------------------------

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(hazPerspectiva){
        float aspect = (float)width / (float)height;
        gluPerspective(85.0f, (GLfloat)width/(GLfloat)height, 1.0f, 40.0f);
    } else 
        glOrtho(-15, 15, -15, 25, -15, 25);

    glMatrixMode(GL_MODELVIEW);
    ancho = width;
    alto = height;
}

//------------------------------------FIGURAS--------------------------------------

void drawBase() {
    int sides = 30;
    float radius = 6.0f;
    float height = 2.0f;

    glColor3f(0.82f, 0.82f, 0.82f);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= sides; i++) {
        float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(sides);
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glVertex3f(x, -height / 2, z);
        glVertex3f(x, height / 2, z);
    }
    glEnd();
    // Tapas del cilindro
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, -height / 2, 0); // Centro de la base inferior
    for (int i = 0; i <= sides; i++) {
        float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(sides);
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glVertex3f(x, -height / 2, z);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, height / 2, 0); // Centro de la base superior
    for (int i = 0; i <= sides; i++) {
        float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(sides);
        float x = radius * cos(theta);
        float z = radius * sin(theta);

        glVertex3f(x, height / 2, z); // Vertices de la base superior
    }
    glEnd();
}

void drawCube(int type)
{
    glPushMatrix();
    switch (type)
    {
    case 0:
        glColor3f(0.82f, 0.82f, 0.82f);
        glScalef(4.0f, 2.0f, 4.0f);
        break;
    case 1:
        glColor3f(0.84f, 1.0f, 0.62f);
        glScalef(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        glColor3f(0.97f, 0.79f, 0.68f);
        glScalef(8.0f, 2.0f, 2.0f);
        break;
    default:
        break;
    }
    glutSolidCube(1.0f); // Cubo sólido
    glPopMatrix();
}

void drawArm(void) {
    glPushMatrix();
    glTranslatef(4.0f, 0.0f, 0.0f);
    drawCube(2);
    glPopMatrix();
    glTranslatef(8.0f, 0.0f, 0.0f);
}

void drawCabine(void) {
    glTranslatef(-8.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(8.0f, 0.0f, 3.0f);
    drawCube(0);
    glTranslatef(-1.0f, 1.5f, 1.0f);
    drawCube(1);
    glTranslatef( 0.0f, 0.0f, -2.0f);
    drawCube(1);
    glTranslatef( 2.0f, 0.0f, 0.0f);
    drawCube(1);
    glTranslatef( 0.0f, 0.0f, 2.0f);
    drawCube(1);
    glPopMatrix();
}

void drawTriangle() {

    glColor3f(0.60f, 0.68f, 0.9f);

    glBegin(GL_TRIANGLES);

    // Triángulo en la base (Z = 0)
    glVertex3f(-6.0f, 0.0f, -1.0f);
    glVertex3f(6.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 10.0f, -1.0f);


    glVertex3f(-6.0f, 0.0f, 1.0f);
    glVertex3f(6.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 10.0f, 1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-6.0f, 0.0f, -1.0f);
    glVertex3f(-6.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 10.0f, 1.0f);
    glVertex3f(0.0f, 10.0f, -1.0f);

    glVertex3f(6.0f, 0.0f, -1.0f);
    glVertex3f(6.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 10.0f, 1.0f);
    glVertex3f(0.0f, 10.0f, -1.0f);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, -5.0f, -25.0f);

    drawBase();
    glTranslatef(0.0f, 1.0f, 0.0f);
    drawTriangle();
    glTranslatef(0.0f, 10.0f, 2.0f);
    glRotatef(anguloBrazo.z, 0.0f, 0.0f, 1.0f);

    drawArm();
    glRotatef(anguloCabina.z, 0.0f, 0.0f, 1.0f);
    drawCabine();

    glFlush();
    glutSwapBuffers();
}

void init() {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    ancho = 800;
    alto = 800;
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void idle() {
    display();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p':
    case 'P':
        hazPerspectiva = 1;
        reshape(ancho, alto);
        break;
    case 'o':
    case 'O':
        hazPerspectiva = 0;
        reshape(ancho, alto);
        break;
    case 'r':
    case 'R':
        sentido = 1 - sentido;
        break;
    case 27:   // escape
        exit(0);
        break;
    }
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Examen");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(speed, timerRotation, 5);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
