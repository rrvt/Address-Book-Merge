// BuildData.h : main header file for the BuildData application

#pragma once
#include "CApp.h"


class BuildDataDoc;
class BuildDataView;
class MainFrame;


// BuildData:
// See BuildData.cpp for the implementation of this class

class BuildData : public CApp {

public:

               BuildData() noexcept : CApp(this) { }

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

          BuildDataDoc*  doc()  {return (BuildDataDoc*)  CApp::getDoc();}
          BuildDataView* view() {return (BuildDataView*) CApp::getView();}
          MainFrame*       mainFrm() {return (MainFrame*) m_pMainWnd;}

  DECLARE_MESSAGE_MAP()

  afx_msg void OnFilePrintSetup();
  afx_msg void OnAppAbout();
  afx_msg void OnHelp();
  };


extern BuildData theApp;

inline void         invalidate() {theApp.invalidate();}
inline BuildDataDoc*  doc()  {return theApp.doc();}
inline BuildDataView* view() {return theApp.view();}

