#include "setup.h"

void pinSetup()
{
	VPORTA.DIR = 0b01111010;
	VPORTB.DIR = 0b00000000;
	VPORTC.DIR = 0b00001111;

}