#!/bin/sh
###############################################################################
# Xcode C++ template install script
# Pete Goodliffe
# (c) 2012 Pete Goodliffe, All rights reserved.
###############################################################################

#------------------------------------------------------------------------------
# Configuration

: ${XCODE_APP:=/Applications/Xcode.app}
: ${XCODE_VERSION:=4.6}
: ${XCODE_TEMPLATES_DIR:="$HOME/Library/Developer/Xcode/Templates/File Templates/C and C++/"}

#------------------------------------------------------------------------------
# Functions

abort()
{
    echo
    echo
    echo "Failed: $1"
    echo "   This may happen because you have not installed the right version"
    echo "   of Xcode. Or because your computer doesn't like you."
    echo
    exit 1
}

#------------------------------------------------------------------------------
# Polite verbosity

echo "========================================================================"
echo "Xcode $XCODE_VERSION C++ class template install script"
echo "   by Pete Goodliffe"
echo
echo "   This script is supplied with no guarantee. Please use it at your"
echo "   peril. I've made it as safe as I can; it shouldn't destroy your"
echo "   Xcode installation."
echo "   I hope you find it useful."
echo "========================================================================"
echo

echo "About to install the template."
echo

mkdir -p "$XCODE_TEMPLATES_DIR"

#------------------------------------------------------------------------------
# Checking

XCODE_PLIST=$XCODE_APP/Contents/Info.plist
TEMPLATE_DIR="Qing C++ Class.xctemplate"
#TEMPLATE_DIR="C++ Class.xctemplate"

[ -d $XCODE_APP ]   || abort "Xcode app bundle not found"
[ -f $XCODE_PLIST ] || abort "Xcode Info.plist not found"

XCODE_PLIST_VERSION=$(defaults read $XCODE_PLIST CFBundleShortVersionString)

# This check is not actually necessary, removing
#[ "X$XCODE_PLIST_VERSION" == "X$XCODE_VERSION" ] || abort "Xcode installation is not version $XCODE_VERSION (it is $XCODE_PLIST_VERSION)"

[ -d "$TEMPLATE_DIR" ]                           || abort "Can't find the template. Are you running from the right directory?"
[ -d "$XCODE_TEMPLATES_DIR" ]                    || abort "Xcode templates directory not found"

#------------------------------------------------------------------------------
# Installing

# Yes, this is all there is to it...
cp -r "$TEMPLATE_DIR" "$XCODE_TEMPLATES_DIR/"

#------------------------------------------------------------------------------
# Done

echo
echo "The template has been installed successfully."
echo "You must restart Xcode $XCODE_VERSION to use it."
echo "Enjoy."
echo

