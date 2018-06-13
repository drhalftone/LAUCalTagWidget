# LAUCalTagWidget
Real-time implementation of Brad Atcheson's CalTag camera calibration scheme (https://github.com/brada/caltag). Portions on this code (some of the most important code) was originally written by Alex Burkhart based on the Matlab code provided by Brad.

So you just downloaded, compiled, and launched the LAUCalTagWidget Qt project.  The first thing you will notice is that the widget accesses your webcam as the source for RGB video, and that this video is converted to luminance (L* = 0.2126 * r + 0.7152 * g + 0.0722 * b) and adaptively quantized to binary (0.0 and 1.0). Adaptive quantization is performed by iteratively applying a Gaussian smoother to generate a continuous tone threshold image.  The original input image is then compared to this threshold surface pixel-by-pixel, with luminance values greater than the threshold pixel set to 1.0 and lesser pixels set to 0.0. The resulting binary image is then smoothed again using a median filter, which chooses the binary value with greater numbers. 

![](https://github.com/drhalftone/LAUCalTagWidget/blob/master/Images/LAUCalTagWidget00.jpg)

You can control this adaptive quantization process using the controls in the top group box, labeled "Binarize Parameters."  The first parameter, number of iterations, determines how many times a Gaussian smoother is applied to the image with larger numbers resulting in greater smoothing.  The Gaussian Smoother Radius is the size of the Gaussian smoother applied in each iteration with larger numbers also resulting in greater smoothing.  The offset parameter adds a fixed constant to the threshold surface prior to quantizing the input image.  And the Median Filter Radius sets the size of the median filter used to post-process the quantized image.  A value of zero is equivalent to turning the median filter off.

Now notice in the figure below that I'm holding my iPhone, which is displaying a copy of the caltag.pdf target included in this repository. At this position the caltag squares are too small to be detected.  What counts as too small is determined by the parameter, "Minimum Region Area," inside the "Caltag Parameters," group box.  This parameters sets the minimum square of a checkerboard square in pixels (height * width).  The parameter, "Maximum Region Area," sets the maximum checkerboard square size, also in pixels.

![](https://github.com/drhalftone/LAUCalTagWidget/blob/master/Images/LAUCalTagWidget01.jpg)

The minimum box count parameter determines what minimum number of detected squares are necessary for us to derive a coordinate transformation from camera pixel row and column coordinate to caltag cartesian XY coordinates.  XY coordinates are in terms of checkerboard squares.  So the boundaries between checkerboards correspond to integer X or Y coordinates. Assuming the checkerboard squares are within the range of minimum and maximum region areas and that you've detected a sufficient number of squares, the widget will display the near-integer coordinates of X or Y as red lines as shown below. Note how the software extrapolates XY coordinates for all camera pixels, even those outside the boundaries of the caltag grid.  The details of this transformation are in the code, but they correspond to a second-order polynomial transformation allowing for radial distortion in the camera lens.

![](https://github.com/drhalftone/LAUCalTagWidget/blob/master/Images/LAUCalTagWidget02.jpg)

At this point, we are now ready to capture an image using the "OK" button.  Doing so, brings up the save to disk dialog, and allows you to save the XY coordinates to an RGB Tiff image where each pixel is stored in single-precision floating point values.  The red and green channels of this image hold the X and Y coordinates assigned to each pixel while the blue channel holds the binary image.  A quick way to look at the results is using Matlab with the following code:

x = imread('Untitled1.tif');
x(:,:,1:2) = x(:,:,1:2)-floor(x(:,:,1:2));
imshow(x);

which results in the following figure:

![](https://github.com/drhalftone/LAUCalTagWidget/blob/master/Images/LAUCalTagWidget03.jpg)

So now for some benchmarks.  Using my MacBook Pro (Retine, 15-inch, mid 2014) laptop with Intel Iris Pro graphics and running my webcam at 640x480, I'm topping out at over 30 fps (30 fps is the maximum rate of the camera at 640x480).
