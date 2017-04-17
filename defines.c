var ingame = 0;
var counter = 0;
var vSoundhandle;
var gvScore = 0;
VECTOR temp;
SOUND* sndDie 		= "die.wav";
SOUND* sndFlupp 	= "flup.wav";
SOUND* sndKlonk 	= "klonk1.wav";
SOUND* sndBumbum	= "inf.wav";
FONT* fontVerdana	= "Verdana#20b";
function Targeting();
function StartGame();

BMAP* bmapMouseMap = "mousemap1.tga";
BMAP* bnLotterOn   = "bPlayOn.tga";
BMAP* bnLotterOff	 = "bPlayOff.tga";

PANEL* pnlScore =
{
	layer = 10;
	pos_x = 10;
	pos_y = 10;
	digits( 0,  0, "Your Score:", fontVerdana, 0,       0); 
	digits(10, 30,             3, fontVerdana, 1, gvScore);
}

PANEL* pnlMenu =
{
	layer = 9;
	layer = 10;
	bmap = bnLotterOn;
	pos_x = 0;
	pos_y = 0;
	button = 0,0,bnLotterOn,bnLotterOff,bnLotterOn,SetIngame,NULL,NULL;
	flags = SHOW;
}

PANEL* pnlLotter =
{
	bmap = "jcl2.tga";
	layer = 8;
	event = PicDataFileOpen;
	flags = SHOW;		
}

PANEL* pnl16tons =
{
	layer = 11;
	bmap = "16tons.tga";
	flags = SHOW;
}


