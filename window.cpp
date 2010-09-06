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
#include "ui_window.h"
#include "window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lastPath = QDir::homePath() + "/MyDocs/.documents";

    ui->searchDockWidget->hide();

    scaleFactors << 0.25 << 0.5 << 0.75 << 1. << 1.25 << 1.5 << 2. << 3. << 4.;

    //addDockWidget(Qt::BottomDockWidgetArea, selectionDockWidget);

    documentWidget = new DocumentWidget();
    ui->scrollArea->setWidget(documentWidget);

    connect(ui->exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->openAction, SIGNAL(triggered()), this, SLOT(openFile()));

//    connect(documentControlsAction, SIGNAL(toggled(bool)),
//            controlsDockWidget, SLOT(setVisible(bool)));
//    connect(selectedTextAction, SIGNAL(toggled(bool)),
//            selectionDockWidget, SLOT(setVisible(bool)));
//    connect(controlsDockWidget, SIGNAL(visibilityChanged(bool)),
//            documentControlsAction, SLOT(setChecked(bool)));
//    connect(selectionDockWidget, SIGNAL(visibilityChanged(bool)),
//            selectedTextAction, SLOT(setChecked(bool)));

    connect(ui->pageSpinBox, SIGNAL(valueChanged(int)),
            documentWidget, SLOT(setPage(int)));
    connect(documentWidget, SIGNAL(pageChanged(int)),
            ui->pageSpinBox, SLOT(setValue(int)));
    connect(ui->scaleComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(scaleDocument(int)));
    connect(documentWidget, SIGNAL(textSelected(const QString &)),
            this, SLOT(showSelectedText(const QString &)));

    connect(ui->searchLineEdit, SIGNAL(returnPressed()), this, SLOT(searchDocument()));
    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(searchDocument()));
    connect(ui->searchLineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(checkSearchText(const QString &)));

    ui->selectedTextAction->setChecked(false);
}

void Window::checkSearchText(const QString &text)
{
    if (text.isEmpty())
        documentWidget->setPage();
}

void Window::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open PDF File"),
        lastPath, tr("PDF files (*.pdf)"));

    if (path.isEmpty())
        return;

    if (documentWidget->setDocument(path)) {
        lastPath = path;
        ui->searchLineEdit->setEnabled(true);
        ui->searchComboBox->setEnabled(true);
        ui->findButton->setEnabled(true);
        ui->scaleComboBox->setEnabled(true);
        ui->pageSpinBox->setEnabled(true);
        ui->pageSpinBox->setMinimum(1);
        ui->pageSpinBox->setMaximum(documentWidget->document()->numPages());
        ui->pageSpinBox->setValue(1);
    } else
        QMessageBox::warning(this, tr("PDF Viewer - Failed to Open File"),
                             tr("The specified file could not be opened."));
}

void Window::scaleDocument(int index)
{
    documentWidget->setScale(scaleFactors[index]);
}

void Window::searchDocument()
{
    QRectF location;
    if (ui->searchComboBox->currentIndex() == 0)
        location = documentWidget->searchForwards(ui->searchLineEdit->text());
    else
        location = documentWidget->searchBackwards(ui->searchLineEdit->text());

    QPoint target = documentWidget->matrix().mapRect(location).center().toPoint();
    ui->scrollArea->ensureVisible(target.x(), target.y());
}

void Window::showSelectedText(const QString &text)
{
//    textViewer->setPlainText(text);
    ui->selectedTextAction->setChecked(true);
}

void Window::on_actionSearch_triggered(bool checked)
{
    if(checked) {
        ui->searchDockWidget->show();
    } else {
        ui->searchDockWidget->hide();
    }
}
