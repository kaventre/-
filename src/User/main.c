/****************************************************************************************************
【平    台】龙邱K66FX智能车VC母板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2019年04月12日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR8.2
【Target  】K66FX1M0VLQ18
【Crystal 】 50.000Mhz
【busclock】 40.000MHz
【pllclock】200.000MHz
-------------------------------------------------------------
LED             单片机接口
LED0            PTE26
LED1            PTA17
LED2            PTC0
LED3            PTD15
=============================================================
-------------------------------------------------------------
按键            单片机接口
K0              PTB20
K1              PTB21
K2              PTB22
-------------------------------------------------------------
-------------------------------------------------------------
OLED/TFT1.8模块 单片机接口
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
    

//主函数

    void main(void)
{   
	PLL_Init(PLL180);         //初始化PLL为180M 
	
	/* 设置中断优先级组  0: 0个抢占优先级16位个子优先级 
	* 1: 2个抢占优先级 8个子优先级 2: 4个抢占优先级 4个子优先级 
	* 3: 8个抢占优先级 2个子优先级 4: 16个抢占优先级 0个子优先级
	*/
	/* 配置优先级组 2: 4个抢占优先级 4个子优先级 */
    NVIC_SetPriorityGrouping(0x07 - 2);     

	
//------------------------------------------------------------------------------------------------    
//测试电机  电机驱动端的电机接线不分正负 ，如果和你的电机方向不一致可以修改程序或者改变PWM信号线
//PTC1和PTC2一组控制一个电机  PTC3和PTC4一组控制一个电机
//------------------------------------------------------------------------------------------------    
    IncPIDInit();
   
    ADC_Init(ADC0);
    ADC_Init(ADC1);
   
//M_Motor();

    while(1)
    {
        /* 获取 ADC通道值 */
         
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

