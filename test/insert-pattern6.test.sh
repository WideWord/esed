echo "Insert near pattern test 6"
echo ""


FILE_IN="insert-pattern6.in"
FILE_OUT="insert-pattern6.out"

echo "Input:"
cat $FILE_IN
echo ""
echo "Command: $ESED_BINARY insert-below 'Lorem ipsum dolor sit amet*' Hello"
echo ""
echo "Output must be:"
cat $FILE_OUT
echo ""
echo ""

$ESED_BINARY insert-below 'Lorem ipsum dolor sit amet*' Hello -o tmp -i $FILE_IN
diff $FILE_OUT tmp >/dev/null
RESULT=$?

echo "Output is:"
cat tmp
echo ""

exit $RESULT
