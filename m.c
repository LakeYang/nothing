#include <stc12c5a60s2.H>    
#include <INTRINS.H>    

sbit Beep =  P1^5;
   
unsigned char n=0;
unsigned char code music_tab[] ={   
0x18, 0x30,
0x1C, 0x10,
0x20, 0x40,
0x1C, 0x10,   
0x18, 0x10,
0x20, 0x10,   
0x1C, 0x10, 
0x18, 0x40,   
0x1C, 0x20,
0x20, 0x20,   
0x1C, 0x20,
0x18, 0x20,   
0x20, 0x80,
0xFF, 0x80,
0x20, 0x30,
0x1C, 0x10, 
0x18, 0x20,
0x15, 0x20,
0x1C, 0x20,
0x20, 0x20,
0x26, 0x40,
0x20, 0x20,
0x2B, 0x20,
0x26, 0x20,
0x20, 0x20,
0x30, 0x80,
0xFF, 0x80,  
0x20, 0x20,
0x1C, 0x10,   
0x18, 0x10,
0x20, 0x20,   
0x26, 0x20,
0x2B, 0x20,   
0x30, 0x20,
0x2B, 0x40,   
0x20, 0x20,
0x1C, 0x10,   
0x18, 0x10,
0x20, 0x20,   
0x26, 0x20,
0x2B, 0x20,   
0x30, 0x20,
0x2B, 0x40,   
0x20, 0x30,
0x1C, 0x10,   
0x18, 0x20,
0x15, 0x20,   
0x1C, 0x20,
0x20, 0x20,   
0x26, 0x40,
0x20, 0x20,   
0x2B, 0x20,
0x26, 0x20,   
0x20, 0x20,
0x30, 0x80,   
0x20, 0x30,
0x1C, 0x10,   
0x20, 0x10,
0x1C, 0x10,   
0x20, 0x20,
0x26, 0x20,   
0x2B, 0x20,
0x30, 0x20,   
0x2B, 0x40,
0x20, 0x15,   
0x1F, 0x05,
0x20, 0x10,   
0x1C, 0x10,
0x20, 0x20,   
0x26, 0x20,
0x2B, 0x20,   
0x30, 0x20,
0x2B, 0x40,   
0x20, 0x30,
0x1C, 0x10,   
0x18, 0x20,
0x15, 0x20,   
0x1C, 0x20,
0x20, 0x20,   
0x26, 0x40,
0x20, 0x20,   
0x2B, 0x20,
0x26, 0x20,   
0x20, 0x20,
0x30, 0x30,   
0x20, 0x30,
0x1C, 0x10,   
0x18, 0x40,
0x1C, 0x20,   
0x20, 0x20,
0x26, 0x40,   
0x13, 0x60,
0x18, 0x20,   
0x15, 0x40,
0x13, 0x40,   
0x18, 0x80,
0x00   
};   
 
unsigned char PL(char m)
{
	switch(m)
	{
		case 0x15: P2=0xfe; break;
		case 0x13: P2=0xfd; break;
		case 0x18: P2=0xfb; break;
		case 0x20: P2=0xf7; break;
		case 0x1C: P2=0xef; break;
		case 0x30: P2=0xdf; break;
		case 0x2B: P2=0xbf; break;
		default: P2=0Xff; break;
	}
}
void int0()  interrupt 1  
{
	TH0=0xd8;   
	TL0=0xef;   
	n--;   
}   
   
void delay (unsigned char m)
{   
	unsigned i=3*m;   
	while(--i);   
}   
   
void delayms(unsigned char a) 
{   
	while(--a);
}   
   
void main()   
{ 
	unsigned char p,m;  
	unsigned char i=0;   
	
	TMOD&=0x0f;
	TMOD|=0x01;
	TH0=0xd8;
	TL0=0xef;
	IE=0x82;

	P2=0x00;
	
	while(1)   
	{
		p=music_tab[i];   
		if(p==0x00)       
		{ 
			i=0; 
			delayms(1000); 
			continue;
		}         
		else if(p==0xff)  
		{ 
			i=i+1;
			Beep=0;
			n=music_tab[i++];
			TR0=1;
			while(n!=0)
			{
				delay(100);
			}  
			TR0=0;
			continue;
		} 
		else         
		{
			m=music_tab[i++];
			n=music_tab[i++];
		}    
		PL(m);
		TR0=1;
		while(n!=0)
		{
			Beep=~Beep;
			delay(m);
		}  
		TR0=0;
	}   
}  
