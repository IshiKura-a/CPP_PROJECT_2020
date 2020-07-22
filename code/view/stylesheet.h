#pragma once
#include <QWidget>
#include <Windows.h>
#include <iostream>

// @param:
	// width: default下的width
	// height: default下的height
	// @return
	// 调整后的size
inline QSize getAdaptedSize(int width, int height)
{
	// sysWidth: resolution_width / expanding rate
	// sysHeight: resolution_height / expanding rate
	// The dafault size of screen is 1920*1080 125%
	// In this case, the size of the software is 960*600.
	// In case of different solutionn, change the width and height in proportion.
	// Windows.h MUST be included!!!
	int sysWidth = ::GetSystemMetrics(SM_CXSCREEN);
	int sysHeight = ::GetSystemMetrics(SM_CYSCREEN);
	int adaptedWidth = (width * sysWidth) / 1536;
	int adaptedHeight = (height * sysHeight) / 864;
	return QSize(adaptedWidth, adaptedHeight);
}
inline QSize getAdaptedSize(QSize size)
{
	return getAdaptedSize(size.width(), size.height());
}