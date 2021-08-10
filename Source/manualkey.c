#include "manualkey.h"
#include "mygpio.h"
#include "ssec.h"
#include "lockproc.h"

void manualkey(void) {
	static uint32_t opentime=0;
	static uint32_t closetime=0;
	if (GGetPin(KEYOPEN)) {
		if (opentime) {
			if (tdlt(opentime)>30) {
				DoorCmd(1);
			}
		  opentime=0;
	  }
	} else {
		if (!opentime) opentime=getssec();
	}
	if (GGetPin(KEYCLOSE)) {
		if (closetime) {
			if (tdlt(closetime)>30) {
				DoorCmd(0);
			}
		  closetime=0;
	  }
	} else {
		if (!closetime) closetime=getssec();
	}
}
