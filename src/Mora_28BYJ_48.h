/*
	Mora_28BYJ_48.h - Library for the 28BYJ_48 stepper motor + ULN2003 driver.
	Created by Moragor, July 13, 2017.
*/

#ifndef MORA_28BYJ_48_H
	#define MORA_28BYJ_48_H					//I'm not good with names ¯\_(ツ)_/¯
	
	#include "Arduino.h"
	
	class Mora_28BYJ_48
	{
		public:
		Mora_28BYJ_48(uint8_t driverPin1, uint8_t driverPin2, uint8_t driverPin3, uint8_t driverPin4);
		void stepF(int16_t numSteps);
		void stepH(int16_t numSteps);
		void setDelay(uint16_t sDelay);
		
		private:
		uint8_t _driverPin1; uint8_t _driverPin2; uint8_t _driverPin3; uint8_t _driverPin4;
		void setOutput(uint8_t _nxt);
		uint16_t _sDelay = 2000;
		int8_t _nextStep = 0;
		static const uint8_t _steps[8] = {B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001};
	};
	
#endif
