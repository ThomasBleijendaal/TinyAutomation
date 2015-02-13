#include "Arduino.h"
#include "PID.h"

void PID::begin(Time * time, Communication * communication) {
	iTimer = false;
}
void PID::loop(Time * time, Communication * communication) {
	bool stateChanged = false;
	bool timer1 = false;
	bool timer2 = false;

	float value = _AI->data.value;
	float output = _AO->data.output;

	float delta = (((settings.sp - value)) / (_AI->settings.rangeHigh - _AI->settings.rangeLow)) * 100.0;

	float historyTotal = 0.0;
	float deltaTotal = 0.0;

	if(settings.I > 0) {
		timer1 = time->timer(settings.I / 10U);
		if(!iTimer && timer1) {
			history.add(delta);
			iTimer = true;
		} else if(!timer1) {
			iTimer = false;
		}
		historyTotal = history.total();
	}
	if(settings.D > 0) {
		timer2 = time->timer(settings.D / 10U);
		if(!dTimer && timer2) {
			historyDelta.add(delta);
			dTimer = true;
		} else if(!timer2) {
			dTimer = false;
		}
		deltaTotal = historyDelta.delta();
	}

	if (status.active) {
		if (time->t100ms) {
			if (!status.wasActive) {
				status.wasActive = stateChanged = true;
			}

			float newOutput = output + ((delta + historyTotal + deltaTotal) * settings.P);

			output = max(settings.minOutput, min(settings.maxOutput, newOutput));

		}
		if (settings.deviationLimit > 0.0 && abs(delta) >= (settings.maxOutput - settings.minOutput) * settings.deviationLimit) {
			if (time->t1s)
				status.deviated = ++data.deviationDelay >= 5;

			if (status.deviated && !status.wasDeviated)
				stateChanged = status.wasDeviated = true;
		}
		else {
			status.deviated = false;

			stateChanged = stateChanged || status.wasDeviated;
			status.wasDeviated = false;

			data.deviationDelay = 0;
		}
	}
	else {
		stateChanged = status.wasActive;
		status.wasActive = false;

		output = 0.0;
	}

	if (time->t1s || stateChanged) {
		PID_commSend_t sendData;

		sendData.status = status;
		sendData.data = data;

		communication->sendData(sizeof(sendData), PID_COM_data_ID, _id, (char *)&sendData);
	}

	_AO->status.active = status.active;
	_AO->data.output = output;
}