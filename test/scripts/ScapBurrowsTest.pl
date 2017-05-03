BEGIN {chdir "../../src" or die "Could not change directory";}

use strict;
use warnings;

use Burrows;
use Console;
use Scap;

Console->setVerbose(1);

my $trainingDirectory = "../test/dataset1/train";
my $outputDirectory = "../test/scripts/train";
my $queryDoc = "../test/dataset1/test/AuthorA/queryA.java";
my $windowSize = 6;
my $ngramLimit = 2000;
my $keywordFile = "../resource/JavaTokens.txt";
my $reportSCAPFile = "../test/scripts/train/reportSCAP.xls";
my $reportBurrowsFile = "../test/scripts/train/reportBurrows.xls";

Scap->train($trainingDirectory, $outputDirectory);
Burrows->train($trainingDirectory, $outputDirectory, $windowSize, $keywordFile);

Scap->query($outputDirectory, $queryDoc, $windowSize, $ngramLimit, $reportSCAPFile);
Burrows->query($outputDirectory, $queryDoc, $reportBurrowsFile);

#Scap->experiment();
#Burrows->experiment();
