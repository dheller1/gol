#pragma once
#include <set>
#include <GL/freeglut.h>
#include "util.h"

class GridRenderer;

class GridState
{
public:
	using CellSet = std::set<Coords>;
	GridState();
	
	bool isAlive(const Coords& cell) const;
	
	void setRenderer(GridRenderer* renderer);

	void iterate();
	
	static void render();
	static void reshape(GLsizei width, GLsizei height);

	static void iterate_current(int value);

private:
	GridRenderer* m_renderer;
	CellSet m_aliveCells;

	static GridState* g_renderedState;
};

