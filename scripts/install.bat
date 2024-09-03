set ArduinoLibraryPath=%USERPROFILE%\Documents\Arduino\libraries

echo Input Arduino Library Path. Default: "%ArduinoLibraryPath%"
set /P "ArduinoLibraryPath="

set SimpitRefactoredArduinoTargetPath="%ArduinoLibraryPath%\SimpitRefactored-Arduino"

CALL :NORMALIZEPATH "%~dp0\.."
SET SimpitRefactoredArduinoSourcePath="%RETVAL%"

if not exist %ArduinoLibraryPath% (
    echo Creating Arduino Library Directory at %ArduinoLibraryPath%
    mkdir %ArduinoLibraryPath%
)

if exist %SimpitRefactoredArduinoTargetPath% (
    echo Removing existing SimpitRefactoredArduino instace at %SimpitRefactoredArduinoTargetPath%
    rmdir %SimpitRefactoredArduinoTargetPath%
)

mklink /J %SimpitRefactoredArduinoTargetPath% %SimpitRefactoredArduinoSourcePath%

GOTO :END
echo Warning: Running function code

:NORMALIZEPATH
  SET RETVAL=%~f1
  EXIT /B

:END
echo Done!
timeout /t 10