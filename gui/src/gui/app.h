#ifndef DAWG_GUI_H
#define DAWG_GUI_H

#include <string>
#include <memory>

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
	std::auto_ptr<dawgFrame> frame;
	std::auto_ptr<dawgPage> subst, indel, root, output, sim, tree;
	
#define XM(name, atype, def) std::auto_ptr<dawg_gui_type< atype >::type> _V(name) ;
#include "dawgma.xmh"
#undef XM
	
	virtual ~DawgGUI();
};

#endif // APP_H
