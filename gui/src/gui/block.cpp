#include "block.h"

dawgBlock::dawgBlock(dawgPage* page,
					 const wxString& key,
					 const std::string& def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	wxDef    = wxString(def.c_str(), wxConvUTF8);
	textctrl = new wxTextCtrl(page->panel,
		wxID_ANY, wxDef, wxDefaultPosition,
		wxSize(100, TEXT_BLOCK_HEIGHT), wxTE_MULTILINE);
	label->SetMinSize(wxSize(LABEL_MIN_WIDTH, -1));
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

std::string dawgBlock::GetValue()
{
	return textctrl->GetValue().c_str();
}

std::string dawgBlock::GetTextValue()
{
	return textctrl->GetValue().c_str();
}

dawgBlock::~dawgBlock(void)
{
}
