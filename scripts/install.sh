SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

KerbalSimpitTargetPath="$HOME/Arduino/libraries/KerbalSimpit"

# KerbalSimpit-Arduino
rm -rf $KerbalSimpitTargetPath
ln -s $SCRIPT_DIR/.. $KerbalSimpitTargetPath