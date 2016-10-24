#pragma once
#include <fstream>
#include "ShapeLib.h"

using namespace ShapeLibrary;

using namespace std;

class CShape
{
protected:
	int bX, bY, aX, aY;
public:
	CShape(int x1, int y1, int x2, int y2);
	virtual void Paint(HDC hdc) = 0;
	virtual void Save(fstream &fi) = 0;
	~CShape();
};

class CLine :public CShape
{
public:
	CLine(int x1, int y1, int x2, int y2) : CShape(x1, y1, x2, y2) {};
	void Paint(HDC hdc);
	void Save(fstream &fi);
	~CLine();
};

class CRectangle : public CShape
{
public:
	CRectangle(int x1, int y1, int x2, int y2) : CShape(x1, y1, x2, y2) {};
	void Paint(HDC hdc);
	void Save(fstream &fi);
	~CRectangle();
};

class CEllipse : public CShape
{
public:
	CEllipse(int x1, int y1, int x2, int y2) : CShape(x1, y1, x2, y2) {};
	void Paint(HDC hdc);
	void Save(fstream &fi);
	~CEllipse();
};
