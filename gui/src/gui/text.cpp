#include "text.h"

dawgText::dawgText(dawgPage* page,
				   const wxString& key,
				   const wxString& value)
{
	hbox       = new wxBoxSizer(wxHORIZONTAL);
	statictext = new wxStaticText(page->panel, wxID_ANY, key);
	textctrl   = new wxTextCtrl(page->panel, wxID_ANY, value);
	hbox->Add(statictext, 0, wxALIGN_LEFT, 0);
	hbox->Add(textctrl, 1, wxALIGN_LEFT | wxLEFT, 10);
	page->vbox->Add(hbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, 10);
	//wxFlexGridSizer *fgs = new wxFlexGridSizer(1, 2, 8, 8);
	//page->vbox->Add(fgs, 0, wxEXPAND | wxALL, 10);
	//fgs->Add(statictext);
	//fgs->Add(textctrl);
}

dawgText::~dawgText(void)
{
	free(statictext);
	free(textctrl);
	free(hbox);
}
