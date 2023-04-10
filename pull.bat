:COMMAND1
git pull origin master
if %errorlevel% NEQ 0 (goto COMMAND1) else (goto END)

:END
echo pull success