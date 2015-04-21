
/*************************************************************
 * Derek Schacht
 * 2015/01/15
 *
 * *** Use Statement and License ***
 * Free for non commercial use! Anything else is not authorized without consent.
 *  Contact [dschacht ( - at - ) gmail ( - dot - ) com] for use questions.
 *************************************************************
 */


#include <Arduino.h>
#include "rotary_knob_decoder.h"

RotaryKnobDecoder::RotaryKnobDecoder()
{
  this->switch_A = 2;
  this->switch_B = 3;

  this->last_change = millis();
  
  this->rot_knob_dir   = NO_CHANGE;
  this->rot_knob_state = ROT_STATE_A;
}

RotaryKnobDecoder::RotaryKnobDecoder(int switch_A, int switch_B)
{
  this->switch_A = switch_A;
  this->switch_B = switch_B;
  
  this->last_change = millis();
  
  this->rot_knob_dir   = NO_CHANGE;
  this->rot_knob_state = ROT_STATE_A;
}


/* This function will return the current state of the rotary knob
 * state machine.
 */

int RotaryKnobDecoder::getState()
{
  return rot_knob_state;  
}

/* This function will return the rate at which the rotary knob is
 * being spun.
 */

int RotaryKnobDecoder::getSpeed()
{
  float speed = 0;
  
  if (interval > 0)
  {
    speed =  1000.0 / ((float)PULSES_PER_REV * (float)interval); /* Rev per sec (RPS) */

    speed = constrain(speed, RPM_LOWER_LIMIT, RPM_UPPER_LIMIT);
  }
  
  return (int)speed;  
}

/* This implements a state machine to track the position of a
 * grey coded rotary encoder. The normal state transition flows
 * from state A to state D wrapping to state A, or the reverse.
 * If somehow the statemachine is out of sync with the rotary
 * encoder the state machine will capture the position of the
 * rotary encoder in 2 steps.
 * This function is designed to be called by an ISR when one of 
 * the two pin states change. However, it can also work in polling
 * mode. In polling mode the maximum rotation speed of the knob
 * is limited by the polling rate. If polling is used it would be 
 * wise to call this function in a deterministic fashion.
 */

int RotaryKnobDecoder::read()
{

  int value;
  value = digitalRead(switch_A) | (digitalRead(switch_B) << 1);

  rot_knob_dir = NO_CHANGE;
  
  /* State A processing the valid state from here are:
   * - State D
   * - State B
   */
  if (value == 2 && rot_knob_state == ROT_STATE_A)
  {
    rot_knob_dir   = CLOCKWISE;
    rot_knob_state = ROT_STATE_D;
  }
  else if (value == 1 && rot_knob_state == ROT_STATE_A)
  {
    rot_knob_dir   = ANTICLOCKWISE;
    rot_knob_state = ROT_STATE_B;
  }
  
  /* State B processing the valid states from here are:
   * - State A
   * - State C
   */
  else if (value == 0 && rot_knob_state == ROT_STATE_B)
  {
    rot_knob_dir   = CLOCKWISE;
    rot_knob_state = ROT_STATE_A;
  }
  else if (value == 3 && rot_knob_state == ROT_STATE_B)
  {
    rot_knob_dir   = ANTICLOCKWISE;
    rot_knob_state = ROT_STATE_C;
  }
  
  /* State C processing the valid states from here are:
   * - State B
   * - State D
   */
  else if (value == 1 && rot_knob_state == ROT_STATE_C)
  {
    rot_knob_dir   = CLOCKWISE;
    rot_knob_state = ROT_STATE_B;
  }
  else if (value == 2 && rot_knob_state == ROT_STATE_C)
  {
    rot_knob_dir   = ANTICLOCKWISE;
    rot_knob_state = ROT_STATE_D;
  }
  
  /* State D processing the valid states from here are:
   * - State C
   * - State A
   */
  else if (value == 3 && rot_knob_state == ROT_STATE_D)
  {
    rot_knob_dir   = CLOCKWISE;
    rot_knob_state = ROT_STATE_C;
  }
  else if (value == 0 && rot_knob_state == ROT_STATE_D)
  {
    rot_knob_dir   = ANTICLOCKWISE;
    rot_knob_state = ROT_STATE_A;
  }
  
  /* If the state changes record the length of time elapsed since
   * the last state change.
   */
  
  if (rot_knob_dir != NO_CHANGE)
  {
    interval = millis() - last_change;
    last_change = millis();
  }
  else 
  {
    interval = 0;
  }

  
  return rot_knob_dir;
  
}
