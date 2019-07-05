#pragma once

#include <stdlib.h> //exit
#include <sstream> //cerr
#include <pylon/PylonIncludes.h> //GenICam::GenericException

#define BEGIN_TRY_CATCH \
	int exitCode = 0; \
	try {

#define END_TRY_CATCH \
	} \
	catch (GenICam::GenericException& e) \
	{ \
		/* Error handling. */ \
		std::cerr << "An exception occurred." << std::endl \
			<< e.GetDescription() << std::endl; \
		/* Comment the following two lines to disable waiting on exit. */ \
		std::cerr << std::endl << "Press Enter to exit." << std::endl; \
		while (std::cin.get() != '\n'); \
		std::exit(1); \
	}

