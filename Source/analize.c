#include "lockproc.h"
#include "mysettings.h"
#include "analize.h"
#include "mygpio.h"
#include "ssec.h"

void SetPass(uint32_t mask, uint32_t key){   
	DSt.currentkey=key;
	DSt.currentmask=mask;
	hssavetime=getssec();

}

void CheckPass(uint32_t mask, uint32_t key){ 
	if(mask == DSt.currentmask && key == DSt.currentkey){  
		DoorCmd(0);
	}
}
void Analize(int16_t massToAnalize[], int16_t size){ 
		int16_t max = massToAnalize[0];
		int16_t min = massToAnalize[0];
	        int16_t averageValue=0;
	        uint32_t mask = 0;
		uint32_t key = 0;
	
          if(size == 1){
		if (massToAnalize[0] >=80){
			DoorCmd(1);
			return;
		}
	}
          	// 	equalValues - флаг разности длительности введеных 
	        //  0 - значения разные 
	        //  1 - значения одинаковые
	        int16_t equalValues = 0;
				
				  for(int i = 2; i<size; i+=2){             
						if (massToAnalize[i] < min){
							min = massToAnalize[i];
						}
						if (massToAnalize[i] > max){
							max = massToAnalize[i];
						}
					}
					averageValue = (max - min) / 2;
					
					if (__fabs(1 - (min/max))<=0.1){ 
						equalValues = 1;
					}
					 
					if (equalValues == 0){
						for(int i = 0; i<size; i+=2){
							mask <<= 1;
							mask |= 1;
							key <<= 1;
							if(massToAnalize[i] <= averageValue){
								key |= 0;
							}
							else{
								key |= 1;
							}
						}
					}
					else{
						for(int i = 0; i < size; i += 2){
							mask <<= 1;
							mask |= 1;
						}
					 }
									
					if(!GGetPin(PROGSW)){ 
						SetPass(mask, key);
					}
					else{
						CheckPass(mask, key); 
					}
}
