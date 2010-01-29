#pragma once
#include <string>
#include <vector>
#include <wx/wx.h>
#include <boost/algorithm/string/join.hpp>
#include "page.h"

class dawgVText
{
public:
	dawgVText(dawgPage* page,
		const wxString& key,
		const std::vector<std::string>& def);
	~dawgVText(void);

private:
	wxStaticText *label;
	wxTextCtrl   *textctrl;
	wxString     wxDef;
};
