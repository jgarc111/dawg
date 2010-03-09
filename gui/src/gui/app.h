#pragma once
#include <string>
#include <vector>
#include <wx/app.h>
#include "frame.h"
#include "page.h"
#include "text.h"
#include "int.h"
#include "double.h"
#include "bool.h"
#include "block.h"
#include "vtext.h"
#include "vint.h"
#include "vdouble.h"

class DawgGUI : public wxApp
{
public:
	DawgGUI();
	virtual bool OnInit();
	virtual int OnExit();
	dawgFrame *frame;
	dawgPage  *subst, *indel, *root, *output, *sim, *tree;
	
	#define XM(name, ctype, gtype, def) gtype* _V(name);
	#include "dawgma.xmh"
	#undef XM
	
	virtual ~DawgGUI();
};
