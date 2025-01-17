#ifndef _PITOT_H
#define _PITOT_H
#include "Sensor.h"
#include <Arduino.h>
#include <Wire.h>

// --------------------------------------------------------------------------------------
// This class holds all the values and methods for the Pitot Tube.
// --------------------------------------------------------------------------------------

class Pitot: public Sensor
{
public:
  bool Initialize();
	// -----------------------------------------------------------------------------------
	// This method is called to update the vel and dis values of the class.
	// -----------------------------------------------------------------------------------
	void Update();
	// -----------------------------------------------------------------------------------
	// This method returns the stored velocity.
	// -----------------------------------------------------------------------------------
	float GetVel();
	// -----------------------------------------------------------------------------------
	// This method returns the stored displacement.
	// -----------------------------------------------------------------------------------
	int GetDis() { return dis; }
  // -----------------------------------------------------------------------------------
  // This method returns the stored pressure.
  // -----------------------------------------------------------------------------------
  int GetPressure() { return pressure; }
	// -----------------------------------------------------------------------------------
	// This method returns whether the Pitot is active or not.
	// -----------------------------------------------------------------------------------
	bool HaveData() { return havePitotData; }
private:
	// -----------------------------------------------------------------------------------
	// This method is called to calculate the seconds since the previous update call.
	// -----------------------------------------------------------------------------------
	float GetDeltaT();
	// -----------------------------------------------------------------------------------
	// This method imcrements the displacment calculated from the pitot velocity.
	// -----------------------------------------------------------------------------------
	void CalcDis();
	const static int MILLISEC_IN_SEC = 1000;
	const static int MAX_12_INT = 1024;
	const static int PITO_ANALOG_PIN = A5;
  const static int RESET_PIN = 50;
  float DISPLACED = 0.4;

	int dis = 0;
  int curFails = 0;
	float vel = 0;
  float pressure = 0;
	bool havePitotData = false;
	long prevTime = 0;
	long currTime = 0;
	float localPitoDisplacement = 0;
};

#endif
