set KerbalSimpitRevampedArduinoTargetPath="%USERPROFILE%\Documents\Arduino\libraries\KerbalSimpitRevamped-Arduino"
set FunctionObjectsTargetPath="%USERPROFILE%\Documents\Arduino\libraries\function_objects"

if exist %KerbalSimpitRevampedArduinoTargetPath% rmdir %KerbalSimpitRevampedArduinoTargetPath%
mklink /J %KerbalSimpitRevampedArduinoTargetPath% "%~dp0\.."

if exist %FunctionObjectsTargetPath% rmdir %FunctionObjectsTargetPath%
mklink /J %FunctionObjectsTargetPath% "%~dp0\..\libraries\function_objects\include"