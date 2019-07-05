#pragma once

// Include files to use the PYLON API.
#include <pylon/PylonIncludes.h>

#include <optional>

// Include files to use OpenCV API.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class CameraGrabber
{
private:
	// Number of images to be grabbed.
	static const size_t c_countOfImagesToGrab = 100;

	// The parameter MaxNumBuffer can be used to control the count of buffers
	// allocated for grabbing. The default value of this parameter is 10.
	static const int64_t MaxNumBuffer = 10;

	// Automagically call PylonInitialize and PylonTerminate to ensure the pylon runtime system
	// is initialized during the lifetime of this object.
	Pylon::PylonAutoInitTerm autoInitTerm;

	std::optional<Pylon::CInstantCamera> camera;

	// create pylon image format converter and pylon image
	Pylon::CImageFormatConverter formatConverter;
	Pylon::CPylonImage pylonImage;

public:
	CameraGrabber();

	void initialize();
	bool isCameraGrabbing();
	std::optional<Pylon::CPylonImage> grabNextImage();
	static cv::Mat pylonImageToOpenCvImage(Pylon::CPylonImage thePylonImage);
	static void showWindow(cv::Mat openCvImage);
};

