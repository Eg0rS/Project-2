#include "lockproc.h"
#include "mysettings.h"
#include "analize.h"
#include "mygpio.h"
#include "ssec.h"



void SetPass(uint32_t mask, uint32_t key){  // запись пароля в в память 
	DSt.currentkey=key;
	DSt.currentmask=mask;
	hssavetime=getssec();

}

void CheckPass(uint32_t mask, uint32_t key){ // проверка пароля с заданым заранее 
	if(mask == DSt.currentmask && key == DSt.currentkey){ // При совпадении открываем замок 
		DoorCmd(0);
	}
}
void Analize(int16_t massToAnalize[], int16_t size){ // анализ массива с паролем 
				  int16_t max = massToAnalize[0];
				  int16_t min = massToAnalize[0];
	        int16_t averageValue=0;
	        //uint32_t mask = 1;
	        //uint32_t key = 0;
	        uint32_t mask = 1;
					uint32_t key = 0;
	
          if(size == 1){
						if (massToAnalize[0] >=80){
							DoorCmd(1);
							return;
						}
					}
          // 	equalValues - флаг разности значений
	        //  0 - Считаем, что элементы в массиве разные
	        //  1 - Считаем, что элементы в массиве одинаковые
	        int16_t equalValues = 0;
				
				  for(int i = 2; i<size; i+=2){             // Находим максимальны и минимальный элемент массива
						if (massToAnalize[i] < min){
							min = massToAnalize[i];
						}
						if (massToAnalize[i] > max){
							max = massToAnalize[i];
						}
					}
					averageValue = (max - min)/2;
					
					if (__fabs(1-(min/max))<=0.1){ // если разница меньше 10 процентов 
						equalValues = 1;
					}
					 
					if (equalValues == 0){
						for(int i = 0; i<size; i+=2){
							mask <<= 1;
							mask |= 1;
							if(massToAnalize[i] <= averageValue){
								key |= 0;
								key <<= 1;
							}
							else{
								key |= 1;
								key <<= 1;
							}
						}
					}
					else{
						for(int i = 0; i<size; i+=2){
							mask <<= 1;
							mask |= 1;
						}
					 }
					key >>= 1;
					mask >>= 1;
					
					if(!GGetPin(PROGSW)){ // Если геркон с магнитом, записываем пароль
						SetPass(mask, key);
					}
					else{
						CheckPass(mask, key); // Если нет, сверяем с текущеим записанным
					}
}
