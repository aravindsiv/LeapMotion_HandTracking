#include "Leap.h"
#include "LeapRecorder.hpp"
#include "Record.hpp"

int Record::record(std::string filename)
{
	FILE* test = fopen(filename.c_str(), "ab");
	if (!test) {
		std::cerr << "Cannot open " << filename << " for writing..." << std::endl;
		return 2;
	}
	fclose(test);
	Leap::Controller controller;
	LeapRecorder recorder;
	controller.addListener(recorder);
	controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

	if (!controller.isConnected()) {
		std::cerr << "Error: No LeapMotion found!" << std::endl;
		return 3;
	}

	// Record until Enter is pressed
	recorder.Record();
	std::cout << "Press Enter to quit..." << std::endl;
	std::cin.get();
	recorder.Stop();

	if (!recorder.Save(filename)) {
		std::cerr << "Error while saving the file.." << std::endl;
			return 2;
	}

	controller.removeListener(recorder);
	return 0;
}	

