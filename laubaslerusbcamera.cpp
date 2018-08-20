#include "laubaslerusbcamera.h"

using namespace Pylon;
using namespace Basler_UsbCameraParams;

bool LAUBaslerUSBCamera::libraryInitializedFlag = false;

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUBaslerUSBCamera::LAUBaslerUSBCamera(QObject *parent) : QObject(parent), numRows(0), numCols(0), bitsPerPixel(12), isConnected(false), camera(NULL)
{
    // INITIALIZE CAMERA LIBRARY AND UNLOAD IF ERROR
    if (!libraryInitializedFlag) {
        PylonInitialize();
        libraryInitializedFlag = true;
    }

    // KEEP TRYING TO FIND CAMERAS WHILE LIBRARY SEARCHES NETWORK
    errorString = QString("No cameras found.");

    // GET A LIST OF AVAILABLE CAMERAS
    QStringList availableCameralist = cameraList();
    if (numAvailableCameras) {
        // NOW SEE IF WE CAN CONNECT TO FIRST DETECTED CAMERA
        if (connectToHost(availableCameralist.first())) {
            errorString = QString();
            isConnected = true;
        } else {
            disconnectFromHost();
            isConnected = false;
        }
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUBaslerUSBCamera::~LAUBaslerUSBCamera()
{
    // DISCONNECT FROM CAMERA
    if (isConnected) {
        disconnectFromHost();
    }
    PylonTerminate();

    qDebug() << QString("LAUBaslerUSBCamera::~LAUBaslerUSBCamera()");
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
QStringList LAUBaslerUSBCamera::cameraList()
{
    // ONLY LOOK FOR CAMERAS SUPPORTED BY CAMERA_T.
    CDeviceInfo info;
    info.SetDeviceClass(CBaslerUsbInstantCamera::DeviceClass());

    // GET THE TRANSPORT LAYER FACTORY.
    CTlFactory &tlFactory = CTlFactory::GetInstance();

    // GET ALL ATTACHED DEVICES AND EXIT APPLICATION IF NO DEVICE IS FOUND.
    DeviceInfoList_t devices;
    numAvailableCameras = tlFactory.EnumerateDevices(devices);

    // PRINT A LIST OF THE CONNECTED CAMERAS
    QStringList stringList;
    for (unsigned int i = 0; i < numAvailableCameras; i++) {
        stringList << QString(devices[i].GetFriendlyName());
    }
    return (stringList);
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
bool LAUBaslerUSBCamera::connectToHost(QString idString)
{
    // ONLY LOOK FOR CAMERAS SUPPORTED BY CAMERA_T.
    CDeviceInfo info;
    info.SetDeviceClass(CBaslerUsbInstantCamera::DeviceClass());

    // GET THE TRANSPORT LAYER FACTORY.
    CTlFactory &tlFactory = CTlFactory::GetInstance();

    // GET ALL ATTACHED DEVICES AND EXIT APPLICATION IF NO DEVICE IS FOUND.
    DeviceInfoList_t devices;
    numAvailableCameras = tlFactory.EnumerateDevices(devices);

    try {
        // PRINT A LIST OF THE CONNECTED CAMERAS
        for (unsigned int i = 0; i < numAvailableCameras; i++) {
            if (QString(devices[i].GetFriendlyName()) == idString) {
                // CREATE AN INSTANT CAMERA OBJECT WITH THE FIRST FOUND CAMERA DEVICE MATCHING THE SPECIFIED DEVICE CLASS.
                camera = new CBaslerUsbInstantCamera(CTlFactory::GetInstance().CreateFirstDevice(info));

                // OPEN THE CAMERA FOR ACCESSING THE PARAMETERS.
                camera->Open();

                if (camera->IsOpen()) {
                    // GET THE MAKE, MODEL, AND SERIAL NUMBER STRINGS
                    makeString = QString(camera->DeviceVendorName.GetValue());
                    modelString = QString(camera->DeviceModelName.GetValue());
                    serialString = QString(camera->DeviceFirmwareVersion.GetValue());

                    // SET THE REGION OF INTEREST TO THE FULL SENSOR
                    if (IsWritable(camera->OffsetX)) {
                        camera->OffsetX.SetValue(camera->OffsetX.GetMin());
                    }

                    if (IsWritable(camera->OffsetY)) {
                        camera->OffsetY.SetValue(camera->OffsetY.GetMin());
                    }

                    if (IsWritable(camera->Width)) {
                        camera->Width.SetValue(camera->Width.GetMax());
                        numCols = camera->Width.GetValue();
                    }

                    if (IsWritable(camera->Height)) {
                        camera->Height.SetValue(camera->Height.GetMax());
                        numRows = camera->Height.GetValue();
                    }

                    if (IsWritable(camera->PixelFormat)) {
                        camera->PixelFormat.SetValue(PixelFormat_Mono8);
                        bitsPerPixel = 10;
                    }

                    if (IsWritable(camera->ExposureAuto)) {
                        camera->ExposureAuto.SetValue(ExposureAuto_Continuous);
                    }

                    // THE PARAMETER MAXNUMBUFFER CAN BE USED TO CONTROL THE COUNT OF BUFFERS
                    // ALLOCATED FOR GRABBING. THE DEFAULT VALUE OF THIS PARAMETER IS 10.
                    camera->MaxNumBuffer = 8;

                    // PUT THE CAMERA IN FREE RUN MODE
                    camera->TriggerMode.SetValue(TriggerMode_Off);

                    // TELL THE USER WE HAVE SUCCESSFULLY CONNECTED TO THE CAMERA
                    return (true);
                }
                return (false);
            }
        }
    } catch (const GenericException &e) {
        errorString = QString("Pylon exception:").append(QString(e.GetDescription()));
        emit emitError(errorString);
    }

    // IF WE MAKE IT THIS FAR, BUT WE ARE NOT CONNECTED, THEN THE CAMERA STRING WASN'T FOUND
    return (false);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
bool LAUBaslerUSBCamera::disconnectFromHost()
{
    if (camera && camera->IsOpen()) {
        camera->Close();
        if (camera->IsOpen() == false) {
            return (true);
        }
    }
    return (true);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUBaslerUSBCamera::setExposure(int microseconds)
{
    // SET THE CAMERA'S EXPOSURE
    if (camera && camera->IsOpen()) {
        camera->ExposureTime.SetValue(microseconds);
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUBaslerUSBCamera::setFrame(LAUMemoryObject object)
{
    if (object.isValid()) {
        // RESET ERROR CODE
        object.setElapsed(0);

        // CALCULATE HOW MANY OF FRAMES WE NEED TO GRAB
        unsigned int numFrmsToGrab = object.frames();

        // THE PARAMETER MAXNUMBUFFER CAN BE USED TO CONTROL THE COUNT OF BUFFERS
        // ALLOCATED FOR GRABBING. THE DEFAULT VALUE OF THIS PARAMETER IS 10.
        camera->MaxNumBuffer = numFrmsToGrab;

        try {
            // KEEP TRACK OF HOW MANY FRAMES WE HAVE SO FAR COLLECTED
            unsigned int counter = 0;

            // START THE GRABBING OF NUMBTCS IMAGES.
            camera->StartGrabbing(numFrmsToGrab);

            // THIS SMART POINTER WILL RECEIVE THE GRAB RESULT DATA.
            CGrabResultPtr ptrGrabResult;

            // CAMERA.STOPGRABBING() IS CALLED AUTOMATICALLY BY THE RETRIEVERESULT() METHOD
            // WHEN C_COUNTOFIMAGESTOGRAB IMAGES HAVE BEEN RETRIEVED.
            while (camera->IsGrabbing() && counter < object.frames()) {
                // WAIT FOR AN IMAGE AND THEN RETRIEVE IT. A TIMEOUT OF 5000 MS IS USED.
                camera->RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

                // IMAGE GRABBED SUCCESSFULLY?
                if (ptrGrabResult->GrabSucceeded()) {
                    memcpy(object.constFrame(counter), ptrGrabResult->GetBuffer(), object.length());
                } else {
                    errorString = QString("Error grabbing frame:").append(QString(ptrGrabResult->GetErrorCode())).append(QString(ptrGrabResult->GetErrorDescription()));
                    object.setElapsed((unsigned int)(255));
                }

                // INCREMENT THE COUNTER FOR THE NEXT FRAME
                counter++;
            }
        } catch (const GenericException &e) {
            errorString = QString("Pylon exception:").append(QString(e.GetDescription()));
            emit emitError(errorString);
        }
    }

    // SEND MEMORY OBJECT BACK TO THE USER
    emit emitFrame(object);
}
