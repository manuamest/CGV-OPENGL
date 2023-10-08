#include <stdio.h>
#include <GL/glut.h>

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Angulo;

Angulo angulos[] = {
    {0.0f, 0.0f, 0.0f}, // Brazo Izquierdo
    {0.0f, 0.0f, 0.0f}, // Antebrazo Izquierdo
    {0.0f, 0.0f, 0.0f}, // Brazo Derecho
    {0.0f, 0.0f, 0.0f}, // Antebrazo Derecho
    // ... otras extremidades ...
};

//--------------------------VARIABLES--------------------------------

GLint ancho = 800;
GLint alto = 800;
Angulo anguloBrazoIzquierdo = {0.0f, 0.0f, 0.0f};
Angulo anguloAntebrazoIzquierdo = {0.0f, 0.0f, 0.0f};
Angulo anguloBrazoDerecho = {0.0f, 0.0f, 0.0f};
Angulo anguloAntebrazoDerecho = {0.0f, 0.0f, 0.0f};
Angulo anguloMusloIzquierdo = {0.0f, 0.0f, 0.0f};
Angulo anguloGemeloIzquierdo = {0.0f, 0.0f, 0.0f};
Angulo anguloMusloDerecho = {0.0f, 0.0f, 0.0f};
Angulo anguloGemeloDerecho = {0.0f, 0.0f, 0.0f};

int cubo1 = 0;
int extremidad = 0;
int piernasLocas = 0;
bool rapido = false;

int mouseX, mouseY;
bool ctrlKeyPressed = false;
bool altKeyPressed = false;

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15, 15, -15, 15, -15, 15);
    glMatrixMode(GL_MODELVIEW);
    ancho = width;
    alto = height;
}

//----------------------------------FIGURAS--------------------------

void drawHandFeet(void)
{
    glColor3f(0.8f, 0.0f, 0.0f); // Rojo
    glPushMatrix();
    glTranslatef(0.0f, -3.75f, 0.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    glutSolidCube(1.0f); // Cubo sólido
    glPopMatrix();
}

void drawCube(void)
{
    glColor3f(1.0f, 1.0f, 1.0f); // Blanco
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    glScalef(1.0f, 3.0f, 1.0f);
    glutSolidCube(1.0f); // Cubo sólido
    glPopMatrix();
}

void drawSphere(void)
{
    glColor3f(0.29f, 0.29f, 0.29f); // Gris
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glutSolidSphere(0.5f, 16, 16); // Esfera sólida
    glPopMatrix();
}

void drawTorso(void)
{
    glColor3f(0.0f, 0.2f, 0.6f);    //Azul
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(4.0f, 6.0f, 2.0f);     // Ajuste de tamaño
    glutSolidCube(1.0f);            // Cubo sólido para el torso
    glPopMatrix();
}

void drawExtremity(Angulo angulo1, Angulo angulo2)
{
    glPushMatrix();
    drawSphere();
    glRotatef(angulo1.x, 1.0f, 0.0f, 0.0f);
    glRotatef(angulo1.y, 0.0f, 1.0f, 0.0f);
    glRotatef(angulo1.z, 0.0f, 0.0f, 1.0f);
    drawCube();
    glTranslatef(0.0f, -4.0f, 0.0f);
    drawSphere();
    glRotatef(angulo2.x, 1.0f, 0.0f, 0.0f);
    glRotatef(angulo2.y, 0.0f, 1.0f, 0.0f);
    glRotatef(angulo2.z, 0.0f, 0.0f, 1.0f);
    drawCube();
    drawHandFeet();
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawTorso();
    glTranslatef(2.5f, 2.5f, 0.0f);
    drawExtremity(anguloBrazoDerecho, anguloAntebrazoDerecho);
    glTranslatef(-5.0f, 0.0f, 0.0f);
    drawExtremity(anguloBrazoIzquierdo, anguloAntebrazoIzquierdo);
    glTranslatef(1.0f, -6.0f, 0.0f);
    drawExtremity(anguloMusloIzquierdo, anguloGemeloIzquierdo);
    glTranslatef(3.0f, 0.0f, 0.0f);
    drawExtremity(anguloMusloDerecho, anguloGemeloDerecho);
    glFlush();
    glutSwapBuffers();
}

//----------------------------------MENUS----------------------------------

void menu_1(int value)
{
    switch (value)
    {
    case 0:     //Piernas locas
        piernasLocas = 1 - piernasLocas;
        break;
    case 1:
        exit(0); // Salir de la aplicación
        break;
    }
}

void menu_2(int value)
{
    // Submenú "Visualizacion"
    switch (value)
    {
    case 0:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Modo sólido
        break;
    case 1:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Modo alambre
        break;
    }
}

void menu_3(int value)
{
    // Submenú "Velocidades"
    switch (value)
    {
    case 0:
        rapido = false;     //Modo lento
        break;
    case 1:
        rapido = true;      //Modo rápido
        break;
    }
}

//-----------------------------------------INIT Y IDLE-----------------------------

void init()
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    ancho = 800;
    alto = 800;

    // Crear los menús y submenús
    int submenu_visualizacion = glutCreateMenu(menu_2);
    glutAddMenuEntry("Solidos", 0);
    glutAddMenuEntry("Alambre", 1);

    int submenu_velocidades = glutCreateMenu(menu_3);
    glutAddMenuEntry("Lento", 0);
    glutAddMenuEntry("Rapido", 1);

    glutCreateMenu(menu_1);
    glutAddSubMenu("Visualizacion", submenu_visualizacion);
    glutAddSubMenu("Velocidades", submenu_velocidades);
    glutAddMenuEntry("Piernas locas", 0);
    glutAddMenuEntry("Salir", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void idle()
{
    if (ctrlKeyPressed) {
        anguloMusloIzquierdo.z = mouseX;
        anguloMusloIzquierdo.z = mouseY;
    } else if (altKeyPressed) {
        anguloMusloDerecho.z = mouseX;
        anguloMusloDerecho.z = mouseY;
    }
    // Incrementa los ángulos de las piernas automáticamente
    if (piernasLocas)
    {
        if (rapido) {
            anguloMusloIzquierdo.y += 3.0f;
            anguloMusloDerecho.y -= 3.0f;
        } else {
            anguloMusloIzquierdo.y += 1.0f;
            anguloMusloDerecho.y -= 1.0f;
        }
    }
    display();
}

//---------------------------------------MOUSE-----------------------------------------

void mouseMotion(int x, int y) {
    mouseX = x;
    mouseY = y;
}

//--------------------------------------KEYBOARD---------------------------------------

void keyboard(unsigned char key, int x, int y)
{   
if (glutGetModifiers() & GLUT_ACTIVE_CTRL) {
    // La tecla Ctrl está presionada
    ctrlKeyPressed = true;
} else {
    ctrlKeyPressed = false;
}
if (glutGetModifiers() & GLUT_ACTIVE_ALT) {
    // La tecla Alt está presionada
    altKeyPressed = true;
} else {
    altKeyPressed = false;
}
    switch (key)
    {
    case 'z': case 'Z':
        cubo1 = 1 - cubo1;
        printf("Tecla z presionada");
        break;
    case 'x': case 'X':
        extremidad = (extremidad + 1) % 4;
        break;
    case 'q': case 'Q':
        if (cubo1 == 0)
        {
            switch (extremidad)
            {
            case 0: anguloBrazoIzquierdo.x += 1.0f; break;
            case 1: anguloBrazoDerecho.x += 1.0f; break;
            case 2: anguloMusloIzquierdo.x += 1.0f; break;
            case 3: anguloMusloDerecho.x += 1.0f; break;
            }
        }
        else
        {
            switch (extremidad)
            {
            case 0: anguloAntebrazoIzquierdo.x += 1.0f; break;
            case 1: anguloAntebrazoDerecho.x += 1.0f; break;
            case 2: anguloGemeloIzquierdo.x += 1.0f; break;
            case 3: anguloGemeloDerecho.x += 1.0f; break;
            }
        }
        break;
    case 'a': case 'A':
        if (cubo1 == 0)
        {
            switch (extremidad)
            {
            case 0: anguloBrazoIzquierdo.x -= 1.0f; break;
            case 1: anguloBrazoDerecho.x -= 1.0f; break;
            case 2: anguloMusloIzquierdo.x -= 1.0f; break;
            case 3: anguloMusloDerecho.x -= 1.0f; break;
            }
        }
        else
        {
            switch (extremidad)
            {
            case 0: anguloAntebrazoIzquierdo.x -= 1.0f; break;
            case 1: anguloAntebrazoDerecho.x -= 1.0f; break;
            case 2: anguloGemeloIzquierdo.x -= 1.0f; break;
            case 3: anguloGemeloDerecho.x -= 1.0f; break;
            }
        }
        break;
    case 'w': case 'W':
        if (cubo1 == 0)
        {
            switch (extremidad)
            {
            case 0: anguloBrazoIzquierdo.y += 1.0f; break;
            case 1: anguloBrazoDerecho.y += 1.0f; break;
            case 2: anguloMusloIzquierdo.y += 1.0f; break;
            case 3: anguloMusloDerecho.y += 1.0f; break;
            }
        }
        else
        {
            switch (extremidad)
            {
            case 0: anguloAntebrazoIzquierdo.y += 1.0f; break;
            case 1: anguloAntebrazoDerecho.y += 1.0f; break;
            case 2: anguloGemeloIzquierdo.y += 1.0f; break;
            case 3: anguloGemeloDerecho.y += 1.0f; break;
            }
        }
        break;
    case 's': case 'S':
        if (cubo1 == 0)
        {
            switch (extremidad)
            {
            case 0: anguloBrazoIzquierdo.y -= 1.0f; break;
            case 1: anguloBrazoDerecho.y -= 1.0f; break;
            case 2: anguloMusloIzquierdo.y -= 1.0f; break;
            case 3: anguloMusloDerecho.y -= 1.0f; break;
            }
        }
        else
        {
            switch (extremidad)
            {
            case 0: anguloAntebrazoIzquierdo.y -= 1.0f; break;
            case 1: anguloAntebrazoDerecho.y -= 1.0f; break;
            case 2: anguloGemeloIzquierdo.y -= 1.0f; break;
            case 3: anguloGemeloDerecho.y -= 1.0f; break;
            }
        }
        break;
    case 'e': case 'E':
        if (cubo1 == 0)
        {
            switch (extremidad)
            {
            case 0: anguloBrazoIzquierdo.z += 1.0f; break;
            case 1: anguloBrazoDerecho.z += 1.0f; break;
            case 2: anguloMusloIzquierdo.z += 1.0f; break;
            case 3: anguloMusloDerecho.z += 1.0f; break;
            }
        }
        else
        {
            switch (extremidad)
            {
            case 0: anguloAntebrazoIzquierdo.z += 1.0f; break;
            case 1: anguloAntebrazoDerecho.z += 1.0f; break;
            case 2: anguloGemeloIzquierdo.z += 1.0f; break;
            case 3: anguloGemeloDerecho.z += 1.0f; break;
            }
        }
        break;
    case 'd': case 'D':
        if (cubo1 == 0)
        {
            switch (extremidad)
            {
            case 0: anguloBrazoIzquierdo.z -= 1.0f; break;
            case 1: anguloBrazoDerecho.z -= 1.0f; break;
            case 2: anguloMusloIzquierdo.z -= 1.0f; break;
            case 3: anguloMusloDerecho.z -= 1.0f; break;
            }
        }
        else
        {
            switch (extremidad)
            {
            case 0: anguloAntebrazoIzquierdo.z -= 1.0f; break;
            case 1: anguloAntebrazoDerecho.z -= 1.0f; break;
            case 2: anguloGemeloIzquierdo.z -= 1.0f; break;
            case 3: anguloGemeloDerecho.z -= 1.0f; break;
            }
        }
        break;
    case 27: // escape
        exit(0);
        break;
    }
}

//--------------------------------------MAIN------------------------------------------

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Ejercicio");
    glutPassiveMotionFunc(mouseMotion);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
