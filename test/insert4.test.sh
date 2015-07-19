echo "Insert test 4"

export FILE_PREFIX="insert4"
export COMMAND="insert 100 INSERTED"

./file_command.template.sh
exit $?