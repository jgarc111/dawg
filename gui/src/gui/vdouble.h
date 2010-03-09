#pragma once
#include <string>
#include <vector>
#include <wx/wx.h>
#include <boost/algorithm/string/join.hpp>
#include <boost/lexical_cast.hpp>
#include "page.h"

class dawgVDouble
{
public:
	dawgVDouble(dawgPage* page,
		const wxString& key,
		const std::vector<double>& def);
	std::vector<double> GetValue();
	std::string GetTextValue();
	~dawgVDouble(void);

private:
	wxStaticText *label;
	wxTextCtrl   *textctrl;
	std::vector<std::string> vstrDef;
	wxString wxDef;
};
