package Console;

################################################################################
# Title:   Console
# Authors: Ethan Hill
# Date:    22 January 2014
# Version: 1.0.0
################################################################################

use strict;
use warnings;

my $verbose = 0;
my $quiet = 0;
my $debug = 0;
my $suppress = 0;

################################################################################
# Subroutine: printMessage
# Params:
#   1. contents
#        - list of contents to print to the console
#        - contents may be undefined, nothing is printed in this case
# Notes:
#   1. subroutine is controlled by the quiet flag, nothing is printed if the
#        quiet flag evaluates to true
################################################################################
sub printMessage {
	print @_[1..$#_] unless $quiet;
}

################################################################################
# Subroutine: printRequired
# Params:
#   1. contents
#        - list of contents to print to the console
#        - contents may be undefined, nothing is printed in this case
################################################################################
sub printRequired {
	print @_[1..$#_];
}

################################################################################
# Subroutine: printVerbose
# Params:
#   1. contents
#        - list of contents to print to the console
#        - contents may be undefined, nothing is printed in this case
# Notes:
#   1. subroutine is controlled by the verbose flag, contents are only printed
#        if the verbose flag evaluates to true
################################################################################
sub printVerbose {
	print @_[1..$#_] if $verbose && !$quiet;
}

################################################################################
# Subroutine: printDebug
# Params:
#   1. contents
#        - list of contents to print to the console
#        - contents may be undefined, nothing is printed in this case
# Notes:
#   1. subroutine is controlled by the debug flag, contents are only printed
#        if the debug flag evaluates to true
################################################################################
sub printDebug {
	print @_[1..$#_] if $debug;
}

################################################################################
# Subroutine: printWarning
# Params:
#   1. contents
#        - list of contents to print to the console
#        - contents may be undefined, nothing is printed in this case
# Notes:
#   1. subroutine is controlled by the suppress flag, nothing is printed if the
#        suppress flag evaluates to true
################################################################################
sub printWarning {
	print "WARNING: ", @_[1..$#_] unless $suppress;
}

################################################################################
# Subroutine: printError
# Params:
#   1. contents
#        - list of contents to print to the console
#        - contents may be undefined, nothing is printed in this case
# Notes:
#   1. any call to this subroutine should be followed by 'and die' or 'and return'
#        for proper functionality
################################################################################
sub printError {
	print "ERROR: ", @_[1..$#_];
}

################################################################################
# Subroutine: isVerbose
# Return:
#   1. scalar value of the verbose flag
################################################################################
sub isVerbose {
	return $verbose;
}

################################################################################
# Subroutine: setVerbose
# Param:
#   1. value
#        - scalar value to set the verbose flag to
#        - value must be numeric, fails otherwise
#        - value should be either 1 or 0
################################################################################
sub setVerbose {
	$verbose = $_[1] if $_[1] =~ /-?\d+/;
}

################################################################################
# Subroutine: isQuiet
# Return:
#   1. scalar value of the quiet flag
################################################################################
sub isQuiet {
	return $quiet;
}

################################################################################
# Subroutine: setQuiet
# Param:
#   1. value
#        - scalar value to set the quiet flag to
#        - value must be numeric, fails otherwise
#        - value should be either 1 or 0
################################################################################
sub setQuiet {
	$quiet = $_ [1]if $_[1] =~ /-?\d+/;
}

################################################################################
# Subroutine: isDebug
# Return:
#   1. scalar value of the debug flag
################################################################################
sub isDebug {
	return $debug;
}

################################################################################
# Subroutine: setDebug
# Param:
#   1. value
#        - scalar value to set the debug flag to
#        - value must be numeric, fails otherwise
#        - value should be either 1 or 0
################################################################################
sub setDebug {
	$debug = $_[1] if $_[1] =~ /-?\d+/;
}

################################################################################
# Subroutine: isSuppress
# Return:
#   1. scalar value of the suppress flag
################################################################################
sub isSuppress {
	return $suppress;
}

################################################################################
# Subroutine: setSuppress
# Param:
#   1. value
#        - scalar value to set the suppress flag to
#        - value must be numeric, fails otherwise
#        - value should be either 1 or 0
################################################################################
sub setSuppress {
	$suppress = $_[1] if $_[1] =~ /-?\d+/;
}

return 1;
