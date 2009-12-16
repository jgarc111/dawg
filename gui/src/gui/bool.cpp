#include "bool.h"

dawgBool::dawgBool(dawgPage* page,
				   const wxString& key,
				   const bool value)
{
	hbox     = new wxBoxSizer(wxHORIZONTAL);
	checkbox = new wxCheckBox(page->panel, wxID_ANY, key);
	hbox->Add(checkbox, 0, wxLEFT, 10);
	page->vbox->Add(hbox, 1, wxALIGN_LEFT | wxLEFT | wxBOTTOM, 10);
}

dawgBool::~dawgBool(void)
{
	delete checkbox;
	delete hbox;
}
