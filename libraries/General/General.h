/*
General Typical functionality

Includes
- OS: one shots: timed bools
- B: blink: blinking bools
- Serial communication (very beta)
*/
#ifndef General_h
#define General_h

#include <Communication.h>
#include <Time.h>
#include <IO.h>

#include <AI.h>
#include <DI.h>
#include <AO.h>
#include <DO.h>
#include <M.h>
#include <PID.h>

class General {
    public:
		General(int numAI, int numDI, int numAO, int numDO, int numM, int numPID);

		AI &addAI(AI object);
		DI &addDI(DI object);
		AO &addAO(AO object);
		DO &addDO(DO object);
		M &addM(M object);
		PID &addPID(PID object);

		void loop();

		Communication communication;
		Time time;
		IO io;
    
	private:
		AI* _AIs;
		int _AIi;

		DI* _DIs;
		int _DIi;

		AO* _AOs;
		int _AOi;

		DO* _DOs;
		int _DOi;

		M* _Ms;
		int _Mi;

		PID* _PIDs;
		int _PIDi;

};

#endif