#include "error_morse.h"
#include <string.h>
#include <util/crc16.h>
#include <stdio.h>//Pel joc de proves (borrar al acabar)

#define INICI_CRC 0

 /*####################  Checksum   ###############################*/

check add_check(char p[]){
  uint16_t suma=0,carry,rest;
  
  uint8_t che_bin;
  
  check che_hex;
  int j=0;
  static char s_check[254];
  
  for (uint8_t i=0; p[i]; i++){ // funcio sumadora checksum
    if ((p[i]>='A' && p[i]<='Z') || (p[i]>='0' && p[i]<='9') || (p[i]==' ')){
      suma+=p[i];
      j++;
      
    }
  }
  rest = suma & 0x00FF;
  carry = suma & 0xFF00;
  carry = carry >> 8;
  che_bin = ~(carry + rest); // checksum en binari
  che_hex=byte2hex(che_bin);
  
  p[j] = che_hex.H;
  p[j+1] = che_hex.L;
  p[j+2] = '\0';
  s_check[0]=che_hex.H;
  s_check[1]=che_hex.L;
  
  return che_hex;
}


check get_redun(char p[]){
  int longi=0;
  check ex;
  while(p[longi]!='\0')
    longi++;

  ex.H=p[longi-2];
  ex.L=p[longi-1];
  p[longi-2]='\0';
  return ex;
}


bool check_is_ok(char strche[]){  
  check c1,c2;
  c1 = get_redun(strche);
  c2 = add_check(strche);
  if (c1.H == c2.H && c1.L == c2.L){
    printf("is ok (CHK)\n");
    return true;
   
      }
  else
    printf("NO ok (CHK)\n");
    return false;
}

/*####################  CRC   ###############################*/

check add_crc(char p[]){
  uint8_t  crc=INICI_CRC, j=0;
  check crc_hex;

  while(p[j]!='\0'){
    crc=_crc_ibutton_update(crc,p[j]);
    j++
  }

  if (p[0]!='\0'){
    crc_hrx=byte2hex(crc);
    p[j]=crc_hex.H;
    p[j+1]=crc_hex.L;
    p[j+3]='\0';
  }

  else{
    crc_hex.H='\0';
    crc_hex.L='\0';
  }
  //printf("")
  return crc_hex;
}


bool crc_is_ok(char p[]){
  check c1,c2;

  c1=get_redun(p);
  c2=add_crc(p);
  if (c1.H == c2.H && c1.L == c2.L){
    printf("is ok (CRC)\n");
    return true;
   
  }
  else
    printf("NO ok (CRC)\n");
  return false;
}

/*##############  funcions auxiliars   #############################*/

 static check byte2hex(uint8_t byte){
  check hex;
  uint8_t H=byte>>4;
  uint8_t L=byte & 0b00001111;
  if(H>=0x0A && H<=0x0F)
    H+=55;
  else
    H+=48;

  if(L>=0x0A && L<=0x0F)
    L+=55;
  else
    L+=48;
  hex.H=H;
  hex.L=L;
  return hex;
}


static uint8_t hex2byte(check hex){
  uint8_t maj, men;
  if (hex.H>=0x41 && hex.H<=0x5A)
    hex.H-=55;
  else
    hex.H-=48;

  if (hex.L>=0x41 && hex.L<=0x5A)
    hex.L-=55;
  else
    hex.L-=48;
  //printf("%i L \n",hex.L);

  maj=hex.H<<4;
  men=hex.L & 0b00001111;
  //printf("%i maj | %i men = %i\n",maj,men,maj|men);

  return maj|men;
}

/*#############  main de proves   ############################*/


void main(){
  check hexad;
  //hexad.L=0x0F;
  //hexad.H=0x00;
  //printf("%i\n",hex2byte(hexad)); // prova hex2byte

  //uint8_t byt= 0b01010101;
  //printf("%i\n",hex2byte(byte2hex(byt))); // prova byte2hex
  char p[255]="HOLA";
  //printf("%s 1\n",p);
  //printf("%s 3\n", p);
  add_check(p);
  check_is_ok(p);
}

