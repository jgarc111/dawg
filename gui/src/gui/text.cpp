#include "text.h"

dawgText::dawgText(dawgPage* page,
				   const wxString& key,
				   const std::string& def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	wxDef    = wxString(def.c_str(), wxConvUTF8);
	textctrl = new wxTextCtrl(page->panel, wxID_ANY, wxDef);
	label->SetMinSize(wxSize(LABEL_MIN_WIDTH, -1));
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

std::string dawgText::GetValue()
{
	return textctrl->GetValue().c_str();
}

std::string dawgText::GetTextValue()
{
	return textctrl->GetValue().c_str();
}

dawgText::~dawgText(void)
{
}
