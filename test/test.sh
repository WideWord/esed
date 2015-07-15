
export ESED_BINARY=esed

for test in *.test.sh; do
	echo "Test $test"
	echo "-----------------------------"
	./$test
	TEST_STATUS=$?
	if [ "$TEST_STATUS" -eq "0" ]; then
		echo "+----+"
		echo "|PASS|" 
		echo "+----+"
	else
		echo "+----+"
		echo "|PASS|" 
		echo "+----+"	
	fi
	echo "============================="
done
