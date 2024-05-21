SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

KerbalSimpitTargetPath="$HOME/Arduino/libraries/KerbalSimpit"
FunctionObjectsTargetPath="$HOME/Arduino/libraries/function_objects"

# KerbalSimpit-Arduino
rm -rf $KerbalSimpitTargetPath
ln -s $SCRIPT_DIR/.. $KerbalSimpitTargetPath

# function_objects
# https://github.com/fopeczek/function_objects/tree/main
rm -rf $FunctionObjectsTargetPath
ln -s $SCRIPT_DIR/../libraries/function_objects/include $FunctionObjectsTargetPath