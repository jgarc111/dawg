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
	~dawgVDouble(void);

private:
	wxStaticText *label;
	wxTextCtrl   *textctrl;
};
