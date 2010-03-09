#include "app.h"

IMPLEMENT_APP( DawgGUI );

DawgGUI::DawgGUI()
{
}

template<class self>
struct self_type {
	typedef self type;
};

bool DawgGUI::OnInit()
{
	frame  = new dawgFrame(wxT("Dawg"));
	subst  = new dawgPage(frame, wxT("Subst"));	
	indel  = new dawgPage(frame, wxT("Indel"));	
	root   = new dawgPage(frame, wxT("Root"));	
	output = new dawgPage(frame, wxT("Ouput"));	
	sim    = new dawgPage(frame, wxT("Sim"));	
	tree   = new dawgPage(frame, wxT("Tree"));

	#define XM(name, ctype, gtype, def) _V(name) = \
		new gtype (BOOST_PP_SEQ_HEAD(name), \
		wxT(_S(BOOST_PP_SEQ_TAIL(name))), self_type< ctype >::type(def));
	#include "dawgma.xmh"
	#undef XM

	frame->Show(true);
	
	// Testing
	std::vector<std::string> vec = indel_model_ins->GetValue();
	std::string val(boost::algorithm::join(vec, ", ").c_str());
	wxMessageBox("Value = " + val, "Dawg Values Testing", wxOK, frame);

	return true;
}

int DawgGUI::OnExit()
{
	#define XM(name, ctype, gtype, def) delete _V(name);
	#include "dawgma.xmh"
	#undef XM
	delete subst, indel, root, output, sim, tree;
	return 0;
}

DawgGUI::~DawgGUI()
{
}
