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

#ifndef LAUVIDEOGLWIDGET_H
#define LAUVIDEOGLWIDGET_H

#include <QTime>
#include <QImage>
#include <QScreen>
#include <QObject>
#include <QVideoFrame>
#include <QApplication>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLPixelTransferOptions>

#include "laumemoryobject.h"

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
class LAUVideoGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit LAUVideoGLWidget(QWidget *parent = NULL) : QOpenGLWidget(parent), videoTexture(NULL), localBuffer(NULL), numCols(-1), numRows(-1), pixelFormat(QOpenGLTexture::RGBA), pixelType(QOpenGLTexture::UInt8), counter(0) { ; }
    ~LAUVideoGLWidget();

    virtual bool isValid() const
    {
        return (wasInitialized());
    }

    bool wasInitialized() const
    {
        return (vertexArrayObject.isCreated());
    }

    void setFrameSize(int cols, int rows)
    {
        numCols = cols;
        numRows = rows;
    }

    void setFrameFormat(QOpenGLTexture::PixelFormat format)
    {
        pixelFormat = format;
    }

    void setPixelType(QOpenGLTexture::PixelType type)
    {
        pixelType = type;
    }

    virtual LAUMemoryObject grabImage()
    {
        return (LAUMemoryObject());
    }

public slots:
    virtual void onUpdate()
    {
        processGL();
        update();
    }
    void setFrame(unsigned char *buffer);
    void setFrame(const QVideoFrame &frame);
    void setFrame(QImage frame);

protected:
    virtual void process() { ; }
    virtual void initialize() { ; }
    virtual void resize(int w, int h)
    {
        Q_UNUSED(w);
        Q_UNUSED(h);
    }
    virtual void paint();

    void processGL()
    {
        if (wasInitialized()) {
            makeCurrent();
            process();
        }
    }
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL()
    {
        paint();
    }

    QOpenGLVertexArrayObject vertexArrayObject;
    QOpenGLBuffer quadVertexBuffer, quadIndexBuffer;
    QOpenGLShaderProgram program;
    QOpenGLTexture *videoTexture;

    QVideoFrame localVideoFrame;
    QImage localImage;
    unsigned char *localBuffer;

    int localWidth, localHeight;
    qreal devicePixelRatio;

private:
    int numCols, numRows;
    QOpenGLTexture::PixelFormat pixelFormat;
    QOpenGLTexture::PixelType pixelType;

    int counter;
    QTime time;
};

#endif // LAUVIDEOGLWIDGET_H
