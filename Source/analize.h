#ifndef ANALIZE_H
#define ANALIZE_H

#include "mainconfig.h"

void SetPass(uint32_t mask, uint32_t key);           // функция записи пароля в HARDDST
void CheckPass(uint32_t mask, uint32_t key);         // функция проверки пароля с текущим 
void Analize(int16_t massToAnalize[], int16_t size); // функция анализа массива

#endif
