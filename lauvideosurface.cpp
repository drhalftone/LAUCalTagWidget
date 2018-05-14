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

#include "lauvideosurface.h"
#include <stdio.h>

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
QList<QVideoFrame::PixelFormat> LAUVideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const
{
    QList<QVideoFrame::PixelFormat> list;
    if (type == QAbstractVideoBuffer::NoHandle) {
        list << QVideoFrame::Format_RGB32;
        list << QVideoFrame::Format_ARGB32;
        list << QVideoFrame::Format_ARGB32_Premultiplied;
        list << QVideoFrame::Format_RGB555;
    }
    return (list);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
QVideoSurfaceFormat LAUVideoSurface::nearestFormat(const QVideoSurfaceFormat &format) const
{
    return (format);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
bool LAUVideoSurface::isFormatSupported(const QVideoSurfaceFormat &format) const
{
    if (QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat()) == QImage::Format_Invalid) {
        return (false);
    } else if (format.frameSize().isEmpty()) {
        return (false);
    } else if (format.handleType() != QAbstractVideoBuffer::NoHandle) {
        return (false);
    }
    return (true);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
bool LAUVideoSurface::present(const QVideoFrame &frame)
{
    // SEND THE IN-COMING VIDEO TO THE LABEL WIDGET, IF IT EXISTS
    if (labelWidget) {
        labelWidget->setFrame(frame);
    }
    return (true);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
bool LAUVideoSurface::start(const QVideoSurfaceFormat &format)
{
    return (QAbstractVideoSurface::start(format));
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUVideoSurface::stop()
{
    QAbstractVideoSurface::stop();
}
