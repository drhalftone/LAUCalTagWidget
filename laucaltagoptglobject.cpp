#include "laucaltagoptglobject.h"

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagOptFilterWidget::LAUCalTagOptFilterWidget(LAUCalTagOptGLObject *object, QWidget *parent) : QWidget(parent)
{
    this->setLayout(new QVBoxLayout());
    this->setWindowTitle(QString("LAUCalTag Dialog"));
    this->layout()->setContentsMargins(6, 6, 6, 6);
    this->layout()->setSpacing(10);

    QGroupBox *box = new QGroupBox(QString("Binarize Parameters"));
    box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    box->setLayout(new QGridLayout());
    box->layout()->setContentsMargins(6, 6, 6, 6);
    ((QGridLayout *)(box->layout()))->setColumnStretch(0, 100);
    ((QGridLayout *)(box->layout()))->setColumnMinimumWidth(2, 160);
    this->layout()->addWidget(box);

    iterSpinBox = new QSpinBox();
    iterSpinBox->setMinimum(1);
    iterSpinBox->setMaximum(5);
    iterSpinBox->setFixedWidth(80);
    iterSpinBox->setAlignment(Qt::AlignRight);
    connect(iterSpinBox, SIGNAL(valueChanged(int)), object, SLOT(onSetIterations(int)));

    QLabel *label = new QLabel(QString("Gaussian Smoother Iterations:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 0, 0, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(iterSpinBox, 0, 1, 1, 1, Qt::AlignLeft);

    gausSpinBox = new QSpinBox();
    gausSpinBox->setMinimum(1);
    gausSpinBox->setMaximum(127);
    gausSpinBox->setFixedWidth(80);
    gausSpinBox->setAlignment(Qt::AlignRight);
    connect(gausSpinBox, SIGNAL(valueChanged(int)), object, SLOT(onSetGaussianRadius(int)));

    label = new QLabel(QString("Guassian Smoother Radius:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 0, 2, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(gausSpinBox, 0, 3, 1, 1, Qt::AlignLeft);

    offsetSpinBox = new QDoubleSpinBox();
    offsetSpinBox->setMinimum(-1.0);
    offsetSpinBox->setMaximum(1.0);
    offsetSpinBox->setSingleStep(0.01);
    offsetSpinBox->setDecimals(4);
    offsetSpinBox->setFixedWidth(80);
    offsetSpinBox->setAlignment(Qt::AlignRight);
    connect(offsetSpinBox, SIGNAL(valueChanged(double)), object, SLOT(onSetOffset(double)));

    label = new QLabel(QString("Gaussian Filter Offset:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 1, 0, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(offsetSpinBox, 1, 1, 1, 1, Qt::AlignLeft);

    mednSpinBox = new QSpinBox();
    mednSpinBox->setMinimum(0);
    mednSpinBox->setMaximum(127);
    mednSpinBox->setFixedWidth(80);
    mednSpinBox->setAlignment(Qt::AlignRight);
    connect(mednSpinBox, SIGNAL(valueChanged(int)), object, SLOT(onSetMedianRadius(int)));

    label = new QLabel(QString("Median Smoother Radius:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 1, 2, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(mednSpinBox, 1, 3, 1, 1, Qt::AlignLeft);

    box = new QGroupBox(QString("CalTag Parameters"));
    box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    box->setLayout(new QGridLayout());
    box->layout()->setContentsMargins(6, 6, 6, 6);
    ((QGridLayout *)(box->layout()))->setColumnStretch(0, 100);
    ((QGridLayout *)(box->layout()))->setColumnMinimumWidth(2, 160);
    this->layout()->addWidget(box);

    minRegionArea = new QSpinBox();
    minRegionArea->setMinimum(0);
    minRegionArea->setMaximum(1000000);
    minRegionArea->setValue(128 - 32);
    minRegionArea->setFixedWidth(80);
    connect(minRegionArea, SIGNAL(valueChanged(int)), object, SLOT(onSetMinRegionArea(int)));

    label = new QLabel(QString("Minimum Region Area:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 0, 0, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(minRegionArea, 0, 1, 1, 1, Qt::AlignLeft);

    maxRegionArea = new QSpinBox();
    maxRegionArea->setMinimum(0);
    maxRegionArea->setMaximum(1000000);
    maxRegionArea->setValue((640 * 480) / 16);
    maxRegionArea->setFixedWidth(80);
    connect(maxRegionArea, SIGNAL(valueChanged(int)), object, SLOT(onSetMaxRegionArea(int)));

    label = new QLabel(QString("Maximum Region Area:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 0, 2, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(maxRegionArea, 0, 3, 1, 1, Qt::AlignLeft);

    minBoxCount = new QSpinBox();
    minBoxCount->setMinimum(0);
    minBoxCount->setMaximum(1000000);
    minBoxCount->setValue(128);
    minBoxCount->setFixedWidth(80);
    connect(minBoxCount, SIGNAL(valueChanged(int)), object, SLOT(onSetMinBoxCount(int)));

    label = new QLabel(QString("Minimum Box Count:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 1, 0, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(minBoxCount, 1, 1, 1, 1, Qt::AlignLeft);

    flipCalTagsFlag = new QCheckBox();
    flipCalTagsFlag->setCheckable(true);
    flipCalTagsFlag->setChecked(false);
    flipCalTagsFlag->setFixedWidth(80);
    connect(flipCalTagsFlag, SIGNAL(toggled(bool)), object, SLOT(onSetFlipCalTagsFlag(bool)));

    label = new QLabel(QString("Flip CalTag (backlight):"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 1, 2, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(flipCalTagsFlag, 1, 3, 1, 1, Qt::AlignLeft);

    // SET THE INITIAL VALUES FROM THE SUPPLIED GLOBJECT
    iterSpinBox->setValue(object->iterations());
    gausSpinBox->setValue(object->gaussianRadius());
    mednSpinBox->setValue(object->medianRadius());
    offsetSpinBox->setValue(object->offset());

    minRegionArea->setValue(object->minRegion());
    maxRegionArea->setValue(object->maxRegion());
    minBoxCount->setValue(object->minBox());
    flipCalTagsFlag->setChecked(object->flipCalTags());
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagOptFilterWidget::load()
{
    // LOAD THE PARAMETERS FROM SETTINGS
    QSettings settings;

    iterSpinBox->setValue(settings.value(QString("LAUCalTagScanWidget::iterSpinBox"), iterSpinBox->value()).toInt());
    gausSpinBox->setValue(settings.value(QString("LAUCalTagScanWidget::gausSpinBox"), gausSpinBox->value()).toInt());
    mednSpinBox->setValue(settings.value(QString("LAUCalTagScanWidget::mednSpinBox"), mednSpinBox->value()).toInt());
    offsetSpinBox->setValue(settings.value(QString("LAUCalTagScanWidget::offsetSpinBox"), offsetSpinBox->value()).toDouble());

    minRegionArea->setValue(settings.value(QString("LAUCalTagScanWidget::minRegionArea"), minRegionArea->value()).toInt());
    maxRegionArea->setValue(settings.value(QString("LAUCalTagScanWidget::maxRegionArea"), maxRegionArea->value()).toInt());
    minBoxCount->setValue(settings.value(QString("LAUCalTagScanWidget::minBoxCount"), minBoxCount->value()).toInt());
    flipCalTagsFlag->setChecked(settings.value(QString("LAUCalTagScanWidget::flipCalTagsFlag"), flipCalTagsFlag->isChecked()).toBool());
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagOptFilterWidget::save()
{
    // LOAD THE PARAMETERS FROM SETTINGS
    QSettings settings;

    settings.setValue(QString("LAUCalTagScanWidget::iterSpinBox"), iterSpinBox->value());
    settings.setValue(QString("LAUCalTagScanWidget::gausSpinBox"), gausSpinBox->value());
    settings.setValue(QString("LAUCalTagScanWidget::mednSpinBox"), mednSpinBox->value());
    settings.setValue(QString("LAUCalTagScanWidget::offsetSpinBox"), offsetSpinBox->value());

    settings.setValue(QString("LAUCalTagScanWidget::minRegionArea"), minRegionArea->value());
    settings.setValue(QString("LAUCalTagScanWidget::maxRegionArea"), maxRegionArea->value());
    settings.setValue(QString("LAUCalTagScanWidget::minBoxCount"), minBoxCount->value());
    settings.setValue(QString("LAUCalTagScanWidget::flipCalTagsFlag"), flipCalTagsFlag->isChecked());
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagOptGLObject::LAUCalTagOptGLObject(QObject *parent) : QObject(parent), isValidFlag(false)
{
    // INITIALIZE PRIVATE VARIABLES
    textureLUT = nullptr;

    frameBufferObjectA = nullptr;
    frameBufferObjectB = nullptr;
    frameBufferObjectC = nullptr;
    frameBufferObjectD = nullptr;

    quantizationOffset = -0.01f;
    medianFilterRadius = 0;
    gaussianFilterRadius = 10;
    iterationCount = 1;

    // INITIALIZE CLASS VARIABLES
    minBoxCount     = 32;                   // 2X2 PIXELS TIMES 8X8 BOX SIZE
    maxRegionArea   = (640 * 480) / 16;     // NEEDS IMAGE SIZE AND BYTES PER PIXEL
    minRegionArea   = maxRegionArea / 10;
    flipCalTagsFlag = false;
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagOptGLObject::~LAUCalTagOptGLObject()
{
    if (textureLUT) {
        delete textureLUT;
    }

    if (frameBufferObjectA) {
        delete frameBufferObjectA;
    }

    if (frameBufferObjectB) {
        delete frameBufferObjectB;
    }

    if (frameBufferObjectC) {
        delete frameBufferObjectC;
    }

    if (frameBufferObjectD) {
        delete frameBufferObjectD;
    }

    qDebug() << "LAUCalTagOptGLObject::~LAUCalTagOptGLObject()";
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagOptGLObject::initializeGL()
{
    // INITIALIZE OUR GL CALLS AND SET THE CLEAR COLOR
    initializeOpenGLFunctions();

    // CREATE VERTEX BUFFER TO HOLD CORNERS OF QUADRALATERAL
    quadVertexBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    quadVertexBuffer.create();
    quadVertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (quadVertexBuffer.bind()) {
        // ALLOCATE THE VERTEX BUFFER FOR HOLDING THE FOUR CORNERS OF A RECTANGLE
        quadVertexBuffer.allocate(16 * sizeof(float));
        float *buffer = (float *)quadVertexBuffer.map(QOpenGLBuffer::WriteOnly);
        if (buffer) {
            buffer[0]  = -1.0;
            buffer[1]  = -1.0;
            buffer[2]  = 0.0;
            buffer[3]  = 1.0;
            buffer[4]  = +1.0;
            buffer[5]  = -1.0;
            buffer[6]  = 0.0;
            buffer[7]  = 1.0;
            buffer[8]  = +1.0;
            buffer[9]  = +1.0;
            buffer[10] = 0.0;
            buffer[11] = 1.0;
            buffer[12] = -1.0;
            buffer[13] = +1.0;
            buffer[14] = 0.0;
            buffer[15] = 1.0;
            quadVertexBuffer.unmap();
        } else {
            qDebug() << QString("quadVertexBuffer not allocated.") << glGetError();
        }
        quadVertexBuffer.release();
    }

    // CREATE INDEX BUFFER TO ORDERINGS OF VERTICES FORMING POLYGON
    quadIndexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    quadIndexBuffer.create();
    quadIndexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (quadIndexBuffer.bind()) {
        quadIndexBuffer.allocate(6 * sizeof(unsigned int));
        unsigned int *indices = (unsigned int *)quadIndexBuffer.map(QOpenGLBuffer::WriteOnly);
        if (indices) {
            indices[0] = 0;
            indices[1] = 1;
            indices[2] = 2;
            indices[3] = 0;
            indices[4] = 2;
            indices[5] = 3;
            quadIndexBuffer.unmap();
        } else {
            qDebug() << QString("indiceBufferA buffer mapped from GPU.");
        }
        quadIndexBuffer.release();
    }

    // CREATE A TEXTURE FOR LOOK UP OPERATIONS
    textureLUT = new QOpenGLTexture(QOpenGLTexture::Target1D);
    textureLUT->setSize(512);
    textureLUT->setFormat(QOpenGLTexture::RGBA32F);
    textureLUT->setWrapMode(QOpenGLTexture::ClampToBorder);
    textureLUT->setMinificationFilter(QOpenGLTexture::Nearest);
    textureLUT->setMagnificationFilter(QOpenGLTexture::Nearest);
    textureLUT->allocateStorage();

    // NOW ADD OUR LIST OF HARRIS CORNER SHADER PROGRAMS
    setlocale(LC_NUMERIC, "C");
    programA.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/filterSobelEdge.vert");
    programA.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/filterSobelEdge.frag");
    programA.link();

    programB.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/filterXGaussian.vert");
    programB.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/filterXGaussian.frag");
    programB.link();

    programC.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/filterYGaussian.vert");
    programC.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/filterYGaussian.frag");
    programC.link();

    programD.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/filterBinaryCalTag.vert");
    programD.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/filterBinaryCalTag.frag");
    programD.link();

    programE.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/displayCalTagOpt.vert");
    programE.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/displayCalTagOpt.frag");
    programE.link();
    setlocale(LC_ALL, "");

    // SET THE VALID TAG TRUE SO WE CAN TEST IF INITIALIZED
    isValidFlag = true;
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagOptGLObject::processGL(QOpenGLTexture *videoTexture, QOpenGLFramebufferObject *outputFBO)
{
    if (isValid()) {
        // SEE IF WE NEED NEW FBOS
        testFBO(&frameBufferObjectA, videoTexture->width(), videoTexture->height());
        testFBO(&frameBufferObjectB, videoTexture->width(), videoTexture->height());
        testFBO(&frameBufferObjectC, videoTexture->width(), videoTexture->height());
        testFBO(&frameBufferObjectD, videoTexture->width(), videoTexture->height());

        // RESIZE THE BYTE ARRAYS AS NEEDED
        if (memoryObject[0].width() != (unsigned int)videoTexture->width() || memoryObject[0].height() != (unsigned int)videoTexture->height()) {
            memoryObject[0] = LAUMemoryObject(videoTexture->width(), videoTexture->height(), 1, sizeof(unsigned char));
            memoryObject[1] = LAUMemoryObject(videoTexture->width(), videoTexture->height(), 1, sizeof(unsigned char));
#ifdef QT_DEBUG
            debugObject = LAUMemoryObject(videoTexture->width(), videoTexture->height(), 3, sizeof(unsigned char));
#endif
        }

        // BINARIZE THE INCOMING BUFFER
        mask(videoTexture, frameBufferObjectC);
        gradient(videoTexture, frameBufferObjectA, frameBufferObjectB);
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagOptGLObject::testFBO(QOpenGLFramebufferObject *fbo[], int cols, int rows)
{
    if ((*fbo) == nullptr) {
        // CREATE A FORMAT OBJECT FOR CREATING THE FRAME BUFFER
        QOpenGLFramebufferObjectFormat frameBufferObjectFormat;
        frameBufferObjectFormat.setInternalTextureFormat(GL_RGBA32F);

        (*fbo) = new QOpenGLFramebufferObject(cols, rows, frameBufferObjectFormat);
        (*fbo)->release();
    } else if ((*fbo)->width() != cols || (*fbo)->height() != rows) {
        delete (*fbo);

        // CREATE A FORMAT OBJECT FOR CREATING THE FRAME BUFFER
        QOpenGLFramebufferObjectFormat frameBufferObjectFormat;
        frameBufferObjectFormat.setInternalTextureFormat(GL_RGBA32F);

        (*fbo) = new QOpenGLFramebufferObject(cols, rows, frameBufferObjectFormat);
        (*fbo)->release();
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagOptGLObject::mask(QOpenGLTexture *videoTexture, QOpenGLFramebufferObject *fbo)
{
    // APPLY A SOBEL EDGE DETECTING FILTER TO THE BINARY IMAGE
    if (fbo && fbo->bind()) {
        if (programD.bind()) {
            // CLEAR THE FRAME BUFFER OBJECT
            glViewport(0, 0, fbo->width(), fbo->height());
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
            if (quadVertexBuffer.bind()) {
                if (quadIndexBuffer.bind()) {
                    // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                    glActiveTexture(GL_TEXTURE5);
                    videoTexture->bind();
                    programD.setUniformValue("qt_texture", 5);

                    // TELL OPENGL PROGRAMMABLE PIPELINE HOW TO LOCATE VERTEX POSITION DATA
                    glVertexAttribPointer(programD.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                    programD.enableAttributeArray("qt_vertex");
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

                    // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                    quadIndexBuffer.release();
                }
                quadVertexBuffer.release();
            }
            programD.release();
        }
        fbo->release();
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagOptGLObject::gradient(QOpenGLTexture *videoTexture, QOpenGLFramebufferObject *fboA, QOpenGLFramebufferObject *fboB)
{
    // APPLY A SOBEL EDGE DETECTING FILTER TO THE BINARY IMAGE
    if (fboA && fboA->bind()) {
        if (programA.bind()) {
            // CLEAR THE FRAME BUFFER OBJECT
            glViewport(0, 0, fboA->width(), fboA->height());
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
            if (quadVertexBuffer.bind()) {
                if (quadIndexBuffer.bind()) {
                    // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                    glActiveTexture(GL_TEXTURE5);
                    videoTexture->bind();
                    programA.setUniformValue("qt_texture", 5);

                    // TELL OPENGL PROGRAMMABLE PIPELINE HOW TO LOCATE VERTEX POSITION DATA
                    glVertexAttribPointer(programA.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                    programA.enableAttributeArray("qt_vertex");
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

                    // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                    quadIndexBuffer.release();
                }
                quadVertexBuffer.release();
            }
            programA.release();
        }
        fboA->release();
    }

    // APPLY A GAUSSIAN FILTER IN THE X-DIRECTION TO THE FBOC TO FBOD
    if (fboB && fboB->bind()) {
        if (programB.bind()) {
            // CLEAR THE FRAME BUFFER OBJECT
            glViewport(0, 0, fboB->width(), fboB->height());
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
            if (quadVertexBuffer.bind()) {
                if (quadIndexBuffer.bind()) {
                    // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, fboA->texture());
                    programB.setUniformValue("qt_texture", 1);

                    // TELL THE SHADER HOW MANY PIXELS WIDE TO APPLY GAUSSIAN FILTER
                    programB.setUniformValue("qt_width", (int)1);

                    // TELL OPENGL PROGRAMMABLE PIPELINE HOW TO LOCATE VERTEX POSITION DATA
                    glVertexAttribPointer(programB.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                    programB.enableAttributeArray("qt_vertex");
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                    // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                    quadIndexBuffer.release();
                }
                quadVertexBuffer.release();
            }
            programB.release();
        }
        fboB->release();
    }

    // APPLY A GAUSSIAN FILTER IN THE Y-DIRECTION TO THE FBOD TO FBOC
    if (fboA && fboA->bind()) {
        if (programC.bind()) {
            // CLEAR THE FRAME BUFFER OBJECT
            glViewport(0, 0, fboA->width(), fboA->height());
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
            if (quadVertexBuffer.bind()) {
                if (quadIndexBuffer.bind()) {
                    // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                    glActiveTexture(GL_TEXTURE2);
                    glBindTexture(GL_TEXTURE_2D, fboB->texture());
                    programC.setUniformValue("qt_texture", 2);

                    // TELL THE SHADER HOW MANY PIXELS WIDE TO APPLY GAUSSIAN FILTER
                    programC.setUniformValue("qt_width", (int)1);

                    // Tell OpenGL programmable pipeline how to locate vertex position data
                    glVertexAttribPointer(programC.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                    programC.enableAttributeArray("qt_vertex");
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                    // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                    quadIndexBuffer.release();
                }
                quadVertexBuffer.release();
            }
            programC.release();
        }
        fboA->release();
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
cv::Mat LAUCalTagOptGLObject::findBestQuadraticMapping(cv::vector<cv::Point2f> fmPoints, cv::vector<cv::Point2f> toPoints, int width, int height, int order)
{
    cv::Mat lVec(30, 1, CV_64F);
    lVec.setTo(0.0);

    int numPoints = (int)fmPoints.size();

    // ALLOCATE SPACE FOR DATA VECTORS
    cv::vector<double> rVec(numPoints);
    cv::vector<double> cVec(numPoints);
    cv::vector<double> xVec(numPoints);
    cv::vector<double> yVec(numPoints);

    // COPY DATA FROM CLUSTER LIST INTO DATA VECTORS
    for (int n = 0; n < numPoints; n++) {
        cVec[n] = (fmPoints[n].x - (width / 2)) / 50.0;
        rVec[n] = (fmPoints[n].y - (height / 2)) / 50.0;
        xVec[n] = toPoints[n].x;
        yVec[n] = toPoints[n].y;
    }

    if (order == 4) {
        // MAKE SURE WE FOUND ENOUGH CLUSTERS TO DO A DECENT INTERPOLATION
        if (fmPoints.size() >= 15) {
            // CREATE MATRIX TO HOLD THE 4TH ORDER TRANSFORM
            cv::Mat A(2 * numPoints, 30, CV_64F);
            A.setTo(0.0);
            cv::Mat B(2 * numPoints,  1, CV_64F);

            for (int r = 0; r < numPoints; r++) {
                // POPULATE THE ODD NUMBERED ROWS
                A.at<double>(2 * r + 0, 0)  = cVec[r] * cVec[r] * cVec[r] * cVec[r];
                A.at<double>(2 * r + 0, 1)  = cVec[r] * cVec[r] * cVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 2)  = cVec[r] * cVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 3)  = cVec[r] * rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 4)  = rVec[r] * rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 5)  = cVec[r] * cVec[r] * cVec[r];
                A.at<double>(2 * r + 0, 6)  = cVec[r] * cVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 7)  = cVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 8)  = rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 9)  = cVec[r] * cVec[r];
                A.at<double>(2 * r + 0, 10) = cVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 11) = rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 12) = cVec[r];
                A.at<double>(2 * r + 0, 13) = rVec[r];
                A.at<double>(2 * r + 0, 14) = 1.0;

                A.at<double>(2 * r + 1, 15) = cVec[r] * cVec[r] * cVec[r] * cVec[r];
                A.at<double>(2 * r + 1, 16) = cVec[r] * cVec[r] * cVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 17) = cVec[r] * cVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 18) = cVec[r] * rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 19) = rVec[r] * rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 20) = cVec[r] * cVec[r] * cVec[r];
                A.at<double>(2 * r + 1, 21) = cVec[r] * cVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 22) = cVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 23) = rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 24) = cVec[r] * cVec[r];
                A.at<double>(2 * r + 1, 25) = cVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 26) = rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 27) = cVec[r];
                A.at<double>(2 * r + 1, 28) = rVec[r];
                A.at<double>(2 * r + 1, 29) = 1.0;

                B.at<double>(2 * r + 0) = xVec[r];
                B.at<double>(2 * r + 1) = yVec[r];
            }
            lVec = (A.t() * A).inv() * A.t() * B;
        }
    } else if (order == 3) {
        // MAKE SURE WE FOUND ENOUGH CLUSTERS TO DO A DECENT INTERPOLATION
        if (fmPoints.size() >= 10) {
            // CREATE MATRIX TO HOLD THE 4TH ORDER TRANSFORM
            cv::Mat A(2 * numPoints, 20, CV_64F);
            A.setTo(0.0);
            cv::Mat B(2 * numPoints,  1, CV_64F);

            for (int r = 0; r < numPoints; r++) {
                // POPULATE THE ODD NUMBERED ROWS
                A.at<double>(2 * r + 0, 0) = cVec[r] * cVec[r] * cVec[r];
                A.at<double>(2 * r + 0, 1) = cVec[r] * cVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 2) = cVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 3) = rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 4) = cVec[r] * cVec[r];
                A.at<double>(2 * r + 0, 5) = cVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 6) = rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 7) = cVec[r];
                A.at<double>(2 * r + 0, 8) = rVec[r];
                A.at<double>(2 * r + 0, 9) = 1.0;

                A.at<double>(2 * r + 1, 10) = cVec[r] * cVec[r] * cVec[r];
                A.at<double>(2 * r + 1, 11) = cVec[r] * cVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 12) = cVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 13) = rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 14) = cVec[r] * cVec[r];
                A.at<double>(2 * r + 1, 15) = cVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 16) = rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 17) = cVec[r];
                A.at<double>(2 * r + 1, 18) = rVec[r];
                A.at<double>(2 * r + 1, 19) = 1.0;

                B.at<double>(2 * r + 0) = xVec[r];
                B.at<double>(2 * r + 1) = yVec[r];
            }
            cv::Mat sVec = (A.t() * A).inv() * A.t() * B;

            // COPY SVECTOR OVER TO LVECTOR
            for (int n = 0; n < 10; n++) {
                lVec.at<double>(n + 5) = sVec.at<double>(n + 0);
                lVec.at<double>(n + 20) = sVec.at<double>(n + 10);
            }
        }
    } else if (order == 2) {
        // MAKE SURE WE FOUND ENOUGH CLUSTERS TO DO A DECENT INTERPOLATION
        if (fmPoints.size() >= 6) {
            // CREATE MATRIX TO HOLD THE 4TH ORDER TRANSFORM
            cv::Mat A(2 * numPoints, 12, CV_64F);
            A.setTo(0.0);
            cv::Mat B(2 * numPoints,  1, CV_64F);

            for (int r = 0; r < numPoints; r++) {
                // POPULATE THE ODD NUMBERED ROWS
                A.at<double>(2 * r + 0, 0) = cVec[r] * cVec[r];
                A.at<double>(2 * r + 0, 1) = cVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 2) = rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 3) = cVec[r];
                A.at<double>(2 * r + 0, 4) = rVec[r];
                A.at<double>(2 * r + 0, 5) = 1.0;

                A.at<double>(2 * r + 1, 6)  = cVec[r] * cVec[r];
                A.at<double>(2 * r + 1, 7)  = cVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 8)  = rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 9)  = cVec[r];
                A.at<double>(2 * r + 1, 10) = rVec[r];
                A.at<double>(2 * r + 1, 11) = 1.0;

                B.at<double>(2 * r + 0) = xVec[r];
                B.at<double>(2 * r + 1) = yVec[r];
            }
            cv::Mat sVec = (A.t() * A).inv() * A.t() * B;

            // COPY SVECTOR OVER TO LVECTOR
            for (int n = 0; n < 6; n++) {
                lVec.at<double>(n + 9) = sVec.at<double>(n + 0);
                lVec.at<double>(n + 24) = sVec.at<double>(n + 6);
            }
        }
    } else if (order == 1) {
        // MAKE SURE WE FOUND ENOUGH CLUSTERS TO DO A DECENT INTERPOLATION
        if (fmPoints.size() >= 3) {
            // CREATE MATRIX TO HOLD THE 4TH ORDER TRANSFORM
            cv::Mat A(2 * numPoints, 6, CV_64F);
            A.setTo(0.0);
            cv::Mat B(2 * numPoints, 1, CV_64F);

            for (int r = 0; r < numPoints; r++) {
                // POPULATE THE ODD NUMBERED ROWS
                A.at<double>(2 * r + 0, 0) = cVec[r];
                A.at<double>(2 * r + 0, 1) = rVec[r];
                A.at<double>(2 * r + 0, 2) = 1.0;

                A.at<double>(2 * r + 1, 3) = cVec[r];
                A.at<double>(2 * r + 1, 4) = rVec[r];
                A.at<double>(2 * r + 1, 5) = 1.0;

                B.at<double>(2 * r + 0) = xVec[r];
                B.at<double>(2 * r + 1) = yVec[r];
            }
            cv::Mat sVec = (A.t() * A).inv() * A.t() * B;

            // COPY SVECTOR OVER TO LVECTOR
            for (int n = 0; n < 3; n++) {
                lVec.at<double>(n + 12) = sVec.at<double>(n + 0);
                lVec.at<double>(n + 27) = sVec.at<double>(n + 3);
            }
        }
    }
    return (lVec);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
QPointF LAUCalTagOptGLObject::transformPoint(QPointF pt, cv::Mat tMat)
{
    double x = (double)pt.x();
    double y = (double)pt.y();

    double xp = 0.0, yp = 0.0;

    xp += x * x * x * x * tMat.at<double>(0);
    xp += x * x * x * y * tMat.at<double>(1);
    xp += x * x * y * y * tMat.at<double>(2);
    xp += x * y * y * y * tMat.at<double>(3);
    xp += y * y * y * y * tMat.at<double>(4);
    xp += x * x * x * tMat.at<double>(5);
    xp += x * x * y * tMat.at<double>(6);
    xp += x * y * y * tMat.at<double>(7);
    xp += y * y * y * tMat.at<double>(8);
    xp += x * x * tMat.at<double>(9);
    xp += x * y * tMat.at<double>(10);
    xp += y * y * tMat.at<double>(11);
    xp += x * tMat.at<double>(12);
    xp += y * tMat.at<double>(13);
    xp += tMat.at<double>(14);

    yp += x * x * x * x * tMat.at<double>(15);
    yp += x * x * x * y * tMat.at<double>(16);
    yp += x * x * y * y * tMat.at<double>(17);
    yp += x * y * y * y * tMat.at<double>(18);
    yp += y * y * y * y * tMat.at<double>(19);
    yp += x * x * x * tMat.at<double>(20);
    yp += x * x * y * tMat.at<double>(21);
    yp += x * y * y * tMat.at<double>(22);
    yp += y * y * y * tMat.at<double>(23);
    yp += x * x * tMat.at<double>(24);
    yp += x * y * tMat.at<double>(25);
    yp += y * y * tMat.at<double>(26);
    yp += x * tMat.at<double>(27);
    yp += y * tMat.at<double>(28);
    yp += tMat.at<double>(28);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUMemoryObject LAUCalTagOptGLObject::grabImage()
{
    LAUMemoryObject object;
    if (frameBufferObjectB) {
        object = LAUMemoryObject(frameBufferObjectB->width(), frameBufferObjectB->height(), 3, sizeof(float));
        glBindTexture(GL_TEXTURE_2D, frameBufferObjectB->texture());
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, object.constPointer());
    }
    return (object);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagOptGLObject::paintGL()
{
    if (frameBufferObjectC) {
        // DISPLAY THE LAST FBO IN OUR LIST
        if (programE.bind()) {
            if (quadVertexBuffer.bind()) {
                if (quadIndexBuffer.bind()) {
                    // SET THE ACTIVE TEXTURE ON THE GPU
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, frameBufferObjectC->texture());
                    programE.setUniformValue("qt_texture", 0);

                    // TELL OPENGL PROGRAMMABLE PIPELINE HOW TO LOCATE VERTEX POSITION DATA
                    programE.setAttributeBuffer("qt_vertex", GL_FLOAT, 0, 4, 4 * sizeof(float));
                    programE.enableAttributeArray("qt_vertex");

                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                    quadIndexBuffer.release();
                }
                quadVertexBuffer.release();
            }
            programE.release();
        }
    }
}
