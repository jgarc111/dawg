#include "vint.h"

dawgVInt::dawgVInt(dawgPage* page,
				   const wxString& key,
				   const std::vector<unsigned int>& def)
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

std::vector<unsigned int> dawgVInt::GetValue()
{
	std::string val(textctrl->GetValue());
	std::vector<unsigned int> vec(val.begin(), val.end());
	return vec;
}

std::string dawgVInt::GetTextValue()
{
	return textctrl->GetValue().c_str();
}

dawgVInt::~dawgVInt(void)
{
}
