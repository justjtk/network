#include "interface.h"

QPixmap PixmapToRound(QPixmap &src, int radius)
{
    if (src.isNull()) {
        return QPixmap();
    }

    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);

    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}

QPixmap PixmapToRound_angle(QPixmap &src, int radius)//没有
{
    if (src.isNull()) {
        return QPixmap();
    }

    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);

    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}

QPixmap getRoundRectPixmap(QPixmap srcPixMap,const QSize & size, int radius)//没用
{
    //不处理空数据或者错误数据
    if (srcPixMap.isNull()) {
        return srcPixMap;
    }

    //获取图片尺寸
    int imageWidth = size.width();
    int imageHeight = size.height();

    //处理大尺寸的图片,保证图片显示区域完整
    QPixmap newPixMap = srcPixMap.scaled(imageWidth, (imageHeight == 0 ? imageWidth : imageHeight),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPixmap destImage(imageWidth, imageHeight);
    destImage.fill(Qt::transparent);
    QPainter painter(&destImage);
    // 抗锯齿
    painter.setRenderHints(QPainter::Antialiasing, true);
    // 图片平滑处理
    painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
    // 将图片裁剪为圆角
    QPainterPath path;
    QRect rect(0, 0, imageWidth, imageHeight);
    path.addRoundedRect(rect, radius, radius);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, imageWidth, imageHeight, newPixMap);
    return destImage;
}

QPixmap Roundpix(const QPixmap& img_in, int radius)//没用
{
    if (img_in.isNull())
    {
        return QPixmap();
    }
    QSize size(img_in.size());
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(mask.rect(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(mask.rect(), radius, radius);
    QPixmap image = img_in;// .scaled(size);
    image.setMask(mask);
    return image;
}

QPixmap scaledPixmap(const QPixmap &src, int width, int height) {
    return src.scaled(width, (height == 0 ? width : height),
            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

QPixmap generatePixmap(const QPixmap &src, const int &radius) {

        // 无效图片不处理
        if (src.isNull()) {
            return src;
        }

        // 压缩图片
        QPixmap pixmap = scaledPixmap(src, radius * 2,radius * 2);

        QPixmap dest(2*radius, 2*radius);
        dest.fill(Qt::transparent);
        QPainter painter(&dest);
        // 抗锯齿 + 平滑边缘处理
        painter.setRenderHints(QPainter::Antialiasing, true);
        painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
        // 裁剪为圆角
        QPainterPath path;
        path.addEllipse(0, 0, 2*radius, 2*radius);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, 2*radius, 2*radius, pixmap);

        return dest;
    }
