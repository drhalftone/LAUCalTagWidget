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

#ifndef LAUCALTAGGLWIDGET_H
#define LAUCALTAGGLWIDGET_H

#include <QtCore>
#include <QObject>

#include <QMenu>
#include <QLabel>
#include <QWidget>
#include <QSpinBox>
#include <QSettings>
#include <QGroupBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QMouseEvent>
#include <QPushButton>
#include <QOpenGLWidget>
#include <QDialogButtonBox>

#include "lauvideoglwidget.h"
#include "laucaltagglobject.h"

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
class LAUCalTagGLWidget : public LAUVideoGLWidget
{
    Q_OBJECT

public:
    explicit LAUCalTagGLWidget(QWidget *parent = nullptr);
    ~LAUCalTagGLWidget();

    LAUCalTagFilterWidget *widget(QWidget *parent = nullptr)
    {
        if (calTagGLObject) {
            return (calTagGLObject->widget(parent));
        }
        return (nullptr);
    }

    LAUMemoryObject grabImage()
    {
        LAUMemoryObject object;
        if (calTagGLObject && calTagGLObject->isValid()) {
            object = calTagGLObject->grabImage();
        }
        return (object);
    }

public slots:

protected:
    void initialize();
    void process();
    void paint();

private:
    LAUCalTagGLObject *calTagGLObject;
};

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
class LAUCalTagWidget : public QWidget
{
    Q_OBJECT

public:
    LAUCalTagWidget(QImage image, QWidget *parent = nullptr);
    LAUCalTagWidget(LAUMemoryObject image, QWidget *parent = nullptr);
    LAUCalTagWidget(QWidget *parent = nullptr);
    ~LAUCalTagWidget()
    {
        if (widget) {
            widget->save();
        }
        qDebug() << "LAUCalTagWidget::~LAUCalTagWidget()";
    }

    bool isValid() const
    {
        if (glWidget) {
            return (glWidget->wasInitialized());
        }
        return (false);
    }

    bool wasInitialized() const
    {
        if (glWidget) {
            return (glWidget->wasInitialized());
        }
        return (false);
    }

    void setFrameSize(int cols, int rows)
    {
        if (glWidget) {
            glWidget->setFrameSize(cols, rows);
        }
    }

    void setFrameFormat(QOpenGLTexture::PixelFormat format)
    {
        if (glWidget) {
            glWidget->setFrameFormat(format);
        }
    }

    void setPixelType(QOpenGLTexture::PixelType type)
    {
        if (glWidget) {
            glWidget->setPixelType(type);
        }
    }

    LAUMemoryObject grabImage()
    {
        if (glWidget) {
            return (glWidget->grabImage());
        }
        return (LAUMemoryObject());
    }

public slots:
    void setFrame(unsigned char *frame)
    {
        if (glWidget) {
            glWidget->setFrame(frame);
        }
    }

    void setFrame(const QVideoFrame &frame)
    {
        if (glWidget) {
            glWidget->setFrame(frame);
        }
    }

    void setFrame(QImage frame)
    {
        if (glWidget) {
            glWidget->setFrame(frame);
        }
    }

private:
    LAUCalTagGLWidget *glWidget;
    LAUCalTagFilterWidget *widget;

    void initialize();
};

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
class LAUCalTagDialog : public QDialog
{
    Q_OBJECT

public:
    LAUCalTagDialog(QImage image, QWidget *parent = nullptr);
    LAUCalTagDialog(LAUMemoryObject image, QWidget *parent = nullptr);

    bool isValid()
    {
        return (validFlag);
    }

protected:
    void accept()
    {
        QSettings settings;
        LAUMemoryObject object = widget->grabImage();
        QString filename = settings.value(QString("LAUCalTagDialog::lastUsedDirectory"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).toString();
        if (filename.endsWith(".png")) {
            filename.chop(3);
            filename.append("tif");
        }
        filename = QFileDialog::getSaveFileName(nullptr, QString("Save image to disk (*.tif)"), filename, QString("*.tif;*.tiff"));
        if (!filename.isNull()) {
            if (object.save(filename)) {
                QDialog::accept();
            }
        }
    }

private:
    bool validFlag;
    LAUCalTagWidget *widget;
};

#endif // LAUCALTAGGLWIDGET_H
