#include "double.h"

dawgDouble::dawgDouble(dawgPage* page,
				   const wxString& key,
				   double d)
{
	hbox       = new wxBoxSizer(wxHORIZONTAL);
	statictext = new wxStaticText(page->panel, wxID_ANY, key);
	wxString value = wxString::Format(wxT("%f"), d);
	textctrl   = new wxTextCtrl(page->panel, wxID_ANY, value);
	hbox->Add(statictext, 0, wxLEFT, 10);
	hbox->Add(textctrl, 0, wxLEFT, 10);
	page->vbox->Add(hbox, 1, wxALIGN_LEFT | wxLEFT | wxBOTTOM, 10);
}

dawgDouble::~dawgDouble(void)
{
	delete statictext;
	delete textctrl;
	delete hbox;
}
