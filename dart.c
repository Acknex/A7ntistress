// Infinite Lottery Antistress Tool
// Don´t try this at work!
// Version 1.2 now with target definition via file open dialog (only 32 bit tga with alphachannel) and time counter!
// Lots of magic numbers in there!
// Everything is open source
// Tested and developed with A7.85

///////////////////////////////
#include <acknex.h>
#include <default.c>
#include <windows.h>
#include <stdio.h>
#include "defines.c"
#include "menu.c"
#include "modplay.c"
#include "jcl.c"
#include "screen.c"
#include "conitec.c"
///////////////////////////////

function StartGame()
{
	var vCounter = 0;
	gvScore = 0;
	ingame = 0;
	mouse_mode = 1;
	pnlMenu.pos_x   = (screen_size.x*0.5)-(bmap_width(pnlMenu.bmap)*0.5);
	pnlMenu.pos_y   = (screen_size.y)-(bmap_height(pnlMenu.bmap))-10;
	pnlLotter.pos_x = (screen_size.x*0.5)-(bmap_width(pnlLotter.bmap)*0.5);
	pnlLotter.pos_y = (screen_size.y)-(bmap_height(pnlLotter.bmap))-bmap_height(pnlMenu.bmap)-10;
	pnl16tons.pos_x = (screen_size.x*0.5)-(bmap_width(pnl16tons.bmap)*0.5);
	reset(pnlScore, SHOW);
	pnl16tons.pos_y = -bmap_height(pnl16tons.bmap);
	set(pnlMenu, SHOW);
	set(pnlLotter, SHOW);
	set(pnl16tons, SHOW);
	while(!ingame)
	{
		vCounter+= 25*time_step;
		pnlLotter.pos_y = abs(sin(vCounter))*-20+200;
		wait(1);
	}	
	TimerReset();
	level_load("dart.WMB");	
	camera.x = -135;
	set(pnlScore, SHOW);
	Targeting(); // set up dart 
	music_start();	
	InitConitec();
}

function updateMouse()
{
	mouse_map = bmapMouseMap;
	while(1)
	{
		vec_set(mouse_pos.x, mouse_cursor.x);
		wait(1);
	}	
}

function main()
{
	video_screen = 2;
	video_mode = 7;
	snd_play(sndKlonk, 1, 0); // preload sounds in a dirty way ;)
	wait(1);
	video_window(NULL, NULL, 0, "::Infinite Lottery Antistress Tool Bielefeld 2010::");
	fps_max = 60;
	StartGame();
	skychange(); // change background color in a loop
 	updateMouse();
 	STDL_OpenFile_Init();
	on_exit = music_stop;	
}




