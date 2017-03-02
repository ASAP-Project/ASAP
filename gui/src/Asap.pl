################################################################################
# Title:   Asap
# Authors: Ethan Hill, Jacob Siegers, Matthew Tennyson
# Date:    11 April 2014
# Version: 1.0.4
################################################################################

use strict;
use warnings;

use Console;
use Directory;
use File;
use Strip;

use Burrows;
use Scap;

################################################################################
# Start of script
################################################################################

my %properties = (
	verbose => 0,
	quiet => 0,
	debug => 0,
	suppress => 0,
	help => 0,
	train => 0,
	query => 0,
	experiment => 0,
    anonymize => 0,
	scap => 0,
	burrows => 0,
	inputdir => undef,
	outputdir => undef,
    testdir => undef,
    trainingdir => undef,
	doc => undef,
	n => undef,
	L => undef,
    k => undef,
	report => undef,
    tokenfile => undef
);

my $propertiesRegex = join("|", keys %properties);
parseArguments(\%properties);
foreach(keys %properties) {
#warn "Unknown option $_" and exit unless $_ =~ /$propertiesRegex/;
}

printHelpDialog() if $properties{help};

setOutputFlags($properties{verbose}, $properties{quiet}, $properties{debug}, $properties{suppress});
my $modeSum = $properties{train} + $properties{query} + $properties{experiment} + $properties{anonymize};
my $methodSum = $properties{scap} + $properties{burrows};

print "Mode not specified (-train|-query|-experiment).\n\n" and printHelpDialog() if $modeSum < 1;
print "Only one mode may be specified (-train|-query|-experiment).\n\n" and printHelpDialog() if $modeSum > 1;
print "Method not specified (-scap|-burrows).\n\n" and printHelpDialog() if !$properties{anonymize} && $methodSum < 1;
print "Only one method may be specified (-scap|-burrows).\n\n" and printHelpDialog() if $methodSum > 1;

if($properties{train}) {
	print "Input directory not specified (-inputdir).\n\n" and printHelpDialog() unless exists $properties{inputdir} && defined $properties{inputdir};
	print "Output directory not specified (-outputdir).\n\n" and printHelpDialog() unless exists $properties{outputdir} && defined $properties{outputdir};
	if($properties{scap}) {
		Scap->train($properties{inputdir}, $properties{outputdir}) or die "SCAP training failed";
	} elsif($properties{burrows}) {
		print "An n-gram size not specified (-n).\n\n" and printHelpDialog() unless exists $properties{n} && defined $properties{n};
		print "Invalid n-gram size (-n=$properties{n}).\n\n" and printHelpDialog() unless $properties{n} =~ /^[1-9]\d*$/;
		print "Token file not specified (-tokenfile).\n\n" and printHelpDialog() unless exists $properties{tokenfile} && defined $properties{tokenfile};
		Burrows->train($properties{inputdir}, $properties{outputdir}, $properties{n}, $properties{tokenfile}) or die "Burrows training failed";
	}
} elsif($properties{query}) {
	print "Input directory not specified (-inputdir).\n\n" and printHelpDialog() unless exists $properties{inputdir} && defined $properties{inputdir};
	print "Query document not specified (-doc).\n\n" and printHelpDialog() unless exists $properties{doc} && defined $properties{doc};
	if($properties{scap}) {
		print "An n-gram size not specified (-n).\n\n" and printHelpDialog() unless exists $properties{n} && defined $properties{n};
		print "Profile length (-L) not specified.\n\n" and printHelpDialog() unless exists $properties{L} && defined $properties{L};
		print "Invalid n-gram size (-n=$properties{n}).\n\n" and printHelpDialog() unless $properties{n} =~ /^[1-9]\d*$/;
		print "Invalid profile length (-L=$properties{L}).\n\n" and printHelpDialog() unless $properties{L} =~ /^[1-9]\d*$/;
		Scap->query($properties{inputdir}, $properties{doc}, $properties{n}, $properties{L}, $properties{report}) or die "SCAP query failed";
	} elsif($properties{burrows}) {
		Burrows->query($properties{inputdir}, $properties{doc}, $properties{report}) or die "Burrows query failed";
	}
} elsif($properties{experiment}) {
    if(exists $properties{k} && defined $properties{k}) {
        print "Input directory not specified (-inputdir).\n\n" and printHelpDialog() unless exists $properties{inputdir} && defined $properties{inputdir};
        print "Invalid k-fold size (-k=$properties{k}).\n\n" and printHelpDialog() unless $properties{k} =~ /^[1-9]\d*$/;
    } elsif(exists $properties{inputdir} && defined $properties{inputdir}) {
        print "Test directory should not be specified (-testdir).\n\n" and printHelpDialog() if exists $properties{testdir} && defined $properties{testdir};
        print "Training directory should not be specified (-trainingdir).\n\n" and printHelpDialog() if exists $properties{trainingdir} && defined $properties{trainingdir};
    } elsif((exists $properties{testdir} && defined $properties{testdir}) || (exists $properties{trainingdir} && defined $properties{trainingdir})) {
        print "Test directory not specified (-testdir).\n\n" and printHelpDialog() unless exists $properties{testdir} && defined $properties{testdir};
        print "Training directory not specified (-trainingdir).\n\n" and printHelpDialog() unless exists $properties{trainingdir} && defined $properties{trainingdir};
        print "K-fold size should not be specified (-k).\n\n" and printHelpDialog() if exists $properties{k} && defined $properties{k};
        print "Input directory should not be specified (-inputdir).\n\n" and printHelpDialog() if exists $properties{inputdir} && defined $properties{inputdir};
    } else {
        print "Unknown combination of arguments.\n\n" and printHelpDialog();
    }
	if($properties{scap}) {
        print "An n-gram size not specified (-n).\n\n" and printHelpDialog() unless exists $properties{n} && defined $properties{n};
        print "Profile length (-L) not specified.\n\n" and printHelpDialog() unless exists $properties{L} && defined $properties{L};
        print "Invalid n-gram size (-n=$properties{n}).\n\n" and printHelpDialog() unless $properties{n} =~ /^[1-9]\d*$/;
		print "Invalid profile length (-L=$properties{L}).\n\n" and printHelpDialog() unless $properties{L} =~ /^[1-9]\d*$/;
		Scap->experiment($properties{testdir}, $properties{trainingdir}, $properties{inputdir}, $properties{k}, $properties{n}, $properties{L}, $properties{report}) or die "SCAP experiment failed";
	} elsif($properties{burrows}) {
        print "An n-gram size not specified (-n).\n\n" and printHelpDialog() unless exists $properties{n} && defined $properties{n};
		print "Invalid n-gram size (-n=$properties{n}).\n\n" and printHelpDialog() unless $properties{n} =~ /^[1-9]\d*$/;
		print "Token file not specified (-tokenfile).\n\n" and printHelpDialog() unless exists $properties{tokenfile} && defined $properties{tokenfile};
		Burrows->experiment($properties{testdir}, $properties{trainingdir}, $properties{inputdir}, $properties{k}, $properties{n}, $properties{tokenfile}, $properties{report}) or die "Burrows experiment failed";
	}
} elsif($properties{anonymize}) {
    print "Must specify either a document (-doc) or input directory (-inputdir).\n\n" and printHelpDialog() unless (exists $properties{doc} && defined $properties{doc}) || (exists $properties{inputdir} && defined $properties{inputdir});
    print "Only a document (-doc) or input directory (-inputdir) may be specified.\n\n" and printHelpDialog() if (exists $properties{doc} && defined $properties{doc}) && (exists $properties{inputdir} && defined $properties{inputdir});
    print "Output directory not specified (-outputdir).\n\n" and printHelpDialog() unless exists $properties{outputdir} && defined $properties{outputdir};
    $properties{outputdir} =~ s/[\\:]/\//g;
    if(defined $properties{doc}) {
        $properties{doc} =~ s/[\\:]/\//g;
        $properties{doc} =~ /\/([^\/]+)$/;
        my $file = $1;
        my $outputFile = $properties{outputdir} . ($properties{outputdir} =~ /\/$/ ? '' : '/') . $file;
        my $contents = File->readContents($properties{doc}, ':raw');
        Strip->removeCComments($contents);
        Strip->removeCPPComments($contents);
        Strip->removeStringLiterals($contents);
        File->writeContents($outputFile, ':raw', $contents);
    } elsif(defined $properties{inputdir}) {
        $properties{inputdir} =~ s/[\\:]/\//g;
        my $inputDir = $properties{inputdir} . ($properties{inputdir} =~ /\/$/ ? '' : '/');
        my $outputDir = $properties{outputdir} . ($properties{outputdir} =~ /\/$/ ? '' : '/');
        my @files = Directory->getFiles($properties{inputdir}, 0);
        foreach my $file (@files) {
            my $contents = File->readContents($inputDir . $file, ':raw');
            Strip->removeCComments($contents);
            Strip->removeCPPComments($contents);
            Strip->removeStringLiterals($contents);
            File->writeContents($outputDir . $file, ':raw', $contents);
        }
    }
}

################################################################################
# Start of subroutine list
################################################################################

sub parseArguments {
	my ($propertiesRef) = @_;
	foreach my $argument (@ARGV) {
        $argument =~ s/\A(-*)(.*?)/$2/;
		my ($key, $value) = split("=", $argument, 2);
		if(defined $value) {
			$$propertiesRef{$key} = $value;
		} else {
			$$propertiesRef{$key} = 1;
		}
	}
	return 1;
}

sub setOutputFlags {
	my ($verbose, $quiet, $debug, $suppress) = @_;
	Console->setVerbose($verbose);
	Console->setQuiet($quiet);
	Console->setDebug($debug);
	Console->setSuppress($suppress);
	return 1;
}

sub printHelpDialog {
	print "Training usage: perl Asap.pl -train (-scap|-burrows) (-inputdir=<directory>) (-outputdir=<directory>) [-n=<natural number>] [-tokenfile=<file>]\n",
          "  Training options:\n",
          "    -scap: Use SCAP method of authorship attribution\n",
          "    -burrows: Use Burrows method of authorship attribution\n",
          "    -inputdir=<directory>: Specifies location of training data\n",
          "    -outputdir=<directory>: Specifies where to store output files\n",
          "    -n=<natural number>: Specifies n-gram size (only required for Burrows method)\n",
          "    -tokenfile=<file>: Specifies the file containing the list of feature tokens (only required for Burrows method)\n",
          "\n",
          "Query usage: perl Asap.pl -query (-scap|-burrows) (-inputdir=<directory>) (-doc=<file>) [-report=<file>] [-n=<natural number>] [-L=<natural number>]\n",
          "  Query options:\n",
          "    -scap: Use SCAP method of authorship attribution\n",
          "    -burrows: Use Burrows method of authorship attribution\n",
          "    -inputdir=<directory>: Specifies location of files created during training mode\n",
          "    -doc=<file>: Specifies query document whose author is to be attributed\n",
          "    -report=<file>: Specifies Excel file to store query results (optional)\n",
          "    -n=<natural number>: Specifies n-gram size (only required for SCAP method)\n",
          "    -L=<natural number>: Specifies profile length (only required for SCAP method)\n",
          "\n",
          "Experiment usage: perl Asap.pl -experiment (-scap|-burrows) [...]\n",
          "  Experiment options:\n",
          "    -scap: Use SCAP method of authorship attribution\n",
          "    -burrows: Use Burrows method of authorship attribution\n",
          "    -testdir=<directory>: Specifies location of testing data (must be used with -trainingdir)\n",
          "    -trainingdir=<directory>: Specifies location of training data (must be used with -testdir)\n",
          "    -inputdir=<directory>: Specifies location of testing and training data (must be used with -k)\n",
          "    -k=<natural number>: Specifies k-fold size (must be used with -inputdir)\n",
          "    -n=<natural number>: Specifies n-gram size\n",
          "    -L=<natural number>: Specifies profile length (only required for SCAP method)\n",
          "    -tokenfile=<file>: Specifies the file containing the list of feature tokens (only required for Burrows method)\n";
    exit;
}
