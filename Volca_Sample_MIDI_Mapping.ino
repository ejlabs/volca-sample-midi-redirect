/*
 * Volca Sample MIDI Mapping v0.2 - 12/Mar/2020
 * Chromatic play on 1-10 MIDI Channel, MIDI Channel 16 = Single note trigger each sound on Sample
 * Eunjae Im https://ejlabs.net/volca-sample-midi-redirect-using-arduino
 *
 *******************************************************************************
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *******************************************************************************
 */

#include <MIDI.h>

#define LED_PIN 13 // LED Pin

int VolcaChannel = 16;

struct MySettings : public midi::DefaultSettings
{    
    /*! Running status enables short messages when sending multiple values    
     * of the same type and channel.
     * Warning: does not work with some hardware, enable with caution.
    */
    static const bool UseRunningStatus = true;
};

MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings);

const int ccSpeed[] = { // CC Speed Value, Code snippet from Volca Simple (https://github.com/mmaisterrena/Volca_Simple)
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  19,  20,  21,  22,  23,  24,  25,  
26, 27, 28, 29, 30, 32, 34, 37, 40, 43, 45, 48, 51, 53, 56, 59, 61, 64, 67, 69, 72, 75, 78, 80, 83, 85, 88, 91, 93, 96, 97, 99, 100, 102, 103, 104, 106, 107, 108, 109, 111, 112
};
    
void setup(){
      
    pinMode (LED_PIN, OUTPUT);    
   
    MIDI.setHandleNoteOn(handleNoteOn);
    
    MIDI.setHandleNoteOff(handleNoteOff);
    
    MIDI.begin(MIDI_CHANNEL_OMNI);

    MIDI.turnThruOff(); // Turn thru off. should be after midi.begin

    /*    
     * Reset speed (pitch) & velocity settings on all channel
     * 7 = Level, 43 = Speed, 44 = Pitch EG Int
    */
    
    int x = 1;
    while (x <= 10)
    {
      MIDI.sendControlChange(7,127,x);
      MIDI.sendControlChange(43,64,x);
      MIDI.sendControlChange(44,64,x);
      x++;
    }

}

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  
  digitalWrite(LED_PIN, HIGH); // Turn ON led  

  int Channel = MIDI.getChannel();
  int Note = MIDI.getData1();
  
  if (Channel == VolcaChannel) { // Channel (16) : each note sending to different midi channel on Sample 

      Channel = Note % 10;
      Channel++; 
    
  } else { // Chromatic play on all other channel
      
      MIDI.sendControlChange(43,ccSpeed[Note],Channel);      
    
  }

  MIDI.sendControlChange(7, MIDI.getData2(), Channel); // Level change
  MIDI.sendNoteOn(60,127,Channel);
  
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
   digitalWrite(LED_PIN, LOW); // Turn Off led 
}

void loop()
{    
    MIDI.read();
}
