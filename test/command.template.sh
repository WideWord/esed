echo ""
echo "Input:"
echo $INPUT
echo ""
echo "Command: $ESED_BINARY $COMMAND"
echo ""
echo "Output must be:"
echo $SHOULD_DISPLAY
echo ""

RESULT=`echo "$INPUT" | $ESED_BINARY $COMMAND`

echo "Outbut is:"
echo $RESULT

if [ "$RESULT" == "$SHOULD_DISPLAY" ]; then
	exit 0
else
	exit 1
fi