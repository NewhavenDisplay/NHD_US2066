#include "NHD_US2066.h"


const char slave2w = 0x3C;  //3C or 78
unsigned char mode = 0; // 0 = 8-bit parallel 6800 mode; 1 = i2c mode; 2 = SPI mode;
unsigned char tx_packet[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void command(unsigned char c)
{
  unsigned char i, temp;
  switch(mode)
  {
    case 0:   digitalWrite(CS, LOW);
              PORTA = c;
              digitalWrite(RS, LOW);
              digitalWrite(E, HIGH);
              delay(1);
              digitalWrite(E, LOW);
              digitalWrite(CS, HIGH);
              break;
   case 1:    tx_packet[0] = 0x00;
              tx_packet[1] = c;
              send_packet(2);
              break;
   case 2:    
              temp = 0xF8;
              for(i=0;i<8;i++)
              {
                digitalWrite(SCLK, LOW);
                if((temp&0x80)>>7==1)
                {
                  digitalWrite(SDIN, HIGH);
                }
                else
                {
                  digitalWrite(SDIN, LOW);
                }
                temp = temp << 1;
                digitalWrite(SCLK, HIGH);
              }
  
              for(i=0;i<4;i++)
              {
                digitalWrite(SCLK, LOW);
                if((c&0x01)==1)
                {
                  digitalWrite(SDIN, HIGH);
                }
                else
                {
                  digitalWrite(SDIN, LOW);
                }
                c = c >> 1;
                digitalWrite(SCLK, HIGH);
              }
              for(i=0;i<4;i++)
              {
                digitalWrite(SCLK, LOW);
                digitalWrite(SDIN, LOW);
                digitalWrite(SCLK, HIGH);
              }
              for(i=0;i<4;i++)
              {
                digitalWrite(SCLK, LOW);
                if((c&0x01)==1)
                {
                  digitalWrite(SDIN, HIGH);
                }
                else
                {
                  digitalWrite(SDIN, LOW);
                }
                c = c >> 1;
                digitalWrite(SCLK, HIGH);
              }
              for(i=0;i<4;i++)
              {
                digitalWrite(SCLK, LOW);
                digitalWrite(SDIN, LOW);
                digitalWrite(SCLK, HIGH);
              }
              break;
  }
  
}
void data(unsigned char d)
{
  unsigned char i, temp;
  switch(mode)
  {
    case 0:   digitalWrite(CS, LOW);
              PORTA = d;
              digitalWrite(RS, HIGH);
              digitalWrite(E, HIGH);
              delay(1);
              digitalWrite(E, LOW);
              digitalWrite(CS, HIGH);
              break;
   case 1:    tx_packet[0] = 0x40;
              tx_packet[1] = d;
              send_packet(2);
              break;
   case 2:    
              temp = 0xFA;
              for(i=0;i<8;i++)
              {
                digitalWrite(SCLK, LOW);
                if((temp&0x80)>>7==1)
                {
                  digitalWrite(SDIN, HIGH);
                }
                else
                {
                  digitalWrite(SDIN, LOW);
                }
                temp = temp << 1;
                digitalWrite(SCLK, HIGH);
              }
  
              for(i=0;i<4;i++)
              {
                digitalWrite(SCLK, LOW);
                if((d&0x01)==1)
                {
                  digitalWrite(SDIN, HIGH);
                }
                else
                {
                  digitalWrite(SDIN, LOW);
                }
                d = d >> 1;
                digitalWrite(SCLK, HIGH);
              }
              for(i=0;i<4;i++)
              {
                digitalWrite(SCLK, LOW);
                digitalWrite(SDIN, LOW);
                digitalWrite(SCLK, HIGH);
              }
              for(i=0;i<4;i++)
              {
                digitalWrite(SCLK, LOW);
                if((d&0x01)==1)
                {
                  digitalWrite(SDIN, HIGH);
                }
                else
                {
                  digitalWrite(SDIN, LOW);
                }
                d = d >> 1;
                digitalWrite(SCLK, HIGH);
              }
              for(i=0;i<4;i++)
              {
                digitalWrite(SCLK, LOW);
                digitalWrite(SDIN, LOW);
                digitalWrite(SCLK, HIGH);
              }
              delay(10);
              break;
  }
  
}

void send_packet(unsigned char x)
{
  unsigned char ix;
  
  Wire.beginTransmission(slave2w);
  for(ix=0;ix<x;ix++)
  {
    Wire.write(tx_packet[ix]);
  }
  Wire.endTransmission();
}

void init_oled()
{
  pinMode(ASCL, OUTPUT);      //set Arduino I2C lines as outputs
  pinMode(ASDA, OUTPUT);      //
  digitalWrite(ASCL, LOW);    //
  digitalWrite(ASDA, LOW);    //
  pinMode(SCLK, OUTPUT);
  pinMode(SDIN, OUTPUT);
  pinMode(SDOUT, INPUT);
  digitalWrite(SCLK, HIGH);
  digitalWrite(SDIN, HIGH);
  DDRA = 0xFF;
  PORTA = 0x00;
  DDRC = 0xFF;
  PORTC = 0x00;
  digitalWrite(RES, HIGH);
  delay(10);
  Wire.begin();
  delay(10);
    //SPI.begin();
    command(0x2A);  //function set (extended command set)
	command(0x71);  //function selection A, disable internal Vdd regualtor
	data(0x00);
	command(0x28);  //function set (fundamental command set)
	command(0x08);  //display off, cursor off, blink off
	command(0x2A);  //function set (extended command set)
	command(0x79);  //OLED command set enabled
	command(0xD5);  //set display clock divide ratio/oscillator frequency
	command(0x70);  //set display clock divide ratio/oscillator frequency
	command(0x78);  //OLED command set disabled
	command(0x09);  //extended function set (4-lines)
    command(0x06);  //COM SEG direction
	command(0x72);  //function selection B, disable internal Vdd regualtor
	data(0x00);     //ROM CGRAM selection
	command(0x2A);  //function set (extended command set)
	command(0x79);  //OLED command set enabled
	command(0xDA);  //set SEG pins hardware configuration
	command(0x10);  //set SEG pins ... NOTE: When using NHD-0216AW-XB3 or NHD_0216MW_XB3 change to (0x00)
	command(0xDC);  //function selection C
	command(0x00);  //function selection C
	command(0x81);  //set contrast control
	command(0x7F);  //set contrast control
	command(0xD9);  //set phase length
	command(0xF1);  //set phase length
	command(0xDB);  //set VCOMH deselect level
	command(0x40);  //set VCOMH deselect level
	command(0x78);  //OLED command set disabled
	command(0x28);  //function set (fundamental command set)
	command(0x01);  //clear display
	command(0x80);  //set DDRAM address to 0x00
	command(0x0C);  //display ON
  delay(100);
  //Wire.begin();
  //delay(10);
}