#include "stylesheet.h"

const QString whiteBackground = "background: white;";
const QString lightBlueBackground = "background: #7BD9D2;";
const QString lightDarkBackground = "background: #2E323A;";
const QString silverBackground = "background: #D4D4D4;";
const QString background4Img = "background-image: url(../../dependency/img/background.jpg);";

const QString whiteWords = "color: white;";
const QString redWords = "color: #FF5555;";
const QString blackWords = "color: black;";

const QString blackBorder2Px = "border: 2px solid black;";
const QString noBottomBorder = "border-bottom: 0px;";

// QString textFontSize = "font-size: 14px";
QString ENGFont = "Courier New";
QString CHNFont = "123";

QFont textNormal = QFont(ENGFont, 14, QFont::Normal, false);
QFont textBold = QFont(ENGFont, 14, QFont::Bold, false);
QFont titleBold = QFont(ENGFont, 22, QFont::Bold, false);
QFont titleBoldCHN = QFont(CHNFont, 22, QFont::Bold, false);
QFont menuNormal = QFont(CHNFont, 10, QFont::Normal, false);
QFont msgNormal = QFont(ENGFont, 10, QFont::Normal, false);
QFont labelTextNormal = QFont(ENGFont, 10, QFont::Normal, false);
QFont labelTextNormalCHN = QFont(CHNFont, 10, QFont::Normal, false);