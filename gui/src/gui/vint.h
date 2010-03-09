#pragma once
#include <string>
#include <vector>
#include <wx/wx.h>
#include <boost/algorithm/string/join.hpp>
#include <boost/lexical_cast.hpp>
#include "page.h"

class dawgVInt
{
public:
	dawgVInt(dawgPage* page,
		const wxString& key,
		const std::vector<unsigned int>& def);
	std::vector<unsigned int> GetValue();
	std::string GetTextValue();
	~dawgVInt(void);

private:
	wxStaticText *label;
	wxTextCtrl   *textctrl;
	std::vector<std::string> vstrDef;
	wxString wxDef;
};
