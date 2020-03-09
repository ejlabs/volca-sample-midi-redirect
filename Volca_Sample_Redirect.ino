 /*
 * Volca Sample MIDI Channel Redirect 09/Mar/2020
 * Simple midi channel redirect for Korg Volca Sample
 * Eunjae Im http://ejlabs.net
 */

#include <MIDI.h>

#define LED_PIN 13 // LED Pin

int VolcaChannel = 16; // Default Channel to send MIDI to Volca Sample

MIDI_CREATE_DEFAULT_INSTANCE();
    
void setup(){
      
    pinMode (LED_PIN, OUTPUT); // Set LED pin to output    
    
    // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

    // Do the same for NoteOffs
    MIDI.setHandleNoteOff(handleNoteOff);    

    // Initiate MIDI communications, listen only VolcaChannel
    MIDI.begin(VolcaChannel);

    //MIDI.turnThruOff(); // Turn Thru Off
    MIDI.setThruFilterMode(midi::Thru::SameChannel); // Set Thru only VolcaChannel

}

void handleNoteOn(byte channel, byte pitch, byte velocity) {

  int Note;
  int Velocity;
  
  digitalWrite(LED_PIN, HIGH); // Turn ON led  
  
  Note = MIDI.getData1();
  Velocity = MIDI.getData2();
  
  if (MIDI.getChannel() == VolcaChannel) { // listen only 1 channel

      /* Volca don't listen velocity so changing level instead.
       * Comment out If you don't need it
      */
      MIDI.sendControlChange(7, Velocity, Note % 11);

      // Sending note to each channel
      MIDI.send(MIDI.getType(), Note, Velocity, Note % 11);
      
  }
  
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
   /*
    * Volca don't listen Note off
    */
   digitalWrite(LED_PIN, LOW); // Turn Off led 
}

void loop()
{    
  MIDI.read();
}
