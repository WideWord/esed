echo "Replace test 3"

export INPUT="ababab"
export COMMAND="replace ab cd"
export SHOULD_DISPLAY="cdcdcd"

./command.template.sh
exit $?