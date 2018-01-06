#include "Leap.h"
#include "LeapRecorder.hpp"
#include "Play.hpp"
#include <iostream>
// #include <Windows.h>

using namespace Leap;

void Play::displayFrame(Frame frame) {
	std::cout << "Frame id: " << frame.id()
			  << ", timestamp: " << frame.timestamp()
			  << ", hands: " << frame.hands().count()
			  << ", extended fingers: " << frame.fingers().extended().count() << std::endl
			  << ", current frame rate: " << frame.currentFramesPerSecond() << " fps" << std::endl;
	
}

void Play::displayFrame(Frame frame, Leap::Vector prevVelocity, int64_t prevFrameTimeStamp) {
	std::cout << "Frame id: " << frame.id() << std::endl;
			  /*<< ", timestamp: " << frame.timestamp()
			  << ", hands: " << frame.hands().count()
			  << ", extended fingers: " << frame.fingers().extended().count() << std::endl
			  << ", current frame rate: " << frame.currentFramesPerSecond() << " fps" << std::endl;*/
	
	HandList hands = frame.hands();
	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
		// Get the first hand
		const Hand hand = *hl;
		std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
		std::cout << std::string(2, ' ') << handType << ", id: " << hand.id()
				  << ", palm position: " << hand.palmPosition() <<  ", palm velocity: "<< hand.palmVelocity();
				  // << ", palm acceleration: "<<1000*1000*(hand.palmVelocity()-prevVelocity)/(frame.timestamp() - prevFrameTimeStamp); 
				  // Acceleration unit is mm/s^2.

		
		  // Get the hand's normal vector and direction
		  const Vector normal = hand.palmNormal();
		  const Vector direction = hand.direction();

		  std::cout << ", Hand Direction: " << direction
		 		    << ", Hand Normal: " << normal << std::endl;

		/*
		  // Calculate the hand's pitch, roll, and yaw angles
		  std::cout << std::string(2, ' ') << "pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
			  << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
			  << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;

		  // Get the Arm bone
		  Arm arm = hand.arm();
		  std::cout << std::string(2, ' ') << "Arm direction: " << arm.direction()
			  << " wrist position: " << arm.wristPosition()
			  << " elbow position: " << arm.elbowPosition() << std::endl;

		  // Get fingers
		  const FingerList fingers = hand.fingers();

		  for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl)
		  {
		  	const Finger finger = *fl;
		  	std::cout << std::string(4, ' ') <<  fingerNames[finger.type()]
					  << " finger, id: " << finger.id()
					  << ", length: " << finger.length()
					  << "mm, width: " << finger.width() << std::endl;

		  	// Get finger bones
		  	for (int b = 0; b < 4; ++b)
		  	{
			  Bone::Type boneType = static_cast<Bone::Type>(b);
			  Bone bone = finger.bone(boneType);
			  std::cout << std::string(6, ' ') <<  boneNames[boneType]
					  << " bone, start: " << bone.prevJoint()
					  << ", end: " << bone.nextJoint()
					  << ", direction: " << bone.direction() << std::endl;
		  	}
		} */
	} 
}

int Play::play(std::string filename)
{
	Controller controller = Leap::Controller();
	LeapRecorder recorder;

	if (!recorder.Load(filename)) {
		return 2;
	}
	recorder.Play();
	bool firstFrame = true;
	int64_t prevFrameID, prevFrameTimeStamp;
	Leap::HandList tempHands;
	Leap::Hand firstHand;

	//@aravind: acceleration calculated for only one hand, need to extend it to other hands.
	Leap::Vector prevVelocity;

	while (recorder.get_state() != LeapRecorder::STATE_IDLE) {
		Frame frame = recorder.GetCurrentFrame();
		if (firstFrame) {
			//std::cout << "Got frame id #" << frame.id() << std::endl;
			prevFrameID = frame.id();
			prevFrameTimeStamp = frame.timestamp();
			tempHands = frame.hands();
			firstHand = tempHands[0];
			prevVelocity = firstHand.palmVelocity();
			displayFrame(frame, prevVelocity, prevFrameTimeStamp);
			firstFrame = !firstFrame;
		}
		else {
			if (frame.id() != prevFrameID) {
				prevFrameID = frame.id();
				//std::cout << "Got frame id #" << frame.id() << std::endl;
				displayFrame(frame, prevVelocity, prevFrameTimeStamp);
				prevFrameTimeStamp = frame.timestamp();
				tempHands = frame.hands();
				firstHand = tempHands[0];
				prevVelocity = firstHand.palmVelocity();
			}
		}
		/* std::cout << "Palm Position: " << firstHand.palmPosition() << std::endl;
				  << ", Palm Velocity: " << firstHand.palmVelocity()
		 		  << ", Hand Direction: " << firstHand.direction()
		 		  << ", Hand Normal: " << firstHand.palmNormal()
		 		  // << ", Hand Acceleration: " << (firstHand.palmVelocity()-prevVelocity)/(frame.timestamp() - prevFrameTimeStamp)
		 		  << std::endl; */
	}
	// std::cout << "Final position of the palm is " << firstHand.palmPosition() << std::endl;
	return 0;
}	
