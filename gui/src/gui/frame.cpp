#include "frame.h"

wxTestFrame::wxTestFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 750))
{
	Centre();
	panelMain = new wxPanel(this, wxID_ANY);
	vboxMain  = new wxBoxSizer(wxVERTICAL);

	// Box One: Sequence

	sbsSeq    = new wxStaticBoxSizer(wxVERTICAL, panelMain, wxT("Sequence"));
	fgsSeq    = new wxFlexGridSizer(2, 2, 8, 8);

	stSeqTree = new wxStaticText(panelMain, wxID_ANY, wxT("Tree:"));
	stSeqLen  = new wxStaticText(panelMain, wxID_ANY, wxT("Length:"));
	tcSeqTree = new wxTextCtrl(panelMain, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1, 60), wxTE_MULTILINE);
	tcSeqLen  = new wxTextCtrl(panelMain, wxID_ANY, wxT("100"), wxDefaultPosition, wxSize(80, 18));
	fgsSeq->Add(stSeqTree);
	fgsSeq->Add(tcSeqTree, 1, wxEXPAND);
	fgsSeq->Add(stSeqLen);
	fgsSeq->Add(tcSeqLen, 1, wxEXPAND);
	fgsSeq->AddGrowableRow(0, 1);
	fgsSeq->AddGrowableCol(1, 1);
	fgsSeq->SetItemMinSize((size_t)0, 64, -1);

	sbsSeq->Add(fgsSeq, 1, wxEXPAND | wxALL, 10);
	vboxMain->Add(sbsSeq, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);

	// Box Two: Substitution

	sbsSub      = new wxStaticBoxSizer(wxVERTICAL, panelMain, wxT("Substitution"));
	fgsSub      = new wxFlexGridSizer(5, 2, 8, 8);

	stSubModel  = new wxStaticText(panelMain, wxID_ANY, wxT("Model:"));
	stSubParams = new wxStaticText(panelMain, wxID_ANY, wxT("Params:"));
	stSubACGT   = new wxStaticText(panelMain, wxID_ANY, wxT("ACGT:"));
	stSubGamma  = new wxStaticText(panelMain, wxID_ANY, wxT("Gamma:"));
	stSubIota   = new wxStaticText(panelMain, wxID_ANY, wxT("Iota:"));

	wxString asSubModels[] = {wxT("Felsenstein 1981"), wxT("Felsenstein 1984"), wxT("General Time Reversible"), wxT("Hasegawa, Kishino, and Yano"),
		wxT("Jukes and Cantor"), wxT("Kimura Two Parameter"), wxT("Kimura Three Parameter"), wxT("Tamura and Nei")};
	chSubModel = new wxChoice(panelMain, wxID_ANY, wxDefaultPosition, wxSize(200, -1), 8, asSubModels);
	chSubModel->SetSelection(4);	// Jukes and Cantor

	tcSubParam1 = new wxTextCtrl(panelMain, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(36, 18));
	tcSubParam2 = new wxTextCtrl(panelMain, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(36, 18));
	tcSubParam3 = new wxTextCtrl(panelMain, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(36, 18));
	tcSubParam4 = new wxTextCtrl(panelMain, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(36, 18));
	tcSubParam5 = new wxTextCtrl(panelMain, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(36, 18));
	tcSubParam6 = new wxTextCtrl(panelMain, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(36, 18));
	hboxSubParams = new wxBoxSizer(wxHORIZONTAL);
	hboxSubParams->Add(tcSubParam1);
	hboxSubParams->Add(tcSubParam2);
	hboxSubParams->Add(tcSubParam3);
	hboxSubParams->Add(tcSubParam4);
	hboxSubParams->Add(tcSubParam5);
	hboxSubParams->Add(tcSubParam6);

	tcSubACGT1 = new wxTextCtrl(panelMain, wxID_ANY, wxT("0.25"), wxDefaultPosition, wxSize(36, 18));
	tcSubACGT2 = new wxTextCtrl(panelMain, wxID_ANY, wxT("0.25"), wxDefaultPosition, wxSize(36, 18));
	tcSubACGT3 = new wxTextCtrl(panelMain, wxID_ANY, wxT("0.25"), wxDefaultPosition, wxSize(36, 18));
	tcSubACGT4 = new wxTextCtrl(panelMain, wxID_ANY, wxT("0.25"), wxDefaultPosition, wxSize(36, 18));
	hboxSubACGT = new wxBoxSizer(wxHORIZONTAL);
	hboxSubACGT->Add(tcSubACGT1);
	hboxSubACGT->Add(tcSubACGT2);
	hboxSubACGT->Add(tcSubACGT3);
	hboxSubACGT->Add(tcSubACGT4);

	tcSubGamma = new wxTextCtrl(panelMain, wxID_ANY, wxT("0.0"), wxDefaultPosition, wxSize(72, 18));
	tcSubIota  = new wxTextCtrl(panelMain, wxID_ANY, wxT("0.0"), wxDefaultPosition, wxSize(72, 18));

	fgsSub->Add(stSubModel);
	fgsSub->Add(chSubModel);
	fgsSub->Add(stSubParams);
	fgsSub->Add(hboxSubParams);
	fgsSub->Add(stSubACGT);
	fgsSub->Add(hboxSubACGT);
	fgsSub->Add(stSubGamma);
	fgsSub->Add(tcSubGamma);
	fgsSub->Add(stSubIota);
	fgsSub->Add(tcSubIota);
	fgsSub->AddGrowableCol(1, 1);
	fgsSub->SetItemMinSize((size_t)0, 64, -1);

	sbsSub->Add(fgsSub, 1, wxEXPAND | wxALL, 10);
	vboxMain->Add(sbsSub, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);

	// Box Three: Indels

	sbsInd = new wxStaticBoxSizer(wxVERTICAL, panelMain, wxT("Indels"));
	fgsInd = new wxFlexGridSizer(5, 2, 8, 8);

	stIndLambda  = new wxStaticText(panelMain, wxID_ANY, wxT("Lambda:"));
	stIndModel   = new wxStaticText(panelMain, wxID_ANY, wxT("Model:"));
	stIndParams  = new wxStaticText(panelMain, wxID_ANY, wxT("Params:"));
	stIndVerbose = new wxStaticText(panelMain, wxID_ANY, wxT("Verbose:"));
	stIndHideLen = new wxStaticText(panelMain, wxID_ANY, wxT("Hide Length:"));

	wxString asIndModels[] = {wxT("Negative Binomial"), wxT("Power Law")};
	chIndModel = new wxChoice(panelMain, wxID_ANY, wxDefaultPosition, wxSize(200, -1), 2, asIndModels);
	chIndModel->SetSelection(1);	// Power Law

	tcIndLambda   = new wxTextCtrl(panelMain, wxID_ANY, wxT("0.0"), wxDefaultPosition, wxSize(72, 18));
	tcIndParam1   = new wxTextCtrl(panelMain, wxID_ANY, wxT("1.5"), wxDefaultPosition, wxSize(36, 18));
	tcIndParam2   = new wxTextCtrl(panelMain, wxID_ANY, wxT("100"), wxDefaultPosition, wxSize(36, 18));
	hboxIndParams = new wxBoxSizer(wxHORIZONTAL);
	hboxIndParams->Add(tcIndParam1);
	hboxIndParams->Add(tcIndParam2);

	cbIndVerbose = new wxCheckBox(panelMain, wxID_ANY, wxT(""));
	cbIndHideLen = new wxCheckBox(panelMain, wxID_ANY, wxT(""));

	fgsInd->Add(stIndLambda);
	fgsInd->Add(tcIndLambda);
	fgsInd->Add(stIndModel);
	fgsInd->Add(chIndModel);
	fgsInd->Add(stIndParams);
	fgsInd->Add(hboxIndParams);
	fgsInd->Add(stIndVerbose);
	fgsInd->Add(cbIndVerbose);
	fgsInd->Add(stIndHideLen);
	fgsInd->Add(cbIndHideLen);
	fgsInd->SetItemMinSize((size_t)0, 64, -1);
	fgsInd->AddGrowableCol(1, 1);

	sbsInd->Add(fgsInd, 1, wxEXPAND | wxALL, 10);
	vboxMain->Add(sbsInd, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);

	// Box Four: Miscellaneous

	sbsMisc = new wxStaticBoxSizer(wxVERTICAL, panelMain, wxT("Miscellaneous"));
	fgsMisc = new wxFlexGridSizer(5, 2, 8, 8);

	stMiscReps   = new wxStaticText(panelMain, wxID_ANY, wxT("Reps:"));
	stMiscSeed   = new wxStaticText(panelMain, wxID_ANY, wxT("Seed:"));
	stMiscFormat = new wxStaticText(panelMain, wxID_ANY, wxT("Format:"));
	stMiscInFile = new wxStaticText(panelMain, wxID_ANY, wxT("Input File:"));
	stMiscSvFile = new wxStaticText(panelMain, wxID_ANY, wxT("Save to File:"));

	tcMiscReps   = new wxTextCtrl(panelMain, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize(72, 18));
	tcMiscSeed   = new wxTextCtrl(panelMain, wxID_ANY, wxT("21569"), wxDefaultPosition, wxSize(72, 18));

	wxString asMiscFormats[] = {wxT("Clustal"), wxT("Fasta"), wxT("Nexus"), wxT("Phylip")};
	chMiscFormat = new wxChoice(panelMain, wxID_ANY, wxDefaultPosition, wxSize(200, -1), 2, asMiscFormats);
	chMiscFormat->SetSelection(0);	// Clustal

	cbMiscInFile = new wxCheckBox(panelMain, wxID_ANY, wxT(""));
	cbMiscSvFile = new wxCheckBox(panelMain, wxID_ANY, wxT(""));

	fgsMisc->Add(stMiscReps);
	fgsMisc->Add(tcMiscReps);
	fgsMisc->Add(stMiscSeed);
	fgsMisc->Add(tcMiscSeed);
	fgsMisc->Add(stMiscFormat);
	fgsMisc->Add(chMiscFormat);
	fgsMisc->Add(stMiscInFile);
	fgsMisc->Add(cbMiscInFile);
	fgsMisc->Add(stMiscSvFile);
	fgsMisc->Add(cbMiscSvFile);
	fgsMisc->SetItemMinSize((size_t)0, 64, -1);
	fgsMisc->AddGrowableCol(1, 1);

	sbsMisc->Add(fgsMisc, 1, wxEXPAND | wxALL, 10);
	vboxMain->Add(sbsMisc, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);

	vboxMain->Add(-1, 1, wxEXPAND | wxALL, 10);

	// Bottom: Buttons

	hboxBottom = new wxBoxSizer(wxHORIZONTAL);

	btnSubmit = new wxButton(panelMain, wxID_EXIT, wxT("Submit"), wxPoint(20, 400), wxDefaultSize);
	btnSubmit->SetFocus();
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxTestFrame::OnButtonExit));
	btnExit = new wxButton(panelMain, wxID_EXIT, wxT("Exit"), wxPoint(20, 400), wxDefaultSize);
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxTestFrame::OnButtonExit));
	
	hboxBottom->Add(btnSubmit, 0, wxLEFT, 10);
	hboxBottom->Add(btnExit, 0, wxLEFT, 10);
	vboxMain->Add(hboxBottom, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);
	panelMain->SetSizer(vboxMain);

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
	
	//textctrlTest = new wxTextCtrl(this, -1, wxT(""), wxPoint(-1, -1), wxSize(800, 380));
}

void wxTestFrame::OnButtonExit(wxCommandEvent & WXUNUSED(event))
{
	Close(true);
}

wxTestFrame::~wxTestFrame(void)
{
}
