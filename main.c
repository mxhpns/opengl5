#include <GL/glew.h>
#include <GL/freeglut.h>
#include "util.h"
#include <stdio.h>

GLuint vbo;

void setUniformLocations() {
}

void createBuffer();

void init() {
    createBuffer();

    GLuint shaders[] = {
        createShader("shader.vs", GL_VERTEX_SHADER),
        createShader("shader.fs", GL_FRAGMENT_SHADER)
    };
    int len = sizeof(shaders) / sizeof(shaders[0]);
    createProg(shaders, len);
    int i = 0;
    for (; i < len; i++) {
        glDeleteShader(shaders[i]);
    }

    setUniformLocations();
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
}

void createBuffer() {
    float vertices[] = {
         // vertices
        -1.0f, -1.0f,  1.0f, 1.0f, // left-bottom
         1.0f, -1.0f,  1.0f, 1.0f, // right-bottom
         0.0f,  1.0f, -1.0f, 1.0f, // top

        -1.0f,  1.0f,  1.0f, 1.0f, // left-top
         1.0f,  1.0f,  1.0f, 1.0f, // right-top
         0.0f, -1.0f, -1.0f, 1.0f, // bottom

         // colors
         1.0f, 0.0f, 0.0f, 1.0f, // red
         0.0f, 1.0f, 0.0f, 1.0f, // green
         0.0f, 0.0f, 1.0f, 1.0f, // blue

         1.0f, 1.0f, 0.0f, 1.0f, // yellow
         1.0f, 0.0f, 1.0f, 1.0f, // purple
         0.0f, 1.0f, 1.1f, 1.0f  // aqua
    };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void display() {
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(prog);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*) (6*4*sizeof(float)));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glUseProgram(0);
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard(unsigned char key, int x, int y) {
    (void) x;
    (void) y;
    if (key == 27) {
        glutLeaveMainLoop();
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Game");

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(res));
        return 1;
    }
    printf("GL version: %s\n", glGetString(GL_VERSION));

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
