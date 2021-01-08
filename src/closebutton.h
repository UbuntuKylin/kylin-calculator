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

#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QIcon>
#include <QMouseEvent>

class CloseButton : public QLabel
{
    Q_OBJECT
public:
    explicit CloseButton(QWidget *parent = nullptr,const QString &filePath = "",const QString &hoverPath = "");

    //Render icon from theme
    const QPixmap renderSvg(const QIcon &icon, QString color);
    // change svg picture's color
    QPixmap drawSymbolicColoredPixmap(const QPixmap &source, QString color);

    void setIconSize(int size);

    ~CloseButton();
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    QIcon *m_icon;
    QIcon *m_hoverIcon;
    bool m_bIsChecked;
    bool m_bIsPressed;
    QColor m_colorBkg;
    int m_cSize;

signals:
    void clicked(bool checked = true);
};

#endif // CLOSEBUTTON_H
