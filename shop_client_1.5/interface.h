#ifndef INTERFACE_H
#define INTERFACE_H

#include <QPixmap>
#include <QBitmap>
#include <QPainter>

QPixmap PixmapToRound(QPixmap &src, int radius);
QPixmap getRoundRectPixmap(QPixmap srcPixMap,const QSize & size, int radius);
QPixmap Roundpix(const QPixmap& img_in, int radius);

QPixmap scaledPixmap(const QPixmap &src, int width, int height);
QPixmap generatePixmap(const QPixmap &src, const int &radius);

#endif // INTERFACE_H

