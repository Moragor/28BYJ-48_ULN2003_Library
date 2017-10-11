/*
	Mora_28BYJ_48.cpp - Library for the 28BYJ_48 stepper motor + ULN2003 driver.
	Created by Moragor, July 13, 2017.
*/

#include "Arduino.h"
#include "Mora_28BYJ_48.h"

Mora_28BYJ_48::Mora_28BYJ_48(byte In1, byte In2, byte In3, byte In4)
{
	pinMode(In1, OUTPUT);
	pinMode(In2, OUTPUT);
	pinMode(In3, OUTPUT);
	pinMode(In4, OUTPUT);
	
	_In1 = In1;
	_In2 = In2;
	_In3 = In3;
	_In4 = In4;
}

void Mora_28BYJ_48::setDelay(unsigned int sDelay){		//Get the delay in micros from the main code
	_sDelay = sDelay;
};

void Mora_28BYJ_48::stepF( int numSteps) {					//Function for the full step movement. Gets the desired number of steps to make
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

void Mora_28BYJ_48::stepH( int numSteps) {				//Function for the half step movement.
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

void Mora_28BYJ_48::setOutput(byte _nxt) {				//The function that sets the outputs on the Arduino HIGH or LOW (1 or 0)
	digitalWrite(_In1, bitRead(_steps[_nxt], 0));			//digitalWrite("Arduino Pin", bitRead("_steps array"["array position "_nextStep""], "bit position from least significant"))
	digitalWrite(_In2, bitRead(_steps[_nxt], 1));
	digitalWrite(_In3, bitRead(_steps[_nxt], 2));
	digitalWrite(_In4, bitRead(_steps[_nxt], 3));
};