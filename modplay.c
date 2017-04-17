/////////////////////////////////////////////////////////////////////////
// Wrapper for bass.dll - Version 1.0 (03/31/02) update 12/18/05	   //
// created by Firoball - http://www.firoball.de - master@firoball.de   //
/////////////////////////////////////////////////////////////////////////

var mod_load(var x,var y);
var mod_init(var x,var y);
var mod_unload();
var mod_play(var x);
var mod_stop(var x);
var mod_volume(var x);
var mod_getname(var x,var y);
var mod_amplify(var x,var y);
var mod_pause(var x);
var mod_resume(var x);

//Frequency Options
#define MOD_LOWFREQ		11025
#define MOD_MEDFREQ		22050
#define MOD_HIGHFREQ	44100 //default;


//Quality Flags (default: all turned off)
#define MOD_INIT8BIT	1	//8Bit playback for slow systems
#define MOD_INITMONO	2	//Mono playback for even slower systems
#define MOD_INIT3D		4	//3D playback for faster system
#define MOD_INITNOSYNC	8 	//turn this flag on to spare cpu time,
 							//but some mods won't work

//MOD Playback Flags (default: all turned off)
#define MOD_LOADLOOP	4		//Loop MOD until stopped
#define MOD_LOADSURROUND 512	//Enable Surround


var mod_handle;
STRING* MOD_Filename = "blirg.mod";


void music_start();
void music_stop();

void music_start()
{
//	mod_volume(20);
	mod_init(MOD_HIGHFREQ,MOD_INIT3D);
	mod_handle=mod_load(MOD_Filename,MOD_LOADLOOP+MOD_LOADSURROUND);
	mod_play(mod_handle);
}

void music_stop()
{
	mod_stop(mod_handle);
}

