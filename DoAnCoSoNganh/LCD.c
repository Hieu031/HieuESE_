#include<p18f4520.h>
#include<stdio.h>
#include<delays.h>


#pragma config OSC = HS  
#pragma config MCLRE = ON 
#pragma config WDT = OFF

#define Up PORTCbits.RC1
#define Down PORTCbits.RC2
#define S PORTCbits.RC0

#define LCD_DATA PORTD
#define LCD_RS PORTEbits.RE0
#define LCD_RW PORTEbits.RE1
#define	LCD_EN PORTEbits.RE2

char A[50];
int i=0;
int k=30;

void Lcd_configure(void);//KHOI TAO LCD
void Lcd_Write_Command(char command);//GHI LENH
void Lcd_Write_Data(char data);//GHI DATA
void Lcd_Write_String (char *str);

void Lcd_configure (void)
{	
	Lcd_Write_Command(0x03);							
 	Lcd_Write_Command(0x38);	
	Lcd_Write_Command(0x06);
	Lcd_Write_Command(0x0c);		
	Lcd_Write_Command(0x01);
}

void Lcd_Write_Command (char command)
{ 						
   LCD_RS = 0;
   LCD_RW = 0;			
   LCD_EN = 1;			
   LCD_DATA = command;
   LCD_EN = 0;
   Delay10KTCYx(1);				
}

void Lcd_Write_Data (char data)
{ 
	if(data =='\n') 
	{
		Lcd_Write_Command(0xC0);//HANG 2
		Delay10KTCYx(1);
		return;
	}
   LCD_RS = 1;
   LCD_RW = 0;				
   LCD_EN = 1;				
   LCD_DATA = data;
   LCD_EN = 0;				
   Delay10KTCYx(1);				
}

void Lcd_Write_String (char *str)
{
	while(*str) 
	{	
		Lcd_Write_Data(*str);
		str++;
	}	
}

void main()
{
TRISC = 0x07;
TRISA = 0;
TRISD = 0x00;//OUT PUT
TRISE = 0X00;
ADCON1 = 0X0f;
Lcd_configure();

while(1)
	{	if (Up == 0)
			{	while(Up == 0);
				if (k<200) k++;
			}
		if (Down==0)
			{	while(Down == 0);
				if (k>25) k--;
			}
		if( S == 0)
			{
				while(S == 0);
				i++;
			}
		if (i<k){
			Lcd_Write_Command(0X80);//dau dong 1	
			sprintf(&A[0],"So san pham:%d    \nSo sp 1 don:%d      ",i,k);
			Lcd_Write_String(&A[0]);
				}
		if (i>=k){
			Lcd_Write_Command(0X80);//dau dong 1	
			sprintf(&A[0],"Da du sp 1 don\nBat dau don moi");
			Lcd_Write_String(&A[0]);
			Delay10KTCYx(200);
			i=0;
			Lcd_Write_Command(0X80);//dau dong 1	
			sprintf(&A[0],"So san pham:%d     \nSo sp 1 don:%d      ",i,k);
			Lcd_Write_String(&A[0]);
				}		
	}	
}
