#include "stdafx.h"
#include "ShapeLib.h"

namespace ShapeLibrary
{
	 void Drawing::DrawLine(HDC hdc, int aX, int aY, int bX, int bY)
	{
		MoveToEx(hdc, bX, bY, NULL);
		LineTo(hdc, aX, aY);
		return;
	}
	void Drawing::DrawRectangle(HDC hdc, int aX, int aY, int bX, int bY)
	{
		Rectangle(hdc, bX, bY, aX, aY);
		return;
	}
	void Drawing::DrawEllipse(HDC hdc, int aX, int aY, int bX, int bY)
	{
		Ellipse(hdc, bX, bY, aX, aY);
		return;
	}
}