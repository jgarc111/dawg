#include "vtext.h"

dawgVText::dawgVText(dawgPage* page,
					 const wxString& key,
					 const std::vector<std::string>& def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	wxString wxDef(boost::algorithm::join(def, ", ").c_str(), wxConvUTF8);
	textctrl = new wxTextCtrl(page->panel, wxID_ANY, wxDef);
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

dawgVText::~dawgVText(void)
{
}
