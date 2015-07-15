echo "Replace test 1"

export INPUT="abcd"
export COMMAND="replace b f"
export SHOULD_DISPLAY="afcd"

./command.template.sh
exit $?