#include "vint.h"

dawgVInt::dawgVInt(dawgPage* page,
				   const wxString& key,
				   const std::vector<unsigned int>& def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	wxString wxDef; // How to convert std::vector<unsigned int> into std::string?
	textctrl = new wxTextCtrl(page->panel, wxID_ANY, wxDef);
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

dawgVInt::~dawgVInt(void)
{
}
