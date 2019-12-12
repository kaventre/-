/****************************************************************************************************
��ƽ    ̨������K66FX���ܳ�VCĸ��
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2019��04��12��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR8.2
��Target  ��K66FX1M0VLQ18
��Crystal �� 50.000Mhz
��busclock�� 40.000MHz
��pllclock��200.000MHz
-------------------------------------------------------------
LED             ��Ƭ���ӿ�
LED0            PTE26
LED1            PTA17
LED2            PTC0
LED3            PTD15
=============================================================
-------------------------------------------------------------
����            ��Ƭ���ӿ�
K0              PTB20
K1              PTB21
K2              PTB22
-------------------------------------------------------------
-------------------------------------------------------------
OLED/TFT1.8ģ�� ��Ƭ���ӿ�
VCC             3.3V
GND             GND
SCK             PTC16
SDA             PTC15
RST             PTC14
DC              PTC13
CS              PTC12                        
-------------------------------------------------------------
******************************************************************************************************/

#include "include.h" 
 double batv,batv1,batv6,batv7;
int i;
typedef struct PID
    {
      double SetPoint;
      long SumError;
      double Proportion;
      double Integral;
      double Derivative;
      double LastError;
      double PreError;
    }PID;
    static PID sPID;
    static PID *sptr=&sPID;
    void IncPIDInit(void)
    {  //NextPoint=Ad_Value();
      sptr->SumError=0;
      sptr->LastError=0;//-1sptr->PreError=0;//-2
      sptr->Proportion=40;
      sptr->Integral=0;
      sptr->Derivative=11;
      sptr->SetPoint=0;
    }
   double IncPIDCalc(double NextPoint)
    { 
      register double iError,iIncpid;
      iError=sptr->SetPoint-NextPoint;
      iIncpid=sptr->Proportion*iError
		  +sptr->Integral*sptr->LastError
		  +sptr->Derivative*sptr->PreError;
      
      sptr->PreError=sptr->LastError;
      sptr->LastError=iError;
     
      return iIncpid;
    }
    

//������

    void main(void)
{   
	PLL_Init(PLL180);         //��ʼ��PLLΪ180M 
	
	/* �����ж����ȼ���  0: 0����ռ���ȼ�16λ�������ȼ� 
	* 1: 2����ռ���ȼ� 8�������ȼ� 2: 4����ռ���ȼ� 4�������ȼ� 
	* 3: 8����ռ���ȼ� 2�������ȼ� 4: 16����ռ���ȼ� 0�������ȼ�
	*/
	/* �������ȼ��� 2: 4����ռ���ȼ� 4�������ȼ� */
    NVIC_SetPriorityGrouping(0x07 - 2);     

	
//------------------------------------------------------------------------------------------------    
//���Ե��  ��������˵ĵ�����߲������� ���������ĵ������һ�¿����޸ĳ�����߸ı�PWM�ź���
//PTC1��PTC2һ�����һ�����  PTC3��PTC4һ�����һ�����
//------------------------------------------------------------------------------------------------    
    IncPIDInit();
   
    ADC_Init(ADC0);
    ADC_Init(ADC1);
   
//M_Motor();

    while(1)
    {
        /* ��ȡ ADCͨ��ֵ */
         
        batv1=-Ad_Value();
        batv6=ADC_Get(6);
        batv7=ADC_Get(7);
        batv=batv6-batv7;
        
       duoji_FTMSD5(batv1);
    
    
       if(-6<batv1<6)
       {
     
       G_Motor();
       delayms(50);
       }
       else
       {
         M_Motor();
         delayms(100);
       }
      
      
    
         
}
        
}

