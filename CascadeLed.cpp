#include <Adafruit_NeoPixel.h>
#include <ArrayConstants.h>  // WARNING: check these constants before compiling, it may need changing between sketches
#include "CascadeLed.h"

CascadeLed::CascadeLed(Adafruit_NeoPixel *strip, byte (*pix)[MAXROW][MAXCOL], byte maxrow, byte maxcol, byte red, byte green, byte blue, long freq, long freqoff)
{
	_strip = strip;
	_pix = pix;
	_maxrow = maxrow;
	_maxcol = maxcol;
	_red = red;
	_green = green;
	_blue = blue;		
	_freq = freq;
	_freqoff = freqoff;
	_nextrow = 0;
	_nextiteration = 0;
	_currentlyOn = false;
}


bool CascadeLed::Blink(bool on){
  if (PseudoOn(on))
  {
    _currentlyOn = true;
    if (_nextiteration < millis()) // is it time?
    {	 
		// phase0 - turn row on
		// phase1 - turn row off
		Set(_nextrow, (_phase==0));
		_strip->show();

		_nextiteration =  millis() + _freq; 
		_nextrow++;
		if (_nextrow >= _maxrow) 
		{
			_nextrow = 0;
			_phase++;
			if (_phase > 1)
			{
				_phase = 0;
			}		
		}
    }
  }
  else
  {
	if(_currentlyOn)
	{
		// only turn off if we are currently on
		// done like this so we don't turn off shared pixels of another animation
		if (_nextiteration < millis()) // is it time?
		{	\
			for (int row = 0; row < _maxrow; row++)
			{
				Set(row, false);
			}
			_strip->show();

			_currentlyOn = false;
			_nextrow = 0;
			_phase = 0;
		}
	}
  }
  return _currentlyOn;
}

void CascadeLed::Set(int row, bool on)
{
   for (int col = 0; col < _maxcol; col++)
   {
     if (on)
     {     
    	 _strip->setPixelColor((*_pix)[row][col], _strip->Color(_red, _green, _blue));
     }
     else
     {
         _strip->setPixelColor((*_pix)[row][col], _strip->Color(0,0,0));
     }
   }
}

// used to ignore the off part of the blinking turn signal 
bool CascadeLed::PseudoOn(bool on)
{
	bool retval = on;
	long now = millis();
	if (retval)
	{
		// light is on, reset the timeout
		_timeout = now + _freqoff; 
	}
	else
	{
		// light is off
		if (_timeout > now)
		{ 
			// we haven't reached the _freqoff timeout so pretend the bulb is still on
			retval = true; 
		}
	}
	return retval;
}