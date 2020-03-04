 /*
 * Volca Sample MIDI Channel Redirect
 * Simple midi channel redirect for Korg Volca Sample
 * Eunjae Im http://ejlabs.net
 */

#include <MIDI.h>

#define LED_PIN 13 // LED Pin

int vPolyChan = 16; // Default Channel to send MIDI to Volca Sample
int vNote;

MIDI_CREATE_DEFAULT_INSTANCE();

void handleNoteOn(byte channel, byte pitch, byte velocity) {  
  
  digitalWrite(LED_PIN, HIGH); // Turn ON led  

  /*
   * receiving midi note from B0(35) to G#1(44) from single midi channel (vPolyChan)
   * and send to 1 to 10 MIDI channel to Volca Sample
  */
  
  vNote = MIDI.getData1();
  if (vNote > 34 && vNote < 45 && MIDI.getChannel() == vPolyChan) {
      MIDI.send(MIDI.getType(), vNote, MIDI.getData2(),vNote - 34);
  }
  
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
   digitalWrite(LED_PIN, LOW); // Turn Off led 
}
    
void setup(){
      
    pinMode (LED_PIN, OUTPUT); // Set LED pin to output    
    
    // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

    // Do the same for NoteOffs
    MIDI.setHandleNoteOff(handleNoteOff);

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);

}

void loop()
{    
    MIDI.read();
}
