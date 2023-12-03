// MFCExLib.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "MFCExLib.h"
#include "resource.h"
#include "ResourceDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void GetBitmapResource(DWORD resource_ID, CBitmap* dstBitmap)
{
	CBitmap srcBitmap[2];
	CPngImage pngImage[2];
	BITMAP bm;

	if (!pngImage[0].Load(IDB_PNG1, nullptr)) {
		return;
	}
	if (!pngImage[1].Load(IDB_PNG2, nullptr)) {
		return;
	}
	srcBitmap[0].Attach(pngImage[0].Detach());
	srcBitmap[1].Attach(pngImage[1].Detach());

	CDC memDCSrc[2], memDCDst;
	memDCSrc[0].CreateCompatibleDC(NULL); // Create a memory DC for the source
	memDCSrc[1].CreateCompatibleDC(NULL); // Create a memory DC for the source
	memDCDst.CreateCompatibleDC(NULL); // Create a memory DC for the destination

	// Select the source bitmap into the first memory DC
	CBitmap* pOldSrcBitmap[2];
	pOldSrcBitmap[0] = memDCSrc[0].SelectObject(&srcBitmap[0]);
	pOldSrcBitmap[1] = memDCSrc[1].SelectObject(&srcBitmap[1]);
	CBitmap* pOldDstBitmap = nullptr;

    if (resource_ID == IDR_BUTTON) {
		srcBitmap[0].GetBitmap(&bm); // Get the dimensions of the source bitmap
		dstBitmap->CreateCompatibleBitmap(&memDCSrc[0], 120, 75);
		pOldDstBitmap = memDCDst.SelectObject(dstBitmap);
        memDCDst.BitBlt(0, 0, 120,75, &memDCSrc[0], 15, 35, SRCCOPY);
		memDCSrc[0].SelectObject(pOldSrcBitmap);
    }
    if (resource_ID == IDR_BUTTON_PUSHED) {
		srcBitmap[1].GetBitmap(&bm); // Get the dimensions of the source bitmap
		dstBitmap->CreateCompatibleBitmap(&memDCSrc[1], 120, 75);
		pOldDstBitmap = memDCDst.SelectObject(dstBitmap);
        memDCDst.BitBlt(0, 0, 120,75, &memDCSrc[1], 15, 35, SRCCOPY);
		memDCSrc[1].SelectObject(pOldSrcBitmap);
    }
    if (resource_ID == IDR_WHOLE_BACKGROUND) {
		srcBitmap[0].GetBitmap(&bm); // Get the dimensions of the source bitmap
		dstBitmap->CreateCompatibleBitmap(&memDCSrc[0], bm.bmWidth, bm.bmHeight);
		pOldDstBitmap = memDCDst.SelectObject(dstBitmap);
        memDCDst.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &memDCSrc[0], 0, 0, SRCCOPY);
		memDCSrc[0].SelectObject(pOldSrcBitmap);
    }

	if(pOldDstBitmap != nullptr )
		memDCDst.SelectObject(pOldDstBitmap);
}


