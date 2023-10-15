#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

//----------------------------------------VARIABLES-----------------------------------------

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Angulo;

typedef struct {
    GLfloat r;
    GLfloat g;
    GLfloat b;
} Color;

Color colorpasajeros = {0.84f, 1.0f, 0.62f};

int ancho = 800;
int alto = 800;
int speed = 50;
Angulo anguloBrazo = {0.0f, 0.0f, 0.0f};
Angulo anguloCabina = {0.0f, 0.0f, 0.0f};
Angulo anguloNoria = {0.0f, 0.0f, 0.0f};
bool bajando = false;
int sentido = 0;
int hazPerspectiva = 0;
int parar = 0;
int mouseX, mouseY;
bool altKeyPressed = false;

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
    if (parar) {
        if (fmod(anguloBrazo.z, 360.0) >= 260 && fmod(anguloBrazo.z, 360.0) <= 280)
        {
            speed = 999999999;
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
        glOrtho(-15, 15, -15, 35, -15, 35);

    glMatrixMode(GL_MODELVIEW);
    ancho = width;
    alto = height;
}

//----------------------------------------------FIGURAS----------------------------------------

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
        glColor3f(colorpasajeros.r, colorpasajeros.g, colorpasajeros.b);
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

//------------------------------------------DISPLAY-----------------------------------------------

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -25.0f);

    glRotatef(anguloNoria.x, 1.0f, 0.0f, 0.0f);
    glRotatef(anguloNoria.y, 0.0f, 1.0f, 0.0f);
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


//----------------------------------MENUS----------------------------------

void menu_1(int value)
{
    // Submenú "Visualizacion"
    switch (value)
    {
    case 0:
        colorpasajeros = {0.84f, 1.0f, 0.62f};
        break;
    case 1:
        colorpasajeros = {0.2f, 0.2f, 0.62f};
        break;
    case 2:
        colorpasajeros = {0.62f, 0.2f, 0.2f};
        break;
    case 3:
        colorpasajeros = {0.8f, 0.8f, 0.2f};
        break;
    }
}

void menu_2(int value)
{
    // Submenú "Velocidades"
    switch (value)
    {
    case 0:
        speed = 80;        // Modo lento
        break;
    case 1:
        speed = 50;         // Modo normal
        break;
    case 2:
        speed = 10;         //Modo rapido
        break;
    }
}

//---------------------------------------------INIT Y IDLE---------------------------------------

void init() {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    ancho = 800;
    alto = 800;
    
    int submenu_visualizacion = glutCreateMenu(menu_1);
    glutAddMenuEntry("Verde", 0);
    glutAddMenuEntry("Azul", 1);
    glutAddMenuEntry("Rojo", 2);
    glutAddMenuEntry("Amarillo", 3);

    int submenu_velocidades = glutCreateMenu(menu_2);
    glutAddMenuEntry("Lento", 0);
    glutAddMenuEntry("Normal", 1);
    glutAddMenuEntry("Rapido", 2);

    glutCreateMenu(menu_1);
    glutAddSubMenu("Colores", submenu_visualizacion);
    glutAddSubMenu("Velocidades", submenu_velocidades);
    glutAddMenuEntry("Salir", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void idle() {
    if (altKeyPressed)
    {
        anguloNoria.y = mouseX;
    } else {
        //anguloNoria.x = mouseY;
    }
    
    display();
}

//---------------------------------------MOUSE-----------------------------------------

void mouseMotion(int x, int y) {
    mouseX = x;
    mouseY = y;
}

//--------------------------------------------KEYBOARD--------------------------------------
//
//                                        P-PERSPECTIVA
//                                        O-ORTOGONAL
//
//                                        R-ALTERNAR SENTIDO
//
//                                        S-PARAR NORIA
//
//                                        QA-MOVER CAMARA Y

void keyboard(unsigned char key, int x, int y)
{
    if (glutGetModifiers() & GLUT_ACTIVE_ALT) {
    // La tecla Alt está presionada (ES NECESARIO PRESIONAR ALT + CUALQUIER OTRA TECLA)
        altKeyPressed = true;
    } else {
        altKeyPressed = false;
    }

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
    case 's':
    case 'S':
        parar = 1 - parar;
        break;
    case 'q':
    case 'Q':
        anguloNoria.y++;
        break;
    case 'a':
    case 'A':
        anguloNoria.y--;
        break;
    case 27:   // escape
        exit(0);
        break;
    }
}

//----------------------------------------MAIN-------------------------------------------

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Examen");
    glutPassiveMotionFunc(mouseMotion);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(speed, timerRotation, 5);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
