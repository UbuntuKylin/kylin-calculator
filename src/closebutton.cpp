/*
 * Copyright (C) 2020, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/* CloseButton by David Peng
 * 2020 10.20
 * Version Beta 1.0
 * 介绍：该控件是用于对话框的关闭按钮，只需指定父对象即可可自动回收。
 * 使用方法：
 * 1、new CloseButton(this); //这样会直接调用主题的关闭按钮。
 * 2、new CloseButton(黑色图标路径,this); //这样会用一个黑色的'X'图标SVG，hover时会渲染成白色。
 * 3、new CloseButton(黑色图标路径，白色图标路径,this) //这样会用两张图片来实现图标显示。
*/

#include "closebutton.h"
#include <QApplication>

CloseButton::CloseButton(QWidget *parent, const QString &filePath, const QString &hoverPath) : QLabel(parent)
{

    //Allocation
    if(filePath != "")
        m_icon = new QIcon(filePath);
    else {
        QIcon icon = QIcon::fromTheme("window-close-symbolic");
        m_icon = new QIcon(icon);
    }
    if(hoverPath != "")
        m_hoverIcon = new QIcon(hoverPath);
    else
        m_hoverIcon = nullptr;

    //Properties
    setProperty("useIconHighlightEffect", true);
    setProperty("iconHighlightEffectMode", 1);
    setFocusPolicy(Qt::NoFocus);

    //Initial componentss
    m_bIsChecked = false;
    m_bIsPressed = false;
    m_cSize = 16;
    m_colorBkg = palette().color(QPalette::Base);
    setAlignment(Qt::AlignCenter);
    setPixmap(renderSvg(*m_icon,"gray"));
}

const QPixmap CloseButton::renderSvg(const QIcon &icon, QString cgColor) {
    int size = m_cSize;
    const auto ratio = qApp->devicePixelRatio();
    if ( 2 == ratio) {
        size = 48;
    } else if (3 == ratio) {
        size = 96;
    }
    QPixmap iconPixmap = icon.pixmap(size,size);
    iconPixmap.setDevicePixelRatio(ratio);
    QImage img = iconPixmap.toImage();
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            auto color = img.pixelColor(x, y);
            if (color.alpha() > 0) {
                if ("white" == cgColor) {
                    color.setRed(255);
                    color.setGreen(255);
                    color.setBlue(255);
                    img.setPixelColor(x, y, color);
                } else if ("black" == cgColor) {
                    color.setRed(0);
                    color.setGreen(0);
                    color.setBlue(0);
                    //                    color.setAlpha(0.1);
                    color.setAlphaF(0.9);
                    img.setPixelColor(x, y, color);
                } else if ("gray" == cgColor) {
                    color.setRed(152);
                    color.setGreen(163);
                    color.setBlue(164);
                    img.setPixelColor(x, y, color);
                } else if ("blue" == cgColor){
                    color.setRed(61);
                    color.setGreen(107);
                    color.setBlue(229);
                    img.setPixelColor(x, y, color);
                } else {
                    return iconPixmap;
                }
            }
        }
    }
    return QPixmap::fromImage(img);
}

QPixmap CloseButton::drawSymbolicColoredPixmap(const QPixmap &source, QString cgColor)
{
    QImage img = source.toImage();
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            auto color = img.pixelColor(x, y);
            if (color.alpha() > 0) {
                if ("white" == cgColor) {
                    color.setRed(255);
                    color.setGreen(255);
                    color.setBlue(255);
                    img.setPixelColor(x, y, color);
                } else if ("black" == cgColor) {
                    color.setRed(0);
                    color.setGreen(0);
                    color.setBlue(0);
                    color.setAlphaF(0.9);
                    img.setPixelColor(x, y, color);
                } else if ("gray" == cgColor) {
                    color.setRed(152);
                    color.setGreen(163);
                    color.setBlue(164);
                    img.setPixelColor(x, y, color);
                } else if ("blue" == cgColor){
                    color.setRed(61);
                    color.setGreen(107);
                    color.setBlue(229);
                    img.setPixelColor(x, y, color);
                } else {
                    return source;
                }
            }
        }
    }
    return QPixmap::fromImage(img);
}

void CloseButton::enterEvent(QEvent *event) {
    Q_UNUSED(event);
    if(m_hoverIcon == nullptr)
        setPixmap(renderSvg(*m_icon,"white"));
    else
        setPixmap(m_hoverIcon->pixmap(m_cSize,m_cSize));
    m_colorBkg = QColor("#FA6056");
}

void CloseButton::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton)
    {
        m_colorBkg = QColor("#E54A50");
        m_bIsPressed = true;
        update();
    }
}

void CloseButton::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    if(m_bIsPressed && this->rect().contains(event->pos()))
    {
        m_bIsChecked = !m_bIsChecked;
        emit clicked(m_bIsChecked);
        m_bIsPressed = false;
    }
}

void CloseButton::leaveEvent(QEvent *event) {
    Q_UNUSED(event);
    m_colorBkg = palette().color(QPalette::Base);
    setPixmap(renderSvg(*m_icon,"gray"));

}

void CloseButton::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setPen(Qt::transparent);
    painter.setBrush(QBrush(m_colorBkg));
    painter.drawRoundedRect(rect(), 4, 4);
    painter.end();
    return QLabel::paintEvent(event);
}

void CloseButton::setIconSize(int size) {
    m_cSize = size;
    update();
}

CloseButton::~CloseButton() {
    delete m_icon;
    if(m_hoverIcon != nullptr)
        delete m_hoverIcon;
}


