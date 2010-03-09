#include "double.h"

dawgDouble::dawgDouble(dawgPage* page,
					   const wxString& key,
					   double def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	wxDef    = wxString::Format(wxT("%f"), def);
	textctrl = new wxTextCtrl(page->panel, wxID_ANY, wxDef);
	label->SetMinSize(wxSize(LABEL_MIN_WIDTH, -1));
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

double dawgDouble::GetValue()
{
	double val = 0;
	textctrl->GetValue().ToDouble(&val);
	return val;
}

std::string dawgDouble::GetTextValue()
{
	return textctrl->GetValue().c_str();
}

dawgDouble::~dawgDouble(void)
{
}
