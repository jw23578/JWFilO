#ifndef COLORS_H
#define COLORS_H

#include "jwqt_macros.h"
#include <QObject>
#include <QColor>

class Colors : public QObject
{
    Q_OBJECT
    JWQT_PROPERTY(QColor, background, Background, "#F5F7FA")
    JWQT_PROPERTY(QColor, groupBackground, GroupBackground, "#EEF2F6")
    JWQT_PROPERTY(QColor, groupBorder, GroupBorder, "#CFD8E3")
    JWQT_PROPERTY(QColor, textPrimary, TextPrimary, "#212B36")
    JWQT_PROPERTY(QColor, textSecondary, TextSecondary, "#637381")
    JWQT_PROPERTY(QColor, textHighlight, TextHighlight, "#8766EE")

    JWQT_PROPERTY(QColor, selectedContainer, SelectedContainer, 0xE2EEFF)
    JWQT_PROPERTY(QColor, selectedBorder, SelectedBorder, 0x2D5F8B)


public:
    explicit Colors(QObject *parent = nullptr);

    void setDarkDefaults();

signals:
};

#endif // COLORS_H
