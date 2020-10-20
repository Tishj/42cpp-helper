#!/bin/bash

SHELL=$(ps -p $$ | awk '{print $4}' | grep -v "CMD" | rev | cut -d '/' -f1 | rev)
SHELLRC_PATH=$HOME"/."$SHELL"rc"

if ! cat $SHELLRC_PATH | grep "alias 42cpp=" > /dev/null;
then
	echo "alias 42cpp=\"~/42cpp-helper/42cpp\"" >> $SHELLRC_PATH
	echo "Alias '42cpp' succesfully added to your shellrc, will now source it.."
	source $SHELLRC_PATH
else
	echo "Already installed."
fi
