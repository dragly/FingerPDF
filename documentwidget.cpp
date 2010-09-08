/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the documentation of Qt. It was originally
** published as part of Qt Quarterly.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#include <QtGui>
#include <poppler-qt4.h>
#include "documentwidget.h"
#include "imageloader.h"

DocumentWidget::DocumentWidget(QWidget *parent)
    : QWidget(parent)
{
    mouseMode = ScrollMode;
    currentPage = -1;
    doc = 0;
    rubberBand = 0;
    scaleFactor = 1.0;
    kineticTimer = new QTimer(this);
    kineticTimer->setInterval((int)1.0/25); // kinetic scrolling with 25 fps
    connect(kineticTimer, SIGNAL(timeout()),
            SLOT(updateKinetics()));
    time.start();
    connect(&imageLoader, SIGNAL(pageLoaded(int,QImage)),
            SLOT(pageLoaded(int,QImage)));
    //    setAlignment(Qt::AlignCenter);
}

DocumentWidget::~DocumentWidget()
{
    delete doc;
}

void DocumentWidget::paintEvent(QPaintEvent *event) {

    if(currentPagePosition.y() + currentPixmap.height() < 0) {
        if(currentPage < document()->numPages() - 1) {
            currentPagePosition.setY(currentPagePosition.y() + currentPixmap.height());
            qDebug() << "Next page please...";
            showPage(currentPage + 2);
//            return;
        }
    } else if(currentPagePosition.y() > currentPixmap.height()) {
        if(currentPage > 0) {
            currentPagePosition.setY(currentPagePosition.y() - currentPixmap.height());
            qDebug() << "Previous page please...";
            showPage(currentPage);
//            return;
        }
    }
    QPainter painter(this);
    //    painter.drawText(rect(), Qt::AlignCenter, "Hello World");
    QPointF prevPixmapPosition = currentPagePosition - QPointF(0, currentPixmap.height() + 10);
    QPointF nextPixmapPosition = currentPagePosition + QPointF(0, currentPixmap.height() + 10);
    painter.drawPixmap(currentPagePosition, currentPixmap);
    if(currentPage > 0) {
        painter.drawPixmap(prevPixmapPosition, prevPixmap);
    }
    painter.drawPixmap(nextPixmapPosition, nextPixmap);

    //    if (!searchLocation.isEmpty()) {
    //        QRect highlightRect = matrix().mapRect(searchLocation).toRect();
    //        highlightRect.adjust(-2, -2, 2, 2);
    //        painter.fillRect(image.rect(), QColor(0, 0, 0, 32));
    //        painter.drawImage(highlightRect, highlight);
    //        painter.end();
    //    }

}

Poppler::Document *DocumentWidget::document()
{
    return doc;
}

QMatrix DocumentWidget::matrix() const
{
    return QMatrix(scaleFactor * physicalDpiX() / 72.0, 0,
                   0, scaleFactor * physicalDpiY() / 72.0,
                   0, 0);
}

void DocumentWidget::mousePressEvent(QMouseEvent *event)
{
    if (!doc)
        return;
    int currentTime = time.elapsed();

    if(mouseMode == ScrollMode) {
        dragCurrentPosition = event->pos();
        dragStartPosition = event->pos();
        dragLastPosition = event->pos();
        dragLongPosition = event->pos();
        dragLongNextPosition = event->pos();
        dragLongTime = currentTime;
        dragLastTime = currentTime;
        dragStartTime = currentTime;
        kineticTimer->stop();
        kineticSpeed *= 0;
    } else if(mouseMode == SelectMode) {
        dragCurrentPosition = event->pos();
        if (!rubberBand)
            rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        rubberBand->setGeometry(QRect(dragCurrentPosition.toPoint(), QSize()));
        rubberBand->show();
    }
}

void DocumentWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!doc)
        return;

    int currentTime = time.elapsed();
    if(mouseMode == ScrollMode) {
        dragCurrentPosition = event->pos();
        drag = dragCurrentPosition - dragLastPosition;
        dragLong = dragCurrentPosition - dragLongPosition;
        if(currentTime - dragLongTime > 200 && currentTime - dragLongTime < 250) { // time to set dragNext
            dragLongNextPosition = dragCurrentPosition;
        }
        if(currentTime - dragLongTime > 400) {
            dragLongTime = currentTime;
            dragLongPosition = dragLongNextPosition;
        }
        //        qDebug() << dragLong.x() << dragLong.y() << (double)dragLong.x() / (double) dragLong.y();
        double aspect = (double)dragLong.x() / (double) dragLong.y();
        if(0.6 < fabs(aspect) && fabs(aspect) < 2.5) { // diagonal drag
            currentPagePosition += drag;
        } else { //
            if(abs(dragLong.x()) > abs(dragLong.y())) {
                currentPagePosition.setX(currentPagePosition.x() + drag.x());
            } else if(abs(dragLong.x()) < abs(dragLong.y())) {
                currentPagePosition.setY(currentPagePosition.y() + drag.y());
            } else { // they are the same, but will probably not happen
                currentPagePosition += drag;
            }
        }
        dragLastPosition = event->pos();
        dragLastTime = currentTime;
        update();
    } else if(mouseMode == SelectMode) {
        rubberBand->setGeometry(QRect(dragCurrentPosition.toPoint(), event->pos()).normalized());
    }
}

void DocumentWidget::mouseReleaseEvent(QMouseEvent *)
{
    if (!doc)
        return;

    int currentTime = time.elapsed();
    if(mouseMode == ScrollMode) {
        int timeElapsed = currentTime - dragStartTime;
        QPointF dragVector = dragCurrentPosition - dragStartPosition;
        int dragLength = (dragVector).manhattanLength();
        if(timeElapsed > 1 && dragLength > 1) {
            kineticSpeed = (dragVector) / (double)(timeElapsed);
            kineticTimer->start();
            currentPagePositionPoint = currentPagePosition.toPoint();
            lastKineticTime = time.elapsed();
            double aspect = (double)dragLong.x() / (double) dragLong.y();
            if(0.6 < fabs(aspect) && fabs(aspect) < 2.5) { // diagonal drag
                // nothing changes
            } else { //
                if(abs(dragLong.x()) > abs(dragLong.y())) {
                    kineticSpeed.setY(0);
                } else if(abs(dragLong.x()) < abs(dragLong.y())) {
                    kineticSpeed.setX(0);
                }
            }
            if(kineticSpeed.manhattanLength() > 2) { // something went wrong, too high speed!
                kineticSpeed *= 0;
            }
        }
        dragLastTime = currentTime;
    } else if(mouseMode == SelectMode) {
        if (!rubberBand->size().isEmpty()) {
            // Correct for the margin around the image in the label.
            QRectF rect = QRectF(rubberBand->pos(), rubberBand->size());
            //            rect.moveLeft(rect.left() - (width() - pixmap()->width()) / 2.0);
            //            rect.moveTop(rect.top() - (height() - pixmap()->height()) / 2.0);
            selectedText(rect);
        }

        rubberBand->hide();
    }
}

void DocumentWidget::updateKinetics() {
    //    qDebug() << kineticSpeed;
    int currentTime = time.elapsed();
    int elapsedTime = currentTime - lastKineticTime;
    kineticSpeed -= 0.03 * kineticSpeed; // "friction"

    currentPagePosition = currentPagePosition + (kineticSpeed * (double)elapsedTime);
    if(currentPagePositionPoint != currentPagePosition.toPoint()) {
        currentPagePositionPoint = currentPagePosition.toPoint();
        update();
    }
    if(kineticSpeed.manhattanLength() < 0.1) {
        kineticTimer->stop();
        kineticSpeed *= 0;
    }
    lastKineticTime = currentTime;
}

qreal DocumentWidget::scale() const
{
    return scaleFactor;
}

void DocumentWidget::showPage(int page)
{
    if(page - 1 == currentPage) { // do nothing

    } else if(page - 1 < currentPage) {
        nextPixmap = currentPixmap;
        currentPixmap = prevPixmap;
        if(page - 2 > 0) { // load prevPixmap
            prevPixmap = QPixmap(currentPixmap.width(), currentPixmap.height());
            QPainter painter(&prevPixmap);
            painter.setBrush(Qt::lightGray);
            painter.drawRect(nextPixmap.rect());
            painter.setPen(Qt::black);
            painter.drawText(nextPixmap.rect(), Qt::AlignCenter, "Loading...");
            painter.end();
            imageLoader.loadPage(page - 2, scaleFactor, physicalDpiX(), physicalDpiY());
        } else {
            prevPixmap = QPixmap();
        }
    } else if (page - 1 > currentPage){
        prevPixmap = currentPixmap;
        currentPixmap = nextPixmap;
        if(page - 1 < document()->numPages() - 1) { // load nextPixmap
            nextPixmap = QPixmap(currentPixmap.width(), currentPixmap.height());
            QPainter painter(&nextPixmap);
            painter.setBrush(Qt::lightGray);
            painter.drawRect(nextPixmap.rect());
            painter.setPen(Qt::black);
            painter.drawText(nextPixmap.rect(), Qt::AlignCenter, "Loading...");
            painter.end();
            imageLoader.loadPage(page, scaleFactor, physicalDpiX(), physicalDpiY());
        } else {
            nextPixmap = QPixmap();
        }
    }

    if (page != -1 && page != currentPage + 1) {
        currentPage = page - 1;
        emit pageChanged(page);
    }

    if(currentPixmap.isNull()) {
        imageLoader.loadPage(page - 1, scaleFactor, physicalDpiX(), physicalDpiY());
    }

    update();
}

void DocumentWidget::pageLoaded(int page, QImage image) {
    qDebug() << "Page has been loaded" << image.isNull();
    qDebug() << "currentPage" << currentPage << "recieved page" << page;
    if(page == currentPage) {
        qDebug() << "Setting current";
        currentPixmap = QPixmap::fromImage(image);
    } else if(page + 1 == currentPage) {
        qDebug() << "Setting prevPixmap";
        prevPixmap = QPixmap::fromImage(image);

    } else if(page - 1 == currentPage) {
        qDebug() << "Setting nextPixmap";

        nextPixmap = QPixmap::fromImage(image);
    }
    update();
}

QRectF DocumentWidget::searchBackwards(const QString &text)
{
    QRectF oldLocation = searchLocation;

    int page = currentPage;
    if (oldLocation.isNull())
        page -= 1;

    while (page > -1) {

        QList<QRectF> locations;
        searchLocation = QRectF();

        while (doc->page(page)->search(text, searchLocation,
                                       Poppler::Page::NextResult, Poppler::Page::CaseInsensitive)) {

            if (searchLocation != oldLocation)
                locations.append(searchLocation);
            else
                break;
        }

        int index = locations.indexOf(oldLocation);
        if (index == -1 && !locations.isEmpty()) {
            searchLocation = locations.last();
            showPage(page + 1);
            return searchLocation;
        } else if (index > 0) {
            searchLocation = locations[index - 1];
            showPage(page + 1);
            return searchLocation;
        }

        oldLocation = QRectF();
        page -= 1;
    }

    if (currentPage == doc->numPages() - 1)
        return QRectF();

    oldLocation = QRectF();
    page = doc->numPages() - 1;

    while (page > currentPage) {

        QList<QRectF> locations;
        searchLocation = QRectF();

        while (doc->page(page)->search(text, searchLocation,
                                       Poppler::Page::NextResult, Poppler::Page::CaseInsensitive)) {

            locations.append(searchLocation);
        }

        if (!locations.isEmpty()) {
            searchLocation = locations.last();
            showPage(page + 1);
            return searchLocation;
        }
        page -= 1;
    }

    return QRectF();
}

QRectF DocumentWidget::searchForwards(const QString &text)
{
    int page = currentPage;
    while (page < doc->numPages()) {

        if (doc->page(page)->search(text, searchLocation,
                                    Poppler::Page::NextResult, Poppler::Page::CaseInsensitive)) {
            if (!searchLocation.isNull()) {
                showPage(page + 1);
                return searchLocation;
            }
        }
        page += 1;
        searchLocation = QRectF();
    }

    page = 0;

    while (page < currentPage) {

        searchLocation = QRectF();

        if (doc->page(page)->search(text, searchLocation,
                                    Poppler::Page::NextResult, Poppler::Page::CaseInsensitive)) {
            if (!searchLocation.isNull()) {
                showPage(page + 1);
                return searchLocation;
            }
        }
        page += 1;
    }

    return QRectF();
}

void DocumentWidget::selectedText(const QRectF &rect)
{
    QRectF selectedRect = matrix().inverted().mapRect(rect);
    // QString text = doc->page(currentPage)->text(selectedRect);

    QString text;
    bool hadSpace = false;
    QPointF center;
    foreach (Poppler::TextBox *box, doc->page(currentPage)->textList()) {
        if (selectedRect.intersects(box->boundingBox())) {
            if (hadSpace)
                text += " ";
            if (!text.isEmpty() && box->boundingBox().top() > center.y())
                text += "\n";
            text += box->text();
            hadSpace = box->hasSpaceAfter();
            center = box->boundingBox().center();
        }
    }

    if (!text.isEmpty())
        emit textSelected(text);
}

bool DocumentWidget::setDocument(const QString &filePath)
{
    Poppler::Document *oldDocument = doc;

    doc = Poppler::Document::load(filePath);
    if (doc) {
        delete oldDocument;
        doc->setRenderHint(Poppler::Document::Antialiasing);
        doc->setRenderHint(Poppler::Document::TextAntialiasing);
        searchLocation = QRectF();
        currentPage = -1;
        setPage(1);
        imageLoader.setDocument(doc);
    }
    return doc != 0;
}

void DocumentWidget::setPage(int page)
{
    if (page != currentPage + 1) {
        searchLocation = QRectF();
        showPage(page);
    }
}

void DocumentWidget::setScale(qreal scale)
{
    if (scaleFactor != scale) {
        scaleFactor = scale;
        showPage();
    }
}
