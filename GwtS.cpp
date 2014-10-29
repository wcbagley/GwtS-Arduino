/*
   Adapted from code by by Paul Martis, October 1, 2011.
   http://www.digitalmisery.com
*/

#include <Arduino.h>
#include <PWM.h>
#include "GwtS.h"

// Define all Pin usage
#define pwmPin  9
#define pwmFreq 38000

byte codeLookup[17][17][17] = 
{
  {
    { 0x1D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 },
    { 0x19, 0x01, 0x01, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 },
    { 0x19, 0x17, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 },
    { 0x19, 0x17, 0x17, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04 },
    { 0x19, 0x18, 0x17, 0x17, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x19, 0x18, 0x17, 0x17, 0x17, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02 },
    { 0x19, 0x18, 0x17, 0x17, 0x17, 0x17, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x01, 0x01 },
    { 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x19, 0x18, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x19, 0x18, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x19, 0x18, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x19, 0x18, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x1A, 0x1A, 0x18, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16 }
  },
  {
    { 0x15, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 },
    { 0x12, 0x1D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 },
    { 0x19, 0x1B, 0x00, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04 },
    { 0x19, 0x19, 0x17, 0x00, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x19, 0x19, 0x17, 0x17, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x19, 0x19, 0x18, 0x17, 0x17, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02 },
    { 0x19, 0x19, 0x18, 0x17, 0x17, 0x17, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02 },
    { 0x19, 0x19, 0x18, 0x17, 0x17, 0x17, 0x17, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x19, 0x19, 0x18, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x19, 0x19, 0x18, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x19, 0x19, 0x18, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x1A, 0x1A, 0x1A, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16 }
  },
  {    
    { 0x15, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 },
    { 0x11, 0x1D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 },
    { 0x12, 0x1D, 0x1D, 0x08, 0x08, 0x08, 0x08, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x12, 0x19, 0x1B, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x19, 0x19, 0x1B, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x19, 0x19, 0x19, 0x17, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x19, 0x19, 0x19, 0x18, 0x17, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02 },
    { 0x19, 0x19, 0x19, 0x18, 0x17, 0x17, 0x17, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x18, 0x17, 0x17, 0x17, 0x17, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x18, 0x17, 0x17, 0x17, 0x17, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x19, 0x19, 0x19, 0x18, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x19, 0x19, 0x19, 0x18, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x1A, 0x1A, 0x1A, 0x1A, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16 }
  },
  {    
    { 0x15, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 },
    { 0x10, 0x1D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 },
    { 0x0F, 0x1D, 0x1D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x07 },
    { 0x12, 0x0F, 0x1D, 0x1D, 0x06, 0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x12, 0x12, 0x1B, 0x1B, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x19, 0x19, 0x19, 0x1B, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x19, 0x19, 0x19, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x19, 0x19, 0x19, 0x19, 0x18, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02 },
    { 0x19, 0x19, 0x19, 0x19, 0x18, 0x17, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x18, 0x17, 0x17, 0x17, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x18, 0x17, 0x17, 0x17, 0x17, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x19, 0x19, 0x19, 0x19, 0x18, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16, 0x16 },
    { 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16 }
  },
  {    
    { 0x15, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x03, 0x03, 0x03, 0x03, 0x03 },
    { 0x13, 0x15, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x03, 0x03, 0x03, 0x03, 0x07 },
    { 0x11, 0x10, 0x1D, 0x09, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07 },
    { 0x0F, 0x0F, 0x1D, 0x1D, 0x05, 0x08, 0x08, 0x08, 0x08, 0x06, 0x06, 0x02, 0x02, 0x02, 0x02, 0x07, 0x07 },
    { 0x12, 0x0F, 0x1D, 0x1D, 0x1D, 0x00, 0x06, 0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x12, 0x12, 0x19, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02 },
    { 0x19, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02 },
    { 0x19, 0x19, 0x19, 0x19, 0x1B, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x18, 0x17, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x18, 0x17, 0x17, 0x17, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16 },
    { 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16 }
  },
  {
    { 0x15, 0x0E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x03, 0x03, 0x03, 0x07 },
    { 0x13, 0x15, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x03, 0x03, 0x07, 0x07, 0x07 },
    { 0x11, 0x13, 0x1D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0x07, 0x07, 0x07, 0x07 },
    { 0x0F, 0x0F, 0x1D, 0x1D, 0x09, 0x09, 0x08, 0x08, 0x08, 0x08, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07 },
    { 0x0F, 0x0F, 0x0F, 0x1D, 0x1D, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x02, 0x02, 0x02, 0x07 },
    { 0x12, 0x12, 0x0F, 0x1D, 0x1D, 0x1D, 0x00, 0x06, 0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x12, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02 },
    { 0x19, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x1B, 0x18, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x00, 0x00, 0x16, 0x01 },
    { 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16, 0x16 }
  },
  {    
    { 0x15, 0x0E, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x03, 0x07, 0x07 },
    { 0x13, 0x15, 0x0E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0x07, 0x07, 0x07 },
    { 0x10, 0x13, 0x15, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x07, 0x07, 0x07, 0x07 },
    { 0x11, 0x11, 0x13, 0x1D, 0x09, 0x09, 0x08, 0x08, 0x08, 0x08, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07 },
    { 0x0F, 0x0F, 0x0F, 0x1D, 0x1D, 0x05, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07 },
    { 0x0F, 0x0F, 0x0F, 0x1D, 0x1D, 0x1D, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07 },
    { 0x12, 0x12, 0x0F, 0x0F, 0x1B, 0x1D, 0x1D, 0x00, 0x06, 0x06, 0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x12, 0x12, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02 },
    { 0x12, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01 },
    { 0x12, 0x19, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x18, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x1B, 0x18, 0x18, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x18, 0x17, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00 }
  },
  {    
    { 0x15, 0x0E, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0x07, 0x07 },
    { 0x14, 0x15, 0x0E, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x07, 0x07, 0x07 },
    { 0x10, 0x13, 0x15, 0x0E, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x06, 0x07, 0x07, 0x07 },
    { 0x11, 0x10, 0x13, 0x15, 0x09, 0x09, 0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07 },
    { 0x11, 0x11, 0x11, 0x13, 0x1D, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x1D, 0x1D, 0x05, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07 },
    { 0x12, 0x0F, 0x0F, 0x0F, 0x1D, 0x1D, 0x1D, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07 },
    { 0x12, 0x12, 0x0F, 0x0F, 0x1B, 0x1B, 0x1B, 0x1D, 0x00, 0x06, 0x06, 0x06, 0x06, 0x02, 0x02, 0x02, 0x02 },
    { 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02 },
    { 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02 },
    { 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02 },
    { 0x12, 0x12, 0x12, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01 },
    { 0x12, 0x12, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 },
    { 0x12, 0x19, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1B, 0x1B, 0x1B, 0x1B, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
  },
  {    
    { 0x15, 0x0E, 0x0D, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0x07, 0x07 },
    { 0x14, 0x15, 0x0E, 0x0D, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0x07, 0x07 },
    { 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x06, 0x06, 0x07, 0x07 },
    { 0x10, 0x10, 0x13, 0x15, 0x0E, 0x09, 0x09, 0x08, 0x08, 0x08, 0x08, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07 },
    { 0x11, 0x11, 0x10, 0x13, 0x1C, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x05, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x12, 0x12, 0x0F, 0x0F, 0x0F, 0x1B, 0x1B, 0x1B, 0x1C, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0x02, 0x02 },
    { 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02 },
    { 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02 },
    { 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 },
    { 0x12, 0x12, 0x12, 0x12, 0x19, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x19, 0x19, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
  },
  {    
    { 0x15, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0B, 0x0B, 0x07 },
    { 0x14, 0x15, 0x0E, 0x0D, 0x0D, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x07, 0x07 },
    { 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x06, 0x06, 0x07 },
    { 0x10, 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x11, 0x10, 0x10, 0x13, 0x15, 0x09, 0x09, 0x09, 0x09, 0x08, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x11, 0x11, 0x11, 0x10, 0x13, 0x1C, 0x05, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x12, 0x12, 0x12, 0x0F, 0x0F, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0x02 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x19, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x19, 0x19, 0x19, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x1A, 0x1A, 0x1A, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00 }
  },
  {    
    { 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0C, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0B, 0x0B, 0x0B },
    { 0x14, 0x15, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0B, 0x0B, 0x07 },
    { 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x0D, 0x0D, 0x0C, 0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x06, 0x06, 0x06 },
    { 0x10, 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x0D, 0x0A, 0x0A, 0x08, 0x08, 0x08, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x11, 0x10, 0x13, 0x14, 0x15, 0x0E, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x11, 0x11, 0x10, 0x10, 0x13, 0x1C, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x10, 0x1C, 0x1C, 0x05, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x12, 0x12, 0x12, 0x0F, 0x0F, 0x0F, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x19, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x1A, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00 }
  },
  {    
    { 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x08, 0x08, 0x08, 0x08, 0x0B, 0x0B, 0x0B, 0x0B },
    { 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x08, 0x08, 0x08, 0x08, 0x0B, 0x0B, 0x0B, 0x0B },
    { 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0A, 0x08, 0x08, 0x08, 0x0A, 0x06, 0x06, 0x06 },
    { 0x13, 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x0D, 0x0D, 0x0A, 0x0A, 0x0A, 0x08, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x10, 0x10, 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x09, 0x09, 0x09, 0x0A, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x11, 0x11, 0x10, 0x13, 0x14, 0x15, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06 },
    { 0x11, 0x11, 0x11, 0x10, 0x10, 0x13, 0x1C, 0x05, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x10, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x06, 0x06, 0x06, 0x06 },
    { 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x1C, 0x05, 0x09, 0x06, 0x06, 0x06, 0x06 },
    { 0x12, 0x12, 0x12, 0x0F, 0x0F, 0x0F, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C, 0x00, 0x00, 0x00, 0x06, 0x06 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00 }
  },
  {    
    { 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x08, 0x08, 0x0B, 0x0B, 0x0B, 0x0B },
    { 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0A, 0x08, 0x0A, 0x0B, 0x0B, 0x0B },
    { 0x13, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A },
    { 0x13, 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x06, 0x06, 0x06 },
    { 0x10, 0x13, 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x0D, 0x0D, 0x0A, 0x0A, 0x0A, 0x0A, 0x06, 0x06, 0x06, 0x06 },
    { 0x11, 0x10, 0x10, 0x13, 0x14, 0x15, 0x0E, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06 },
    { 0x11, 0x11, 0x11, 0x10, 0x13, 0x14, 0x1C, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06 },
    { 0x11, 0x11, 0x11, 0x11, 0x10, 0x10, 0x1C, 0x1C, 0x05, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x10, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x05, 0x09, 0x09, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x09, 0x06, 0x06 },
    { 0x12, 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x06, 0x06, 0x06 },
    { 0x12, 0x12, 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C, 0x00, 0x00, 0x00, 0x06 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00 }
  },
  {    
    { 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B },
    { 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x0A, 0x0A, 0x0A, 0x0B, 0x0B },
    { 0x14, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A },
    { 0x13, 0x13, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0C, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A },
    { 0x10, 0x13, 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x06, 0x06 },
    { 0x11, 0x10, 0x13, 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06 },
    { 0x11, 0x11, 0x10, 0x10, 0x13, 0x14, 0x15, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06 },
    { 0x11, 0x11, 0x11, 0x11, 0x10, 0x13, 0x14, 0x1C, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x10, 0x10, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x05, 0x09, 0x09, 0x09, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x05, 0x09, 0x09, 0x06 },
    { 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x09, 0x06 },
    { 0x12, 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x06 },
    { 0x12, 0x12, 0x12, 0x12, 0x0F, 0x0F, 0x0F, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00 }
  },
  {    
    { 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0B, 0x0B, 0x0B, 0x0B },
    { 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x0A, 0x0A, 0x0A, 0x0B },
    { 0x14, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A },
    { 0x13, 0x14, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A },
    { 0x10, 0x13, 0x13, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A },
    { 0x10, 0x10, 0x13, 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x0D, 0x09, 0x09, 0x09, 0x09, 0x0A, 0x0A, 0x06, 0x06 },
    { 0x11, 0x11, 0x10, 0x13, 0x13, 0x14, 0x15, 0x0E, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06 },
    { 0x11, 0x11, 0x11, 0x10, 0x10, 0x13, 0x14, 0x1C, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06 },
    { 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x13, 0x1C, 0x1C, 0x05, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x10, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x09, 0x09, 0x09, 0x09 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x05, 0x09, 0x09, 0x09 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x05, 0x09, 0x09 },
    { 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x09 },
    { 0x12, 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1B, 0x1C, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x09 },
    { 0x12, 0x12, 0x12, 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00 }
  },
  {    
    { 0x15, 0x0E, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0B, 0x0B, 0x0B },
    { 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0A, 0x0A, 0x0B },
    { 0x14, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0A, 0x0A, 0x0A, 0x0A },
    { 0x13, 0x14, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A },
    { 0x13, 0x13, 0x14, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A },
    { 0x10, 0x10, 0x13, 0x13, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A },
    { 0x11, 0x10, 0x10, 0x13, 0x13, 0x14, 0x15, 0x0E, 0x0D, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06 },
    { 0x11, 0x11, 0x11, 0x10, 0x13, 0x13, 0x14, 0x15, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09 },
    { 0x11, 0x11, 0x11, 0x11, 0x10, 0x10, 0x13, 0x14, 0x1C, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x11, 0x10, 0x13, 0x1C, 0x1C, 0x05, 0x05, 0x09, 0x09, 0x09, 0x09, 0x09 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x05, 0x09, 0x09, 0x09 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x05, 0x09, 0x09 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x05, 0x09 },
    { 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x05 },
    { 0x12, 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1B, 0x1C, 0x1C, 0x1C, 0x1C, 0x05, 0x05 },
    { 0x12, 0x12, 0x12, 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C, 0x00 },
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x0F, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00 }
  },
  {    
    { 0x15, 0x0E, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0B, 0x0B },
    { 0x14, 0x15, 0x0E, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0A, 0x0A },
    { 0x14, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x0A, 0x0A, 0x0A },
    { 0x13, 0x14, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0A, 0x0A, 0x0A, 0x0A },
    { 0x13, 0x13, 0x14, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A },
    { 0x10, 0x13, 0x13, 0x14, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A },
    { 0x10, 0x10, 0x10, 0x13, 0x13, 0x14, 0x15, 0x0E, 0x0E, 0x0D, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09 },
    { 0x11, 0x11, 0x10, 0x10, 0x13, 0x13, 0x14, 0x15, 0x0E, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09 },
    { 0x11, 0x11, 0x11, 0x11, 0x10, 0x13, 0x13, 0x14, 0x15, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09 },
    { 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x10, 0x13, 0x14, 0x1C, 0x05, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x10, 0x13, 0x1C, 0x1C, 0x05, 0x05, 0x05, 0x09, 0x09, 0x09 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x05, 0x05, 0x09 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x05, 0x05 },
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x1C, 0x05, 0x05, 0x05 },
    { 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x05, 0x05 },
    { 0x12, 0x12, 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1B, 0x1C, 0x1C, 0x1C, 0x1C, 0x05 },
    { 0x12, 0x12, 0x12, 0x12, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C }
  }
};

byte GWTS::calc_crc(byte *data, uint8_t length) {
  // Courtesy of rjchu and Timon - A godsend
  byte crc = 0;
  
  while(length--) 
  {
    crc ^= *data++;
    
    unsigned n = 8;
    
    do 
    {
      crc = ((crc & 1) ? ((crc >> 1) ^ (byte)0x8C) : (crc >> 1));
    } while(--n);
  }
  
  return crc;
}

//Constructor
GWTS::GWTS()
{
  cmdcount = 0;

  _lred = 0;
  _lgreen = 0;
  _lblue = 0;
  _rred = 0;
  _rgreen = 0;
  _rblue = 0;
}

// Had to create a function to be called during setup because these registers would not initialize correctly during contructor
void GWTS::setup(void)
{
  // Inititalize the PWM timers except Timer 0
  InitTimersSafe();  
  
  // Set the timer pin to 38 KHz
  SetPinFrequencySafe(pwmPin, pwmFreq);
  // Output a square wave  
  pwmWrite(pwmPin, 255/2);
  
  // Setup the hardware serial port 1 to 2400,N,8,1
  Serial1.begin(2400, SERIAL_8N1);
  //Data is now a combinations of serial 1 output (pin 18) and PWM output (pin 9)
  // For testing just put an IR LED between pin 18 (anode) and pin 9 (cathode) on Arduino Mega
}

// Function that actually sets the colors of the 
void GWTS::set_colors(uint8_t lRed, uint8_t lGreen, uint8_t lBlue, uint8_t rRed, uint8_t rGreen, uint8_t rBlue)
{
  // Make sure the input values are within limits
  lRed = min(lRed,256);
  lGreen = min(lGreen,256);
  lBlue = min(lBlue,256);
  rRed = min(rRed,256);
  rGreen = min(rGreen,256);
  rBlue = min(rBlue,256);
  
  // Round to the nearest multiple so we can look it up in the table 'codeLookup'
  _lred   = lRed/16;
  _lgreen = lGreen/16;
  _lblue  = lBlue/16;
  _rred   = rRed/16;
  _rgreen = rGreen/16;
  _rblue  = rBlue/16;

  // Make sure the scaled values are within limits
  _lred = min(_lred, 16);
  _lgreen = min(_lgreen, 16);
  _lblue = min(_lblue, 16);
  _rred = min(_rred, 16);
  _rgreen = min(_rgreen, 16);
  _rblue = min(_rblue, 16);

  
  if ((_lred == _rred) && (_lgreen == _rgreen) && (_lblue == _rblue)) {
    // Left and right ears are the same color: send a shorter command
    cmdbuf[0] = (byte)0x90;
    cmdbuf[1] = (byte)0x0E;
    cmdbuf[2] = codeLookup[_lred][_lgreen][_lblue]; // Color code for both ears
    cmdcount = 3;
  }
  else 
  {
    // Left and right ears are different colors
    cmdbuf[0] = (byte)0x90;
    cmdbuf[1] = (byte)0x0E;
    cmdbuf[2] = codeLookup[_lred][_lgreen][_lblue]; // Color code for the left ear
    cmdbuf[3] = (byte)0x0E;
    cmdbuf[4] = (byte)0x80 | codeLookup[_rred][_rgreen][_rblue]; // Add 0x80 to color code for the right ear
    cmdcount = 5;
  }
  // Set the count of bytes in the first byte
  cmdbuf[0] |= (byte)(cmdcount - 2);
  
  // Add the checksum to the command buffer
  cmdbuf[cmdcount++] = calc_crc(cmdbuf, cmdcount);

#ifdef DEBUG
  Serial.print("Sending: ");
  for (int j=0; j < cmdcount; j++) 
  {
    if ( cmdbuf[j] < 0x10 ) 
    { 
      Serial.print('0'); 
    }
    Serial.print(cmdbuf[j], HEX);
    Serial.print(" ");
  }
  Serial.print("\n");
#endif

  // Send the data to the hat
  for (int j=0; j < cmdcount; j++) 
  {
    Serial1.write(cmdbuf[j]);
  }
}
