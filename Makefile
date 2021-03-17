#   File:       Sparks.make
#   Target:     Sparks
#   Created:    Wednesday, March 17, 2021 09:47:32 AM



ObjDir = :
Includes =

Sym-PPC = -sym off
Sym-68K = -sym off

CPlusOptions-PPC = {Includes} {Sym-PPC} 

CPlusOptions-68K = {Includes} {Sym-68K} -model near 

### Source Files ###

SrcFiles = ∂
	Draw.cpp ∂
	Entity.cpp ∂
	Explosion.cpp ∂
	Game.cpp ∂
	Graphics.cpp ∂
	Input.cpp ∂
	Main.cpp ∂
	PaletteTable.cpp ∂
	Player.cpp ∂
	Scenery.cpp ∂
	Sound.cpp ∂
	Sparks.cpp ∂
	Stars.cpp ∂
	Vectors.cpp ∂
	Viewpoint.cpp


### Object Files ###

ObjFiles-PPC = ∂
	"{ObjDir}Draw.cpp.x" ∂
	"{ObjDir}Entity.cpp.x" ∂
	"{ObjDir}Explosion.cpp.x" ∂
	"{ObjDir}Game.cpp.x" ∂
	"{ObjDir}Graphics.cpp.x" ∂
	"{ObjDir}Input.cpp.x" ∂
	"{ObjDir}Main.cpp.x" ∂
	"{ObjDir}PaletteTable.cpp.x" ∂
	"{ObjDir}Player.cpp.x" ∂
	"{ObjDir}Scenery.cpp.x" ∂
	"{ObjDir}Sound.cpp.x" ∂
	"{ObjDir}Sparks.cpp.x" ∂
	"{ObjDir}Stars.cpp.x" ∂
	"{ObjDir}Vectors.cpp.x" ∂
	"{ObjDir}Viewpoint.cpp.x"

ObjFiles-68K = ∂
	"{ObjDir}Draw.cpp.o" ∂
	"{ObjDir}Entity.cpp.o" ∂
	"{ObjDir}Explosion.cpp.o" ∂
	"{ObjDir}Game.cpp.o" ∂
	"{ObjDir}Graphics.cpp.o" ∂
	"{ObjDir}Input.cpp.o" ∂
	"{ObjDir}Main.cpp.o" ∂
	"{ObjDir}PaletteTable.cpp.o" ∂
	"{ObjDir}Player.cpp.o" ∂
	"{ObjDir}Scenery.cpp.o" ∂
	"{ObjDir}Sound.cpp.o" ∂
	"{ObjDir}Sparks.cpp.o" ∂
	"{ObjDir}Stars.cpp.o" ∂
	"{ObjDir}Vectors.cpp.o" ∂
	"{ObjDir}Viewpoint.cpp.o"

### Libraries ###

LibFiles-PPC =  ∂
	"{SharedLibraries}InterfaceLib" ∂
	"{SharedLibraries}StdCLib" ∂
	"{SharedLibraries}MathLib" ∂
	"{PPCLibraries}StdCRuntime.o" ∂
	"{PPCLibraries}PPCCRuntime.o" ∂
	"{PPCLibraries}PPCToolLibs.o" ∂
	"{PPCLibraries}MrCPlusLib.o" ∂
	"{PPCLibraries}MrCIOStreams.o"

LibFiles-68K    =  ∂
	"{Libraries}MathLib.o" ∂
	"{CLibraries}StdCLib.o" ∂
	"{CLibraries}IOStreams.o" ∂
	"{CLibraries}CPlusLib.o" ∂
	"{Libraries}MacRuntime.o" ∂
	"{Libraries}IntEnv.o" ∂
	"{Libraries}ToolLibs.o" ∂
	"{Libraries}Interface.o"


### Default Rules ###

.cpp.x  ƒ  .cpp
	{PPCCPlus} {depDir}{default}.cpp -o {targDir}{default}.cpp.x {CPlusOptions-PPC}

.cpp.o  ƒ  .cpp
	{CPlus} {depDir}{default}.cpp -o {targDir}{default}.cpp.o {CPlusOptions-68K}


### Build Rules ###

Sparks.ppc ƒƒ {ObjFiles-PPC} {LibFiles-PPC}
	PPCLink ∂
		-o {Targ} ∂
		{ObjFiles-PPC} ∂
		{LibFiles-PPC} ∂
		{Sym-PPC} ∂
		-mf -d ∂
		-t 'APPL' ∂
		-c '????'

Sparks.ppc ƒƒ Resources.r Resources.rsrc
	Rez -o {Targ} -a Resources.r

Sparks.68k ƒƒ {ObjFiles-68K} {LibFiles-68K}
	ILink ∂
		-o {Targ} ∂
		{ObjFiles-68K} ∂
		{LibFiles-68K} ∂
		{Sym-68K} ∂
		-mf -d ∂
		-t 'APPL' ∂
		-c '????' ∂
		-model near ∂
		-state rewrite ∂
		-compact -pad 0
	If "{Sym-68K}" =~ /-sym ≈[nNuU]≈/
		ILinkToSYM {Targ}.NJ -mf -sym 3.2 -c 'sade'
	End

Sparks.68k ƒƒ Resources.r Resources.rsrc
	Rez -o {Targ} -a Resources.r

### Required Dependencies ###

"{ObjDir}Draw.cpp.x" "{ObjDir}Draw.cpp.o"  ƒ  Draw.cpp
"{ObjDir}Entity.cpp.x" "{ObjDir}Entity.cpp.o"  ƒ  Entity.cpp
"{ObjDir}Explosion.cpp.x" "{ObjDir}Explosion.cpp.o"  ƒ  Explosion.cpp
"{ObjDir}Game.cpp.x" "{ObjDir}Game.cpp.o"  ƒ  Game.cpp
"{ObjDir}Graphics.cpp.x" "{ObjDir}Graphics.cpp.o"  ƒ  Graphics.cpp
"{ObjDir}Input.cpp.x" "{ObjDir}Input.cpp.o"  ƒ  Input.cpp
"{ObjDir}Main.cpp.x" "{ObjDir}Main.cpp.o"  ƒ  Main.cpp
"{ObjDir}PaletteTable.cpp.x" "{ObjDir}PaletteTable.cpp.o"  ƒ  PaletteTable.cpp
"{ObjDir}Player.cpp.x" "{ObjDir}Player.cpp.o"  ƒ  Player.cpp
"{ObjDir}Scenery.cpp.x" "{ObjDir}Scenery.cpp.o"  ƒ  Scenery.cpp
"{ObjDir}Sound.cpp.x" "{ObjDir}Sound.cpp.o"  ƒ  Sound.cpp
"{ObjDir}Sparks.cpp.x" "{ObjDir}Sparks.cpp.o"  ƒ  Sparks.cpp
"{ObjDir}Stars.cpp.x" "{ObjDir}Stars.cpp.o"  ƒ  Stars.cpp
"{ObjDir}Vectors.cpp.x" "{ObjDir}Vectors.cpp.o"  ƒ  Vectors.cpp
"{ObjDir}Viewpoint.cpp.x" "{ObjDir}Viewpoint.cpp.o"  ƒ  Viewpoint.cpp


### Optional Dependencies ###
### Build this target to generate "include file" dependencies. ###

Dependencies  ƒ  $OutOfDate
	MakeDepend ∂
		-append Makefile ∂
		-skip "{CIncludes}" ∂
		-objdir "{ObjDir}" ∂
		-objext .x ∂
		-objext .o ∂
		{Includes} ∂
		{SrcFiles}

