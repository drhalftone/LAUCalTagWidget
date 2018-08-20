#-------------------------------------------------
#                                                                               #
# Copyright (c) 2017, Dr. Daniel L. Lau                                         #
# All rights reserved.                                                          #
#                                                                               #
# Redistribution and use in source and binary forms, with or without            #
# modification, are permitted provided that the following conditions are met:   #
# 1. Redistributions of source code must retain the above copyright             #
#    notice, this list of conditions and the following disclaimer.              #
# 2. Redistributions in binary form must reproduce the above copyright          #
#    notice, this list of conditions and the following disclaimer in the        #
#    documentation and/or other materials provided with the distribution.       #
# 3. All advertising materials mentioning features or use of this software      #
#    must display the following acknowledgement:                                #
#    This product includes software developed by the <organization>.            #
# 4. Neither the name of the <organization> nor the                             #
#    names of its contributors may be used to endorse or promote products       #
#    derived from this software without specific prior written permission.      #
#                                                                               #
# THIS SOFTWARE IS PROVIDED BY Dr. Daniel L. Lau ''AS IS'' AND ANY              #
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED     #
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE        #
# DISCLAIMED. IN NO EVENT SHALL Dr. Daniel L. Lau BE LIABLE FOR ANY             #
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES    #
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;  #
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND   #
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    #
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS #
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                  #
#                                                                               #
#-------------------------------------------------

CONFIG  += basler

QT      += core gui multimedia widgets multimediawidgets opengl
TARGET   = LAUWebCalTag
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        laumemoryobject.cpp \
        lauwebcamerawidget.cpp \
        lauvideosurface.cpp \
        lauvideoglwidget.cpp \
        laucaltagglwidget.cpp \
        laucaltagglobject.cpp

HEADERS += \
        laumemoryobject.h \
        lauwebcamerawidget.h \
        lauvideosurface.h \
        lauvideoglwidget.h \
        laucaltagglwidget.h \
        laucaltagglobject.h

RESOURCES += lauwebcameracapture.qrc

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

basler {
    DEFINES += USEBASLERUSBCAMERA
    HEADERS += laubaslerusbcamera.h
    SOURCES += laubaslerusbcamera.cpp
}

unix:macx {
    CONFIG        += c++11
    INCLUDEPATH   += /usr/local/opt/opencv@3/include /usr/local/include
    DEPENDPATH    += /usr/local/opt/opencv@3/include /usr/local/include
    LIBS          += -L/usr/local/opt/opencv@3/lib -lopencv_core -lopencv_objdetect -lopencv_imgcodecs \
                     -lopencv_imgproc -lopencv_calib3d -lopencv_highgui -lopencv_ml \
                     /usr/local/lib/libtiff.5.dylib
    basler{
        INCLUDEPATH += /Library/Frameworks/pylon.framework/Versions/A/Headers \
                       /Library/Frameworks/pylon.framework/Versions/A/Headers/GenICam
        DEPENDPATH  += /Library/Frameworks/pylon.framework/Versions/A/Headers \
                       /Library/Frameworks/pylon.framework/Versions/A/Headers/GenICam
        LIBS        += /Library/Frameworks/pylon.framework/Versions/A/pylon
    }
}

unix:!macx {
    CONFIG        += c++11
    INCLUDEPATH   += /usr/local/opt/opencv/include
    DEPENDPATH    += /usr/local/opt/opencv/include
    LIBS          += -L/usr/local/lib -lopencv_core -lopencv_objdetect -lopencv_imgproc -lopencv_calib3d -lopencv_highgui -lopencv_ml
}

win32 {
    INCLUDEPATH   += $$quote(C:/usr/opencv/build/include) $$quote(C:/usr/include)
    DEPENDPATH    += $$quote(C:/usr/opencv/build/include) $$quote(C:/usr/include)
    LIBS          += -L$$quote(C:/usr/lib) -L$$quote(C:/usr/opencv/build/x64/vc12/lib) -llibtiff_i -lopengl32
    CONFIG(release, debug|release): LIBS += -lopencv_world310
    CONFIG(debug, debug|release):   LIBS += -lopencv_world310d

    basler{
        INCLUDEPATH += $$quote(C:/Program Files/Basler/pylon 5/Development/include)
        DEPENDPATH  += $$quote(C:/Program Files/Basler/pylon 5/Development/include)
        LIBS        += -L$$quote(C:/Program Files/Basler/pylon 5/Development/lib/x64/) -lPylonBase_MD_VC120_v5_0
    }
}
