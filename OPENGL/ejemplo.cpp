#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 400
#define HEIGTH 400
#define ORIGIN_X 100
#define ORIGIN_Y 100

void init()
{
    glClearColor(0.0,0.0,0.0, 0.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibuja el fondo verde
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.4, 0.0);  // Color verde
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();

    // Dibuja la cruz diagonal negra
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);  // Color negro
    glVertex2f(-0.2, 1.0);  // Arriba izquierda
    glVertex2f(0.2, 1.0);   // Arriba derecha
    glVertex2f(-0.2, -1.0); // Abajo izquierda
    glVertex2f(0.2, -1.0);  // Abajo derecha
    glEnd();

    // Dibuja los triángulos amarillos
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 0.0);  // Color amarillo
    glVertex2f(-1.0, 0.2);   // Triángulo izquierdo
    glVertex2f(-0.2, 1.0);
    glVertex2f(-0.2, 0.2);

    glVertex2f(1.0, 0.2);    // Triángulo derecho
    glVertex2f(0.2, 1.0);
    glVertex2f(0.2, 0.2);

    glVertex2f(-1.0, -0.2);  // Triángulo inferior izquierdo
    glVertex2f(-0.2, -1.0);
    glVertex2f(-0.2, -0.2);

    glVertex2f(1.0, -0.2);   // Triángulo inferior derecho
    glVertex2f(0.2, -1.0);
    glVertex2f(0.2, -0.2);
    glEnd();

    glFlush();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
 glutInit(&argc, argv); 
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
 glutInitWindowSize(WIDTH, HEIGTH); 
 glutInitWindowPosition(ORIGIN_X, ORIGIN_Y); 
 glutCreateWindow("Hola Mundo"); 
 init();
 glutDisplayFunc(display); 
 glutReshapeFunc(reshape); 
 glutMainLoop(); 
 return 0;
}