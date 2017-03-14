BEGIN {chdir "../../src" or die "Could not change directory";}

use strict;
use warnings;

use Burrows;
use Scap;

my $testDirectory = "../test/dataset1/test";
my $trainingDirectory = "../test/dataset1/train";
my $inputDirectory = "../test/dataset1/train";
my $kFoldSize = 3;
my $ngramSize = 6;
my $ngramLimit = 2000;
my $keywordFile = "../resource/JavaTokens.txt";

Burrows->experiment($testDirectory, $trainingDirectory, undef, undef, $ngramSize, $keywordFile);
print "\n========================================\n",
      "========================================\n\n";
Burrows->experiment(undef, undef, $inputDirectory, $kFoldSize, $ngramSize, $keywordFile);
print "\n========================================\n",
      "========================================\n\n";
Burrows->experiment(undef, undef, $inputDirectory, undef, $ngramSize, $keywordFile);
print "\n========================================\n",
      "========================================\n\n";

Scap->experiment($testDirectory, $trainingDirectory, undef, undef, $ngramSize, $ngramLimit);
print "\n========================================\n",
      "========================================\n\n";
Scap->experiment(undef, undef, $inputDirectory, $kFoldSize, $ngramSize, $ngramLimit);
print "\n========================================\n",
      "========================================\n\n";
Scap->experiment(undef, undef, $inputDirectory, undef, $ngramSize, $ngramLimit);
print "\n========================================\n",
      "========================================\n\n";
