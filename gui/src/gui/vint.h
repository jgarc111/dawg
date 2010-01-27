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
	~dawgVInt(void);

private:
	wxStaticText *label;
	wxTextCtrl   *textctrl;
};
