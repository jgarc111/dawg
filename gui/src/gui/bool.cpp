#include "bool.h"

dawgBool::dawgBool(dawgPage* page, const wxString& key, bool def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	checkbox = new wxCheckBox(page->panel, wxID_ANY, wxEmptyString);
	checkbox->SetValue(def);
	page->sizer->Add(label, 0);
	page->sizer->Add(checkbox, 0);
}

dawgBool::~dawgBool(void)
{
	delete label, checkbox;
}
