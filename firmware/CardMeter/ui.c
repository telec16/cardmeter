#include "ui.h"

void drawUI(){

	char buf[16];

	sprintf(buf, "%03X Rng: %04.1f", data.raw0, range_table[config.gain]);
	putString(buf, 0, 2);
	
	sprintf(buf, "%+06.3f", data.ch0);
	putString(buf, 0, 3);

	switch(config.menu){
		case UI_ROOT:
			putString("Rng Tbs Oft   ", 0, 5);
		break;

		case UI_GAIN:
		case UI_TIMEBASE:
			putString(" -   +    Exit", 0, 5);
		break;

		default:
			putString("              ", 0, 5);
		break;
	}
}
