#ifndef WXTEST_1PANEL_H
#define WXTEST_1PANEL_H

#include "gui.h"

class Panel : public MainPanel
{
public:
	Panel( wxWindow* parent );
	~Panel();

private:
	void OnOK( wxCommandEvent& event );
	DECLARE_EVENT_TABLE();
};

#endif //PANEL_H
