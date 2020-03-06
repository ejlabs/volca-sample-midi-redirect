# volca-sample-midi-redirect
Simple MIDI channel redirect for Korg Volca Sample

The Korg Volca Sample uses 10 MIDI channels for the each sound.

This is annoying if you want to use as a external drum machine with pad or DAW.

This arduino code listen single MIDI channel (16) and send note to each channel on Sample (support velocity) and filter out all other midi message except clock, start, stop & continue.

https://ejlabs.net/volca-sample-midi-redirect-using-arduino/
