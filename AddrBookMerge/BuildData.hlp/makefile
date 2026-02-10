

BuildData.chm : *.htm BuildData.hhp BuildData.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" BuildData


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist BuildData.chm del /F BuildData.chm


$(TgtFolder)/BuildData.chm : BuildData.chm
  copy $(MAKEDIR)\BuildData.chm  $(MAKEDIR)\..\$(TgtFolder)\BuildData.chm


$(TgtFolder)/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\$(TgtFolder)
  if exist BuildData.chm del /F BuildData.chm
  cd $(MAKEDIR)


$(TgtFolder)/Rebuild.rbd : $(TgtFolder)/Clean.cln $(TgtFolder)/BuildData.chm


