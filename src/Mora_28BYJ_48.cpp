/*
	Mora_28BYJ_48.cpp - Library for the 28BYJ_48 stepper motor + ULN2003 driver.
	Created by Moragor, July 13, 2017.
	Updated by Moragor, October 15, 2017.
*/

#include "Arduino.h"
#include "Mora_28BYJ_48.h"

Mora_28BYJ_48::Mora_28BYJ_48(uint8_t driverPin1, uint8_t driverPin2, uint8_t driverPin3, uint8_t driverPin4)		//The constructor, fetches the pin numbers connected to the driver module.
: _driverPin1(driverPin1), _driverPin2(driverPin2), _driverPin3(driverPin3), _driverPin4(driverPin4)		//Initializer list
{
	pinMode(driverPin1, OUTPUT);
	pinMode(driverPin2, OUTPUT);
	pinMode(driverPin3, OUTPUT);
	pinMode(driverPin4, OUTPUT);
}

void Mora_28BYJ_48::setDelay(uint16_t sDelay, bool precMode){		//Get the delay and the precision mode status from the main code.
	_sDelay = sDelay;
	_precMode = precMode;
};

void Mora_28BYJ_48::stepF( int16_t numSteps) {		//Function for the full step movement. Gets the desired number of steps to make.
	while (numSteps > 0){											//Positive numbers for forward rotation.
		if(_nextStep % 2 != 1){										//to make sure to use the right values in the_steps array and not switch to the less torquey single inputs.
			_nextStep++;
		}
		else {																//Advance two positions in _steps per step for full step movement.
			_nextStep++;
			_nextStep++;
		}
		if (_nextStep > 7){											//Start over after the last step in _steps
			_nextStep = 1;
		}
		setOutput(_nextStep);										//Powers the motor's coils through the "setOutput" function at the bottom.
		executeDelay();													//delays the next step through the "executeDelay" function at the bottom.
		numSteps--;														//Reduce the remaining steps by one. Loop ends if numSteps is 0 or below.
	}
	
	while (numSteps < 0){											//Negative number for backwards rotation. Same a above, but in the opposite direction.
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
		executeDelay();
		numSteps++;
	}
};

void Mora_28BYJ_48::stepH( int16_t numSteps) {		//Function for the half step movement.
	while (numSteps > 0){
		_nextStep++;													//Similar to above's function, but with single advancements in _steps.
		if (_nextStep > 7){
			_nextStep = 0;
		}
		setOutput(_nextStep);
		executeDelay();
		numSteps--;
	}
	
	while (numSteps < 0){
		_nextStep--;
		if (_nextStep < 0){
			_nextStep = 7;
		}
		setOutput(_nextStep);
		executeDelay();
		numSteps++;
	}
};

void Mora_28BYJ_48::setOutput(uint8_t _nxt) {		//The function that sets the outputs on the Arduino HIGH or LOW (1 or 0).
	digitalWrite(_driverPin1, bitRead(_steps[_nxt], 0));		//digitalWrite("Arduino Pin", bitRead("_steps array"["array position "_nextStep""], "bit position from least significant"))
	digitalWrite(_driverPin2, bitRead(_steps[_nxt], 1));
	digitalWrite(_driverPin3, bitRead(_steps[_nxt], 2));
	digitalWrite(_driverPin4, bitRead(_steps[_nxt], 3));
};

void Mora_28BYJ_48::executeDelay(){		//The function for the delay between steps.
	if(_precMode == true){							//Checks if precision mode is used.
		delayMicroseconds(_sDelay);				//If true, delay is in microseconds.
	}
	else{													//If false delay is in milliseconds.
		delay(_sDelay);
	}	
};


