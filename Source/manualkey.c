#include "manualkey.h"
#include "mygpio.h"
#include "ssec.h"
#include "lockproc.h"

void manualkey(void) {
	static uint32_t opentime=0;			//Время нажатия на кнопку открытия. 0 - ничего не делаем. отличное от 0 - обрабатываем нажатие.
	static uint32_t closetime=0;			//Время нажатия на кнопку закрытия. 0 - ничего не делаем. отличное от 0 - обрабатываем нажатие.
	if (GGetPin(KEYOPEN)) {				//Если кнопка не нажата.
		if (opentime) {				//Если время нажатия не равно 0.
			if (tdlt(opentime)>30) {	//Если время нажатия больше 30мс. (отсекание дребезга)
				DoorCmd(1);		//Открытие двери.
			}
		  opentime=0;				
	  	}
	} else {					//Если кнопка нажата.
		if (!opentime){ 			//Если кнопка не была нажата
			opentime=getssec();		//Засекаем время нажатия.
		}
	}
	if (GGetPin(KEYCLOSE)) {			//Если кнопка не нажата.
		if (closetime) {			//Если время нажатия не равно 0.
			if (tdlt(closetime)>30) {	//Если время нажатия больше 30мс. (отсекание дребезга)
				DoorCmd(0);		//Закрытие двери.
			}
		closetime=0;
	  	}
	} else {					//Если кнопка нажата.
		if (!closetime){			//Если кнопка не была нажата
			closetime=getssec();		//Засекаем время нажатия.
		}
	}
}
