#include "colors.h"

Colors::Colors(QObject *parent)
    : QObject{parent}
{}

void Colors::setDarkDefaults()
{
    setBackground("#1D2733");
    setGroupBackground("#232D3A");
    setGroupBorder("#384251");
    setTextPrimary("#E8ECEF");
    setTextSecondary("#A0AEC0");
    setTextHighlight("#A285FF");

    setSelectedContainer(0x1A3450);
    setSelectedBorder(0x3476AD);
}
