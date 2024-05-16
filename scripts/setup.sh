SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

KerbalSimpitTargetPath="$HOME/Arduino/libraries/KerbalSimpit"
AUnitTargetPath="$HOME/Arduino/libraries/AUnit"

# KerbalSimpit-Arduino
rm -rf $KerbalSimpitTargetPath
ln -s $SCRIPT_DIR/.. $KerbalSimpitTargetPath

# AUnit
rm -rf $AUnitTargetPath
# ln -s $SCRIPT_DIR/../libraries/AUnit $AUnitTargetPath