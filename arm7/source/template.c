/*---------------------------------------------------------------------------------

	default ARM7 core

		Copyright (C) 2005 - 2010
		Michael Noland (joat)
		Jason Rogers (dovoto)
		Dave Murphy (WinterMute)

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any
	damages arising from the use of this software.

	Permission is granted to anyone to use this software for any
	purpose, including commercial applications, and to alter it and
	redistribute it freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you
		must not claim that you wrote the original software. If you use
		this software in a product, an acknowledgment in the product
		documentation would be appreciated but is not required.

	2.	Altered source versions must be plainly marked as such, and
		must not be misrepresented as being the original software.

	3.	This notice may not be removed or altered from any source
		distribution.

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <sndcommon.h>

//---------------------------------------------------------------------------------
void VblankHandler(void) {
//---------------------------------------------------------------------------------
	inputGetAndSend();
}

volatile bool exitflag = false;

//---------------------------------------------------------------------------------
void powerButtonCB() {
//---------------------------------------------------------------------------------
	exitflag = true;
}

//---------------------------------------------------------------------------------
int main() {
	u32 i=0;
//---------------------------------------------------------------------------------
    // Read user information from the firmware (name, birthday, etc)
    readUserSettings();

    // Stop LED blinking
    ledBlink(LED_ALWAYS_ON);

    irqInit();
    fifoInit();

	installSoundFIFO();
	installSystemFIFO();

    // This sets a callback that is called when the power button in a DSi
    // console is pressed. It has no effect in a DS.
    setPowerButtonCB(powerButtonCB);

    // Read current date from the RTC and setup an interrupt to update the time
    // regularly. The interrupt simply adds one second every time, it doesn't
    // read the date. Reading the RTC is very slow, so it's a bad idea to do it
    // frequently.
    initClockIRQTimer(3);

	//mmInstall(FIFO_MAXMOD);
	InstallSoundSys();

	irqSet(IRQ_VBLANK, VblankHandler);
	irqEnable(IRQ_VBLANK);

	// Keep the ARM7 mostly idle
	while (!exitflag) {
		if ( 0 == (REG_KEYINPUT & (KEY_SELECT | KEY_START | KEY_L | KEY_R))) {
			exitflag = true;
		}
		swiWaitForVBlank();
		if(seq_status==STATUS_FADING)
		{
			if(i<24)
			{
				i+=10;
			}
			else
			{
				i-=24;
				ADSR_mastervolume--;
				if(!ADSR_mastervolume)
					StopSeq();
			}
		}
	}
	return 0;
}