// Pick eMail Field for build data


#pragma once


// PickEmailDlg dialog

class PickEmailDlg : public CDialogEx {

  DECLARE_DYNAMIC(PickEmailDlg)

public:
CComboBox comboBoxCtl;
CString   comboBox;

  PickEmailDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~PickEmailDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_PickEmail };
#endif

protected:

  virtual BOOL OnInitDialog();
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
