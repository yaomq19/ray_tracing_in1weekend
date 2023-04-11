:COMMAND1
git add .
if %errorlevel% NEQ 0 (goto COMMAND2) else (goto COMMAND2)

:COMMAND2
git commit -m "none"
if %errorlevel% NEQ 0 (goto COMMAND3) else (goto COMMAND3)

:COMMAND3
git push origin master
if %errorlevel% NEQ 0 (goto COMMAND3) else (goto END)

:END
echo success
