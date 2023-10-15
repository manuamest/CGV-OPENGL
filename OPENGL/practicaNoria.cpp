#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int ancho = 800;
int alto = 800;
float rotationAngle = 0.0f;
float rotationSpeed = 20.0f;  // Velocidad de rotación en grados por segundo

void timerRotation(int value) {
    // Actualiza el ángulo de rotación
    rotationAngle += rotationSpeed * 0.016f;  // 0.016 es un ajuste de tiempo

    // Establece el temporizador nuevamente
    glutTimerFunc(16, timerRotation, value);
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    ancho = width;
    alto = height;
}

void drawTriangle(void) {
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.4, 0.0);
    glVertex3f(-1.5f, 0.0f, 0.0f);   // Vértice inferior izquierdo
    glVertex3f(1.5f, 0.0f, 0.0f);   // Vértice inferior derecho
    glVertex3f(0.0f, 3.0f, 0.0f);   // Vértice superior
    glEnd();
}

void drawCircule(void) {
    float radio = 2.5f;
    int numSegmentos = 32;

    glPushMatrix();  // Guarda la matriz actual para el círculo
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);  // Aplica la rotación al círculo

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0, 0.0, 0.4);
    glVertex3f(0.0f, 0.0f, 0.0f);   // Centro del círculo
    for (int i = 0; i <= numSegmentos; i++) {
        float angulo = 2.0f * M_PI * i / numSegmentos;
        float x = radio * cos(angulo);
        float y = radio * sin(angulo);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();

    // Dibujar cubos alrededor del círculo
    float cubeSize = 0.2f;
    for (int i = 0; i < 8; i++) {
        float angle = 2.0f * M_PI * i / 8;
        float x = radio * cos(angle);
        float y = radio * sin(angle);

        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        // Rotación adicional para alinear con la gravedad
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(i * 45.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
        glColor3f(0.4, 0.0, 0.0);
        glVertex3f(-cubeSize, -cubeSize, -cubeSize);
        glVertex3f(cubeSize, -cubeSize, -cubeSize);
        glVertex3f(cubeSize, cubeSize, -cubeSize);
        glVertex3f(-cubeSize, cubeSize, -cubeSize);
        glEnd();
        glPopMatrix();
    }

    glPopMatrix();  // Restaura la matriz para el círculo
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawTriangle();
    glTranslatef(0.0f, 3.0f, 0.0f);  // Mover el círculo hacia arriba
    drawCircule();

    glFlush();
    glutSwapBuffers();
}

void init() {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    ancho = 800;
    alto = 800;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void idle() {
    display();
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
    glutIdleFunc(idle);
    glutTimerFunc(0, timerRotation, 0);
    glutMainLoop();

    return 0;
}
