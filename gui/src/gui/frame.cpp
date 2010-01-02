#include "frame.h"

dawgFrame::dawgFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(360, 280))
{
	srand(123);//GetTickCount());
	Centre();
	pnlFrm  = new wxPanel(this);
	vbsFrm  = new wxBoxSizer(wxVERTICAL);
	pnlFrm->SetSizer(vbsFrm);

	nbMain  = new wxNotebook(pnlFrm, wxID_ANY);
	vbsFrm->Add(nbMain, 1, wxEXPAND | wxALL, 8);

	pnlSeq  = new wxPanel(nbMain);
	pnlSub  = new wxPanel(nbMain);
	pnlInd  = new wxPanel(nbMain);
	pnlMisc = new wxPanel(nbMain);

	nbMain->AddPage(pnlSeq, wxT("Sequence"), true);
	nbMain->AddPage(pnlSub, wxT("Substitution"));
	nbMain->AddPage(pnlInd, wxT("Indels"));
	nbMain->AddPage(pnlMisc, wxT("Miscellaneous"));

	// Sequence Panel

	vbsSeq    = new wxBoxSizer(wxVERTICAL);
	fgsSeq    = new wxFlexGridSizer(2, 2, 8, 8);
	vbsSeq->Add(fgsSeq, 1, wxEXPAND | wxALL, 10);
	pnlSeq->SetSizer(vbsSeq);

	stSeqTree = new wxStaticText(pnlSeq, wxID_ANY, wxT("Tree:"));
	stSeqLen  = new wxStaticText(pnlSeq, wxID_ANY, wxT("Length:"));
	tcSeqTree = new wxTextCtrl(pnlSeq, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxSize(-1, 60), wxTE_MULTILINE);
	tcSeqTree->SetLabel(wxT("Test"));
	tcSeqLen  = new wxTextCtrl(pnlSeq, wxID_ANY, wxT("100"), wxDefaultPosition, wxSize(80, 18));
	fgsSeq->Add(stSeqTree);
	fgsSeq->Add(tcSeqTree, 1, wxEXPAND);
	fgsSeq->Add(stSeqLen);
	fgsSeq->Add(tcSeqLen, 1, wxEXPAND);
	fgsSeq->AddGrowableRow(0, 1);
	fgsSeq->AddGrowableCol(1, 1);

	// Substitution Panel

	vbsSub      = new wxBoxSizer(wxVERTICAL);
	fgsSub      = new wxFlexGridSizer(5, 2, 8, 8);
	vbsSub->Add(fgsSub, 1, wxEXPAND | wxALL, 10);
	pnlSub->SetSizer(vbsSub);

	stSubModel  = new wxStaticText(pnlSub, wxID_ANY, wxT("Model:"));
	stSubParams = new wxStaticText(pnlSub, wxID_ANY, wxT("Params:"));
	stSubACGT   = new wxStaticText(pnlSub, wxID_ANY, wxT("ACGT:"));
	stSubGamma  = new wxStaticText(pnlSub, wxID_ANY, wxT("Gamma:"));
	stSubIota   = new wxStaticText(pnlSub, wxID_ANY, wxT("Iota:"));

	wxString asSubModels[] = {wxT("Felsenstein 1981"), wxT("Felsenstein 1984"),
		wxT("General Time Reversible"), wxT("Hasegawa, Kishino, and Yano"), wxT("Jukes and Cantor"),
		wxT("Kimura Two Parameter"), wxT("Kimura Three Parameter"), wxT("Tamura and Nei")};
	chSubModel = new wxChoice(pnlSub, wxID_ANY, wxDefaultPosition, wxDefaultSize, 8, asSubModels);
	chSubModel->SetSelection(4);	// Jukes and Cantor

	tcSubParam1 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(32, 18));
	tcSubParam2 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(32, 18));
	tcSubParam3 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(32, 18));
	tcSubParam4 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(32, 18));
	tcSubParam5 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(32, 18));
	tcSubParam6 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(32, 18));
	hbsSubParams = new wxBoxSizer(wxHORIZONTAL);
	hbsSubParams->Add(tcSubParam1);
	hbsSubParams->Add(tcSubParam2);
	hbsSubParams->Add(tcSubParam3);
	hbsSubParams->Add(tcSubParam4);
	hbsSubParams->Add(tcSubParam5);
	hbsSubParams->Add(tcSubParam6);

	tcSubACGT1 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("0.25"), wxDefaultPosition, wxSize(32, 18));
	tcSubACGT2 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("0.25"), wxDefaultPosition, wxSize(32, 18));
	tcSubACGT3 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("0.25"), wxDefaultPosition, wxSize(32, 18));
	tcSubACGT4 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("0.25"), wxDefaultPosition, wxSize(32, 18));
	hbsSubACGT = new wxBoxSizer(wxHORIZONTAL);
	hbsSubACGT->Add(tcSubACGT1);
	hbsSubACGT->Add(tcSubACGT2);
	hbsSubACGT->Add(tcSubACGT3);
	hbsSubACGT->Add(tcSubACGT4);

	tcSubGamma = new wxTextCtrl(pnlSub, wxID_ANY, wxT("0.0"), wxDefaultPosition, wxSize(64, 18));
	tcSubIota  = new wxTextCtrl(pnlSub, wxID_ANY, wxT("0.0"), wxDefaultPosition, wxSize(64, 18));

	fgsSub->Add(stSubModel);
	fgsSub->Add(chSubModel);
	fgsSub->Add(stSubParams);
	fgsSub->Add(hbsSubParams);
	fgsSub->Add(stSubACGT);
	fgsSub->Add(hbsSubACGT);
	fgsSub->Add(stSubGamma);
	fgsSub->Add(tcSubGamma);
	fgsSub->Add(stSubIota);
	fgsSub->Add(tcSubIota);
	fgsSub->AddGrowableCol(1, 1);

	// Indels Panel

	vbsInd       = new wxBoxSizer(wxVERTICAL);
	pnlInd->SetSizer(vbsInd);

	fgsInd       = new wxFlexGridSizer(3, 2, 8, 8);
	vbsInd->Add(fgsInd, 0, wxEXPAND | wxALL, 10);

	stIndLambda  = new wxStaticText(pnlInd, wxID_ANY, wxT("Lambda:"));
	stIndModel   = new wxStaticText(pnlInd, wxID_ANY, wxT("Model:"));
	stIndParams  = new wxStaticText(pnlInd, wxID_ANY, wxT("Params:"));

	wxString asIndModels[] = {wxT("Negative Binomial"), wxT("Power Law")};
	chIndModel   = new wxChoice(pnlInd, wxID_ANY, wxDefaultPosition, wxDefaultSize, 2, asIndModels);
	chIndModel->SetSelection(1);	// Power Law

	tcIndLambda  = new wxTextCtrl(pnlInd, wxID_ANY, wxT("0.0"), wxDefaultPosition, wxSize(72, 18));
	tcIndParam1  = new wxTextCtrl(pnlInd, wxID_ANY, wxT("1.5"), wxDefaultPosition, wxSize(36, 18));
	tcIndParam2  = new wxTextCtrl(pnlInd, wxID_ANY, wxT("100"), wxDefaultPosition, wxSize(36, 18));
	hbsIndParams = new wxBoxSizer(wxHORIZONTAL);
	hbsIndParams->Add(tcIndParam1);
	hbsIndParams->Add(tcIndParam2);

	cbIndVerbose = new wxCheckBox(pnlInd, wxID_ANY, wxT(" Verbose"));
	cbIndHideLen = new wxCheckBox(pnlInd, wxID_ANY, wxT(" Hide Length"));
	hbsIndCb     = new wxBoxSizer(wxHORIZONTAL);
	vbsInd->Add(hbsIndCb, 0, wxLEFT | wxRIGHT | wxBOTTOM, 10);
	hbsIndCb->Add(cbIndVerbose, 0, wxRIGHT, 16);
	hbsIndCb->Add(cbIndHideLen, 1);

	fgsInd->Add(stIndLambda);
	fgsInd->Add(tcIndLambda);
	fgsInd->Add(stIndModel);
	fgsInd->Add(chIndModel);
	fgsInd->Add(stIndParams);
	fgsInd->Add(hbsIndParams);
	fgsInd->AddGrowableCol(1, 1);

	// Miscellaneous Panel

	vbsMisc      = new wxBoxSizer(wxVERTICAL);
	pnlMisc->SetSizer(vbsMisc);

	fgsMisc      = new wxFlexGridSizer(3, 2, 8, 8);

	stMiscReps   = new wxStaticText(pnlMisc, wxID_ANY, wxT("Reps:"));
	scMiscReps   = new wxSpinCtrl(pnlMisc, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize(72, 18), wxSP_ARROW_KEYS, 1, 1000000);

	stMiscSeed   = new wxStaticText(pnlMisc, wxID_ANY, wxT("Seed:"));
	hbsMiscSeed  = new wxBoxSizer(wxHORIZONTAL);
	tcMiscSeed   = new wxTextCtrl(pnlMisc, wxID_ANY, wxString::Format(wxT("%ld"), rand()), wxDefaultPosition, wxSize(72, 18));
	btnMiscSeed  = new wxButton(pnlMisc, wxID_ANY, wxT("Random"));
	hbsMiscSeed->Add(tcMiscSeed, 0, wxRIGHT, 10);
	hbsMiscSeed->Add(btnMiscSeed);

	stMiscFormat = new wxStaticText(pnlMisc, wxID_ANY, wxT("Format:"));
	wxString asMiscFormats[] = {wxT("Clustal"), wxT("Fasta"), wxT("Nexus"), wxT("Phylip")};
	chMiscFormat = new wxChoice(pnlMisc, wxID_ANY, wxDefaultPosition, wxDefaultSize, 2, asMiscFormats);
	chMiscFormat->SetSelection(0);	// Clustal

	cbMiscInFile = new wxCheckBox(pnlMisc, wxID_ANY, wxT(" Input File"));
	cbMiscSvFile = new wxCheckBox(pnlMisc, wxID_ANY, wxT(" Save to File"));
	hbsMiscCb    = new wxBoxSizer(wxHORIZONTAL);
	hbsMiscCb->Add(cbMiscInFile, 0, wxRIGHT, 16);
	hbsMiscCb->Add(cbMiscSvFile, 1);

	fgsMisc->Add(stMiscReps);
	fgsMisc->Add(scMiscReps);
	fgsMisc->Add(stMiscSeed);
	fgsMisc->Add(hbsMiscSeed);
	fgsMisc->Add(stMiscFormat);
	fgsMisc->Add(chMiscFormat);
	fgsMisc->AddGrowableCol(1, 1);
	vbsMisc->Add(fgsMisc, 0, wxEXPAND | wxALL, 10);
	vbsMisc->Add(hbsMiscCb, 0, wxLEFT | wxRIGHT | wxBOTTOM, 10);

	// Bottom: Buttons

	hbsBottom = new wxBoxSizer(wxHORIZONTAL);

	btnSubmit = new wxButton(pnlFrm, wxID_EXIT, wxT("Submit"), wxPoint(20, 400), wxDefaultSize);
	btnSubmit->SetFocus();
	btnExit = new wxButton(pnlFrm, wxID_EXIT, wxT("Exit"), wxPoint(20, 400), wxDefaultSize);
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(dawgFrame::OnButtonExit));
	
	hbsBottom->Add(btnSubmit, 0, wxLEFT, 10);
	hbsBottom->Add(btnExit, 0, wxLEFT, 10);
	
	vbsFrm->Add(hbsBottom, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);

	// Menu Bar

	menubarMain = new wxMenuBar;
	menuFile = new wxMenu;
	menuFile->Append(wxID_NEW, wxT("&New"));
	menuFile->Append(wxID_OPEN, wxT("&Open"));
	menuFile->Append(wxID_EXIT, wxT("&Save"));
	menuFile->Append(wxID_EXIT, wxT("Save &As..."));
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT, wxT("E&xit"));
	menubarMain->Append(menuFile, wxT("&File"));
	menuEdit = new wxMenu;
	menuEdit->Append(wxID_CUT, wxT("Cu&t"));
	menuEdit->Append(wxID_COPY, wxT("&Copy"));
	menuEdit->Append(wxID_PASTE, wxT("&Paste"));
	menuEdit->Append(wxID_DELETE, wxT("&Delete"));
	menubarMain->Append(menuEdit, wxT("&Edit"));
	menuHelp = new wxMenu;
	menuHelp->Append(wxID_HELP, wxT("&Help"));
	menuHelp->AppendSeparator();
	menuHelp->Append(wxID_ABOUT, wxT("&About"));
	menubarMain->Append(menuHelp, wxT("&Help"));
	SetMenuBar(menubarMain);
}

void dawgFrame::OnButtonExit(wxCommandEvent & WXUNUSED(event))
{
	Close(true);
}

dawgFrame::~dawgFrame(void)
{
}
