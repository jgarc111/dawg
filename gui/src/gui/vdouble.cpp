#include "vdouble.h"

dawgVDouble::dawgVDouble(dawgPage* page,
						 const wxString& key,
						 const std::vector<double>& def)
{
	label    = new wxStaticText(page->panel, wxID_ANY, key);
	for (unsigned int i = 0; i < def.size(); i ++)
		vstrDef.push_back(boost::lexical_cast<std::string>(def.at(i)));
	wxDef    = wxString(boost::algorithm::join(vstrDef, ", ").c_str(), wxConvUTF8);
	textctrl = new wxTextCtrl(page->panel, wxID_ANY, wxDef);
	label->SetMinSize(wxSize(LABEL_MIN_WIDTH, -1));
	page->sizer->Add(label, 0);
	page->sizer->Add(textctrl, 1, wxEXPAND);
}

std::vector<double> dawgVDouble::GetValue()
{
	std::string val(textctrl->GetValue());
	std::vector<double> vec(val.begin(), val.end());
	return vec;
}

std::string dawgVDouble::GetTextValue()
{
	return textctrl->GetValue().c_str();
}

dawgVDouble::~dawgVDouble(void)
{
}
