#include "util.h"

Coords operator+(const Coords& A, const Coords& B)
{
	return Coords{ A.x + B.x, A.y + B.y };
}
