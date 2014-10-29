/*
   GEColorEffects.h - Library for driving GE Color Effects
   LED Holiday Lights with an Arduino

   Created by Paul Martis, October 1, 2011.
   http://www.digitalmisery.com

   Based on Christmas Light Control by Robert Quattlebaum <darco@deepdarc.com>
   (http://www.deepdarc.com/2010/11/27/hacking-christmas-lights)
   and Arduino adaptation by Scott Harris <scottrharris@gmail.com>
   http://scottrharris.blogspot.com/2010/12/controlling-ge-color-effects-lights.html
*/

#ifndef GwtS_h
#define GwtS_h

#include "Arduino.h"

class GWTS
{
  public:
    GWTS();
    void setup(void);
    void set_colors(uint8_t lRed, uint8_t lGreen, uint8_t lBlue, uint8_t rRed, uint8_t rGreen, uint8_t rBlue);
  private:
    byte calc_crc(byte *data, uint8_t length);

    uint8_t _lred;
    uint8_t _lgreen;
    uint8_t _lblue;
    uint8_t _rred;
    uint8_t _rgreen;
    uint8_t _rblue;

    byte cmdbuf[15];
    uint8_t cmdcount;
};
 
#endif
