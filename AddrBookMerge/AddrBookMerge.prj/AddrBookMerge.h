// AddrBookMerge.h : main header file for the AddrBookMerge application

#pragma once
#include "CApp.h"


class AddrBookMergeDoc;
class AddrBookMergeView;
class MainFrame;


// AddrBookMerge:
// See AddrBookMerge.cpp for the implementation of this class

class AddrBookMerge : public CApp {

public:

               AddrBookMerge() noexcept : CApp(this) { }

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

          AddrBookMergeDoc*  doc()  {return (AddrBookMergeDoc*)  CApp::getDoc();}
          AddrBookMergeView* view() {return (AddrBookMergeView*) CApp::getView();}
          MainFrame*       mainFrm() {return (MainFrame*) m_pMainWnd;}

  DECLARE_MESSAGE_MAP()

  afx_msg void OnFilePrintSetup();
  afx_msg void OnAppAbout();
  afx_msg void OnHelp();
  };


extern AddrBookMerge theApp;

inline void               invalidate() {theApp.invalidate();}
inline AddrBookMergeDoc*  doc()        {return theApp.doc();}
inline AddrBookMergeView* view()       {return theApp.view();}

