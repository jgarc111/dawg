#include "text.h"

dawgText::dawgText(dawgPage* page,
				   const wxString& key,
				   const wxString& value)
{
	hbsText = new wxBoxSizer(wxHORIZONTAL);
	stKey   = new wxStaticText(page->pnlPage, wxID_ANY, key);
	tcValue = new wxTextCtrl(page->pnlPage, wxID_ANY, value);
	//hbsText->Add(stKey, 0, wxLEFT, 10);
	//hbsText->Add(tcValue, 0, wxLEFT, 10);
	page->vbsPage->Add(stKey, 0, wxLEFT, 100);
	page->vbsPage->Add(hbsText, 1, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);
}

dawgText::~dawgText(void)
{
}