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

#include "lauwebcamerawidget.h"

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUWebCameraWidget::LAUWebCameraWidget(QCamera::CaptureMode capture, QWidget *parent) : QWidget(parent), mode(capture), thread(NULL), camera(NULL), imageCapture(NULL), surface(NULL)
{
    this->setLayout(new QVBoxLayout());
    this->setWindowTitle(QString("LAUCalTag Video Widget"));
    this->layout()->setContentsMargins(6, 6, 6, 6);

    label = new LAUCalTagGLWidget();
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->layout()->addWidget(label);

    LAUCalTagFilterWidget *widget = new LAUCalTagFilterWidget((LAUCalTagGLWidget *)label);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    this->layout()->addWidget(widget);

    QStringList strings;
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for (int n = 0; n < cameras.count(); n++) {
        strings << cameras.at(n).description();
    }

    if (strings.count() > 1) {
        bool okay = false;
        QString string = QInputDialog::getItem(this, QString("Select Camera"), QString("Select input device"), strings, 0, false, &okay);
        if (okay) {
            int n = strings.indexOf(string);
            camera = new QCamera(cameras.at(n));
        }
    } else if (strings.count() == 1) {
        camera = new QCamera(cameras.first());
    }

    if (camera) {
        surface = new LAUVideoSurface();
        surface->setLabel(label);

        QCameraViewfinderSettings set = camera->viewfinderSettings();
        QSize res = set.resolution();
        set.setResolution(LAUWEBCAMERAWIDGETWIDTH, LAUWEBCAMERAWIDGETHEIGHT);
        set.setMaximumFrameRate(30.0f);
        set.setMinimumFrameRate(30.0f);
        set.setPixelFormat(QVideoFrame::Format_ARGB32);
        camera->setViewfinderSettings(set);

        camera->setViewfinder(surface);
        camera->setCaptureMode(mode);

        if (mode == QCamera::CaptureStillImage) {
            imageCapture = new QCameraImageCapture(camera);
            imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
            connect(imageCapture, SIGNAL(imageCaptured(int, QImage)), this, SLOT(onImageAvailable(int, QImage)));
        }

        // CREATE A NEW THREAD TO HOST THE CAMERA
        thread = new QThread();
        camera->moveToThread(thread);
        thread->start();
    }
    label->setMinimumSize(640 * 2 / 3, 480 * 2 / 3);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUWebCameraWidget::~LAUWebCameraWidget()
{
    if (thread) {
        thread->quit();
        while (thread->isRunning()) {
            qApp->processEvents();
        }
        delete thread;
    }

    if (surface) {
        surface->stop();
        delete surface;
    }

    if (camera) {
        camera->stop();
        delete camera;
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUWebCameraWidget::onCapture()
{
    if (imageCapture) {
        // WAIT HERE UNTIL CAMERA IS READY TO CAPTURE
        while (imageCapture->isReadyForCapture() == false) {
            qApp->processEvents();
        }
        imageCapture->capture();
        if (imageCapture->error() != QCameraImageCapture::NoError) {
            qDebug() << imageCapture->errorString();
        }
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUWebCameraWidget::onImageAvailable(int id, QImage image)
{
    Q_UNUSED(id);

    QLabel *label = new QLabel();
    label->setPixmap(QPixmap::fromImage(image));
    label->show();
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUWebCameraWidget::grabImage()
{
    if (label) {
        LAUMemoryObject object = label->grabImage();
        if (object.isNull() == false) {
            object.save(QString());
        }
    }
}
