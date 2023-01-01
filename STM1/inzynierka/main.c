	#include "myfun.h"
 extern volatile int temp;
 extern volatile uint8_t set;
 extern volatile uint8_t status;
 extern volatile uint8_t status1;
 extern volatile uint8_t status2;
 extern volatile uint8_t status3;
 extern volatile uint8_t position;
 extern volatile uint8_t alg;
 
int main()
{
		Led_Conf();
	  Pin_Conf();
	  Timer_Conf();
		USART_Conf();
		SysTick_Config(80000000 / 1000);


	while(1)
	{
	/*	Led_OnOff(0, LedOn);
			delay_ms(2000);//for(int i=0; i<=5000000; i++);
		Led_OnOff(0, LedOff);
			delay_ms(2000);	//for(int i=0; i<=5000000; i++);
	*/
	
	 Start_Position();
	 BluetoothReceive();
	 if (alg==0)
	 {
		 Algorythm_one();
	 }
	 if (alg==1)
	 {
		 Algorytm_two();
	 }

	}
}

