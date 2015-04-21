/*************************************************************
 * Derek Schacht
 * 2015/01/13
 *
 * *** Use Statement and License ***
 * Free for non commercial use! Anything else is not authorized without consent.
 *  Contact [dschacht ( - at - ) gmail ( - dot - ) com] for use questions.
 *************************************************************
 * Initial Code based on a function I wrote in college for a microblaze CPU.
 */

/* Known to work with:
 *   https://www.sparkfun.com/products/10596
 */

#ifndef ROTARY_KNOB_DECODER_H
#define ROTARY_KNOB_DECODER_H

#define NO_CHANGE     215
#define ANTICLOCKWISE 216
#define CLOCKWISE     217

#define ROT_STATE_A 112
#define ROT_STATE_B 113
#define ROT_STATE_C 114
#define ROT_STATE_D 115

class RotaryKnobDecoder
{
public:
  RotaryKnobDecoder();
  RotaryKnobDecoder(int switch_A, int switch_B);
  
  int read();
  
private:
  int switch_A;
  int switch_B;

  unsigned int rot_knob_dir;
  unsigned int rot_knob_state;
};

#endif