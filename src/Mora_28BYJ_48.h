/*
	Mora_28BYJ_48.h - Library for the 28BYJ_48 stepper motor + ULN2003 driver.
	Created by Moragor, July 13, 2017.
*/

#ifndef Mora_28BYJ_48_h
	#define Mora_28BYJ_48_h					//I'm not good with names ¯\_(ツ)_/¯
	
	#include "Arduino.h"
	
	class Mora_28BYJ_48
	{
		public:
		Mora_28BYJ_48(byte In1, byte In2, byte In3, byte In4);
		void stepF(int numSteps);
		void stepH(int numSteps);
		void setDelay(unsigned int sDelay);
		
		private:
		byte _In1; byte _In2; byte _In3; byte _In4;
		void setOutput(byte _nxt);
		unsigned int _sDelay = 2000;
		char _nextStep = 0;
		int _steps[8] = {B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001};
	};
	
#endif