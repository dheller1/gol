#pragma once
#include "util.h"
#include "GridState.h"

class GridRenderer
{
public:
	GridRenderer() : m_pixelColor(Color(.9f, .9f, .1f)) {}
	virtual void render(const GridState::CellSet& cells) = 0;
	virtual void reshape(GLsizei width, GLsizei height) = 0;
protected:
	void setColor(const Color& c);
	inline float getX(const Coords& c) const { return (m_pixelSize + m_marginSize) * c.x; }
	inline float getY(const Coords& c) const { return (m_pixelSize + m_marginSize) * c.y; }

	float m_pixelSize = .02f;
	float m_marginSize = .01f;
	Color m_pixelColor;
};

class GridRenderer_GL : public GridRenderer
{
public:
	void render(const GridState::CellSet& cells) override;
	void reshape(GLsizei width, GLsizei height) override;
};
