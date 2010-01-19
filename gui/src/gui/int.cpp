#include "int.h"

dawgIntegar::dawgIntegar(dawgPage* page, const wxString& key, int def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	wxString wxDef = wxString::Format(wxT("%d"), def);
	textctrl = new wxTextCtrl(page->panel, wxID_ANY, wxDef);
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

dawgIntegar::~dawgIntegar(void)
{
}
