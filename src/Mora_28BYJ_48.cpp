/*
	Mora_28BYJ_48.cpp - Library for the 28BYJ_48 stepper motor + ULN2003 driver.
	Created by Moragor, July 13, 2017.
*/

#include "Arduino.h"
#include "Mora_28BYJ_48.h"

Mora_28BYJ_48::Mora_28BYJ_48(uint8_t driverPin1, uint8_t driverPin2, uint8_t driverPin3, uint8_t driverPin4)
	: _driverPin1(driverPin1), _driverPin2(driverPin2), _driverPin3(driverPin3), _driverPin4(driverPin4)
{
	pinMode(driverPin1, OUTPUT);
	pinMode(driverPin2, OUTPUT);
	pinMode(driverPin3, OUTPUT);
	pinMode(driverPin4, OUTPUT);
}

void Mora_28BYJ_48::setDelay(uint16_t sDelay){		//Get the delay in micros from the main code
	_sDelay = sDelay;
};

void Mora_28BYJ_48::stepF( int16_t numSteps) {					//Function for the full step movement. Gets the desired number of steps to make
	while (numSteps > 0){												//Positive numbers for forward rotation
		if(_nextStep % 2 != 1){											//to make sure to use the right values in _steps and not switch to the less torquey single inputs
			_nextStep++;
		}
		else {																	//Advance two positions in _steps per step for full step movement
			_nextStep++;
			_nextStep++;
		}
		if (_nextStep > 7){												//Start over after the last step in _steps
			_nextStep = 1;
		}
		setOutput(_nextStep);											//Powers the motor's coils through the function at the bottom
		delayMicroseconds(_sDelay);									//Delay between the steps
		numSteps--;															//Reduce the remaining steps by one. Loop ends if numSteps is 0 or below.
	}
	
	while (numSteps < 0){												//Negative number for backwards rotation. Same a above, but in the opposite direction
		if(_nextStep % 2 != 1){
			_nextStep--;
		}
		else {
			_nextStep--;
			_nextStep--;
		}
		if (_nextStep < 1){
			_nextStep = 7;
		}
		setOutput(_nextStep);
		delayMicroseconds(_sDelay);
		numSteps++;
	}
};

void Mora_28BYJ_48::stepH( int16_t numSteps) {				//Function for the half step movement.
	while (numSteps > 0){
		_nextStep++;													//Similar to above's function, but with single advancements in _steps
		if (_nextStep > 7){
			_nextStep = 0;
		}
		setOutput(_nextStep);
		delayMicroseconds(_sDelay);
		numSteps--;
	}
	
	while (numSteps < 0){
		_nextStep--;
		if (_nextStep < 0){
			_nextStep = 7;
		}
		setOutput(_nextStep);
		delayMicroseconds(_sDelay);
		numSteps++;
	}
};

void Mora_28BYJ_48::setOutput(uint8_t _nxt) {				//The function that sets the outputs on the Arduino HIGH or LOW (1 or 0)
	digitalWrite(_driverPin1, bitRead(_steps[_nxt], 0));			//digitalWrite("Arduino Pin", bitRead("_steps array"["array position "_nextStep""], "bit position from least significant"))
	digitalWrite(_driverPin2, bitRead(_steps[_nxt], 1));
	digitalWrite(_driverPin3, bitRead(_steps[_nxt], 2));
	digitalWrite(_driverPin4, bitRead(_steps[_nxt], 3));
};
