#include <iostream>
#include <set>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "GridRenderer.h"
#include "GridState.h"

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("OpenGL First Window");
	
	glEnable(GL_DEPTH_TEST);

	GridState state;
	GridRenderer_GL renderer;
	state.setRenderer(&renderer);

	// register callbacks
	glutDisplayFunc(GridState::render);
	glutReshapeFunc(GridState::reshape);

	int interval = 250; // ms
	glutTimerFunc(interval, GridState::iterate_current, interval);

	glutMainLoop();

	return 0;
}
