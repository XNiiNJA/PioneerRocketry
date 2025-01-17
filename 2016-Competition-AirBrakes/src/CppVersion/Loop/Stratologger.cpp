#include "Stratologger.h"

bool Stratologger::Initialize()
{
	Serial2.begin(9600);
#ifdef _DONT_WAIT_FOR_STRATO
  long endTime = millis() + NO_DELAY_DELAY;
#else
	long endTime = millis() + DELAY_FOR_STRATO;
#endif
	while (Serial2.available() <= 0 && millis() < endTime); // loop until we receive data from stratologger
	prevTime = currTime = millis();
	if (millis() >= endTime)
		return false;
	else
	{
		int altAboveSea = Serial2.parseInt();
		return true;
	}
}

void Stratologger::Update()
{
	if (Serial2.available() > 0)
	{
    prevDis = dis;
    prevTime = currTime;
    currTime = millis();
		dis = Serial2.parseInt();
		vel = CalcVel();
		haveStratoData = true;
	}
	else
	{
		haveStratoData = false;
	}
}

float Stratologger::CalcVel()
{
	float temp = CalcDeltaT();
	if (temp == 0.0f)
		return 0;
	else
		return (float)(dis - prevDis) / temp;
}

float Stratologger::CalcDeltaT()
{
	
	return (float)(currTime - prevTime) / MILLISEC_IN_SEC;
}
