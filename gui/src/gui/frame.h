#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/spinctrl.h>

class dawgFrame :
	public wxFrame
{
private:
	void OnButtonExit(wxCommandEvent& eventQuit);
	wxNotebook *nbMain;
	wxPanel *pnlFrm, *pnlSeq, *pnlSub, *pnlInd, *pnlMisc;
	wxBoxSizer *vbsFrm, *vbsNb, *vbsSeq, *vbsSub, *vbsInd, *vbsMisc,
		*hbsSubParams, *hbsSubACGT, *hbsIndParams, *hbsIndCb,
		*hbsMiscCb, *hbsMiscSeed, *hbsBottom;
	wxFlexGridSizer *fgsSeq, *fgsSub, *fgsInd, *fgsMisc;
	wxStaticBoxSizer *sbsSeq, *sbsSub, *sbsInd, *sbsMisc;
	wxStaticText *stSeqTree, *stSeqLen,
		*stSubModel, *stSubParams, *stSubACGT, *stSubGamma, *stSubIota,
		*stIndLambda, *stIndModel, *stIndParams,
		*stMiscReps, *stMiscSeed, *stMiscFormat;
	wxChoice *chSubModel, *chIndModel, *chMiscFormat;
	wxTextCtrl *tcSeqTree, *tcSeqLen,
		*tcSubParam1, *tcSubParam2, *tcSubParam3,
		*tcSubParam4, *tcSubParam5, *tcSubParam6,
		*tcSubACGT1, *tcSubACGT2, *tcSubACGT3, *tcSubACGT4,
		*tcSubGamma, *tcSubIota,
		*tcIndLambda, *tcIndParam1, *tcIndParam2,
		*tcMiscReps, *tcMiscSeed;
	wxSpinCtrl *scMiscReps;
	wxCheckBox *cbIndVerbose, *cbIndHideLen, *cbMiscInFile, *cbMiscSvFile;
	wxButton *btnSubmit, *btnExit, *btnMiscSeed;
	wxMenuBar *menubarMain;
	wxMenu *menuFile, *menuEdit, *menuHelp;

public:
	dawgFrame(const wxString& title);
	~dawgFrame(void);

	wxNotebook* GetNotebook() { return nbMain; }
};
