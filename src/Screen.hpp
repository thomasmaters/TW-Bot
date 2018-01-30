/*
 * Screen.hpp
 *
 *  Created on: 3 feb. 2017
 *      Author: Thomas
 */

#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include <windows.h>

#include <string>

const std::string screenshotLocation = "screenshot.bmp";

class Screen
{
public:
    Screen()
    {
    }

    static void takeScreenShot()
    {
        // Get screen info.
        HWND DesktopHwnd = GetDesktopWindow();
        RECT DesktopParams;
        HDC DevC = GetDC(DesktopHwnd);
        GetWindowRect(DesktopHwnd, &DesktopParams);
        DWORD Width  = DesktopParams.right - DesktopParams.left;
        DWORD Height = DesktopParams.bottom - DesktopParams.top;

        // Construct empty bitmap.
        DWORD FileSize    = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(RGBTRIPLE) + 1 * (Width * Height * 4));
        char *BmpFileData = (char *)GlobalAlloc(0x0040, FileSize);

        PBITMAPFILEHEADER BFileHeader = (PBITMAPFILEHEADER)BmpFileData;
        PBITMAPINFOHEADER BInfoHeader = (PBITMAPINFOHEADER)&BmpFileData[sizeof(BITMAPFILEHEADER)];

        BFileHeader->bfType        = 0x4D42;  // BM
        BFileHeader->bfSize        = sizeof(BITMAPFILEHEADER);
        BFileHeader->bfOffBits     = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        BInfoHeader->biSize        = sizeof(BITMAPINFOHEADER);
        BInfoHeader->biPlanes      = 1;
        BInfoHeader->biBitCount    = 24;
        BInfoHeader->biCompression = BI_RGB;
        BInfoHeader->biHeight      = Height;
        BInfoHeader->biWidth       = Width;

        RGBTRIPLE *Image = (RGBTRIPLE *)&BmpFileData[sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)];

        // Load screen pixels in bitmap.
        HDC CaptureDC         = CreateCompatibleDC(DevC);
        HBITMAP CaptureBitmap = CreateCompatibleBitmap(DevC, Width, Height);
        SelectObject(CaptureDC, CaptureBitmap);
        BitBlt(CaptureDC, 0, 0, Width, Height, DevC, 0, 0, SRCCOPY | CAPTUREBLT);
        GetDIBits(CaptureDC, CaptureBitmap, 0, Height, Image, (LPBITMAPINFO)BInfoHeader, DIB_RGB_COLORS);

        // Write bitmap to file.
        DWORD Junk;
        HANDLE FH = CreateFileA(screenshotLocation.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);
        WriteFile(FH, BmpFileData, FileSize, &Junk, 0);
        CloseHandle(FH);
        GlobalFree(BmpFileData);
        DeleteObject(CaptureBitmap);
        DeleteDC(CaptureDC);
    }

    static RECT getScreenSize()
    {
        int nScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
        int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
        return { 0, 0, nScreenWidth, nScreenHeight };
    }

    virtual ~Screen()
    {
    }

private:
};

#endif /* SCREEN_HPP_ */
