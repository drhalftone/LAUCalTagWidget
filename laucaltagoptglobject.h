#ifndef LAUCALTAGOPTGLOBJECT_H
#define LAUCALTAGOPTGLOBJECT_H

#ifndef USEHEADLESS
#include <QLabel>
#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QDoubleSpinBox>
#endif

#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFramebufferObject>

#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "laumemoryobject.h"

namespace cv
{
    using std::vector;
}

#define CALTAGOPTPOLYNOMIALORDER 2

class LAUCalTagOptGLObject;
class LAUCalTagOptFilterWidget;

#ifndef USEHEADLESS
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
class LAUCalTagOptFilterWidget : public QWidget
{
    Q_OBJECT

public:
    LAUCalTagOptFilterWidget(LAUCalTagOptGLObject *object, QWidget *parent = nullptr);

    void load();
    void save();

private:
    QSpinBox *iterSpinBox;
    QSpinBox *gausSpinBox;
    QSpinBox *mednSpinBox;
    QDoubleSpinBox *offsetSpinBox;

    QSpinBox *minRegionArea;     // MINIMUM REGION AREA
    QSpinBox *maxRegionArea;     // MAXIMUM REGION AREA
    QSpinBox *minBoxCount;       // MINIMUM BOX AREA
    QCheckBox *flipCalTagsFlag;  // IS THE TARGET BACKLIT?
};
#endif

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
class LAUCalTagOptGLObject : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    LAUCalTagOptGLObject(QObject *parent = nullptr);
    ~LAUCalTagOptGLObject();

    bool isValid() const
    {
        return (isValidFlag);
    }

    bool isNull() const
    {
        return (!isValid());
    }

    float offset() const
    {
        return (quantizationOffset);
    }

    unsigned int medianRadius() const
    {
        return (medianFilterRadius);
    }

    unsigned int gaussianRadius() const
    {
        return (gaussianFilterRadius);
    }

    unsigned int iterations() const
    {
        return (iterationCount);
    }

    int minRegion() const
    {
        return (minRegionArea);
    }

    int maxRegion() const
    {
        return (maxRegionArea);
    }

    int minBox() const
    {
        return (minBoxCount);
    }

    bool flipCalTags() const
    {
        return (flipCalTagsFlag);
    }

    void initializeGL();
    void processGL(QOpenGLTexture *videoTexture, QOpenGLFramebufferObject *outputFBO = nullptr);
    void paintGL();

    LAUMemoryObject grabImage();

    static QPointF transformPoint(QPointF pt, cv::Mat transformMatrix);
    static cv::Mat findBestQuadraticMapping(cv::vector<cv::Point2f> fmPoints, cv::vector<cv::Point2f> toPoints, int width, int height, int order = 4);
    static cv::Mat findBestLinearMapping(cv::vector<cv::Point2f> fmPoints, cv::vector<cv::Point2f> toPoints);

#ifndef USEHEADLESS
    LAUCalTagOptFilterWidget *widget(QWidget *parent = nullptr)
    {
        return (new LAUCalTagOptFilterWidget(this, parent));
    }
#endif

public slots:
    void onSetOffset(double val)
    {
        quantizationOffset = val;
        emit update();
    }

    void onSetMedianRadius(int val)
    {
        medianFilterRadius = val;
        emit update();
    }

    void onSetGaussianRadius(int val)
    {
        gaussianFilterRadius = val;
        emit update();
    }

    void onSetIterations(int val)
    {
        iterationCount = val;
        emit update();
    }

    void onSetMinRegionArea(int val)
    {
        minRegionArea = val;
        emit update();
    }

    void onSetMaxRegionArea(int val)
    {
        maxRegionArea = val;
        emit update();
    }

    void onSetMinBoxCount(int val)
    {
        minBoxCount = val;
        emit update();
    }

    void onSetFlipCalTagsFlag(bool val)
    {
        flipCalTagsFlag = val;
        emit update();
    }

private:
    typedef struct {
        QPoint cr;
        QPoint xy;
    } Pairing;

    bool isValidFlag;
    int numRows, numCols;

    QList<LAUCalTagOptGLObject::Pairing> gridPairings; // KEEP TRACK OF THE LAST SET OF GRID POINT PAIRINGS

    float quantizationOffset;
    unsigned int medianFilterRadius;
    unsigned int gaussianFilterRadius;
    unsigned int iterationCount;

    int minRegionArea;     // MINIMUM REGION AREA
    int maxRegionArea;     // MAXIMUM REGION AREA
    int minBoxCount;       // MINIMUM BOX AREA
    bool flipCalTagsFlag;  // IS THE TARGET BACKLIT?

    LAUMemoryObject memoryObject[2];
#ifdef QT_DEBUG
    LAUMemoryObject debugObject;
#endif

    QOpenGLBuffer quadVertexBuffer, quadIndexBuffer;

    QOpenGLShaderProgram programA, programB, programC;
    QOpenGLShaderProgram programD, programE, programF;
    QOpenGLShaderProgram programG, programH, programI;
    QOpenGLShaderProgram programJ, programK;

    QOpenGLTexture *textureLUT;

    QOpenGLFramebufferObject *frameBufferObjectA, *frameBufferObjectB;
    QOpenGLFramebufferObject *frameBufferObjectC, *frameBufferObjectD;

    void testFBO(QOpenGLFramebufferObject *fbo[], int cols, int rows);
    void mask(QOpenGLTexture *videoTexture, QOpenGLFramebufferObject *fbo);
    void gradient(QOpenGLTexture *videoTexture, QOpenGLFramebufferObject *fboA, QOpenGLFramebufferObject *fboB);

signals:
    void update();
};

#endif // LAUCALTAGOPTGLOBJECT_H
