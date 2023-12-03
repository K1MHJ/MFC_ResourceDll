#pragma once


#ifdef _USRDLL;
#define RESOURCEDLL_API __declspec(dllexport)
#else
#define RESOURCEDLL_API __declspec(dllimport)
#endif


extern "C" RESOURCEDLL_API void GetBitmapResource(DWORD resource_ID, CBitmap* dstBmp);
