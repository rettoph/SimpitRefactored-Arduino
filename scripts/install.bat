set KerbalSimpitRevampedArduinoTargetPath="%USERPROFILE%\Documents\Arduino\libraries\KerbalSimpitRevamped-Arduino"
if exist %KerbalSimpitRevampedArduinoTargetPath% rmdir %KerbalSimpitRevampedArduinoTargetPath%
mklink /J %KerbalSimpitRevampedArduinoTargetPath% %~dp0\..