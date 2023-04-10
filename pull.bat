git pull origin master
IF %errorlevel% NEQ 0 GOTO ERROR

:ERROR
git pull origin master
IF %errorlevel% NEQ 0 GOTO ERROR