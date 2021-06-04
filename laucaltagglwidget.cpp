/*********************************************************************************
 *                                                                               *
 * Copyright (c) 2017, Dr. Daniel L. Lau and Alex Burkhart                       *
 * All rights reserved.                                                          *
 *                                                                               *
 * Redistribution and use in source and binary forms, with or without            *
 * modification, are permitted provided that the following conditions are met:   *
 * 1. Redistributions of source code must retain the above copyright             *
 *    notice, this list of conditions and the following disclaimer.              *
 * 2. Redistributions in binary form must reproduce the above copyright          *
 *    notice, this list of conditions and the following disclaimer in the        *
 *    documentation and/or other materials provided with the distribution.       *
 * 3. All advertising materials mentioning features or use of this software      *
 *    must display the following acknowledgement:                                *
 *    This product includes software developed by the <organization>.            *
 * 4. Neither the name of the <organization> nor the                             *
 *    names of its contributors may be used to endorse or promote products       *
 *    derived from this software without specific prior written permission.      *
 *                                                                               *
 * THIS SOFTWARE IS PROVIDED BY Dr. Daniel L. Lau ''AS IS'' AND ANY              *
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED     *
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE        *
 * DISCLAIMED. IN NO EVENT SHALL Dr. Daniel L. Lau BE LIABLE FOR ANY             *
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES    *
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;  *
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND   *
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS *
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                  *
 *                                                                               *
 *********************************************************************************/

#include "laucaltagglwidget.h"

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagDialog::LAUCalTagDialog(QImage image, QWidget *parent) : QDialog(parent)
{
    if (image.isNull()) {
        QSettings settings;
        QString directory = settings.value("LAUCalTagDialog::lastUsedDirectory", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).toString();
        QString filename = QFileDialog::getOpenFileName(0, QString("Load image from disk"), directory, QString("*.tif *.tiff *.bmp *.jpg *.jpeg"));
        if (filename.isEmpty() == false) {
            settings.setValue("LAUCalTagDialog::lastUsedDirectory", QFileInfo(filename).absolutePath());
        } else {
            return;
        }
        image = QImage(filename);
        this->setWindowTitle(QFileInfo(filename).baseName());
    }

    this->setLayout(new QVBoxLayout());
    this->layout()->setContentsMargins(0, 0, 0, 0);
    widget = new LAUCalTagWidget(image);
    this->layout()->addWidget(widget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(accept()));
    connect(buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(reject()));
    this->layout()->addWidget(buttonBox);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagDialog::LAUCalTagDialog(LAUMemoryObject image, QWidget *parent) : QDialog(parent)
{
    if (image.isNull()) {
        QSettings settings;
        QString directory = settings.value("LAUCalTagDialog::lastUsedDirectory", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).toString();
        QString filename = QFileDialog::getOpenFileName(0, QString("Load image from disk"), directory, QString("*.tif *.tiff"));
        if (filename.isEmpty() == false) {
            settings.setValue("LAUCalTagDialog::lastUsedDirectory", QFileInfo(filename).absolutePath());
        } else {
            return;
        }
        image = LAUMemoryObject(filename);
    }

    this->setLayout(new QVBoxLayout());
    this->layout()->setContentsMargins(0, 0, 0, 0);
    widget = new LAUCalTagWidget(image);
    this->layout()->addWidget(widget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(accept()));
    connect(buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(reject()));
    this->layout()->addWidget(buttonBox);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagWidget::LAUCalTagWidget(QImage image, QWidget *parent) : QWidget(parent), glWidget(nullptr), widget(nullptr)
{
    this->setLayout(new QVBoxLayout());
    this->setWindowTitle(QString("LAUCalTag Dialog"));
    this->layout()->setContentsMargins(6, 6, 6, 6);
    this->layout()->setSpacing(10);

    glWidget = new LAUCalTagGLWidget();
    glWidget->setMinimumSize(320, 240);
    glWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->layout()->addWidget(glWidget);

    widget = glWidget->widget();
    widget->load();
    this->layout()->addWidget(widget);

    glWidget->setFrame(image);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagWidget::LAUCalTagWidget(LAUMemoryObject image, QWidget *parent) : QWidget(parent), glWidget(nullptr), widget(nullptr)
{
    this->setLayout(new QVBoxLayout());
    this->setWindowTitle(QString("LAUCalTag Dialog"));
    this->layout()->setContentsMargins(6, 6, 6, 6);
    this->layout()->setSpacing(10);

    glWidget = new LAUCalTagGLWidget();
    glWidget->setMinimumSize(320, 240);
    glWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->layout()->addWidget(glWidget);

    widget = glWidget->widget();
    widget->load();
    this->layout()->addWidget(widget);

    glWidget->setFrame(image);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagWidget::LAUCalTagWidget(QWidget *parent) : QWidget(parent), glWidget(nullptr), widget(nullptr)
{
    this->setLayout(new QVBoxLayout());
    this->setWindowTitle(QString("LAUCalTag Dialog"));
    this->layout()->setContentsMargins(6, 6, 6, 6);
    this->layout()->setSpacing(10);

    glWidget = new LAUCalTagGLWidget();
    glWidget->setMinimumSize(320, 240);
    glWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->layout()->addWidget(glWidget);

    widget = glWidget->widget();
    widget->load();
    this->layout()->addWidget(widget);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagGLWidget::LAUCalTagGLWidget(QWidget *parent) : LAUVideoGLWidget(parent), calTagGLObject(nullptr)
{
    calTagGLObject = new LAUCalTagGLObject();
    connect(calTagGLObject, SIGNAL(update()), this, SLOT(onUpdate()));
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagGLWidget::~LAUCalTagGLWidget()
{
    if (calTagGLObject) {
        if (calTagGLObject->isValid()) {
            makeCurrent();
        }
        delete calTagGLObject;
    }
    qDebug() << "LAUCalTagGLWidget::~LAUCalTagGLWidget()";
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagGLWidget::initialize()
{
    if (calTagGLObject) {
        calTagGLObject->initializeGL();
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagGLWidget::process()
{
    if (calTagGLObject) {
        calTagGLObject->processGL(videoTexture);
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagGLWidget::paint()
{
    if (calTagGLObject && calTagGLObject->isValid()) {
        calTagGLObject->paintGL();
    } else {
        LAUVideoGLWidget::paint();
    }
}
