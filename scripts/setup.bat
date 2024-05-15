set KerbalSimpitRevampedArduinoTargetPath="%USERPROFILE%\Documents\Arduino\libraries\KerbalSimpitRevamped-Arduino"
if exist %KerbalSimpitRevampedArduinoTargetPath% rmdir %KerbalSimpitRevampedArduinoTargetPath%
mklink /J %KerbalSimpitRevampedArduinoTargetPath% %~dp0\..

set AUnitTargetPath="%USERPROFILE%\Documents\Arduino\libraries\AUnit"
if exist %AUnitTargetPath% rmdir %AUnitTargetPath%
mklink /J %AUnitTargetPath% %~dp0\..\libraries\AUnit