#pragma once
#include <string>
#include <wx/app.h>
#include "frame.h"
#include "page.h"
#include "text.h"
#include "double.h"
#include "bool.h"

template<typename t>
struct dawg_gui_type {
};
template<>
struct dawg_gui_type<bool> {
	typedef dawgBool type;
	typedef bool default_type;
};
template<>
struct dawg_gui_type<std::string> {
	typedef dawgText type;
	typedef std::string default_type;
};
template<>
struct dawg_gui_type<double> {
	typedef dawgDouble type;
	typedef double default_type;
};
template<>
struct dawg_gui_type<unsigned int> {
	typedef dawgDouble type;
	typedef double default_type;
};

class DawgGUI : public wxApp
{
public:
	DawgGUI();
	virtual bool OnInit();
	dawgFrame *frame;
	dawgPage  *subst, *indel, *root, *output, *sim, *tree;
	
	#define XM(name, atype, def) dawg_gui_type< atype >::type* _V(name);
	#include "dawgma.xmh"
	#undef XM
	
	virtual ~DawgGUI();
};
