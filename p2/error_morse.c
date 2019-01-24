#include <string.h>
#include <stdio.h>
#include <util/crc16.h>
#include "error_morse.h"

/* ################## aux ############## */


check byte2hex(uint8_t sum){
	uint8_t mask1=0x0F;
  uint8_t mask2=0xF0;
  check x;
  
  x.L=mask1 & ~sum;
  x.H=mask2 & ~sum;
  x.H=x.H >> 4;
  
  if ((x.L <= 0xF) && (x.L >=0xA))
	  x.L+='A'-10;
  else if ((x.L <= 0x9) && (x.L >=0x0))
	  x.L+='0';
  
  if ((x.H <= 0xF) && (x.H >= 0xA))
	  x.H+='A'-10;
  else if ((x.H <= 0x9) && (x.H >=0x0))
	  x.H+='0';
  return x;	
}

uint8_t hex2byte(check x){
  if( (x.L <= 'F') && (x.L >= 'A')){
	  x.L-='A';}
  else if( (x.L <= '9') && (x.L >='0')){
	  x.L-='0';}
  if ((x.H <= 'F') && (x.H >= 'A')){
	  x.H-='A';}
  else if ((x.H <= '9') && (x.H >='0')){
	  x.H-='0';}
  return x.L+(x.H<<4);
  }
/* ################## get redun ############## */

check get_redun(uint8_t string[]){
  int i;
  check x;
  for(i=0;string[i]!='\0';i++);
  x.H=string[i-1];
  x.L=string[i-2];
  string[i-2]='\0';
  return x;
}


/* ########## checksum ########## */

check add_check(uint8_t string[]){
  uint8_t sum=0;
  int c;
  check x;
  for(c=0; string[c]!='\0'; c++)
	sum+=string[c];
  x=byte2hex(sum);
  string[c]=x.L;
  string[c+1]=x.H;
  string[c+2]='\0';
  return x;
}



bool check_is_ok(uint8_t string[]){
  int a,b;
  a=hex2byte(get_redun(string));
  b=hex2byte(add_check(string));
  get_redun(string);
  return a==b;
}


/* ########## crc ########## */

check add_crc(uint8_t string[]){
  uint8_t crc=0;
  int c;
  check x;
  for(c=0;string[c]!='\0';c++)
	crc=_crc_ibutton_update(crc,string[c]);
  x=byte2hex(crc);
  string[c]=x.L;
  string[c+1]=x.H;
  string[c+2]='\0';
  return x;
}

bool crc_is_ok(uint8_t string[]){
  int a,b;
  a=hex2byte(get_redun(string));
  b=hex2byte(add_crc(string));
  get_redun(string);
  return a==b;
}





