echo "Replace test 2"

export INPUT="ababab"
export COMMAND="replace a f"
export SHOULD_DISPLAY="fbfbfb"

./command.template.sh
exit $?