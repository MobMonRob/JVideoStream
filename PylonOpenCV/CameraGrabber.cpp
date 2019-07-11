#include "CameraGrabber.h"

#include "TRY_CATCH.h"

// Include files to use the PYLON API.
#include <pylon/PylonIncludes.h>

// Use sstream to create image names including integer
#include <sstream>

// Namespace for using pylon objects.
using namespace Pylon;

// Namespace for using GenApi objects
using namespace GenApi;

// Namespace for using cout.
using namespace std;


CameraGrabber::CameraGrabber()
{
	formatConverter.OutputPixelFormat = PixelType_BGR8packed;
}

void CameraGrabber::initialize()
{
	BEGIN_TRY_CATCH

	// Create an instant camera object with the camera device found first.
	cout << "Creating Camera..." << endl;
	camera.emplace(CTlFactory::GetInstance().CreateFirstDevice());

	// or use a device info object to use a specific camera
	//CDeviceInfo info;
	//info.SetSerialNumber("21694497");
	//CInstantCamera camera( CTlFactory::GetInstance().CreateFirstDevice(info));

	cout << "Camera created." << endl;
	// Print the model name of the camera.
	cout << "Using device " << camera->GetDeviceInfo().GetModelName() << endl;

	// The camera device is parameterized with a default configuration which
	// sets up free-running continuous acquisition.
	if (DEBUG) {
		camera->StartGrabbing(c_countOfImagesToGrab);
	}
	else {
		camera->StartGrabbing();
	}

	END_TRY_CATCH
}

bool CameraGrabber::isCameraGrabbing()
{
	if (camera.has_value()) {
		return camera->IsGrabbing();
	}
	return false;
}

std::optional<Pylon::CPylonImage> CameraGrabber::grabNextImage()
{
	BEGIN_TRY_CATCH

	if (!camera.has_value()) throw  ACCESS_EXCEPTION("!camera.has_value(): CameraGrabber::initialize() was not invoked before.");
	if (!camera->IsGrabbing()) throw  ACCESS_EXCEPTION("!camera->IsGrabbing(): CameraGrabber::initialize() was not invoked before.");

	// This smart pointer will receive the grab result data.
	CGrabResultPtr ptrGrabResult;

	// Wait for an image and then retrieve it. A timeout of 5000 ms is used.
	camera->RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

	// Image grabbed successfully?
	if (!ptrGrabResult->GrabSucceeded())
	{
		cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << endl;
		return std::nullopt;
	}

	// Access the image data.
	//cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
	//cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;
	const uint8_t* pImageBuffer = (uint8_t*)ptrGrabResult->GetBuffer();
	//cout << "Gray value of first pixel: " << (uint32_t)pImageBuffer[0] << endl << endl;

	// Convert the grabbed buffer to pylon image
	formatConverter.Convert(pylonImage, ptrGrabResult);

	return pylonImage;

	END_TRY_CATCH
}

cv::Mat CameraGrabber::pylonImageToOpenCvImage(Pylon::CPylonImage thePylonImage)
{
	// Create an OpenCV image out of pylon image
	return cv::Mat(thePylonImage.GetHeight(), thePylonImage.GetWidth(), CV_8UC3, (uint8_t*)thePylonImage.GetBuffer());
}

void CameraGrabber::showWindow(cv::Mat openCvImage)
{
	// Create a display window
	//namedWindow("OpenCV Display Window");//AUTOSIZE //FREERATIO
	// Display the current image with opencv
	cv::imshow("OpenCV Display Window", openCvImage);
	// Define a timeout for customer's input in ms.
	// '0' means indefinite, i.e. the next image will be displayed after closing the window 
	// '1' means live stream
	cv::waitKey(1);
}

int CameraGrabber::execute()
{
	CameraGrabber cameraGrabber;

	cameraGrabber.initialize();

	while (cameraGrabber.isCameraGrabbing()) {
		std::optional<Pylon::CPylonImage> optImage = cameraGrabber.grabNextImage();

		if (!optImage.has_value()) continue;

		cv::Mat openCvImage = cameraGrabber.pylonImageToOpenCvImage(optImage.value());

		cameraGrabber.showWindow(openCvImage);
	}

	return 0;
}

