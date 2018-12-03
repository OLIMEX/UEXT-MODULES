/*
 * IO2.cpp
 * 
 * Copyright 2013 OLIMEX LTD/Stefan Mavrodiev <support@olimex.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
 

#include "IO2.h"
#include "../Wire/Wire.h"



/*
 * Class variables
 */
 uint8_t IO2::address = 0x21;
 uint8_t IO2::relay_status = 0x00;
 uint8_t IO2::tris_status = 0x00;
 uint8_t IO2::lat_status = 0x00;
 uint8_t IO2::pp_status = 0x00;
 
  uint8_t IO2::IN = 1;
  uint8_t IO2::OUT = 0;
  uint8_t IO2::LO = 0;
  uint8_t IO2::HI = 1;
  uint8_t IO2::ON = 1;
  uint8_t IO2::OFF = 0;
	
  uint8_t IO2::RELAY1 = 0x01;
  uint8_t IO2::RELAY2 = 0x02;
	
  uint8_t IO2::GPIO0 = 0x01;
  uint8_t IO2::GPIO1 = 0x02;
  uint8_t IO2::GPIO2 = 0x04;
  uint8_t IO2::GPIO3 = 0x08;
  uint8_t IO2::GPIO4 = 0x10;
  uint8_t IO2::GPIO5 = 0x20;
  uint8_t IO2::GPIO6 = 0x40;
  
  uint8_t IO2::AN0 = 0x10;
  uint8_t IO2::AN1 = 0x11;
  uint8_t IO2::AN2 = 0x12;
  uint8_t IO2::AN3 = 0x13;
  uint8_t IO2::AN5 = 0x15;


/*
 * Constructors
 */
IO2::IO2(){
}

IO2::IO2(uint8_t addr){
    address = addr;
}

void IO2::setRelay(uint8_t relay, uint8_t state){
  if(state == 1)
    relay_status |= relay;
  else if(state == 0)
    relay_status &= ~relay;
  
  
    Wire.begin();
    Wire.beginTransmission(address);
    Wire.write(SET_RELAY);
    Wire.write(relay_status);
    Wire.endTransmission();
}

void IO2::setAddress(uint8_t newAddress){
    Wire.begin();
    Wire.beginTransmission(address);
    Wire.write(SET_ADDRESS);
    Wire.write(newAddress);
    Wire.endTransmission();
}

uint16_t IO2::analogRead(uint8_t pin){
  uint16_t data = 0;
  uint8_t a[2];
  Wire.begin();
  Wire.beginTransmission(address);
  Wire.write(pin);
  Wire.endTransmission();
  Wire.requestFrom((int)address, 2);
  a[0] = Wire.read();
  a[1] = Wire.read();
  
  data = (a[1] << 8) | a[0];
  return data;
}

void IO2::pinMode(uint8_t pin, uint8_t mode){
  if(mode == 1)
    tris_status |= pin;
  else if(mode == 0)
    tris_status &= ~pin;
  
  Wire.begin();
  Wire.beginTransmission(address);
  Wire.write(SET_TRIS);
  Wire.write(tris_status);
  Wire.endTransmission();  
}

void IO2::digitalWrite(uint8_t pin, uint8_t level){
  if(level == 1)
    lat_status |= pin;
  else if(level == 0)
    lat_status &= ~pin;
  
  Wire.begin();
  Wire.beginTransmission(address);
  Wire.write(SET_LAT);
  Wire.write(lat_status);
  Wire.endTransmission();  
}
void IO2::setPullpin(uint8_t pin, uint8_t state){
  if(state == 1)
    pp_status |= pin;
  else if(state == 0)
    pp_status &= ~pin;
  
  Wire.begin();
  Wire.beginTransmission(address);
  Wire.write(SET_LAT);
  Wire.write(pp_status);
  Wire.endTransmission(); 
}

uint8_t IO2::digitalRead(uint8_t pin){
  uint8_t data;
  Wire.begin();
  Wire.beginTransmission(address);
  Wire.write(GET_PORT);
  Wire.endTransmission();
  Wire.requestFrom((int)address, 1);
  data = Wire.read();
  return !!(data & pin);
}
uint8_t IO2::readID(){
  uint8_t id;
  Wire.begin();
  Wire.beginTransmission(address);
  Wire.write(GET_ID);
  Wire.endTransmission();
  Wire.requestFrom((int)address, 1);
  id = Wire.read();
  
  return id;
}
