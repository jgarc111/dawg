#include "double.h"

dawgDouble::dawgDouble(dawgPage* page,
				   const wxString& key,
				   const wxString& value)
{
	hbox       = new wxBoxSizer(wxHORIZONTAL);
	statictext = new wxStaticText(page->panel, wxID_ANY, key);
	textctrl   = new wxTextCtrl(page->panel, wxID_ANY, value);
	hbox->Add(statictext, 0, wxLEFT, 10);
	hbox->Add(textctrl, 0, wxLEFT, 10);
	page->vbox->Add(hbox, 1, wxALIGN_LEFT | wxLEFT | wxBOTTOM, 10);
}

dawgDouble::~dawgDouble(void)
{
	free(statictext);
	free(textctrl);
	free(hbox);
}
