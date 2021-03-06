#include "buttonpush.h"
#include "mygpio.h"
#include "ssec.h"

int16_t pnum;							//Позиция текущего элемента массива в который записываем время паузы\нажатия в данный момент.
int16_t pnum1;							//Позиция элемента массива, до которого нужно проводить анализ.
int16_t onb = 0;   						//0 - кнопка еще не нажата. 1 - кнопка нажата какое то время.
int16_t starton = 0; 						//0 - начало нажатия. 1 - нажатие продолжается какое то время.
uint32_t ontime1 = 0;						//Время нажатия.
uint32_t ontime2 = 0;						//Время паузы.

// добавляет очередное нажатие на кнопку в массив нажатий
uint8_t buttonpush() {  
	uint8_t rezt = 0;					//Результат функции. 0 - анализировать массив не надо. 1 - нужно проанализировани массив.
	if (!GGetPin(BUTTON)) {					//Если кнопка нажата.
    		onb=1;							
    		if (starton == 0) {  				//Если это начало нажатия.
      			ontime1 = getssec();			//Запоминаем время начала нажатия.
      			starton = 1;
      			if(tdlt(ontime2) < 20) {		//Отсеивание дрезга. За дребезг считаем нажатие меньше 20мс.
				return rezt;
			}
      			if (pnum){				//Если массив нажатий пустой.
        			push[pnum] = tdlt(ontime2);	//Записываем первое нажатие.
        			pnum++;				//Увеличиваем кол-во нажатий на 1.
      			}
	  	}
  	} else {						//Если кнопка не нажата.
    		if (onb == 1) {					//Если кнопка была нажата.
      			onb=0;					//Сбрасываем флаг нажатия.
      			if(pnum> = MAXIMPULS){			//Если число элементов в массиве нажатий больше максимального кол-ва нажатий.
        			pnum = 0;			//Сбрасываем кол-во 
      			} else{					//Если лимит нажатий не достигнут.
        			push[pnum] = tdlt(ontime1);	//Записывается время нажатия.
        			pnum++;				
      			}
      			starton = 0;				//Нажатие закончено.
      			ontime2 = getssec();			//Запсываем время начала паузы
    		} else {					//Если кнопка не была нажата.
      			if (ontime2&&(tdlt(ontime2) > 1000)) {  //Если пауза длится более 1000мс.
        			rezt = 1;			//Массив надо проанализировать.
        			ontime2 = 0;			//Обнуляем время паузы.
				pnum1 = pnum;			//Колличество нажатий в массиве.
        			pnum = 0;			//Обнуляем номер текущего элемента массива.
      			}
    		}
  	}
	return rezt; 						//Возвращаем результат.
}
