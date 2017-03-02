package Strip;

################################################################################
# Title:   Strip
# Authors: Ethan Hill
# Date:    25 January 2014
# Version: 1.0.2
################################################################################

use strict;
use warnings;

my $cComment = qr/\/\*([^\*]|\*[^\/])*\*\//;
my $cppComment = qr/\/\/([^\v\\]|\\\v|\\.)*(?=\R)/;
my $stringLiteral = qr/"([^"\v\\]|\\\v|\\.)*("|(?=\R))/;
my $characterLiteral = qr/'([^'\v\\]|\\\v|\\.)*('|(?=\R))/;

################################################################################
# Subroutine: removeCComments
# Params:
#   1. contents
#        - scalar contents to be stripped of C-style comments
#        - contents must be defined, fails otherwise
#        - contents may be altered post-call (see Return 2)
# Return:
#   1. scalar contents without any C-style comments if the caller expects a scalar
#   2. nothing, but removes all C-style comments from the original contents if
#        the caller expects nothing
################################################################################
sub removeCComments {
    my $regex = qr/$cComment|($cppComment|$stringLiteral|$characterLiteral)/;
	if(defined wantarray) {
        my $retval = $_[1];
        $retval =~ s/$regex/defined $2 ? $2 : ""/gse;
		return $retval;
	} else {
		$_[1] =~ s/$regex/defined $2 ? $2 : ""/gse;
	}
	return 1;
}

################################################################################
# Subroutine: removeCPPComments
# Params:
#   1. contents
#        - scalar contents to be stripped of C++-style comments
#        - contents must be defined, fails otherwise
#        - contents may be altered post-call (see Return 2)
# Return:
#   1. scalar contents without any C++-style comments if the caller expects a scalar
#   2. nothing, but removes all C++-style comments from the original contents if
#        the caller expects nothing
################################################################################
sub removeCPPComments {
    my $regex = qr/$cppComment|($cComment|$stringLiteral|$characterLiteral)/;
	if(defined wantarray) {
        my $retval = $_[1];
        $retval =~ s/$regex/defined $2 ? $2 : ""/gse;
		return $retval;
	} else {
		$_[1] =~ s/$regex/defined $2 ? $2 : ""/gse;
	}
	return 1;
}

################################################################################
# Subroutine: removeStringLiterals
# Params:
#   1. contents
#        - scalar contents to be stripped of string literals
#        - contents must be defined, fails otherwise
#        - contents may be altered post-call (see Return 2)
# Return:
#   1. scalar contents without any string literals if the caller expects a scalar
#   2. nothing, but removes all string literals from the original contents if
#        the caller expects nothing
################################################################################
sub removeStringLiterals {
    my $regex = qr/$stringLiteral|($cComment|$cppComment|$characterLiteral)/;
	if(defined wantarray) {
        my $retval = $_[1];
        $retval =~ s/$regex/defined $3 ? $3 : ""/gse;
		return $retval;
	} else {
		$_[1] =~ s/$regex/defined $3 ? $3 : ""/gse;
	}
	return 1;
}

################################################################################
# Subroutine: removeCharacterLiterals
# Params:
#   1. contents
#        - scalar contents to be stripped of character literals
#        - contents must be defined, fails otherwise
#        - contents may be altered post-call (see Return 2)
# Return:
#   1. scalar contents without any character literals if the caller expects a scalar
#   2. nothing, but removes all character literals from the original contents if
#        the caller expects nothing
################################################################################
sub removeCharacterLiterals {
    my $regex = qr/$characterLiteral|($cComment|$cppComment|$stringLiteral)/;
	if(defined wantarray) {
        my $retval = $_[1];
        $retval =~ s/$regex/defined $3 ? $3 : ""/gse;
		return $retval;
	} else {
		$_[1] =~ s/$regex/defined $3 ? $3 : ""/gse;
	}
	return 1;
}

return 1;
