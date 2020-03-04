# volca-sample-midi-redirect
Simple MIDI channel redirect for Korg Volca Sample

The Korg Volca Sample uses 10 MIDI channels for the each sound.

This is annoying if you want to use as a external drum machine with pad or DAW.

This is simple arduino code receiving MIDI note from B0(35) to G#1(44) from single MIDI channel (16)
and send to each channel on Sample.

https://ejlabs.net/volca-sample-midi-redirect-using-arduino/
