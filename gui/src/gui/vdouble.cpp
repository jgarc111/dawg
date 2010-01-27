#include "vdouble.h"

dawgVDouble::dawgVDouble(dawgPage* page,
						 const wxString& key,
						 const std::vector<double>& def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	wxString wxDef; // How to convert std::vector<double> into std::string?
	textctrl = new wxTextCtrl(page->panel, wxID_ANY, wxDef);
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

dawgVDouble::~dawgVDouble(void)
{
}
