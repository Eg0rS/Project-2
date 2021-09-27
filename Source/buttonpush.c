#include "buttonpush.h"
#include "mygpio.h"
#include "ssec.h"

int16_t pnum;
int16_t pnum1;
int16_t onb = 0;   
int16_t starton = 0; 
uint32_t ontime1 = 0;
uint32_t ontime2 = 0;


uint8_t buttonpush() {  // добавляет очередное нажатие на кнопку в массив нажатий
	uint8_t rezt = 0;
	if (!GGetPin(BUTTON)) {
    	onb=1;
    	if (starton == 0) {  			
      		ontime1 = getssec();
      		starton = 1;
      		if(tdlt(ontime2) < 20) {
			return rezt;
		}
      		if (pnum){
        		push[pnum] = tdlt(ontime2);
        		pnum++;
      		}
	  }
  	} else {
    		if (onb == 1) { 
      			onb=0;
      			if(pnum> = MAXIMPULS){
        			pnum = 0;
      			} else{
        			push[pnum] = tdlt(ontime1);
        			pnum++;
      			}
      			starton = 0;
      			ontime2 = getssec();
    		} else {

      			if (ontime2&&(tdlt(ontime2) > 1000)) {
        			rezt = 1;
        			ontime2 = 0;
				pnum1 = pnum;
        			pnum = 0;
      			}
    		}
  	}
	return rezt;
}
