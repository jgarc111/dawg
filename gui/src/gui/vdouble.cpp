#include "vdouble.h"

dawgVDouble::dawgVDouble(dawgPage* page,
						 const wxString& key,
						 const std::vector<double>& def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	for (unsigned int i = 0; i < def.size(); i ++)
		vstrDef.push_back(boost::lexical_cast<std::string>(def.at(i)));
	wxDef    = wxString(boost::algorithm::join(vstrDef, ", ").c_str(), wxConvUTF8);
	textctrl = new wxTextCtrl(page->panel, wxID_ANY, wxDef);
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

dawgVDouble::~dawgVDouble(void)
{
}
