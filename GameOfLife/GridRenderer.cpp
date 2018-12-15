#include "GridRenderer.h"
#include <GL/freeglut.h>

void GridRenderer::setColor(const Color& c)
{
	glColor3f(c.r, c.g, c.b);
}

void GridRenderer_GL::render(const GridState::CellSet& cells)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.02f, 0.02f, 0.1f, 1.0f); //clear dark blue
	
	setColor(m_pixelColor);

	glBegin(GL_QUADS);
	for(const auto& cell : cells) {
		RectF rect(getY(cell) + .5f*m_pixelSize, getY(cell) - .5f*m_pixelSize, getX(cell) - .5f*m_pixelSize, getX(cell) + .5f*m_pixelSize);
		glVertex2f(rect.left, rect.btm);
		glVertex2f(rect.right, rect.btm);
		glVertex2f(rect.right, rect.top);
		glVertex2f(rect.left, rect.top);
	}
	glEnd();

	glutSwapBuffers();
}


void GridRenderer_GL::reshape(GLsizei width, GLsizei height)
{
	if(height == 0) {
		height = 1; // no zero-division
	}
	float aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION); // operate on projection matrix
	glLoadIdentity();
	if(width >= height) {
		gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1., 1.);
	}
	else {
		gluOrtho2D(-1., 1., -1. / aspect, 1. / aspect);
	}
}
