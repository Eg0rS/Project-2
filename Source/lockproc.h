#ifndef LOCKPROC_H
#define LOCKPROC_H

#include "mainconfig.h"

// Функция запуска открытия или закрытия двери
// 0 - закрываем
// 1 - открываем
void DoorCmd(uint8_t cmd);
// Функция работы с замком. Вызывать постоянно
void opendoor(void);

#endif
