#include "imageloader.h"
#include <QThread>
#include <QDebug>

ImageLoader::ImageLoader(QObject *parent) :
        QThread(parent)
{
    doc = 0;
    abort = false;
}

ImageLoader::~ImageLoader()
{
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();

    wait();
}

void ImageLoader::loadPage(int page, qreal scaleFactor, int physicalDpiX, int physicalDpiY) {
    qDebug() << "Called load page" << page;
    mutex.lock();
    pageQueue.append(page);
    this->scaleFactor = scaleFactor;
    this->physicalDpiX = physicalDpiX;
    this->physicalDpiY = physicalDpiY;
    mutex.unlock();
    if(!isRunning()) {
        qDebug() << "Running for the first time...!";
        start();
    } else {
        qDebug() << "Wake up...!";
        condition.wakeOne();
    }
}

void ImageLoader::run() {
    forever {
        if(abort) {
            qDebug() << "Aborting imageloader thread";
            return;
        }
        mutex.lock();
        foreach(int page, pageQueue) {
            qDebug() << "ImageLoader::run(): Loading page" << page;
            qDebug() << this->thread()->currentThreadId();
            if(doc != 0) {
                if(page > -1 && page < doc->numPages()) {
                    QImage image = doc->page(page)->renderToImage(scaleFactor * physicalDpiX, scaleFactor * physicalDpiY);
                    emit pageLoaded(page, image);
                    qDebug() << "Page" << page << "is loaded by the image loader";
                } else {
                    qWarning() << "Illegal page requested!" << page;
                }
                pageQueue.removeAll(page);
            }
        }
        mutex.unlock();
        qDebug() << "waiting";
        condition.wait(&mutex, 1000); // recheck every 1 seconds for new pages
    }
}
