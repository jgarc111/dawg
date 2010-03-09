#include "bool.h"

dawgBool::dawgBool(dawgPage* page,
				   const wxString& key,
				   bool def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	checkbox = new wxCheckBox(page->panel, wxID_ANY, wxEmptyString);
	checkbox->SetValue(def);
	label->SetMinSize(wxSize(LABEL_MIN_WIDTH, -1));
	page->sizer->Add(label, 0);
	page->sizer->Add(checkbox, 0);
}

bool dawgBool::GetValue()
{
	return checkbox->GetValue();
}

std::string dawgBool::GetTextValue()
{
	return checkbox->GetValue() ? "True" : "False";
}

dawgBool::~dawgBool(void)
{
}
