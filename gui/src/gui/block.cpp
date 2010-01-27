#include "block.h"

dawgBlock::dawgBlock(dawgPage* page, const wxString& key, const std::string& def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	wxString wxDef(def.c_str(), wxConvUTF8);
	textctrl = new wxTextCtrl(page->panel,
		wxID_ANY, wxDef, wxDefaultPosition,
		wxSize(100, BLOCK_HEIGHT), wxTE_MULTILINE);
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

dawgBlock::~dawgBlock(void)
{
}
