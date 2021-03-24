#   File:       Sparks.make
#   Target:     Sparks
#   Created:    Wednesday, March 17, 2021 09:47:32 AM



ObjDir = :Objects:
Includes =

Sym-PPC = -sym off
Sym-68K = -sym off

CPlusOptions-PPC = {Includes} {Sym-PPC} -bool on

CPlusOptions-68K = {Includes} {Sym-68K} -bool on -model near

### Source Files ###

SrcFiles = ∂
	Draw.cpp ∂
	Entity.cpp ∂
	Error.cpp ∂
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

RFiles = ∂
	Resources.r

### Object Files ###

ObjFiles-PPC = ∂
	"{ObjDir}Draw.cpp.x" ∂
	"{ObjDir}Entity.cpp.x" ∂
	"{ObjDir}Error.cpp.x" ∂
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
	"{ObjDir}Error.cpp.o" ∂
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

Sparks.ppc ƒƒ {RFiles} Resources.rsrc
	Rez -o {Targ} -a {RFiles}

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

Sparks.68k ƒƒ {RFiles} Resources.rsrc
	Rez -o {Targ} -a {RFiles}

### Required Dependencies ###

"{ObjDir}Draw.cpp.x" "{ObjDir}Draw.cpp.o"  ƒ  Draw.cpp
"{ObjDir}Entity.cpp.x" "{ObjDir}Entity.cpp.o"  ƒ  Entity.cpp
"{ObjDir}Error.cpp.x" "{ObjDir}Error.cpp.o"  ƒ  Error.cpp
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


#*** Dependencies: Cut here ***
# These dependencies were produced at 1:01:32 PM on Thu, Mar 18, 2021 by MakeDepend

:Objects:Draw.cpp.x :Objects:Draw.cpp.o	ƒ  ∂
	:Draw.cpp ∂
	:Entity.h ∂
	:Header.h ∂
	:Vectors.h ∂
	:Viewpoint.h ∂
	:Draw.h ∂
	:Game.h

:Objects:Entity.cpp.x :Objects:Entity.cpp.o	ƒ  ∂
	:Entity.cpp ∂
	:Entity.h ∂
	:Header.h ∂
	:Params.h ∂
	:Draw.h ∂
	:Game.h ∂
	:Vectors.h

:Objects:Explosion.cpp.x :Objects:Explosion.cpp.o	ƒ  ∂
	:Explosion.cpp ∂
	:Explosion.h ∂
	:Header.h ∂
	:PaletteTable.h ∂
	:Sparks.h ∂
	:Entity.h ∂
	:Vectors.h ∂
	:Draw.h ∂
	:Game.h

:Objects:Game.cpp.x :Objects:Game.cpp.o	ƒ  ∂
	:Game.cpp ∂
	:Game.h ∂
	:Entity.h ∂
	:Graphics.h ∂
	:Header.h ∂
	:Input.h ∂
	:Params.h ∂
	:Sparks.h ∂
	:Stars.h ∂
	:Vectors.h ∂
	:Viewpoint.h ∂
	:Draw.h

:Objects:Graphics.cpp.x :Objects:Graphics.cpp.o	ƒ  ∂
	:Graphics.cpp ∂
	:Graphics.h ∂
	:Header.h ∂
	:PaletteTable.h ∂
	:ResourceList.h

:Objects:Input.cpp.x :Objects:Input.cpp.o	ƒ  ∂
	:Input.cpp ∂
	:Input.h ∂
	:Header.h

:Objects:Main.cpp.x :Objects:Main.cpp.o	ƒ  ∂
	:Main.cpp ∂
	:Main.h ∂
	:Entity.h ∂
	:Graphics.h ∂
	:Header.h ∂
	:Params.h ∂
	:Player.h ∂
	:ResourceList.h ∂
	:Scenery.h ∂
	:Sparks.h ∂
	:Stars.h ∂
	:Vectors.h ∂
	:Viewpoint.h ∂
	:Draw.h ∂
	:Game.h

:Objects:PaletteTable.cpp.x :Objects:PaletteTable.cpp.o	ƒ  ∂
	:PaletteTable.cpp

:Objects:Player.cpp.x :Objects:Player.cpp.o	ƒ  ∂
	:Player.cpp ∂
	:Player.h ∂
	:Entity.h ∂
	:Explosion.h ∂
	:Header.h ∂
	:Input.h ∂
	:PaletteTable.h ∂
	:Sparks.h ∂
	:Vectors.h ∂
	:Viewpoint.h ∂
	:Draw.h ∂
	:Game.h

:Objects:Scenery.cpp.x :Objects:Scenery.cpp.o	ƒ  ∂
	:Scenery.cpp ∂
	:Scenery.h ∂
	:Entity.h ∂
	:Header.h ∂
	:PaletteTable.h ∂
	:Vectors.h ∂
	:Draw.h ∂
	:Game.h

:Objects:Sound.cpp.x :Objects:Sound.cpp.o	ƒ  ∂
	:Sound.cpp

:Objects:Sparks.cpp.x :Objects:Sparks.cpp.o	ƒ  ∂
	:Sparks.cpp ∂
	:Sparks.h ∂
	:Draw.h ∂
	:Game.h ∂
	:Header.h ∂
	:Vectors.h ∂
	:Viewpoint.h ∂
	:Entity.h

:Objects:Stars.cpp.x :Objects:Stars.cpp.o	ƒ  ∂
	:Stars.cpp ∂
	:Stars.h ∂
	:Entity.h ∂
	:Header.h ∂
	:PaletteTable.h ∂
	:Params.h ∂
	:Vectors.h ∂
	:Viewpoint.h ∂
	:Draw.h ∂
	:Game.h

:Objects:Vectors.cpp.x :Objects:Vectors.cpp.o	ƒ  ∂
	:Vectors.cpp ∂
	:Vectors.h

:Objects:Viewpoint.cpp.x :Objects:Viewpoint.cpp.o	ƒ  ∂
	:Viewpoint.cpp ∂
	:Viewpoint.h ∂
	:Entity.h ∂
	:Header.h ∂
	:Params.h ∂
	:Vectors.h ∂
	:Draw.h ∂
	:Game.h

