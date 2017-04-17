function SetIngame()
{
	var temp = 0;
	mouse_mode = 0;
	while(mouse_left)wait(1);	
	while(pnl16tons.pos_y < 68)
	{
		
		pnl16tons.pos_y+= temp*time_step;
		temp+= 3*time_step;
		wait(1);
	}
	snd_play(sndKlonk, 100, 0);
	pnl16tons.pos_y = 68;
	reset(pnlLotter, SHOW);
	wait(-1);
	snd_play(sndBumbum, 100, 0);
	wait(-2);
	ingame = 1;
	reset(pnlMenu, SHOW);
	reset(pnl16tons, SHOW);
	set(pnlScore, SHOW);
}





////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// windows.h / stdio.h

function SetDir()
{	
	// switch to executable directory	
	_chdir( work_dir.chars )  ;
}

STRING* GetCurDir(void)
{	
	STRING* curDir[MAX_PATH] ; 			
	_getcwd( curDir, (MAX_PATH-1) ) ;		
	return curDir ;
}
//
////////////////////////////////// Set current directory//////////////////////////////
//
void SetCurDir(STRING* pstrDir ) //( const char* pstrDir )
{	
	_chdir( pstrDir.chars ) ;

}
//
// File open / save dialog

typedef char WCHAR;
OPENFILENAME  m_ofn;         
WCHAR m_szFileName[2000];
WCHAR m_szTitleName[2000];
WCHAR *szUntitled = "Unbenannt\0";
// Thanks JCL
DWORD __stdcall GetSaveFileName (DWORD);

void STDL_OpenFile_Init()
{	
	m_ofn.lStructSize       = sizeof(OPENFILENAME);	
	m_ofn.hwndOwner         = NULL;	
	m_ofn.hInstance         = NULL;	
	m_ofn.lpstrFilter       = NULL;            // Set in Open and Save functions	
	m_ofn.lpstrCustomFilter = NULL;	
	m_ofn.nMaxCustFilter    = 0;	
	m_ofn.nFilterIndex      = 0;	
	m_ofn.lpstrFile         = m_szFileName;   // Set to member variable address      	
	m_ofn.nMaxFile          = 2000;	
	m_ofn.lpstrFileTitle    = m_szTitleName;   // Set to member variable address 	
	m_ofn.nMaxFileTitle     = 2000;	
	m_ofn.lpstrInitialDir   = NULL;	
	m_ofn.lpstrTitle        = NULL;           // Set in Open and Save functions	
	m_ofn.Flags             = NULL;   	
	m_ofn.nFileOffset       = 0;	
	m_ofn.nFileExtension    = 0;	
	m_ofn.lpstrDefExt       = NULL;          // Set in Open and Save functions	
	m_ofn.lCustData         = 0 ;	
	m_ofn.lpfnHook          = NULL;	
	m_ofn.lpTemplateName    = NULL;
}

BOOL STDL_OpenFile_OpenDialog(char* szFilter, char* szDefExt, char* szDlgTitle, BOOL fMultSel)
{	
	m_szFileName[0] = m_szTitleName[0] = (WCHAR)'\0';	
	m_ofn.lpstrFilter = szFilter;	
	m_ofn.lpstrDefExt = szDefExt;	
	m_ofn.lpstrTitle  = szDlgTitle;	
	if(fMultSel)  // allows multiple file selection		
		m_ofn.Flags = OFN_EXPLORER |OFN_ALLOWMULTISELECT;	
	GetOpenFileName(&m_ofn);
}

BOOL STDL_OpenFile_SaveDialog(char* szFilter, char* szDefExt, char* szDlgTitle)
{	
	m_szFileName[0] = m_szTitleName[0] = (WCHAR)'\0';	
	int i;	
	for(i = 0; i <= 10; i++)		
		m_szFileName[i] = m_szTitleName[i] = szUntitled[i];	
	m_ofn.lpstrFilter = szFilter;	
	m_ofn.lpstrDefExt = szDefExt;	
	m_ofn.lpstrTitle  = szDlgTitle;	
	m_ofn.Flags       = OFN_OVERWRITEPROMPT;	
	GetSaveFileName(&m_ofn);
}

char* STDL_OpenFile_GetFilePath()
{	
	return (char*) m_ofn.lpstrFile;
}



function ExpCreateFolder(STRING* folder)
{
	return(CreateDirectory(folder,NULL));
}


function PicDataFileOpen()
{
	STRING* szFilename = "#6";
	var vVideoScreen = 0;
	var vFilehandle;
	SetDir();
	wait(1);
	if(STDL_OpenFile_OpenDialog("tga 32bit(*.tga)\0*.tga\0" , "tga", "32bit tga with alphachannel please...", 0))
	{
		pnlLotter.bmap = bmap_create(_str(m_szFileName));
		pnlLotter.size_x = bmap_width(pnlLotter.bmap);
		pnlLotter.size_y = bmap_height(pnlLotter.bmap);	
		pnlLotter.scale_x = 128/pnlLotter.size_x;
		pnlLotter.scale_y = 128/pnlLotter.size_y;
	}
}


////// Time Counter //////////////////////////
var count,ms,sc,mn = 0;
var start = 0;
PANEL* pnlTimer =
{
	pos_x = 10;
	pos_y = 70;
	layer = 9;
	digits(  0, 0, 3, fontVerdana, 1, mn);
	digits( 40, 0,":",fontVerdana, 0,  0);
	digits( 50, 0, 3, fontVerdana, 1, sc);
	digits( 90, 0,":",fontVerdana, 0,  0);	
	digits(100, 0, 3, fontVerdana, 1, ms);	
	flags = SHOW;
}

function TimerReset()
{
	start = total_ticks;
	count = 0;
	ms = 0;
	sc = 0;
	mn = 0;	
}

function TimerCount() 
{
	start = total_ticks;
	while (ingame) 
	{
		count = (total_ticks - start) / 16 * 1000;
		ms = integer(cycle (count,0,1000));
		sc = integer(cycle (count / 1000,0,60));
		mn = integer(cycle (count / 60000,0,60));
		wait(1);
	}
}

action Timer()
{
	set(my, PASSABLE | INVISIBLE);
	TimerCount();
}
