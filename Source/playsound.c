#include "playsound.h"
#include "ssec.h"

int16_t action_time = 0;
int16_t pnum2 = 0; 
int16_t playsound = 0;

void StartSound(void) {
  pnum2 = 0;
  playsound = 1;
  action_time = getssec();
  Sound(1); 
}

void beep(void){
	if (playsound) {
		if (tdlt(action_time) >= push[pnum2]) {
			pnum2++;
			if (pnum2 < pnum1) {
				action_time=getssec();
				if (pnum2 & 1){ 
					Sound(0);
				} else { 
					Sound(1);
				}
			} else {
				playsound=0;
				Sound(0);
			}
		}
	}
}
