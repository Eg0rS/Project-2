#include "buttonpush.h"
#include "mygpio.h"
#include "ssec.h"

// Переменные функции записи данных
int16_t pnum;
//extern int16_t pnum;  // Число записанных элементов
int16_t pnum1;
int16_t onb=0;   // Флаг нажатой кнопки
int16_t starton=0; // Флаг отжатой кнопки
// Измерение времени паузы и нажатия
uint32_t ontime1=0;
uint32_t ontime2=0;

//function for mass and push
// Возвращает ноль, если ничего не произошло, и единицу, если нужно проанализировать массив
uint8_t buttonpush() {
	uint8_t rezt=0;
	if (!GGetPin(BUTTON)) {
    onb=1;
    if (starton==0) {  // Сюда попадаем, если кнопку только что нажали				
      ontime1=getssec();
      starton=1;
      if(tdlt(ontime2)<20) return rezt; // Исключаем дребезг
      if (pnum){
        push[pnum]=tdlt(ontime2);
        pnum++;
      }
	  }
  } else {
    if (onb==1) { //Сюда попадаем, если кнопку только что отпустили 
      onb=0;
      if(pnum>=MAXIMPULS){
        pnum=0;
      } else{
        push[pnum]=tdlt(ontime1);
        pnum++;
      }
      starton=0;
      ontime2=getssec();
    } else {
// Сюда попадаем, если кнопку уже давно отпустили
      if (ontime2&&(tdlt(ontime2)>1000)) {
        rezt=1;
        ontime2=0;
				pnum1 = pnum;
        pnum=0;
      }
    }
  }
	return rezt;
}
