﻿# --- swang swung ---
This monstrosity of a code is presumably going to be some sort of a TBS game, being made from scratch for some enigmatic reason.\
Status: *compiles. not sure about the rest.*
___
## Contributors:
- `rhisth` — original repository owner.
- `StresseR` — lazy dev.
- `*You could be here*` — but you aren't.
___
## TODO:
- enhanced logs
- error codes
- configuration file parser revision
- cubic-bezier interpreter
- window class rework
- concurrency
- basic objects:
	- window
	- interface (base object)
	- texture : interface
	- object : texture
	- trigger : object
	- audio chunk : interface
- nodes:
	- cell : object
	- counter : trigger
	- sequence : trigger
	- audio stream : audio chunk
	- camera (kill me) : object
	- particle emitter : trigger
	- shader (GLSL) : trigger
	- gradient : shader, cell
- render layers
- blending: normal, multiply, screen, linear light, invert
- audio channels
- audio effects: pitch shift, lowpass
- events: keyboard input, mouse input, exit
- scenario & map editor (gui)
- scripting language for the editor (Lua)
- script: enforce UTF-8, documentation (pdf)
- scenario archiver (compression)
- save data serialization
- main campaign
- achievements
- client/server: TCP connection, authorization, player db (MariaDB)
- text processing: everything to unicode (UTF-8)
- multiplayer
- anticheat?
___
# UNIT TESTS PLEASE