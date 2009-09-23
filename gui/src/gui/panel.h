#ifndef WXTEST_1PANEL_H
#define WXTEST_1PANEL_H

#include "gui.h"

class wxTest_1Panel : public MainPanel
{
public:
	wxTest_1Panel( wxWindow* parent );
	~wxTest_1Panel();

private:
	void OnOK( wxCommandEvent& event );
	DECLARE_EVENT_TABLE();
};

#endif //WXTEST_1PANEL_H
