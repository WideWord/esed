echo "Replace test 4"

export INPUT="qwer tyui tyui ghjk"
export COMMAND="replace tyui ghjk"
export SHOULD_DISPLAY="qwer ghjk ghjk ghjk"

./command.template.sh
exit $?