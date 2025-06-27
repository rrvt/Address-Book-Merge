

BuildData.chm : *.htm BuildData.hhp BuildData.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" BuildData


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist BuildData.chm del /F BuildData.chm


Release/BuildData.chm : BuildData.chm
  copy $(MAKEDIR)\BuildData.chm  $(MAKEDIR)\..\Release\BuildData.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  if exist BuildData.chm del /F BuildData.chm
  cd $(MAKEDIR)


Debug/BuildData.chm : BuildData.chm
  copy $(MAKEDIR)\BuildData.chm  $(MAKEDIR)\..\Debug\BuildData.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  if exist BuildData.chm del /F BuildData.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/BuildData.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/BuildData.chm


