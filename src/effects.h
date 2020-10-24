#include <qimage.h>
#include <algorithm>

#define CLAMP(val, min, max) (val < max ? (val > min ? val : min) : max)


static int calcValue(unsigned int pixel)
{
    const int red = qRed(pixel);
    const int green = qGreen(pixel);
    const int blue = qBlue(pixel);
    if (red > green) {
        if (red > blue) {
            return red;
        } else {
            return blue;
        }
    } else if (blue > green) {
        return blue;
    } else {
        return green;
    }
}

static void adjustContrast(QPixmap &pixmap, int c)
{
    QImage img = pixmap.convertToImage();

    if(c > 255)
        c = 255;
    if(c < -50)
        c =  -50;
    int pixels = img.depth() > 8 ? img.width()*img.height() :
        img.numColors();
    unsigned int *data = img.depth() > 8 ? (unsigned int *)img.bits() :
        (unsigned int *)img.colorTable();
    int i, r, g, b;
    c += 50;
    for(i=0; i < pixels; ++i){
        r = (qRed(data[i]) - 127) * c / 50 + 127;
        g = (qGreen(data[i]) - 127) * c / 50 + 127;
        b = (qBlue(data[i]) - 127) * c / 50 + 127;
        data[i] = qRgb(CLAMP(r, 0, 255), CLAMP(g, 0, 255), CLAMP(b, 0, 255));
    }

    pixmap.convertFromImage(img);
}

static void adjustBrightness(QPixmap &pixmap, float percent)
{
    QImage image = pixmap.convertToImage();
    int i, tmp, r, g, b;
    int segColors = image.depth() > 8 ? 256 : image.numColors();
    unsigned char *segTbl = new unsigned char[segColors];
    int pixels = image.depth() > 8 ? image.width()*image.height() :
        image.numColors();
    unsigned int *data = image.depth() > 8 ? (unsigned int *)image.bits() :
        (unsigned int *)image.colorTable();

    bool brighten = (percent >= 0);
    if(percent < 0)
        percent = -percent;

    if(brighten){ // keep overflow check out of loops
        for(i=0; i < segColors; ++i){
            tmp = (int)(i*percent);
            if(tmp > 255)
                tmp = 255;
            segTbl[i] = tmp;
        }
    }
    else{
        for(i=0; i < segColors; ++i){
            tmp = (int)(i*percent);
            if(tmp < 0)
                tmp = 0;
            segTbl[i] = tmp;
        }
    }

    if(brighten){ // same here
        for(i=0; i < pixels; ++i){
            r = qRed(data[i]);
            g = qGreen(data[i]);
            b = qBlue(data[i]);
            r = r + segTbl[r] > 255 ? 255 : r + segTbl[r];
            g = g + segTbl[g] > 255 ? 255 : g + segTbl[g];
            b = b + segTbl[b] > 255 ? 255 : b + segTbl[b];
            data[i] = qRgb(r, g, b);
        }
    }
    else{
        for(i=0; i < pixels; ++i){
            r = qRed(data[i]);
            g = qGreen(data[i]);
            b = qBlue(data[i]);
            r = r - segTbl[r] < 0 ? 0 : r - segTbl[r];
            g = g - segTbl[g] < 0 ? 0 : g - segTbl[g];
            b = b - segTbl[b] < 0 ? 0 : b - segTbl[b];
            data[i] = qRgb(r, g, b);
        }
    }
    delete [] segTbl;

    pixmap.convertFromImage(image);
}
