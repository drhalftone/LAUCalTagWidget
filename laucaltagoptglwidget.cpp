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

#include "laucaltagoptglwidget.h"

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagOptDialog::LAUCalTagOptDialog(QImage image, QWidget *parent) : QDialog(parent)
{
    if (image.isNull()) {
        QSettings settings;
        QString directory = settings.value("LAUCalTagOptDialog::lastUsedDirectory", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).toString();
        QString filename = QFileDialog::getOpenFileName(0, QString("Load image from disk"), directory, QString("*.tif *.tiff *.bmp *.jpg *.jpeg *.png"));
        if (filename.isEmpty() == false) {
            settings.setValue("LAUCalTagOptDialog::lastUsedDirectory", QFileInfo(filename).absoluteFilePath());
        } else {
            return;
        }
        image = QImage(filename);
    }

    this->setLayout(new QVBoxLayout());
    this->layout()->setContentsMargins(0, 0, 0, 0);
    widget = new LAUCalTagOptWidget(image);
    this->layout()->addWidget(widget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(accept()));
    connect(buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(reject()));
    this->layout()->addWidget(buttonBox);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagOptDialog::LAUCalTagOptDialog(LAUMemoryObject image, QWidget *parent) : QDialog(parent)
{
    if (image.isNull()) {
        QSettings settings;
        QString directory = settings.value("LAUCalTagOptDialog::lastUsedDirectory", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).toString();
        QString filename = QFileDialog::getOpenFileName(0, QString("Load image from disk"), directory, QString("*.tif *.tiff"));
        if (filename.isEmpty() == false) {
            settings.setValue("LAUCalTagOptDialog::lastUsedDirectory", QFileInfo(filename).absoluteFilePath());
        } else {
            return;
        }
        image = LAUMemoryObject(filename);
    }

    this->setLayout(new QVBoxLayout());
    this->layout()->setContentsMargins(0, 0, 0, 0);
    widget = new LAUCalTagOptWidget(image);
    this->layout()->addWidget(widget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(accept()));
    connect(buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(reject()));
    this->layout()->addWidget(buttonBox);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagOptWidget::LAUCalTagOptWidget(QImage image, QWidget *parent) : QWidget(parent), glWidget(nullptr), widget(nullptr)
{
    this->setLayout(new QVBoxLayout());
    this->setWindowTitle(QString("LAUCalTag Dialog"));
    this->layout()->setContentsMargins(6, 6, 6, 6);
    this->layout()->setSpacing(10);

    glWidget = new LAUCalTagOptGLWidget();
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
LAUCalTagOptWidget::LAUCalTagOptWidget(LAUMemoryObject image, QWidget *parent) : QWidget(parent), glWidget(nullptr), widget(nullptr)
{
    this->setLayout(new QVBoxLayout());
    this->setWindowTitle(QString("LAUCalTag Dialog"));
    this->layout()->setContentsMargins(6, 6, 6, 6);
    this->layout()->setSpacing(10);

    glWidget = new LAUCalTagOptGLWidget();
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
LAUCalTagOptWidget::LAUCalTagOptWidget(QWidget *parent) : QWidget(parent), glWidget(nullptr), widget(nullptr)
{
    this->setLayout(new QVBoxLayout());
    this->setWindowTitle(QString("LAUCalTag Dialog"));
    this->layout()->setContentsMargins(6, 6, 6, 6);
    this->layout()->setSpacing(10);

    glWidget = new LAUCalTagOptGLWidget();
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
LAUCalTagOptGLWidget::LAUCalTagOptGLWidget(QWidget *parent) : LAUVideoGLWidget(parent), calTagOptGLObject(nullptr)
{
    calTagOptGLObject = new LAUCalTagOptGLObject();
    connect(calTagOptGLObject, SIGNAL(update()), this, SLOT(onUpdate()));
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagOptGLWidget::~LAUCalTagOptGLWidget()
{
    if (calTagOptGLObject) {
        if (calTagOptGLObject->isValid()) {
            makeCurrent();
        }
        delete calTagOptGLObject;
    }
    qDebug() << "LAUCalTagOptGLWidget::~LAUCalTagOptGLWidget()";
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagOptGLWidget::initialize()
{
    if (calTagOptGLObject) {
        calTagOptGLObject->initializeGL();
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagOptGLWidget::process()
{
    if (calTagOptGLObject) {
        calTagOptGLObject->processGL(videoTexture);
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagOptGLWidget::paint()
{
    if (calTagOptGLObject && calTagOptGLObject->isValid()) {
        calTagOptGLObject->paintGL();
    } else {
        LAUVideoGLWidget::paint();
    }
}
