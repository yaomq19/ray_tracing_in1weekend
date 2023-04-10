:ERROR
git add .
git commit -m "none"
git push origin master
if %errorlevel%!=0 (goto ERROR) else (goto END)

:END
echo success
