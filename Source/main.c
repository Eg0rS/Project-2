#include "mainconfig.h"
#include "mygpio.h"
#include "myiwdg.h"
#include "ssec.h"
#include "mysettings.h"
#include "playsound.h"
#include "buttonpush.h"
#include "lockproc.h"
#include "manualkey.h"
#include "analize.h"


int16_t push[MAXIMPULS];  

void SysInit(void) {
  RCC->CR |= 0x00000001;     
  while (!(RCC->CR&0x02));  

  RCC->CR &= 0x0000FFF8;
  RCC->CFGR=0;  

  RCC->CFGR2=1;  
  RCC->CFGR3=0;
  RCC->CFGR|=0x00080000;  
  RCC->CR |= 0x01000000;  
  while (!RCC->CR&0x02000000);        
  FLASH->ACR = 0x00000010;  
  RCC->CFGR|=0x00000002;    
  while (!((RCC->CFGR&0x0C)==(0x02<<2)));  

  RCC->CIR = 0x00000000;    
}

void ConfigHW() {

  RCC->AHBENR|=RCC_AHBENR_GPIOAEN|RCC_AHBENR_GPIOBEN|RCC_AHBENR_GPIOCEN|RCC_AHBENR_GPIODEN|RCC_AHBENR_GPIOFEN;
  RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;     
  RCC->APB2ENR|=RCC_APB2ENR_SYSCFGCOMPEN;

  GSetPinToOutput(RELAYOPEN,0,0);
  GSetPinToOutput(RELAYCLOSE,0,0);  
  GSetPinToOutput(MAINLED,1,0);
  GSetPinToOutput(SOUND,0,0);

  GSetPinToInput(KEYOPEN,GPIO_PULLUP);
  GSetPinToInput(KEYCLOSE,GPIO_PULLUP);
  GSetPinToInput(PROGSW,GPIO_PULLUP);
  GSetPinToInput(BUTTON,0);

  GSetPinToInput(GPIOA,0,GPIO_PULLDOWN);
  GSetPinToInput(GPIOA,1,GPIO_PULLDOWN);
  GSetPinToInput(GPIOA,2,GPIO_PULLDOWN);
  GSetPinToInput(GPIOA,3,GPIO_PULLDOWN);
  GSetPinToInput(GPIOA,4,GPIO_PULLDOWN);
  GSetPinToInput(GPIOA,5,GPIO_PULLDOWN);
  GSetPinToInput(GPIOA,11,GPIO_PULLDOWN);
  GSetPinToInput(GPIOA,12,GPIO_PULLDOWN);
  GSetPinToInput(GPIOB,5,GPIO_PULLDOWN);
  GSetPinToInput(GPIOB,7,GPIO_PULLDOWN);

  InitSSEC();
  __enable_irq();
}


int main() {	

  SysInit();   
#ifndef MYDEBUG
  InitIWDG(4);
#endif
  ConfigHW();  
  ReinitFromHardDSt(0);
  while (hssavetime!=0) {
    CLRWDT();
    CheckSaveHardDSt();
  }
  for (;;) {  
    CheckSaveHardDSt();
    if (buttonpush()) {  
	Analize(push, pnum1);	 			
	StartSound();			
    }
    beep();
    opendoor();
    manualkey();
  }

}
