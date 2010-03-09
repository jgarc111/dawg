#include "int.h"

dawgIntegar::dawgIntegar(dawgPage* page,
						 const wxString& key,
						 unsigned int def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	wxDef    = wxString::Format(wxT("%d"), def);
	textctrl = new wxTextCtrl(page->panel, wxID_ANY, wxDef);
	label->SetMinSize(wxSize(LABEL_MIN_WIDTH, -1));
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

unsigned int dawgIntegar::GetValue()
{
	return wxAtoi(textctrl->GetValue());
}

std::string dawgIntegar::GetTextValue()
{
	return textctrl->GetValue().c_str();
}

dawgIntegar::~dawgIntegar(void)
{
}
