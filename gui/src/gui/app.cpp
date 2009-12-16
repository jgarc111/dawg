#include "app.h"

IMPLEMENT_APP( DawgGUI );

DawgGUI::DawgGUI()
{

}

bool DawgGUI::OnInit()
{
	frame.reset(new dawgFrame(wxT("Dawg Test Frame")));
	
	subst.reset(new dawgPage(frame.get(), wxT("Subst")));	
	indel.reset(new dawgPage(frame.get(), wxT("Indel")));	
	root.reset(new dawgPage(frame.get(), wxT("Root")));	
	output.reset(new dawgPage(frame.get(), wxT("Ouput")));	
	sim.reset(new dawgPage(frame.get(), wxT("Sim")));	
	tree.reset(new dawgPage(frame.get(), wxT("Tree")));	
	
	#define XM(name, atype, def) _V(name).reset(new dawg_gui_type< atype >::type( \
		BOOST_PP_SEQ_HEAD(name).get(), wxT(_S(BOOST_PP_SEQ_TAIL(name))), \
		dawg_gui_type< atype >::default_type(def))) ;
	#include "dawgma.xmh"
	#undef XM

	frame->Show(true);
	return true;
}

DawgGUI::~DawgGUI()
{

}
