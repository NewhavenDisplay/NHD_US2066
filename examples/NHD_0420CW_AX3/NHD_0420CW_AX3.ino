//---------------------------------------------------------
/*

NHD_0420CW_AX3.ino

Program for writing to Newhaven Display Slim OLEDs based on US2066 controller.

Pick one up today in the Newhaven Display shop!
------> http://www.newhavendisplay.com/oled-slim-character-oleds-c-119_825.html

This code is written for the Arduino Mega.

Copyright (c) 2015 - Newhaven Display International, Inc.

Newhaven Display invests time and resources providing this open source code,
please support Newhaven Display by purchasing products from Newhaven Display!

*/
//---------------------------------------------------------

#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include <avr\io.h>

#include "NHD_US2066.h"
unsigned char text1[] = {"   Please Support   "};
unsigned char text2[] = {"    Open-Source     "};
unsigned char text3[] = {"Hardware & Software!"};
unsigned char text4[] = {"--------------------"};

unsigned char text5[] = {"  Newhaven Display  "};
unsigned char text6[] = {"4x20  Character OLED"};
unsigned char text7[] = {"    Slim  Design    "};


void output()
{
	int i;

        command(0x01);
        delay(2);
        for(i=0;i<20;i++){
          data(text1[i]);
        }
        
        command(0xA0);
        for(i=0;i<20;i++){
          data(text2[i]);
        }
        
        command(0xC0);
        for(i=0;i<20;i++){
          data(text3[i]);
        }
        
        command(0xE0);
        for(i=0;i<20;i++){
          data(text4[i]);
        }
        
        delay(3500);
        
        command(0x01);
        delay(2);
        for(i=0;i<20;i++){
          data(text5[i]);
        }
        
        command(0xA0);
        for(i=0;i<20;i++){
          data(text6[i]);
        }
        
        command(0xC0);
        for(i=0;i<20;i++){
          data(text7[i]);
        }
        
        command(0xE0);
        for(i=0;i<20;i++){
          data(text4[i]);
        }
        
        delay(3500);
}


void blocks()
{
	int i;

        command(0x01);
        delay(2);

        for(i=0;i<20;i++){
          data(0x1F);
        }

        command(0xA0);
        for(i=0;i<20;i++){
          data(0x1F);
        }
}

void setup()
{
init_oled();
}

void loop() 
{  
  while(1)
  {
    output();
    //blocks();
    delay(2000);
  }
}