:ERROR
git add .
git commit -m "none"
git push origin master
git pull origin master
if %errorlevel%==1 (goto ERROR) else (goto END)

:END