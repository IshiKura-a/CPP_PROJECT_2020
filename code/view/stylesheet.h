#ifndef _STYLE_SHEET_H_
#define _STYLE_SHEET_H_

#include <QWidget>
#include <Windows.h>
#include "../common/def.h"
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

inline void inversePixmapFontColor(ptr<QPixmap> pixmap)
{
	QColor fontColor = Qt::white;
	QImage tmpImg = pixmap->toImage();
	int i, j;
	for (i = 0; i < tmpImg.height(); i++)
	{
		for (j = 0; j < tmpImg.width(); j++)
		{
			bool tmp = (tmpImg.pixelColor(j, i) == Qt::black);
			fontColor.setAlpha(tmpImg.pixelColor(j, i).alpha());
			tmpImg.setPixelColor(j, i, fontColor);
		}
	}

	*pixmap = QPixmap::fromImage(tmpImg);
}

extern const QString whiteBackground;
extern const QString whiteBackgroundSemiTransparent;
extern const QString lightBlueBackground;
extern const QString lightDarkBackground;
extern const QString silverBackground;
extern const QString transparentBackground;
extern const QString background4Img;

extern const QString whiteWords;
extern const QString redWords;
extern const QString blackWords;
// mouse event: hover, to menu 'selected' is used instead
extern const QString hoverBlackWords;

extern const QString blackBorder2Px;
extern const QString noBottomBorder;

// extern QString textFontSize;

extern QString ENGFont;
extern QString CHNFont;

extern QFont textNormal;
extern QFont textBold;
extern QFont titleBold;
extern QFont titleBoldCHN;
extern QFont menuNormal;
extern QFont msgNormal;
extern QFont labelTextNormal;
extern QFont labelTextBold;
extern QFont labelTextNormalCHN;
#endif