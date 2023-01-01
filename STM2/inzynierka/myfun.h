#ifndef _MYFUN
#define _MYFUN

#include <stm32f10x.h>

typedef enum{LedOff = 0, LedOn = 1, LedTog = 2}eLed;



void delay_ms(uint32_t ms);
void Led_Conf(void);
void Led_OnOff(uint8_t num, eLed state);
void Timer_Conf(void);
void Pin_Conf(void);
void USART_Conf(void);
void BluetoothReceive(void);
int ComReceive(USART_TypeDef* USARTx);
void Start_Position(void);
void MoveForward1(void);
void MoveForward2(void);
void MoveBackwards1(void);
void MoveBackwards2(void);
void TurnLeft1(void);
void TurnLeft2(void);
void TurnRight1(void);
void TurnRight2(void);
void ResetPosition(void);
void ResetPositionB(void);
void Algorythm_one(void);
void ResetPosition_2 (void);
void StartPosition_2 (void);
void MoveFroward_2(void);
void abc (void);
void abc2 (void);
void abc3 (void);
void abc4 (void);
void Algorytm_two (void);


#endif
