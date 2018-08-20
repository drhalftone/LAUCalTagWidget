#ifndef LAUBASLERUSBCAMERA_H
#define LAUBASLERUSBCAMERA_H

#include <QTime>
#include <QList>
#include <QTimer>
#include <QtCore>
#include <QDebug>
#include <QImage>
#include <QString>
#include <QObject>
#include <QMessageBox>
#include <QApplication>
#include <QHostAddress>

#include "laumemoryobject.h"
#if defined(Q_OS_WIN)
#include <pylon/PylonIncludes.h>
#include <pylon/usb/BaslerUsbInstantCamera.h>
#elif defined(Q_OS_MAC)
#include <PylonIncludes.h>
#include <usb/BaslerUsbInstantCamera.h>
#endif

#define USE_USB

class LAUBaslerUSBCamera : public QObject
{
    Q_OBJECT

public:
    explicit LAUBaslerUSBCamera(QObject *parent = 0);
    ~LAUBaslerUSBCamera();

    bool isValid() const
    {
        return (isConnected);
    }

    unsigned short maxIntensityValue() const
    {
        return ((unsigned short)(0x01 << bitsPerPixel));
    }

    QString error() const
    {
        return (errorString);
    }

    QString make() const
    {
        return (makeString);
    }

    QString model() const
    {
        return (modelString);
    }

    QString serial() const
    {
        return (serialString);
    }

    unsigned int width() const
    {
        return (numCols);
    }

    unsigned int height() const
    {
        return (numRows);
    }

    LAUMemoryObject memoryObject() const
    {
        return (LAUMemoryObject(width(), height(), 1, sizeof(unsigned char)));
    }

public slots:
    void setExposure(int microseconds);
    void setFrame(LAUMemoryObject buffer);

private:
    static bool libraryInitializedFlag;

    unsigned int numRows;
    unsigned int numCols;
    unsigned short bitsPerPixel;
    bool isConnected;

    QString makeString;
    QString errorString;
    QString modelString;
    QString serialString;

    // DECLARE POINTERS TO PRIMESENSE SENSOR OBJECTS
    unsigned int numAvailableCameras;
    Pylon::CBaslerUsbInstantCamera *camera;

    QStringList cameraList();

    void unpack10Bits(unsigned char *toBuffer, unsigned char *fmBuffer);
    bool connectToHost(QString idString);
    bool disconnectFromHost();

signals:
    void emitError(QString);
    void emitFrame(LAUMemoryObject);
};
#endif // LAUBASLERUSBCAMERA_H
