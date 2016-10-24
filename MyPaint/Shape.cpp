#include "stdafx.h"
#include "Shape.h"
#include "ShapeLib.h"

using namespace ShapeLibrary;

CShape::CShape(int x1, int y1, int x2, int y2)
{
	bX = x1;
	bY = y1;
	aX = x2;
	aY = y2;
}

CShape::~CShape()
{
}

void CLine::Paint(HDC hdc)
{
	Drawing::DrawLine(hdc, bX, bY, aX, aY);
}

void CLine::Save(fstream &fi)
{
	fi << 0 << "\t" << bX << "\t" << bY << "\t" << aX << "\t" << aY << "\n";
}

CLine::~CLine()
{
}

void CRectangle::Paint(HDC hdc)
{
	Drawing::DrawRectangle(hdc, bX, bY, aX, aY);
}

void CRectangle::Save(fstream &fi)
{
	fi << 1 << "\t" << bX << "\t" << bY << "\t" << aX << "\t" << aY << "\n";
}

CRectangle::~CRectangle()
{
}

void CEllipse::Paint(HDC hdc)
{
	Drawing::DrawEllipse(hdc, bX, bY, aX, aY);
}

void CEllipse::Save(fstream &fi)
{
	fi << 2 << "\t" << bX << "\t" << bY << "\t" << aX << "\t" << aY << "\n";
}

CEllipse::~CEllipse()
{
}
