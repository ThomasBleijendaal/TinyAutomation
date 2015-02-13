/*
General Time functionality

Includes
- OS: one shots: timed booleans
- B: blink: blinking booleans
*/
#ifndef Time_h
#define Time_h

class Time {
    public:
        Time() : _ms(0U), _1000ms(0U), _customTimer(0U), _m(0U), _h(0), cps(0U), _cps(0U), b1s(false) {};

		bool b1s;

		bool t10ms;
		bool t100ms;
		bool t1s;
		bool t5s;
		bool t30s;
		bool t1m;
		bool t5m;
		bool t1h;

		unsigned long cps;

		void loop();

		bool timer(unsigned int ms);

	private:
		// stored value of micros() //
		unsigned long _ms;
		// counter up to 1000 ms (resolution 10 ms)
		unsigned int _1000ms;
		// counter up to 655350 ms (resolution 10 ms) for custom timers //
		unsigned int _customTimer;

		// counter up to 60 s (resolution 1 s)
		unsigned char _m;
		// counter up to 60 m (resolution 1 m)
		unsigned char _h;

		unsigned long _cps;

		inline void _resetTimers();
};

#endif