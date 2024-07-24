set ArduinoLibraryPath=%USERPROFILE%\Documents\Arduino\libraries

echo Input Arduino Library Path. Default: "%ArduinoLibraryPath%"
set /P "ArduinoLibraryPath="

set KerbalSimpitRevampedArduinoTargetPath="%ArduinoLibraryPath%\KerbalSimpitRevamped-Arduino"
set FunctionObjectsTargetPath="%ArduinoLibraryPath%\function_objects"

CALL :NORMALIZEPATH "%~dp0\.."
SET KerbalSimpitRevampedArduinoSourcePath="%RETVAL%"

CALL :NORMALIZEPATH "%~dp0\..\libraries\function_objects\include"
SET FunctionObjectsSourcePath="%RETVAL%"

if not exist %KerbalSimpitRevampedArduinoTargetPath% (
    echo Creating Arduino Library Directory at %ArduinoLibraryPath%
    mkdir %ArduinoLibraryPath%
)

if exist %KerbalSimpitRevampedArduinoTargetPath% (
    echo Removing existing KerbalSimpitRevampedArduino instace at %KerbalSimpitRevampedArduinoTargetPath%
    rmdir %KerbalSimpitRevampedArduinoTargetPath%
)

mklink /J %KerbalSimpitRevampedArduinoTargetPath% %KerbalSimpitRevampedArduinoSourcePath%

if exist %FunctionObjectsTargetPath% (
    echo Removing existing function_objects instace at %FunctionObjectsTargetPath%
    rmdir %FunctionObjectsTargetPath%
)

mklink /J %FunctionObjectsTargetPath% %FunctionObjectsSourcePath%



GOTO :END
echo Warning: Running function code

:NORMALIZEPATH
  SET RETVAL=%~f1
  EXIT /B

:END
echo Done!
timeout /t 10