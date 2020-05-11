#include "user_input.h"

void scanBtn(){
	switch(config.menu){
		case UI_ROOT:
			if(_SW1) config.menu = UI_GAIN;
			if(_SW2) config.menu = UI_TIMEBASE;
			if(_SW3) config.action = ACT_OFFSET;
			if(_SW4) ;
		break;
		case UI_GAIN:
			if(_SW1) config.gain++;
			if(_SW2) config.gain--;
			if(_SW3) ;
			if(_SW4) config.menu = UI_ROOT;

			config.gain = _CLIP(0, config.gain, 7);
			AD8231_gain(config.gain, CS_GAIN);
		break;
		case UI_TIMEBASE:
			if(_SW1) config.timebase--;
			if(_SW2) config.timebase++;
			if(_SW3) ;
			if(_SW4) config.menu = UI_ROOT;
		break;
	}
}
