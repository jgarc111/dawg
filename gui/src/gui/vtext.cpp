#include "vtext.h"

dawgVText::dawgVText(dawgPage* page,
					 const wxString& key,
					 const std::vector<std::string>& def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	wxDef    = wxString(boost::algorithm::join(def, ", ").c_str(), wxConvUTF8);
	textctrl = new wxTextCtrl(page->panel, wxID_ANY, wxDef);
	label->SetMinSize(wxSize(LABEL_MIN_WIDTH, -1));
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

std::vector<std::string> dawgVText::GetValue()
{
	std::string val(textctrl->GetValue());
	std::vector<std::string> vec;
	boost::split(vec, val, boost::is_any_of(","));
	return vec;
}

std::string dawgVText::GetTextValue()
{
	return textctrl->GetValue().c_str();
}

dawgVText::~dawgVText(void)
{
}
