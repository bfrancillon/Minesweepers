#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
//    EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Brianca Francillon ", wxPoint(30,30), wxSize(800,600))
{
	bton = new wxButton * [nFieldWidth * nFieldHeight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldWidth, 0, 0);

	nField = new int[nFieldWidth * nFieldHeight];
	wxFont font(26, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false);


	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeight; y++)
		{
			bton[y * nFieldWidth + x] = new wxButton(this, 10000+(y*nFieldWidth + x));
			grid->Add(bton[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

			bton[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			nField[y * nFieldWidth + x] = 0;
		}

	}
	this->SetSizer(grid);
	grid->Layout();
	//m_btn1 = new wxButton(this,10001 ,"Click me", wxPoint(10, 10), wxSize(150, 50));
	//m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
	//m_list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
}

cMain::~cMain()
{
	delete[]bton;
}

void cMain::OnButtonClicked(wxCommandEvent& event)
{
	int x = (event.GetId() - 10000) % nFieldWidth;
	int y = (event.GetId() - 10000) % nFieldHeight;

	if (bFirstClick)
	{
		int mines = 30;
		while (mines)
		{
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;

			if (nField[ry * nFieldWidth + rx]== 0 && rx != x && ry != y)
			{
				nField[ry * nFieldWidth + rx] = -1;
				mines--;
			}

		}
		bFirstClick = false;
	}
	bton[y * nFieldWidth + x]->Enable(false);

	if (nField[y * nFieldWidth + x] == -1)
	{
		wxMessageBox("Game Over: (");
		bFirstClick = true;
		for (int x = 0; x < nFieldWidth; x++)
		{
			for (int y = 0; y <  nFieldHeight; y++)
			{
				nField[y*nFieldWidth + x] = 0;
				bton[y * nFieldWidth + x]->SetLabel("");
				bton[y * nFieldWidth + x]->Enable(true);
			}
		}
	}
	else
	{
		int mine_count = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x+i>=0 && x+i <nFieldWidth && y + j >= 0 && y + j <nFieldWidth)
				{
					if (nField[(y+j) * nFieldWidth + (x + i)] == -1)
					{
						mine_count++;
					}
				}
			}

		}
		if (mine_count > 0)
		{
			bton[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}

	}

	//m_list1->AppendString(m_txt1->GetValue());
	event.Skip();
}
