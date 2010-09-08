#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QObject>
#include <QRectF>
#include <QPixmap>
#include <poppler-qt4.h>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class ImageLoader : public QThread
{
    Q_OBJECT
public:
    explicit ImageLoader(QObject *parent = 0);
    ~ImageLoader();
    void setDocument(Poppler::Document *doc) {this->doc = doc;}
    void loadPage(int page, qreal scaleFactor, int physicalDpiX, int physicalDpiY);

signals:
    void pageLoaded(int page, QImage image);

protected:
    void run();

public slots:

private:
    Poppler::Document *doc;

    QMutex mutex;
    QWaitCondition condition;
    qreal scaleFactor;
    int physicalDpiX;
    int physicalDpiY;
    bool abort;

    QList<int> pageQueue;
    QHash<int,QImage> pageImages;

};

#endif // IMAGELOADER_H
