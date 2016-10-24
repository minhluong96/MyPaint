#pragma once

#ifdef SHAPELIBRARY_EXPORTS
#define SHAPELIBRARY_API __declspec(dllexport) 
#else
#define SHAPELIBRARY_API __declspec(dllimport) 
#endif

namespace ShapeLibrary
{
	class Drawing
	{
	public:
		static SHAPELIBRARY_API void DrawLine(HDC hdc, int aX, int aY, int bX, int bY);
		static SHAPELIBRARY_API void DrawRectangle(HDC hdc, int aX, int aY, int bX, int bY);
		static SHAPELIBRARY_API void DrawEllipse(HDC hdc, int aX, int aY, int bX, int bY);
	};
}