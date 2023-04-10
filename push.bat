:ERROR
git add .
git commit -m "none"
git push origin master
if %errorlevel% NEQ 0 (goto ERROR) else (goto END)

:END
echo success
