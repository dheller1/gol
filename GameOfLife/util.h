#pragma once

struct Coords {
	Coords(int x_, int y_) : x(x_), y(y_) {}
	int x, y;
	bool operator<(const Coords& o) const { return x < o.x || (x == o.x && y < o.y); }
};

Coords operator+(const Coords& A, const Coords& B);

struct Color {
	Color(float r_, float g_, float b_) : r(r_), g(g_), b(b_) {}
	float r, g, b;
};

struct RectF {
	RectF(float t, float b, float l, float r) : top(t), btm(b), left(l), right(r) {}
	float top, btm, left, right;
};
