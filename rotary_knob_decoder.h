/*************************************************************
 * Derek Schacht
 * 2015/01/13
 *
 * *** Use Statement and License ***
 * Free for non commercial use! Anything else is not authorized without consent.
 *  Contact [dschacht ( - at - ) gmail ( - dot - ) com] for use questions.
 *************************************************************
 * Initial Code based on a function I wrote in college for a microblaze CPU.
 *
 * Updated to use 8 bit data where applicable. This should help with speed on
 * 8 bit MCUs. The original code was written for a PIC24 which is a 16 bit
 * device.
 *
 * Updated to implement the other functions of the sparkfun 10596 device.
 */

/* Known to work with:
 *   https://www.sparkfun.com/products/10596
 */

#ifndef ROTARY_KNOB_DECODER_H
#define ROTARY_KNOB_DECODER_H

#define NOT_USED 99

#define NO_CHANGE     215
#define ANTICLOCKWISE 216
#define CLOCKWISE     217

#define ROT_STATE_A 112
#define ROT_STATE_B 113
#define ROT_STATE_C 114
#define ROT_STATE_D 115

#define RPM_LOWER_LIMIT 1.0
#define RPM_UPPER_LIMIT 100.0
#define PULSES_PER_REV  48

class RotaryKnobDecoder
{
public:
  RotaryKnobDecoder();
  RotaryKnobDecoder(unsigned char switch_A, unsigned char switch_B);
  RotaryKnobDecoder(unsigned char switch_A, unsigned char switch_B, unsigned char push_button,
                    unsigned char light_A, unsigned char light_B);
  
  unsigned char getState();
  unsigned char getSpeed();
  unsigned char read();
  
  unsigned char getButtonState();
  
  void setLightA(unsigned char state);
  void setLightB(unsigned char state);
  
private:
  unsigned char switch_A;
  unsigned char switch_B;
  
  unsigned char push_button;
  
  unsigned char light_A;
  unsigned char light_B;
  
  unsigned long last_change;
  unsigned long interval;

  unsigned char rot_knob_dir;
  unsigned char rot_knob_state;
};

#endif