#include "GridState.h"
#include "GridRenderer.h"

GridState* GridState::g_renderedState = nullptr;

GridState::GridState()
{
	g_renderedState = this;

	//m_aliveCells.insert({ 0, 0 });
	m_aliveCells.insert({ 0, 0 });
	m_aliveCells.insert({ 1, 0 });
	m_aliveCells.insert({ -1, 0 });
	//m_aliveCells.insert({ -2, -2 });
	//>m_aliveCells.insert({ 0, 0 });




	Coords base{ 20, -20 };

	m_aliveCells.insert(base + Coords{  0, +1 });
	m_aliveCells.insert(base + Coords{ +1,  0 });
	m_aliveCells.insert(base + Coords{ +1, -1 });
	m_aliveCells.insert(base + Coords{  0, -1 });
	m_aliveCells.insert(base + Coords{ -1, -1 });
}

bool GridState::isAlive(const Coords& cell) const
{
	return m_aliveCells.find(cell) != m_aliveCells.end();
}

void GridState::setRenderer(GridRenderer* renderer)
{
	m_renderer = renderer;
}

void GridState::iterate()
{
	CellSet nextCells;
	CellSet deadNeighbors;

	Coords neighbors[] = { { -1, +1 }, {  0, +1 }, { +1, +1 },
						   { -1,  0 },             { +1,  0 },
						   { -1, -1 }, {  0, -1 }, { +1, -1 } };

	for(const auto& c : m_aliveCells) {
		size_t count = 0;
		for(const auto& n : neighbors) {
#ifdef _DEBUG
			auto cn = c + n;
#endif
			if(isAlive(c + n)) {
				++count;
			}
			else {
				deadNeighbors.insert(c + n);
			}
		}

		if(count == 2 || count == 3) {
			nextCells.insert(c);
		}
	}

	for(const auto& n : deadNeighbors) {
		size_t count = 0;
		for(const auto& nn : neighbors) {
			if(isAlive(n + nn)) {
				++count;
			}

			if(count > 3) {
				break;
			}
		}
		if(count == 3) {
			nextCells.insert(n);
		}
	}

	m_aliveCells.swap(nextCells);
}

void GridState::render()
{
	if(g_renderedState->m_renderer) {
		g_renderedState->m_renderer->render(g_renderedState->m_aliveCells);
	}
}

void GridState::reshape(GLsizei width, GLsizei height)
{
	if(g_renderedState->m_renderer) {
		g_renderedState->m_renderer->reshape(width, height);
	}
}

void GridState::iterate_current(int value)
{
	g_renderedState->iterate();
	glutPostRedisplay();
	glutTimerFunc(value, GridState::iterate_current, value);
}
