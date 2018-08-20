/*********************************************************************************
 *                                                                               *
 * Copyright (c) 2017, Dr. Daniel L. Lau                                         *
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

#ifndef LAUWEBCAMERAWIDGET_H
#define LAUWEBCAMERAWIDGET_H

#include <QList>
#include <QTimer>
#include <QLabel>
#include <QImage>
#include <QCamera>
#include <QWidget>
#include <QThread>
#include <QSettings>
#include <QFileDialog>
#include <QPushButton>
#include <QVideoFrame>
#include <QStringList>
#include <QVBoxLayout>
#include <QCameraInfo>
#include <QInputDialog>
#include <QApplication>
#include <QDialogButtonBox>
#include <QCameraImageCapture>

#include "lauvideosurface.h"
#include "laucaltagglwidget.h"

#ifdef USEBASLERUSBCAMERA
#include "laubaslerusbcamera.h"
#endif

#define LAUWEBCAMERAWIDGETWIDTH  640
#define LAUWEBCAMERAWIDGETHEIGHT 480

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
class LAUWebCameraWidget : public QWidget
{
    Q_OBJECT

public:
    LAUWebCameraWidget(QCamera::CaptureMode capture, QWidget *parent = 0);
    ~LAUWebCameraWidget();

    bool isValid() const
    {
        return (camera);
    }

    bool isNull() const
    {
        return (!isValid());
    }

    void grabImage();

public slots:
    void onCapture();
    void onImageAvailable(int id, QImage image);

    void setFrame(LAUMemoryObject object)
    {
        emit emitFrame(object);
    }

protected:
    void showEvent(QShowEvent *)
    {
        if (camera) {
#ifdef USEBASLERUSBCAMERA
            emit emitFrame(camera->memoryObject());
            emit emitFrame(camera->memoryObject());
            emit emitFrame(camera->memoryObject());
#else
            camera->start();
            QTimer::singleShot(1000, this, SLOT(onCapture()));
#endif
        }
    }

private:
#ifdef USEBASLERUSBCAMERA
    LAUBaslerUSBCamera *camera;
    QObject *imageCapture;
    QObject *surface;
#else
    QCamera *camera;
    QCameraImageCapture *imageCapture;
    LAUVideoSurface *surface;
#endif
    QThread *thread;
    LAUVideoGLWidget *label;
    LAUCalTagFilterWidget *widget;
    QCamera::CaptureMode mode;

signals:
    void emitFrame(LAUMemoryObject);
};

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
class LAUWebCameraDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LAUWebCameraDialog(QCamera::CaptureMode capture, QWidget *parent = 0) : QDialog(parent)
    {
        // CREATE A WIDGET TO WRAP AROUND
        widget = new LAUWebCameraWidget(capture);

        // SET THE LAYOUT AND DISPLAY OUR WIDGET INSIDE OF IT
        this->setWindowTitle(QString("LAUCalTagWidget"));
        this->setLayout(new QVBoxLayout());
        this->layout()->setContentsMargins(0, 0, 0, 0);
        this->layout()->addWidget(widget);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        connect(buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(accept()));
        connect(buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(reject()));
        this->layout()->addWidget(buttonBox);
    }

    bool isValid() const
    {
        return (widget->isValid());
    }

    bool isNull() const
    {
        return (widget->isNull());
    }

protected:
    void accept()
    {
        widget->grabImage();
    }

private:
    LAUWebCameraWidget *widget;
};

#endif // LAUWEBCAMERAWIDGET_H
