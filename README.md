#Morrowind Key Remapper

##Overview
A DirectX keyboard device wrapper to remap the Morrowind
keys for opening the console and typing a quote character.

When using a non-US keyboard with Morrowind, often the
scan codes for the keys are different, and it is impossible
to open the console. DInputWrapper hooks into the DInput
device creating function and replaces the device with one
which remaps two specific keys: the tilde (~) character key
and the quote (') key.

Currently the keys which are mapped to the above are hard-coded
for a Japanese keyboard. They are the Insert key (for the tilde
or 'open console' key), and the right bracket key (']', for the
single quote key). It would be possible to add functionality to
read the keys to remap from a configuration file (like MGE).

In fact, this project was largely inspired by the [Morrowind Graphics
Extender](http://sourceforge.net/projects/morrgraphext/) project, specifically because that project requires
Bloodmoon to use, and I don't have Bloodmoon. So I spent a frustrating
day trying to find some way to use MGE anyway, and ended up
recoding the DInput wrapper part to suit my own purpose. The basic
idea and the structure of the Visual Studio projects are due to MGE.
