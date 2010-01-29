#include "double.h"

dawgDouble::dawgDouble(dawgPage* page, const wxString& key, double def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	wxDef    = wxString::Format(wxT("%f"), def);
	textctrl = new wxTextCtrl(page->panel, wxID_ANY, wxDef);
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

dawgDouble::~dawgDouble(void)
{
}
