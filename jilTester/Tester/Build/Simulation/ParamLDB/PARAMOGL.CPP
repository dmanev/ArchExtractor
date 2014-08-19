
#include "config.h"
#ifdef IHM_OPENGL

#include "stdafx.h"
#include "DefTypes.h"
#include "gl\glu.h"
/*--------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/
extern "C" void JGLRefreshScreen();

#define cMAX_SCREEN	((U8)0xFF)

// Screen Option
#define	cSCR_AUTO_SAVE_POS	0x00000001
#define	cSCR_AUTO_REFRESH	0x00000010

/*--------------------------------------------------------------------------
  Exported types

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  --------------------------------------------------------------------------*/

typedef struct
{
	U32 screenId;
	U8 * pName;
	U32 x;
	U32 y;
	U32 cx;
	U32 cy;
	U32 option;
	U32 refreshPeriodMs;
	CWnd * pParent;
} tScreen;

static int cx = 400;
static int cy = 300;
static int y = 60;

extern "C" __declspec(dllimport) void JGLCreateScreen(tScreen *);
extern "C" __declspec(dllimport) void JGLSelectScreenId(U8 Id);

extern "C" void JGLInit()
{
	glViewport(0,0,cx,cy);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)cx/(GLfloat)cy,0.1f,300.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glTranslated(0.0,0.0,-100.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
	JGLRefreshScreen();
}

void OpenGl_Init_Param(void)
{
	tScreen SCR;
	U8 Left[] = {"Left Screen"};
	U8 Right[] = {"Right Screen"};

	SCR.screenId = 0;
	SCR.x	= 0;
	SCR.y	= y;
	SCR.cx	= cx;
	SCR.cy	= cy;
	SCR.pName = Left;
	SCR.option = 0;
	SCR.refreshPeriodMs = 10;
	SCR.pParent = AfxGetApp()->GetMainWnd();

	JGLCreateScreen(&SCR);

	SCR.screenId = 1;
	SCR.x	= cx;
	SCR.y	= y;
	SCR.cx	= cx;
	SCR.cy	= cy;
	SCR.pName = Right;
	SCR.option = 0;
	SCR.refreshPeriodMs = 10;
	SCR.pParent = AfxGetApp()->GetMainWnd();

	JGLCreateScreen(&SCR);

	JGLSelectScreenId(1);
	JGLInit();
	
	JGLSelectScreenId(0);
	JGLInit();

	wglMakeCurrent(NULL,NULL);
}
#endif



