echo "Insert near pattern test 5"
echo ""


FILE_IN="insert-pattern5.in"
FILE_OUT="insert-pattern5.out"

echo "Input:"
cat $FILE_IN
echo ""
echo "Command: $ESED_BINARY insert-below 'AA*' ooo"
echo ""
echo "Output must be:"
cat $FILE_OUT
echo ""
echo ""

$ESED_BINARY insert-below 'AA*' ooo -o tmp -i $FILE_IN
diff $FILE_OUT tmp >/dev/null
RESULT=$?

echo "Output is:"
cat tmp
echo ""

exit $RESULT
