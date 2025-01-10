all: stl

stl:    Chest/Chest.stl

PCBCase/case: PCBCase/case.c
	make -C PCBCase

%.stl: %.scad
	echo "Making $@"
	/Applications/OpenSCAD.app/Contents/MacOS/OpenSCAD $< -o $@
	echo "Made $@"

Chest/Chest.scad: Chest/Chest.kicad_pcb PCBCase/case Makefile
	PCBCase/case -o $@ $< --edge=2 --bottom=2 --top=7 --pcb=2

