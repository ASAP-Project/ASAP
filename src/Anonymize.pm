package Anonymize;

################################################################################
# Title:   Anonymize
# Authors: Matthew Tennyson
# Date:    6 July 2018
################################################################################

use strict;
use warnings;

sub stripComments
{
    my $file = $_[1];

    my $isCPP = 1;
    my $isC = 1;
    my $isString = 1;

    while(1)
    {
        my $cppPos = ~0;
        my $cPos = ~0;
        my $stringPos = ~0;

        if($isCPP)
        {
            # print "*** Matching cpp comment...\n";
            if($file =~ /([\s\S]*?)\/\//) { $cppPos = length $1; }
            else { $isCPP = 0; }
        }

        if($isC)
        {
            # print "*** Matching c comment...\n";
            if($file =~ /([\s\S]*?)\/\*/) { $cPos = length $1; }
            else { $isC = 0; }
        }

        if($isString)
        {
            # print "*** Matching string...\n";
            if($file =~ /\A("|[\s\S]*?[^\\']")/) { $stringPos = (length $1) - 1; }
            else { $isString = 0; }
        }

        #print "cpp($cppPos) c($cPos) str($stringPos)\n";

        if($cppPos<$cPos && $cppPos<$stringPos)
        {
            #cpp-style comment comes first
            $file =~ s/\/\/[^\v]*//;
        }
        elsif($cPos<$cppPos && $cPos<$stringPos)
        {
            #c-style comment comes first
            if($file =~ s/\/\*[\s\S]*?\*\///) {}
            elsif($file =~ s/\/\*[\s\S]*//) {}
        }
        elsif($stringPos<$cppPos && $stringPos<$cPos)
        {
            #string comes first
            if($file =~ s/\A""//) {}
            elsif($file =~ s/\A"[^\v]*?[^\\\v]"//) {}
            elsif($file =~ /\A([\s\S]*?[^\\'])(?:""|"[^\v]*?[^\\\v]"|"[^\v]*?\\\\")/)
            {
                #a closed string exists in the file, but we have to make sure
                #that we don't have an unclosed string first

                if($stringPos==length $1)
                {
                    #closed string comes first, so remove it
                    $file =~ s/\A([\s\S]*?[^\\'])(?:""|"[^\v]*?[^\\\v]"|"[^\v]*?\\\\")/$1/;
                }
                else
                {
                    #unclosed string comes first, so just remove the quote
                    if($file =~ s/\A"//) {}
                    elsif($file =~ s/\A([\s\S]*?[^\\'])"/$1/) {}
                }
            }
            else
            {
                #no closed string exists
                if($file =~ s/\A"//) {}
                elsif($file =~ s/\A([\s\S]*?[^\\'])"/$1/) {}
            }
        }
        else
        {
            #no c-comments, cpp-comments, or strings were found
            last;
        }
    }

    if(defined wantarray) {
		return $file;
	} else {
		$_[1] =~ $file;
	}
}

return 1; #file must return true
