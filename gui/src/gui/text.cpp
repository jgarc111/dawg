#include "text.h"

dawgText::dawgText(dawgPage* page, const wxString& key, const std::string& def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	wxDef    = wxString(def.c_str(), wxConvUTF8);
	textctrl = new wxTextCtrl(page->panel, wxID_ANY, wxDef);
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

dawgText::~dawgText(void)
{
}
