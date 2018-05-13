
class CascadeLed{

public:	
	//
	//CascadeLedconstructor:
	// strip - pointer to Adafruit Neopixel instance
	// pic   - pointer to a 2 dimensional array of pixels.   Pixels will be turned on in row order
	// maxrow, maxcol - dimensions of the 2 dimensional array that are actually used.   MAXROW/MAXCOL define the actual array limits
	// red, green, blue  - rgb values ranging from 0-255
	// freq - frequency in which to transition between the row pixels
	// freqoff - this library was written to trigger off a car light turn signal.  While blinking, there will be a period when the 
	//              triggering light will be off.  freqoff is the time you normally see the line off when blinking
	CascadeLed(Adafruit_NeoPixel *strip, byte (*pix)[MAXROW][MAXCOL], byte  maxrow, byte  maxcol, byte  red, byte  green, byte  blue, long freq, long offfreq);

	// animate the LEDs.  
	// on  - true - animate
	//       false - animate until ignorefreq is exceeded and then turn off.   Leds turn off only once (i.e.   multiple false calls will not turn the 
	//               leds off multiple times.   This is to keep this animation from turning off shared LEDs of a different animation.
	bool Blink(bool on);

	// explicity turn on/off a specific row w/o animation.
	void Set(int row, bool on);



private:
	bool PseudoOn(bool on);
	Adafruit_NeoPixel *_strip;	
	byte(*_pix)[MAXROW][MAXCOL];
	byte  _maxrow;
	byte  _maxcol;
	byte  _red;
	byte  _green;
	byte  _blue;
	long _freq;
	long _freqoff;
	long _timeout;
	long _nextiteration;
	byte  _nextrow;
	byte  _phase;
	bool _currentlyOn;
};