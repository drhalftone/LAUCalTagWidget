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

#ifndef LAUCALTAGOPTGLWIDGET_H
#define LAUCALTAGOPTGLWIDGET_H

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
#include "laucaltagoptglobject.h"

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
class LAUCalTagOptGLWidget : public LAUVideoGLWidget
{
    Q_OBJECT

public:
    explicit LAUCalTagOptGLWidget(QWidget *parent = nullptr);
    ~LAUCalTagOptGLWidget();

    LAUCalTagOptFilterWidget *widget(QWidget *parent = nullptr)
    {
        if (calTagOptGLObject) {
            return (calTagOptGLObject->widget(parent));
        }
        return (nullptr);
    }

    LAUMemoryObject grabImage()
    {
        LAUMemoryObject object;
        if (calTagOptGLObject && calTagOptGLObject->isValid()) {
            object = calTagOptGLObject->grabImage();
        }
        return (object);
    }

public slots:

protected:
    void initialize();
    void process();
    void paint();

private:
    LAUCalTagOptGLObject *calTagOptGLObject;
};

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
class LAUCalTagOptWidget : public QWidget
{
    Q_OBJECT

public:
    LAUCalTagOptWidget(QImage image, QWidget *parent = nullptr);
    LAUCalTagOptWidget(LAUMemoryObject image, QWidget *parent = nullptr);
    LAUCalTagOptWidget(QWidget *parent = nullptr);
    ~LAUCalTagOptWidget()
    {
        qDebug() << "LAUCalTagOptWidget::~LAUCalTagOptWidget()";
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
    LAUCalTagOptGLWidget *glWidget;
    LAUCalTagOptFilterWidget *widget;

    void initialize();
};

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
class LAUCalTagOptDialog : public QDialog
{
    Q_OBJECT

public:
    LAUCalTagOptDialog(QImage image, QWidget *parent = nullptr);
    LAUCalTagOptDialog(LAUMemoryObject image, QWidget *parent = nullptr);

protected:
    void accept()
    {
        LAUMemoryObject object = widget->grabImage();
        if (object.save(QString())) {
            QDialog::accept();
        }
    }

private:
    LAUCalTagOptWidget *widget;
};

#endif // LAUCALTAGOPTGLWIDGET_H
