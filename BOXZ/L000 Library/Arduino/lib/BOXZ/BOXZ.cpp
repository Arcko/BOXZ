/*
BOXZ.h - Library for general robot control.
Created by Leo.Zhu, 21 July, 2013.
https://github.com/leolite/BOXZ

License: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
http://creativecommons.org/licenses/by-nc-sa/3.0/
*/

/*******************************************************************************/
#include "BOXZ.h"

//I/O check
boolean BOXZ::checkIO_ED()
{
  int startPin = 8;
  int endPin = 13;
  boolean value[]={0,1,1,0,0,0};
  boolean check[]={0,0,0,0,0,0};
  int result = 1;
  for(int i=startPin;i<=endPin;i++){
    pinMode(i, OUTPUT);  
    digitalWrite(i,1);
    pinMode(i, INPUT);
    check[i-startPin] = digitalRead(i);
    if(check[i-startPin] != value[i-startPin]){
      if(DEBUG ==1){
        Serial.println("ERROR: It's not Seeed Motor Shield V2.0"); 
      }
      result = 0;
	  return result;
//      break;
    }
    if((result = 1)&&(DEBUG == 1)){
      Serial.println("INFO: Driver board checked done! Type: Seeed Motor Shield V2.0"); 
    }
    return result;
  }
}

boolean BOXZ::checkIO_DF()
{
  int startPin = 4;
  int endPin = 7;
  boolean value[]={0,0,0,0};
  boolean check[]={0,0,0,0};
  int result = 1;
  for(int i=startPin;i<=endPin;i++){
    pinMode(i, OUTPUT);  
    digitalWrite(i,1);
    pinMode(i, INPUT);
    check[i-startPin] = digitalRead(i);
    if(check[i-startPin] != value[i-startPin]){
      if(DEBUG ==1){
        Serial.println("ERROR: It's not DFRobot L298 or L293 Shield"); 
      }
      result = 0;
	  return result;
//      break;
    }
    if((result = 1)&&(DEBUG == 1)){
      Serial.println("INFO: Driver board checked done! Type: DFRobot L298 or L293 Shield"); 
    }
    return result;
  }
}


//initialization
//DFRobot 4,7,5,6
void BOXZ::init(int inA, int inB, int pwmA, int pwmB)
{
	pinMode(inA,OUTPUT);
	pinMode(inB,OUTPUT);
	pinMode(pwmA,OUTPUT);
	pinMode(pwmB,OUTPUT);
	_inA = inA;
	_inB = inB;
	_pwmA = pwmA;
	_pwmB = pwmB;
	_driverMode = 4;
	stop();
}

void BOXZ::init(int in1, int in2, int in3, int in4, int pwmA, int pwmB)
{
	pinMode(in1,OUTPUT);
	pinMode(in2,OUTPUT);
	pinMode(in3,OUTPUT);
	pinMode(in4,OUTPUT);
	pinMode(pwmA,OUTPUT);
	pinMode(pwmB,OUTPUT);
	_in1 = in1;
	_in2 = in2;
	_in3 = in3;
	_in4 = in4;
	_pwmA = pwmA;
	_pwmB = pwmB;
	_driverMode = 6;
	stop();
}

boolean BOXZ::init()
{
    if(checkIO_DF() == 1){
      init(DF_INA,DF_INB,DF_SPEEDA,DF_SPEEDB);
	  return true;
    }else if(checkIO_ED() == 1){
      init(SD_IN1,SD_IN2,SD_IN3,SD_IN4,SD_SPEEDA,SD_SPEEDB);
	  return true;
    }else{
	return false;
	}
}



boolean BOXZ::init(int type)
{
  if(type ==0xDF){
    //checking I/O
    if(checkIO_DF() == 1){
      //Define I/O
      init(DF_INA,DF_INB,DF_SPEEDA,DF_SPEEDB);
      //Output
//      if(DEBUG ==1){
//       Serial.println("INFO: DFRobot L298N shield configured done!");
//      }
      return true;
    }
    else{
      if(DEBUG ==1){
        Serial.println("ERROR:Unknown type driver board");
      }
      return false;
    }
  }
  else if(type ==0xED){
    //checking I/O
    if(checkIO_ED() == 1){
      //Define I/O
      init(SD_IN1,SD_IN2,SD_IN3,SD_IN4,SD_SPEEDA,SD_SPEEDB);
      //Output
//      if(DEBUG ==1){
//        Serial.println("INFO: Seeed L298N shield configured done");
//      }
      return true;
    }
    else{
      if(DEBUG ==1){
        Serial.println("ERROR:Unknown type driver board");
      }
      return false;
    }
  }
  else{
    if(DEBUG ==1){
      Serial.println("ERROR:Unknown type driver board");
    }
    return false;
  }
}

/*************************************************************/


void BOXZ::goForward()
{
if(_driverMode == 4){
	digitalWrite(_inA,HIGH);
    digitalWrite(_inB,HIGH);
	analogWrite(_pwmA,DEFAULT_SPEED);
	analogWrite(_pwmB,DEFAULT_SPEED);
	if(DEBUG == 1) Serial.println("FORWARD");
}else if(_driverMode == 6){
	digitalWrite(_in1,HIGH);
    digitalWrite(_in2,LOW);
	digitalWrite(_in3,LOW);
    digitalWrite(_in4,HIGH);
	analogWrite(_pwmA,DEFAULT_SPEED);
	analogWrite(_pwmB,DEFAULT_SPEED);
	if(DEBUG == 1) Serial.println("FORWARD");
	}else{
	if(DEBUG == 1) Serial.println("ERROR:UNKNOWN MODE");
	}	
}

void BOXZ::goBackward()
{
if(_driverMode == 4){
	digitalWrite(_inA,LOW);
    digitalWrite(_inB,LOW);
	analogWrite(_pwmA,DEFAULT_SPEED);
	analogWrite(_pwmB,DEFAULT_SPEED);
	if(DEBUG == 1) Serial.println("BACKWARD");
}else if(_driverMode == 6){
	digitalWrite(_in1,LOW);
    digitalWrite(_in2,HIGH);
	digitalWrite(_in3,HIGH);
    digitalWrite(_in4,LOW);
	analogWrite(_pwmA,DEFAULT_SPEED);
	analogWrite(_pwmB,DEFAULT_SPEED);
	if(DEBUG == 1) Serial.println("BACKWARD");
	}else{
	if(DEBUG == 1) Serial.println("ERROR:UNKNOWN MODE");
	}	
}

void BOXZ::goLeft()
{
if(_driverMode == 4){
	digitalWrite(_inA,HIGH);
    digitalWrite(_inB,LOW);
	analogWrite(_pwmA,DEFAULT_SPEED);
	analogWrite(_pwmB,DEFAULT_SPEED);
	if(DEBUG == 1) Serial.println("LEFT");
}else if(_driverMode == 6){
	digitalWrite(_in1,HIGH);
    digitalWrite(_in2,LOW);
	digitalWrite(_in3,HIGH);
    digitalWrite(_in4,LOW);
	analogWrite(_pwmA,DEFAULT_SPEED);
	analogWrite(_pwmB,DEFAULT_SPEED);
	if(DEBUG == 1) Serial.println("LEFT");
	}else{
	if(DEBUG == 1) Serial.println("ERROR:UNKNOWN MODE");
	}	
}

void BOXZ::goRight()
{
if(_driverMode == 4){
	digitalWrite(_inA,LOW);
    digitalWrite(_inB,HIGH);
	analogWrite(_pwmA,DEFAULT_SPEED);
	analogWrite(_pwmB,DEFAULT_SPEED);
	if(DEBUG == 1) Serial.println("LEFT");
}else if(_driverMode == 6){
	digitalWrite(_in1,LOW);
    digitalWrite(_in2,HIGH);
	digitalWrite(_in3,LOW);
    digitalWrite(_in4,HIGH);
	analogWrite(_pwmA,DEFAULT_SPEED);
	analogWrite(_pwmB,DEFAULT_SPEED);
	if(DEBUG == 1) Serial.println("LEFT");
	}else{
	if(DEBUG == 1) Serial.println("ERROR:UNKNOWN MODE");
	}	
}

/**********************SPEED Control******************************/
void BOXZ::goForward(int speedA, int speedB)
{
if(_driverMode == 4){
	digitalWrite(_inA,HIGH);
    digitalWrite(_inB,HIGH);
	analogWrite(_pwmA,speedA);
	analogWrite(_pwmB,speedB);
	if(DEBUG == 1) {
    Serial.print(speedA);
    Serial.print(",");
    Serial.print(speedB);
    Serial.println(",FORWARD");
  }
}else if(_driverMode == 6){
	digitalWrite(_in1,HIGH);
    digitalWrite(_in2,LOW);
	digitalWrite(_in3,LOW);
    digitalWrite(_in4,HIGH);
	analogWrite(_pwmA,speedA);
	analogWrite(_pwmB,speedB);
	if(DEBUG == 1) {
    Serial.print(speedA);
    Serial.print(",");
    Serial.print(speedB);
    Serial.println(",FORWARD");
  }
}else{
	if(DEBUG == 1) Serial.println("ERROR:UNKNOWN MODE");
	}	
}


void BOXZ::goBackward(int speedA, int speedB)
{
if(_driverMode == 4){
	digitalWrite(_inA,LOW);
    digitalWrite(_inB,LOW);
	analogWrite(_pwmA,speedA);
	analogWrite(_pwmB,speedB);
	if(DEBUG == 1)   {
    Serial.print(speedA);
    Serial.print(",");
    Serial.print(speedB);
    Serial.println(",BACKWARD");
  }
}else if(_driverMode == 6){
	digitalWrite(_in1,LOW);
    digitalWrite(_in2,HIGH);
	digitalWrite(_in3,HIGH);
    digitalWrite(_in4,LOW);
	analogWrite(_pwmA,speedA);
	analogWrite(_pwmB,speedB);
	if(DEBUG == 1)   {
    Serial.print(speedA);
    Serial.print(",");
    Serial.print(speedB);
    Serial.println(",BACKWARD");
  }
}else{
	if(DEBUG == 1) Serial.println("ERROR:UNKNOWN MODE");
	}	
}

void BOXZ::goLeft(int speedA, int speedB)
{
if(_driverMode == 4){
	digitalWrite(_inA,HIGH);
    digitalWrite(_inB,LOW);
	analogWrite(_pwmA,speedA);
	analogWrite(_pwmB,speedB);
	if(DEBUG == 1) {
    Serial.print(speedA);
    Serial.print(",");
    Serial.print(speedB);
    Serial.println(",LEFT");
  }
}else if(_driverMode == 6){
	digitalWrite(_in1,HIGH);
    digitalWrite(_in2,LOW);
	digitalWrite(_in3,HIGH);
    digitalWrite(_in4,LOW);
	analogWrite(_pwmA,speedA);
	analogWrite(_pwmB,speedB);
	if(DEBUG == 1) {
    Serial.print(speedA);
    Serial.print(",");
    Serial.print(speedB);
    Serial.println(",LEFT");
  }
}else{
	if(DEBUG == 1) Serial.println("ERROR:UNKNOWN MODE");
	}	
}

void BOXZ::goRight(int speedA, int speedB)
{
if(_driverMode == 4){
	digitalWrite(_inA,LOW);
    digitalWrite(_inB,HIGH);
	analogWrite(_pwmA,speedA);
	analogWrite(_pwmB,speedB);
	if(DEBUG == 1) {
    Serial.print(speedA);
    Serial.print(",");
    Serial.print(speedB);
    Serial.println(",RIGHT");
  }
}else if(_driverMode == 6){
	digitalWrite(_in1,LOW);
    digitalWrite(_in2,HIGH);
	digitalWrite(_in3,LOW);
    digitalWrite(_in4,HIGH);
	analogWrite(_pwmA,speedA);
	analogWrite(_pwmB,speedB);
	if(DEBUG == 1) {
    Serial.print(speedA);
    Serial.print(",");
    Serial.print(speedB);
    Serial.println(",RIGHT");
  }
}else{
	if(DEBUG == 1) Serial.println("ERROR:UNKNOWN MODE");
	}	
}

void BOXZ::stop()
{
if(_driverMode == 4){
	/*Unenble the pin, to stop the motor. */
	digitalWrite(_pwmA,LOW);
    digitalWrite(_pwmB,LOW);
}else if(_driverMode == 6){
	digitalWrite(_in1,HIGH);
    digitalWrite(_in2,HIGH);
	digitalWrite(_in3,HIGH);
    digitalWrite(_in4,HIGH);
	digitalWrite(_pwmA,LOW);
    digitalWrite(_pwmB,LOW);
}else{
	if(DEBUG == 1) Serial.println("ERROR:UNKNOWN MODE");
	}	
//	if(DEBUG == 1) Serial.println("STOP");
}

/*goRaw() mode
You can control you motor with raw data(Long int HEX), The format is b0101|0xFF|0xFF
Here is a sample how to control 4 pin or 6 pin driver board, also if you known the sequence you can control other kinds of driver board
If you want to goForward in 4 pin mode, you should send "262143", or "0x3FFFF"
Byte 1(High): Control bit
Byte 2-3: SpeedA from 0x00 to 0xFF
Byte 4-5(Low): SpeedB  from 0x00 to 0xFF
goForward
4P: 0x3FFFF = 262143
6P: 0x9FFFF = 655359
goBackward
4P: 0x0FFFF = 65535
6P: 0x6FFFF = 458751
goLeft
4P: 0x2FFFF = 196607
6P: 0xAFFFF = 720895
goRight
4P: 0x1FFFF = 131071
6P: 0x5FFFF = 393215
*/

void BOXZ::goRaw(unsigned long data)
{
  //Data convert
  int controlByte;
  //Right speed
  _speedA = data & 0x000000FF;
  //Left speed
  data= data >> 8;
  _speedB = data & 0x000000FF;
  //Control bit
  data= data >> 8;
  controlByte = data & 0x000000FF;
  _in4Status = data & 0x00000001;
  data= data >> 1;
  _in3Status = data & 0x00000001;
  data= data >> 1;
  _in2Status = data & 0x00000001;
  data= data >> 1;
  _in1Status = data & 0x00000001;
  //Output
  if(_driverMode == 4){
    digitalWrite(_inA,_in3Status);
    digitalWrite(_inB,_in4Status);
    analogWrite(_pwmA,_speedA);
    analogWrite(_pwmB,_speedB);
  }
  else if(_driverMode == 6){
    digitalWrite(_in1,_in1Status);
    digitalWrite(_in2,_in2Status);
    digitalWrite(_in3,_in3Status);
    digitalWrite(_in4,_in4Status);
    analogWrite(_pwmA,_speedA);
    analogWrite(_pwmB,_speedB);
  }
  //DEBUG MODE
  if(DEBUG == 1) {
    Serial.println("----Control byte------");
    Serial.println(_speedA,HEX);
    Serial.println(_speedB,HEX);
    Serial.println(controlByte,HEX);
    Serial.println("----Control bit------");
    Serial.println(int(_in1Status),HEX);
    Serial.println(int(_in2Status),HEX);
    Serial.println(int(_in3Status),HEX);
    Serial.println(int(_in4Status),HEX);
    Serial.println("----END------");
  }
}

/*goRaws() mode
You can control you motor with raw data(String HEX). The format is b0101|0xFF|0xFF
Input value is a string.
If you want to goForward in 4 pin mode, you should send "3FFFF", not "0x3FFFF"
*/
void BOXZ::goRaws(String datas)
{
  int rawLength = 5; 			//valid length of string
  unsigned long datain =0;		//data input 0xFFFFF
  unsigned long power =1; 		//power of 16 such as 16^0, 16^1, 16^2...
  int datasl = datas.length(); 	//Data string length

  //String HEX to Long HEX
    if (datasl >0 && datasl <= rawLength)
  {
    for(int n=datasl-1;n>=0;n--){
      switch(datas.charAt(n)){
      case '0':
        datain += 0*power;
        break;
      case '1':
        datain += 1*power;
        break;
      case '2':
        datain += 2*power;
        break;
      case '3':
        datain += 3*power;
        break;
      case '4':
        datain += 4*power;
        break;
      case '5':
        datain += 5*power;
        break;
      case '6':
        datain += 6*power;
        break;
      case '7':
        datain += 7*power;
        break;
      case '8':
        datain += 8*power;
        break;
      case '9':
        datain += 9*power;
        break;
      case 'A':
        datain += 10*power;
        break;
      case 'B':
        datain += 11*power;
        break;
      case 'C':
        datain += 12*power;
        break;
      case 'D':
        datain += 13*power;
        break;
      case 'E':
        datain += 14*power;
        break;
      case 'F':
        datain += 15*power;
        break;
      default: 
        datain += 0;
      }
      power *= 16;
    }
	//DEBUG MODE
    if(datain == 0&&DEBUG == 1){
      Serial.print("ERROR: Unknown format: ");
      Serial.println(datas);
    }
	//action
    boxz.goRaw(datain);
  }
  else if (datasl >rawLength && DEBUG == 1){
    Serial.print("ERROR: Unknown format: ");
    Serial.println(datas);
  }
}

BOXZ boxz;