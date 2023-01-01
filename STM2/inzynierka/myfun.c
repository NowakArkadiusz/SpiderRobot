#include "myfun.h"

volatile uint32_t tick = 0;
volatile int temp = 0;
volatile uint8_t set = 0;
volatile uint8_t position=0;
volatile uint8_t alg = 0;

uint16_t z1F1=0;
uint16_t z2F1=0;
uint16_t z3F1=0;
uint16_t z4F1=0;
uint16_t z1F2=0;
uint16_t z2F2=0;
uint16_t z3F2=0;
uint16_t z4F2=0;
uint16_t z1F3=0;
uint16_t z2F3=0;
uint16_t z3F3=0;
uint16_t z4F3=0;
uint16_t z1F4=0;
uint16_t z2F4=0;
uint16_t z3F4=0;
uint16_t z4F4=0;
int pos1=0;
int pos2=0;
int pos3=0;
int pos4=0;
int pos5=0;
int pos6=0;
volatile uint8_t status=0;
volatile uint8_t status1=0;

void delay_ms(uint32_t ms)
{
	tick=0;
	while(tick < ms);
}	
void SysTick_Handler(void)
{
	tick++;
}
void Led_Conf(void)
{
		RCC->APB2ENR |= (1<<4);
		GPIOC->CRH |= (  (1<<20) | (1<<21)  );
		GPIOC->CRH &= ~(  (1<<22) | (1<<23)  );	
}
void Led_OnOff(uint8_t num, eLed state)
{
	switch(num)
	{
		case 0:
		if(state == LedOn) 				GPIOC->BSRR = (1<<13);//GPIOC->CRH |= (  (1<<20) | (1<<21)  );
		else if(state == LedOff)	GPIOC->BSRR = (1<<29);//GPIOC->CRH &= ~(  (1<<22) | (1<<23)  );	
		else if(state == LedTog)  GPIOC->BSRR = (1<<13);//GPIOC->CRH ^= (  (1<<22) | (1<<23)  );	
		break;
	}
}
void Timer_Conf(void) // enable timers used for steering servos
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM2EN;
	
								//  TIMER 4
	
	TIM4->CCER |= TIM_CCER_CC4E | TIM_CCER_CC3E | TIM_CCER_CC2E | TIM_CCER_CC1E;
	TIM4->CR1 |= TIM_CR1_ARPE;
	
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE |
							   TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3PE;
	TIM4->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2PE|
								 TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE;
	
  TIM4->PSC = 36;
  TIM4->ARR = 20000;
  TIM4->CCR4;
  TIM4->CCR3;
	TIM4->CCR2;
	TIM4->CCR1;
		
	TIM4->EGR |= TIM_EGR_UG;
	TIM4->CR1 |= TIM_CR1_CEN;

								//  TIMER 3	
								
	TIM3->CCER |= TIM_CCER_CC4E | TIM_CCER_CC3E | TIM_CCER_CC2E | TIM_CCER_CC1E;
	TIM3->CR1 |= TIM_CR1_ARPE;
	
	TIM3->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE |
							   TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3PE;
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2PE|
								 TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE;
	
  TIM3->PSC = 36;
  TIM3->ARR = 20000;
  TIM3->CCR4;
  TIM3->CCR3;
	TIM3->CCR2;
	TIM3->CCR1;
		
	TIM3->EGR |= TIM_EGR_UG;
	TIM3->CR1 |= TIM_CR1_CEN;
	
								//  TIMER 2
								
	TIM2->CCER |= TIM_CCER_CC4E | TIM_CCER_CC3E | TIM_CCER_CC2E | TIM_CCER_CC1E;
	TIM2->CR1 |= TIM_CR1_ARPE;
	
	TIM2->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE |
							   TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3PE;
	TIM2->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2PE|
								 TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE;
	
  TIM2->PSC = 36;
  TIM2->ARR = 20000;
  TIM2->CCR4;
  TIM2->CCR3;
	TIM2->CCR2;
	TIM2->CCR1;
		
	TIM2->EGR |= TIM_EGR_UG;
	TIM2->CR1 |= TIM_CR1_CEN;
}
void Pin_Conf(void) // enable pins for servos (12x per 1 STM32)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
	
	            // pin B6, B7, B8, B9
	GPIOB->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1 |
              	GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1 | GPIO_CRH_CNF8_1;
	GPIOB->CRL |= GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1 | GPIO_CRL_CNF7_1 |
								GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1 | GPIO_CRL_CNF6_1;
	
  GPIOB->CRH &= ~GPIO_CRH_CNF9_0 & ~GPIO_CRH_CNF8_0;
	GPIOB->CRL &=	~GPIO_CRL_CNF7_0 & ~GPIO_CRL_CNF6_0;
	
	            // pin A6, A7, B0, B1
	GPIOA->CRL |= GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1 | GPIO_CRL_CNF7_1 |
								GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1 | GPIO_CRL_CNF6_1;
	GPIOB->CRL |= GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1 | GPIO_CRL_CNF0_1 |
              	GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1 | GPIO_CRL_CNF1_1;

	GPIOA->CRL &=	~GPIO_CRL_CNF7_0 & ~GPIO_CRL_CNF6_0;
  GPIOB->CRL &= ~GPIO_CRL_CNF0_0 & ~GPIO_CRL_CNF1_0;

	            // pin A0, A1, A2, A3
	GPIOA->CRL |= GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1 | GPIO_CRL_CNF0_1 |
              	GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1 | GPIO_CRL_CNF1_1;
	GPIOA->CRL |= GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1 |
								GPIO_CRL_MODE3_0 | GPIO_CRL_MODE3_1 | GPIO_CRL_CNF3_1;


  GPIOA->CRL &= ~GPIO_CRL_CNF0_0 & ~GPIO_CRL_CNF1_0;
	GPIOA->CRL &=	~GPIO_CRL_CNF2_0 & ~GPIO_CRL_CNF3_0;
}
void USART_Conf(void) // enable USART
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
	
	GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1;
	GPIOA->CRH &= ~(GPIO_CRH_CNF9_0);
	
	USART1->BRR = 0x1D4C;
	//						 RX enable			TX enable			 UART enable
	USART1->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
	
	// enable RXNE and TXE interrupts
	USART1->CR1 |= USART_CR1_RXNEIE | USART_CR1_TXEIE;
	
	//NVIC_EnableIRQ(USART1_IRQn);
	
}

int ComReceive(USART_TypeDef* USARTx) // function for receiving signals from android application
{
	int znak;
	if((USARTx->SR & USART_SR_RXNE) != RESET)
	{
		znak = USARTx->DR;
		return znak;
	}
	return 0;
}
void BluetoothReceive(void)
{
	switch (ComReceive(USART1))
	{
		case 1:
		set = 1;
		position=1;
		break;
		case 2:
		set = 2;
		position=2;
		break;
		case 3:
		set = 3;
		position=3;
		break;
		case 4:
		set = 4;
		position=4;
		break;	
		case 5:
		set = 5;
		position=5;
		break;	
		case 6:
		alg = 0;
		break;
		case 7:
		alg=1;
		break;
	}
}
void Start_Position(void) // algorithm at the Power On
{
 while (pos1 <200)
	{
		TIM4->CCR3=2950; //+700
		TIM4->CCR4=3000; //+600
		TIM2->CCR4=2250; //-700
		TIM3->CCR1=2000; //-600
		pos1++;
		delay_ms(1);
	}
	while (pos2<=400)
	{
		TIM2->CCR3=2500;
		TIM4->CCR2=2300;
		pos2++;
		delay_ms(1);
	}
	while (pos3 <200)
	{
		TIM2->CCR4=2950;
		TIM3->CCR1=2600;
		TIM4->CCR3=2250;
		TIM4->CCR4=2400;
		pos3++;
		delay_ms(1);
	}
	 while (pos4 <200)
	{
		TIM3->CCR3=2400; //-700
    TIM3->CCR4=2400; //-600
		TIM2->CCR2=3230; //+700
		TIM2->CCR1=3100; //+600
		pos4++;
		delay_ms(1);
	}
	while (pos5<=400)
	{
		TIM4->CCR1=2000;
		TIM3->CCR2=2200; 
		pos5++;
		delay_ms(1);
	}
	while (pos6 <200)
	{
		TIM3->CCR3=3100;
		TIM3->CCR4=3000;
		TIM2->CCR2=2530;
		TIM2->CCR1=2500;
		pos6++;
		delay_ms(1);
		position=1;
	}
	if (pos6 >200)
	{
pos1=0;
pos2=0;
pos3=0;
pos4=0;
pos5=0;
pos6=0;
	}
	
}
void MoveForward1(void)
{
	/*STM2
	P4	
TIM2->CCR3=2500;
TIM2->CCR4=2950;
TIM3->CCR1=2600;
	P3
TIM3->CCR2=2200;
TIM3->CCR3=3100;
TIM3->CCR4=3000;
	L4	
TIM4->CCR1=2000;
TIM2->CCR2=2530;
TIM2->CCR1=2500;
	L3
TIM4->CCR2=2300;
TIM4->CCR3=2250;
TIM4->CCR4=2400; */


	if (z1F1<100)
	{
		TIM4->CCR3=2950; //+700
		TIM4->CCR4=3000; //+600
		TIM2->CCR4=2250; //-700
		TIM3->CCR1=2000; //-600
		z1F1++;
		delay_ms(1);
	}
	if (z2F1<=200)
	{
		TIM4->CCR2=2300+z2F1*2.5; //+500
		TIM2->CCR3=2500-z2F1*2.5; //-500
		z2F1++;
		delay_ms(1);
		
		if (z2F1>160 && z3F1<100)
		{
			TIM2->CCR4=2950;
			TIM3->CCR1=2600;
			TIM4->CCR3=2250;
			TIM4->CCR4=2400;
			z3F1++;
			delay_ms(1);
		}
	}
	if(z2F1>200 && z4F1<=200)
	{
		TIM4->CCR2=2800-z4F1*2.5;
		TIM2->CCR3=2000+z4F1*2.5;
		z4F1++;
		status=1;
	}
	if (z4F1 >200)
	{
		z1F1=0;
		z2F1=0;
		z3F1=0;
		z4F1=0;
	}
}
void MoveForward2(void)
{
if (z1F2<100)
	{
		TIM3->CCR3=2400; //-700
    TIM3->CCR4=2400; //-600
		TIM2->CCR2=3230; //+700
		TIM2->CCR1=3100; //+600
		z1F2++;
		delay_ms(1);
	}
	if (z2F2<=200)
	{
		TIM3->CCR2=2200-z2F2*2.5; //-500
		TIM4->CCR1=2000+z2F2*2.5; //+500
		z2F2++;
		delay_ms(1);
		
		if (z2F2>160 && z3F2<100)
		{
			TIM3->CCR3=3100;
			TIM3->CCR4=3000;
			TIM2->CCR2=2530;
			TIM2->CCR1=2500;
			z3F2++;
			delay_ms(1);
		}
	}
	if (z2F2>200 && z4F2<=200)
	{
		TIM3->CCR2=1700+z4F2*2.5;
		TIM4->CCR1=2500-z4F2*2.5;
		z4F2++;
	}
	
	if (z4F2 >200)
	{
		
		z1F2=0;
		z2F2=0;
		z3F2=0;
		z4F2=0;
	}  
}
void MoveBackwards1(void)
{
	if (z1F1<100)
	{
		TIM4->CCR3=2950; //+700
		TIM4->CCR4=3000; //+600
		TIM2->CCR4=2250; //-700
		TIM3->CCR1=2000; //-600
		z1F1++;
		delay_ms(1);
	}
	if (z2F1<=500)
	{
		TIM4->CCR2=2800-z2F1; //-500
		TIM2->CCR3=2000+z2F1; //+500
		z2F1++;
		delay_ms(1);
		
		if (z2F1>400 && z3F1<100)
		{
			TIM2->CCR4=2950;
			TIM3->CCR1=2600;
			TIM4->CCR3=2250;
			TIM4->CCR4=2400;
			z3F1++;
			delay_ms(1);
		}
	}
	if(z2F1>500 && z4F1<=500)
	{
		TIM4->CCR2=2300+z4F1;
		TIM2->CCR3=2500-z4F1;
		z4F1++;
		status=4;
	}
	if (z4F1 >500)
	{
		z1F1=0;
		z2F1=0;
		z3F1=0;
		z4F1=0;
	}
}
void MoveBackwards2(void)
{
if (z1F2<100)
	{
		TIM3->CCR3=2400; //-700
    TIM3->CCR4=2400; //-600
		TIM2->CCR2=3230; //+700
		TIM2->CCR1=3100; //+600
		z1F2++;
		delay_ms(1);
	}
	if (z2F2<=500)
	{
		TIM3->CCR2=1700+z2F2; //+500
		TIM4->CCR1=2500-z2F2; //-500
		z2F2++;
		delay_ms(1);
		
		if (z2F2>400 && z3F2<100)
		{
			TIM3->CCR3=3100;
			TIM3->CCR4=3000;
			TIM2->CCR2=2530;
			TIM2->CCR1=2500;
			z3F2++;
			delay_ms(1);
		}
	}
	if (z2F2>500 && z4F2<=500)
	{
		TIM3->CCR2=2200-z4F2;
		TIM4->CCR1=2000+z4F2;
		z4F2++;
	}
	
	if (z4F2 >500)
	{
		
		z1F2=0;
		z2F2=0;
		z3F2=0;
		z4F2=0;
	}  
}
void TurnLeft1(void)
{
	if (z1F1<100)
	{
		TIM3->CCR3=2400; //-700
		TIM3->CCR4=2400; //-600
		TIM2->CCR2=3230; //+700
		TIM2->CCR1=3100; //+600
		z1F1++;
		delay_ms(1);
	}
	if (z2F1<=200)
	{
		TIM4->CCR1=2000-z2F1*2; //-400
		TIM3->CCR2=2200-z2F1*2; //-400
		z2F1++;
		delay_ms(1);
		
		if (z2F1>150 && z3F1<100)
		{
			TIM2->CCR2=2530;
			TIM2->CCR1=2500;
			TIM3->CCR3=3100;
			TIM3->CCR4=3000;
			z3F1++;
			delay_ms(1);
		}
	}
	if(z2F1>200 && z4F1<=200)
	{
		TIM4->CCR1=1600+z4F1*2;
		TIM3->CCR2=1800+z4F1*2;
		z4F1++;
		status=2;
	}
	if (z4F1 >200)
	{
		z1F1=0;
		z2F1=0;
		z3F1=0;
		z4F1=0;
	}
}
void TurnLeft2(void)
{
	if (z1F2<100)
	{
		TIM2->CCR4=2250; //-700
    TIM3->CCR1=2000; //-600
		TIM4->CCR3=2950; //+700
		TIM4->CCR4=3000; //+600
		z1F2++;
		delay_ms(1);
	}
	if (z2F2<=200)
	{
		TIM2->CCR3=2500-z2F2*2; //-400
		TIM4->CCR2=2300-z2F2*2; //-400
		z2F2++;
		delay_ms(1);
		
		if (z2F2>150 && z3F2<100)
		{
			TIM4->CCR3=2250;
			TIM4->CCR4=2400;
			TIM2->CCR4=2950;
			TIM3->CCR1=2600;
			z3F2++;
			delay_ms(1);
		}
	}
	if (z2F2>200 && z4F2<=200)
	{
		TIM2->CCR3=2100+z4F2*2;
		TIM4->CCR2=1900+z4F2*2;
		z4F2++;
	}
	if (z4F2 >200)
	{
		z1F2=0;
		z2F2=0;
		z3F2=0;
		z4F2=0;
	} 
}
void TurnRight1(void)
{
	if (z1F2<100)
	{
		TIM4->CCR3=2950; //+700
		TIM4->CCR4=3000; //+600
		TIM2->CCR4=2250; //-700
		TIM3->CCR1=2000; //-600
		z1F2++;
		delay_ms(1);
	}
	if (z2F2<=200)
	{
		TIM4->CCR2=2300+z2F2; //+400
		TIM2->CCR3=2500+z2F2; //+400
		z2F2++;
		delay_ms(1);
		
		if (z2F2>150 && z3F2<100)
		{
			TIM4->CCR3=2250;
			TIM4->CCR4=2400;
			TIM2->CCR4=2950;
			TIM3->CCR1=2600;
			z3F2++;
			delay_ms(1);
		}
	}
	if (z2F2>200 && z4F2<=200)
	{
		TIM4->CCR2=2700-z4F2*2;
		TIM2->CCR3=2900-z4F2*2;
		z4F2++;
		status=3;
	}
	if (z4F2 >200)
	{
		z1F2=0;
		z2F2=0;
		z3F2=0;
		z4F2=0;
	} 
}
void TurnRight2(void)
{
	if (z1F1<100)
	{
		TIM3->CCR3=2400; //-700
    TIM3->CCR4=2400; //-600
		TIM2->CCR2=3230; //+700
		TIM2->CCR1=3100; //+600
		z1F1++;
		delay_ms(1);
	}
	if (z2F1<=200)
	{
		TIM4->CCR1=2000+z2F1*2; //+400
		TIM3->CCR2=2200+z2F1*2; //+400
		z2F1++;
		delay_ms(1);
		
		if (z2F1>150 && z3F1<100)
		{
			TIM3->CCR3=3100;
			TIM3->CCR4=3000;
			TIM2->CCR2=2530;
			TIM2->CCR1=2500;
			z3F1++;
			delay_ms(1);
		}
	}
	if(z2F1>200 && z4F1<=200)
	{
		TIM4->CCR1=2400-z4F1*2;
		TIM3->CCR2=2600-z4F1*2;
		z4F1++;
	}
	if (z4F1 >200)
	{
		z1F1=0;
		z2F1=0;
		z3F1=0;
		z4F1=0;
	}
}
void ResetPosition(void)
{
TIM2->CCR3=2500;
TIM2->CCR4=2950;
TIM3->CCR1=2600;

TIM3->CCR2=2200;
TIM3->CCR3=3100;
TIM3->CCR4=3000;

TIM4->CCR1=2000;
TIM2->CCR2=2530;
TIM2->CCR1=2500;

TIM4->CCR2=2300;
TIM4->CCR3=2250;
TIM4->CCR4=2400;
		z1F1=0;
		z2F1=0;
		z3F1=0;
		z4F1=0;
		z1F2=0;
		z2F2=0;
		z3F2=0;
		z4F2=0;
}
void ResetPositionB(void)
{
	
TIM2->CCR3=2000;
TIM2->CCR4=2950;
TIM3->CCR1=2600;

TIM3->CCR2=1700;
TIM3->CCR3=3100;
TIM3->CCR4=3000;

TIM4->CCR1=2500;
TIM2->CCR2=2530;
TIM2->CCR1=2500;

TIM4->CCR2=2800;
TIM4->CCR3=2250;
TIM4->CCR4=2400;
		z1F1=0;
		z2F1=0;
		z3F1=0;
		z4F1=0;
		z1F2=0;
		z2F2=0;
		z3F2=0;
		z4F2=0;
}
void Algorythm_one(void)// set spider to walk in faster way
{
			if (set==1)
		{
			if (position!=0)
			{
			ResetPosition();
			delay_ms(250);
			position=0;
			}
			MoveForward1();
			if (status==1)
			MoveForward2();
		}
		if (set==2)
		{
			if (position==2)
			{
			ResetPositionB();
			delay_ms(250);
			position=0;
			}
			MoveBackwards1();
			if (status==4)
			MoveBackwards2();
		}
		if (set==3)
		{
			if (position==3)
			{
			ResetPosition();
			delay_ms(250);
			position=0;
			}
			TurnRight1();
			if (status==3)
			TurnRight2();
		}
		if (set==4)
		{
			if (position==4)
			{
			ResetPosition();
			delay_ms(250);
			position=0;
			}
			TurnLeft1();
			if (status==2)
			TurnLeft2();
		}
		if (set==5)
		{
			ResetPosition();
			delay_ms(250);
			position=0;
		}
}
void ResetPosition_2 (void)
{
TIM4->CCR2=2800;
TIM4->CCR3=2250;
TIM4->CCR4=2400; 
//L4
TIM4->CCR1=2000;
TIM2->CCR2=2530;
TIM2->CCR1=2500;
//P3
TIM3->CCR2=2034;
TIM3->CCR3=3100;
TIM3->CCR4=3000;
//P4
TIM2->CCR3=2167;
TIM2->CCR4=2950;
TIM3->CCR1=2600;
		z1F1=0;
		z2F1=0;
		z3F1=0;
		z4F1=0;
		z1F2=0;
		z2F2=0;
		z3F2=0;
		z4F2=0;
}
void StartPosition_2 (void)
{
	while (pos1 <200)
	{
		TIM2->CCR4=3200; //+700
		TIM3->CCR1=3000; //+600
		TIM4->CCR2=2280; //-700
		TIM4->CCR3=2200; //-600
		pos1++;
		delay_ms(1);
	}
	while (pos2<=400)
	{
		TIM2->CCR3=3050; 
		TIM4->CCR1=2150; 
		pos2++;
		delay_ms(1);
	}
	while (pos3 <200)
	{
		TIM2->CCR4=2500;
		TIM3->CCR1=2400;
		TIM4->CCR2=2980;
		TIM4->CCR3=2800;
		pos3++;
		delay_ms(1);
	}
	 while (pos4 <200)
	{
		TIM2->CCR2=2500; //-700
    TIM2->CCR1=2200; //-600
		TIM3->CCR3=3050; //+700
		TIM3->CCR4=3000; //+600
		pos4++;
		delay_ms(1);
	}
	while (pos5<=400)
	{
		TIM4->CCR4=2800; 
		TIM3->CCR2=3225; 
		pos5++;
		delay_ms(1);
	}
	while (pos6 <200)
	{
		TIM2->CCR2=3200;
		TIM2->CCR1=2800;
		TIM3->CCR3=2350;
		TIM3->CCR4=2400;
		pos6++;
		delay_ms(1);
		position=1;	
	}
	if (pos6 >200)
	{
pos1=0;
pos2=0;
pos3=0;
pos4=0;
pos5=0;
pos6=0;
	}	
}

void abc (void)
{	/*STM2
	P4	
TIM2->CCR3=2500;
TIM2->CCR4=2950;
TIM3->CCR1=2600;
	P3
TIM3->CCR2=2200;
TIM3->CCR3=3100;
TIM3->CCR4=3000;
	L4	
TIM4->CCR1=2000;
TIM2->CCR2=2530;
TIM2->CCR1=2500;
	L3
TIM4->CCR2=2300;
TIM4->CCR3=2250;
TIM4->CCR4=2400; */
		if (z1F1<100)
	{
		z1F4=0;
		z2F4=0;				
		z3F4=0;
		z4F4=0;
		TIM2->CCR2=3230; //+700
		TIM2->CCR1=2000; //-500
		z1F1++;
		delay_ms(1);
	}
		if (z2F1<=200)
	{
		TIM4->CCR1=2000+z2F1*2.5; //+500
		TIM2->CCR3=2167+z2F1/1.2;
		TIM3->CCR2=2034+z2F1/1.2;
		TIM4->CCR2=2800-z2F1/1.2;
		z2F1++;
		delay_ms(1);
		
		if (z2F1>160 && z3F1<100)
		{
		TIM2->CCR2=2530; //-700
		TIM2->CCR1=2500; //+500
		z3F1++;
		delay_ms(1);
		}
		if (z2F1>200 && z4F1 <=201)
		{
			z4F1++;
			status1=1;
		}
	 }
}
void abc2(void)
{
	//Noga2
	if (z1F2<100)
	{
		z1F1=0;
		z2F1=0;
		z3F1=0;
		z4F1=0;
		TIM3->CCR3=2400; //-700
		TIM3->CCR4=3500; //+500
		z1F2++;
		delay_ms(1);
	}
	if (z2F2<=200)
	{
		TIM3->CCR2=2200-z2F2*2.5; //-600
		TIM2->CCR3=2334+z2F2/1.2;
		TIM4->CCR2=2633-z2F2/1.2;
		TIM4->CCR1=2500-z2F2/1.2;
		z2F2++;
		delay_ms(1);
		
		if (z2F2>160 && z3F2<100)
		{
		TIM3->CCR3=3100; //+700
		TIM3->CCR4=3000; //-500
		z3F2++;
		delay_ms(1);
		}
	 }
	if (z2F2>200 && z4F2<=201)
	{
		z4F2++;
		status1=2;
	}
}
void abc3 (void)
{
   //Noga3
	if (z1F3<=100)
	{
		z1F2=0;
		z2F2=0;
		z3F2=0;
		z4F2=0;
		TIM2->CCR4=2250; //-700
		TIM3->CCR1=3100; //+500
		z1F3++;
		delay_ms(1);
	}
	if (z2F3<=200)
	{
		TIM2->CCR3=2500-z2F3*2.5; //+500
		TIM3->CCR2=1700+z2F3/1.2;
		TIM4->CCR2=2633-z2F3/1.2;
		TIM4->CCR1=2333-z2F3/1.2;
		z2F3++;
		delay_ms(1);
		
		if (z2F3>160 && z3F3<100)
		{
		TIM2->CCR4=2950; //+700
		TIM3->CCR1=2600; //-500
		z3F3++;
		delay_ms(1);
		}
	 }
	if (z2F3>200 && z4F3<=201)
	{
		z4F3++;
		status1=3;
	}
}
void abc4 (void)
{	 
	 //Noga4
	 if (z1F4<100)
	{
		z1F3=0;
		z2F3=0;						
		z3F3=0;
		z4F3=0;
		TIM4->CCR3=2950; //+700
		TIM4->CCR4=1900; //-500
		z1F4++;
		delay_ms(1);
	}
	if (z2F4<=200)
	{
		TIM4->CCR2=2300+z2F4*2.5; //-500
		TIM3->CCR2=1867+z2F4/1.2;
		TIM2->CCR3=2000+z2F4/1.2;
		TIM4->CCR1=2167-z2F4/1.2;
		z2F4++;
		delay_ms(1);
		
		if (z2F4>160 && z3F4<100)
		{
		TIM4->CCR3=2250; //-700
		TIM4->CCR4=2400; //+500
		z3F4++;
			delay_ms(1);
		}
	 }
	if(z2F4>200 && z4F4<=201)
	{
		z4F4++;
		status1=0;
	}	
}
void Algorytm_two (void) // set spider to walk in slower but more precise way
{
		if (set==1)
		{
			if (position!=0)
			{
			ResetPosition_2();
			delay_ms(250);
			position=0;
			}
		if (status1==0)
		abc();
		if (status1==1)
		abc2();
		if (status1==2)
		abc3();
		if (status1==3)
		abc4();
		}
		if (set==2)
		{
			if (position==2)
			{
			ResetPositionB();
			delay_ms(250);
			position=0;
			}
			MoveBackwards1();
			if (status==4)
			MoveBackwards2();
		}
		if (set==3)
		{
			if (position==3)
			{
			ResetPosition();
			delay_ms(250);
			position=0;
			}
			TurnRight1();
			if (status==3)
			TurnRight2();
		}
		if (set==4)
		{
			if (position==4)
			{
			ResetPosition();
			delay_ms(250);
			position=0;
			}
			TurnLeft1();
			if (status==2)
			TurnLeft2();
		}
		if (set==5)
		{
			ResetPosition();
			delay_ms(250);
			position=0;
		}
}
