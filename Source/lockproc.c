#include "lockproc.h"
#include "ssec.h"
#include "mygpio.h"

// Текущая команда
// 0 - ничего не делаем
// 10 - команда на открытие двери
// 11 - идет импульс открытия двери
// 20 - команда на закрытие двери
// 21 - идет закрытие двери
// 30 - пауза после выполнения операции
int16_t doorst = 0;

// Функция запуска открытия или закрытия двери
// 0 - закрываем
// 1 - открываем
void DoorCmd(uint8_t cmd) {
	if (doorst) return; // Что-то выполняется, команды выполнять нельзя
	if (cmd) {
		doorst=10;
	} else {
		doorst=20;
	}
}

void opendoor(void) {
	static uint32_t dtime=0; // Время операции
  switch (doorst) {
		case (0):       // Ничего не делаем. На всякий случай выключаем реле
			GResetPin(RELAYOPEN);  	
			GResetPin(RELAYCLOSE);
			break;
		case (10):              // Команда открыватия замка
			GSetPin(RELAYOPEN);
		  dtime=getssec();
		  doorst=11;
		  break;
		case (11):              // Выполняется команда открывания замка
			if (tdlt(dtime)>300) {
				doorst=30;
				GResetPin(RELAYOPEN);
				dtime=getssec();
			}
			break;
		case (20):              // Команда открыватия замка
			GSetPin(RELAYCLOSE);
		  dtime=getssec();
		  doorst=21;
		  break;
		case (21):              // Выполняется команда открывания замка
			if (tdlt(dtime)>300) {
				doorst=30;
				GResetPin(RELAYCLOSE);
				dtime=getssec();
			}
			break;	
	  case (30):
			if (tdlt(dtime)>500) {
				dtime=0;
				doorst=0;
			}
			break;
		default:
			doorst=0; // На всякий случай
	}
}
 
