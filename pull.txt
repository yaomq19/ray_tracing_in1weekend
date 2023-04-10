:ERROR
git pull origin master
if %errorlevel% NEQ 0 (goto ERROR) else (goto END)

:END
echo pull success