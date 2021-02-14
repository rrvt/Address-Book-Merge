// PickEmailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PickEmailDlg.h"
#include "CodeBldr.h"
#include "Resource.h"


// PickEmailDlg dialog

IMPLEMENT_DYNAMIC(PickEmailDlg, CDialogEx)

PickEmailDlg::PickEmailDlg(CWnd* pParent) : CDialogEx(IDD_PickEmail, pParent) , comboBox(_T("")) { }

PickEmailDlg::~PickEmailDlg() { }


BOOL PickEmailDlg::OnInitDialog() {
CFldIter iter(codeBldr.csvRcd);
CSVfld*  fld;

  CDialogEx::OnInitDialog();

  for (fld = iter(); fld; fld = iter++) {
    comboBoxCtl.AddString(fld->name);
    }

  return TRUE;
  }


void PickEmailDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX,  IDC_COMBO1, comboBoxCtl);
  DDX_CBString(pDX, IDC_COMBO1, comboBox);
  }


BEGIN_MESSAGE_MAP(PickEmailDlg, CDialogEx)
END_MESSAGE_MAP()


// PickEmailDlg message handlers
