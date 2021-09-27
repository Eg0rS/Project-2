#ifndef ANALIZE_H
#define ANALIZE_H

#include "mainconfig.h"

//  Записывает новый пароль в 2 коде в постоянную память HARDDST
void SetPass(uint32_t mask, uint32_t key);     

// Сравнивает введеный пароль с паролем записанным в постоянную память при помощи функции Analize, если пароли совпали, открывает замок 
void CheckPass(uint32_t mask, uint32_t key);    

// Переводит пароль в двоичный код и сравнивает с паролем из постоянной памяти
void Analize(int16_t massToAnalize[], int16_t size); 

#endif
