#include <stdio.h>
#include <GL/glut.h>

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Angulo;

GLint ancho = 800;
GLint alto = 800;
Angulo anguloCubo = {0.0f, 0.0f, 0.0f};
Angulo anguloCubo2 = {0.0f, 0.0f, 0.0f};
int hazPerspectiva = 0;

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (hazPerspectiva)
        gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 10.0f, 20.0f);
    else
        glOrtho(-10, 10, -10, 10, -10, 10);

    glMatrixMode(GL_MODELVIEW);
    ancho = width;
    alto = height;
}

void drawCube(void)
{
    glColor3f(1.0f, 1.0f, 1.0f); // Blanco
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawSphere();
    glRotatef(anguloCubo.x, 1.0f, 0.0f, 0.0f);
    glRotatef(anguloCubo.y, 0.0f, 1.0f, 0.0f);
    glRotatef(anguloCubo.z, 0.0f, 0.0f, 1.0f);
    drawCube();
    glTranslatef(0.0f, -2.0f, 0.0f);
    drawSphere();
    glRotatef(anguloCubo2.x, 1.0f, 0.0f, 0.0f);
    glRotatef(anguloCubo2.y, 0.0f, 1.0f, 0.0f);
    glRotatef(anguloCubo2.z, 0.0f, 0.0f, 1.0f);
    drawCube();
    glFlush();
    glutSwapBuffers();
}

void init()
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    ancho = 800;
    alto = 800;
}

void idle()
{
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
    case 'q':
    case 'Q':
        anguloCubo.x += 1.0f;
        break;
    case 'a':
    case 'A':
        anguloCubo.x -= 1.0f;
        break;
    case 'w':
    case 'W':
        anguloCubo.y += 1.0f;
        break;
    case 's':
    case 'S':
        anguloCubo.y -= 1.0f;
        break;
    case 'e':
    case 'E':
        anguloCubo.z += 1.0f;
        break;
    case 'd':
    case 'D':
        anguloCubo.z -= 1.0f;
        break;
    case 'r':
    case 'R':
        anguloCubo2.x += 1.0f;
        break;
    case 'f':
    case 'F':
        anguloCubo2.x -= 1.0f;
        break;
    case 't':
    case 'T':
        anguloCubo2.y += 1.0f;
        break;
    case 'g':
    case 'G':
        anguloCubo2.y -= 1.0f;
        break;
    case 'y':
    case 'Y':
        anguloCubo2.z += 1.0f;
        break;
    case 'h':
    case 'H':
        anguloCubo2.z -= 1.0f;
        break;
    case 27:   // escape
        exit(0);
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Ejercicio");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
