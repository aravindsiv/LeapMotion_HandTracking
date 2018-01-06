#include "Leap.h"
#include "LeapRecorder.hpp"
#include <iostream>
// #include <Windows.h>

using namespace Leap;

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};

class Play {
public:
	Play() {};
	~Play() {};
	void displayFrame(Frame frame, Leap::Vector prevVelocity, int64_t prevFrameTimeStamp);
	void displayFrame(Frame frame);
	int play(std::string filename);
};