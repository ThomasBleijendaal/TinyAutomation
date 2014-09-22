#include "Arduino.h"
#include "General.h"

General::General(int numAI, int numDI, int numAO, int numDO, int numM, int numPID) {
	communication = Communication();
	time = Time();
	io = IO(1);

	_AIs = new AI[numAI];
	_AIi = 0;
	_DIs = new DI[numDI];
	_DIi = 0;
	_AOs = new AO[numAO];
	_AOi = 0;
	_DOs = new DO[numDO];
	_DOi = 0;
	_Ms = new M[numM];
	_Mi = 0;
	_PIDs = new PID[numPID];
	_PIDi = 0;
}

void General::begin() {
	io.begin();

	// typicals begin //

}

void General::loop() {
	time.loop();
	
	communication.read();
	//io.read();

	for (int i = 0; i < _DIi; i++) {
		_DIs[i].loop(time, communication, io);
	}
	
	for (int i = 0; i < _AIi; i++) {
		_AIs[i].loop(time, communication, io);
	}

	for (int i = 0; i < _PIDi; i++) {
		_PIDs[i].loop(time, communication);
	}

	for (int i = 0; i < _DOi; i++) {
		_DOs[i].loop(time, communication, io);            
	}

	for (int i = 0; i < _AOi; i++) {
		_AOs[i].loop(time, communication, io);
	}

	for (int i = 0; i < _Mi; i++) {
		_Ms[i].loop(time, communication, io);
	}
	
	io.cycle();
	communication.send();
}
	
AI &General::addAI(AI object) {
	
	_AIs[_AIi] = object;
	_AIs[_AIi].setId(_AIi);
	
	return _AIs[_AIi++];
}
DI &General::addDI(DI object) {
	object.setId(_DIi);
	_DIs[_DIi] = object;

	return _DIs[_DIi++];
}
AO &General::addAO(AO object) {
	object.setId(_AOi);
	_AOs[_AOi] = object;

	return _AOs[_AOi++];
}
DO &General::addDO(DO object) {
	object.setId(_DOi);
	_DOs[_DOi] = object;

	return _DOs[_DOi++];
}
PID &General::addPID(PID object) {
	object.setId(_PIDi);
	_PIDs[_PIDi] = object;

	return _PIDs[_PIDi++];
}
M &General::addM(M object) {
	object.setId(_Mi);
	_Ms[_Mi] = object;

	return _Ms[_Mi++];
}

