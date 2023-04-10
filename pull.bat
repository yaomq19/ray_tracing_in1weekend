:ERROR
git pull origin master
if errorlevel 1 goto ERROR
else goto END
:END