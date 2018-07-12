package Scap;

################################################################################
# Title:   Scap
# Authors: Ethan Hill, Justin Sassine, Matthew Tennyson
# Date:    11 April 2014
################################################################################

use strict;
use warnings;

use Text::Ngrams;
use Console;
use Directory;
use File;
use Validate;
use Report;

################################################################################
# Subroutine: train
# Params:
#   1. inputDirectory
#        - scalar name of the root directory to search in
#        - name must be defined, fails otherwise
#        - actual directory must exist, fails otherwise
#        - name must refer to a valid directory, fails otherwise
#   2. outputDirectory
#        - scalar name of directory to output to
#        - name must be defined, fails otherwise
#        - name must refer to a valid directory, fails otherwise
# Return:
#   1. scalar 1 on success
################################################################################
sub train {
	my ($inputDirectory, $outputDirectory) = @_[1..$#_];
	warn "Input directory is undefined" and return unless defined $inputDirectory;
	warn "Output directory is undefined" and return unless defined $outputDirectory;
	warn "Input directory $inputDirectory does not exist" and return unless -e $inputDirectory;
	warn "Input directory $inputDirectory is not a valid directory" and return unless -d $inputDirectory;
	mkdir $outputDirectory unless -e $outputDirectory;
	my @subDirectories = Directory->getSubDirectories($inputDirectory);
	warn "Input directory $inputDirectory does not contain any sub-directories" unless @subDirectories;
	my @extensions = qw(h c cpp java H C CPP JAVA);
	foreach(@subDirectories) {
		mkdir $outputDirectory . '/' . $_ unless -e $outputDirectory . '/' . $_;
		my @files = Directory->getFiles($inputDirectory . '/' . $_, 1, @extensions);
		warn "Sub-directory $_ does not contain any matching files" and next unless @files;
		my $joinedContent = File->joinContents("", ":raw", @files);
		Console->printVerbose("Creating concatenated file $outputDirectory/$_/$_.scap\n");
		File->writeContents($outputDirectory . '/' . $_ . '/' . $_ . '.scap', ':raw', $joinedContent);
	}
	Console->printVerbose("\n");
	return 1;
}

################################################################################
# Subroutine: query
# Params:
#   1. inputDirectory
#        - scalar name of the training directory to query against
#        - name must be defined, fails otherwise
#        - actual directory must exist, fails otherwise
#        - name must refer to a valid directory, fails otherwise
#   2. inputFile
#        - scalar name of the file being queried
#        - name must be defined, fails otherwise
#        - actual file must exist, fails otherwise
#        - name must refer to a valid file, fails otherwise
#   3. ngramSize
#        - scalar size of each n-gram generated
#        - size must be defined, fails otherwise
#        - size must be numeric, fails otherwise
#        - size must be greater than 0, fails otherwise
#   4. ngramLimit
#        - scalar limit of number of n-grams that can be generated
#        - limit must be numeric, fails otherwise
#        - limit must be greater than 0, fails otherwise
#        - limit may be undefined, no limit on n-grams in this case
#   5. outputFile
#        - scalar name of file to be written
#        - name must refer to a valid file, fails otherwise
#        - name may be undefined, no output file is written in this case
# Return:
#   1. scalar 1 on success
################################################################################
sub query {
	my ($inputDirectory, $inputFile, $ngramSize, $ngramLimit, $outputFile, $outputRef) = @_[1..$#_];
	warn "Input directory is undefined" and return unless defined $inputDirectory;
	warn "Input file is undefined" and return unless defined $inputFile;
	warn "N-gram size is undefined" and return unless defined $ngramSize;
	warn "Input directory $inputDirectory does not exist" and return unless -e $inputDirectory;
	warn "Input file $inputFile does not exist" and return unless -e $inputFile;
	warn "Input directory $inputDirectory is not a valid directory" and return unless -d $inputDirectory;
	warn "Input file $inputFile is not a valid file" and return unless -f $inputFile;
	warn "N-gram size $ngramSize is not a valid size" and return unless $ngramSize =~ /^0*[1-9]\d*$/;
	warn "N-gram limit $ngramLimit is not a valid limit" and return unless !defined $ngramLimit || $ngramLimit =~ /^0*[1-9]\d*$/;
	Console->printDebug(">>>>CREATING N-GRAMS OBJECT...\n");
    my $inputFileNgramsObject = Text::Ngrams->new(type => 'byte', windowsize => $ngramSize);
	Console->printVerbose("Creating n-grams for query file $inputFile\n");
	$inputFileNgramsObject->process_files($inputFile);
    Console->printDebug(">>>>GETTING N-GRAMS FOR $inputFile...\n");
	my %inputFileNgrams = $inputFileNgramsObject->get_ngrams(orderby => 'frequency', onlyfirst => $ngramLimit, spartan => 1);
	warn "Input file $inputFile did not generate any N-grams" and return unless %inputFileNgrams;
    Console->printDebug(">>>>GETTING SUB-DIRECTROIES FROM $inputDirectory...\n");
	my @subDirectories = Directory->getSubDirectories($inputDirectory);
	warn "Input directory $inputDirectory does not contain any sub-directories" and return unless @subDirectories;
	my %subDirectoryScores;
	foreach(@subDirectories) {
		my $file = $inputDirectory . '/' . $_ . '/' . $_ . '.scap';
		warn "Sub-directory $_ does not contain ${_}.scap" and next unless -e $file;
        Console->printDebug(">>>>CREATING N-GRAMS OBJECT FOR $_...\n");
		my $subDirectoryNgramsObject = Text::Ngrams->new(type => 'byte', windowsize => $ngramSize);
        Console->printDebug(">>>>CREATING N-GRAMS FOR $_...\n");
		$subDirectoryNgramsObject->process_files($file);
        Console->printDebug(">>>>GETTING N-GRAMS FOR $_...\n");
		my %subDirectoryNgrams = $subDirectoryNgramsObject->get_ngrams(orderby => 'frequency', onlyfirst => $ngramLimit, spartan => 1);
		warn "File ${_}.scap did not generate any N-grams" unless %subDirectoryNgrams;
		my $subDirectoryScore = 0;
		Console->printVerbose("Comparing query file to $file\n") if !Console->isDebug();
        Console->printDebug(">>>>COMPARING TO $file...");
		if(scalar keys %subDirectoryNgrams <= scalar keys %inputFileNgrams) {
			foreach(keys %subDirectoryNgrams) {
				$subDirectoryScore++ if exists $inputFileNgrams{$_};
			}
		} else {
			foreach(keys %inputFileNgrams) {
				$subDirectoryScore++ if exists $subDirectoryNgrams{$_};
			}
		}
        Console->printDebug("DONE\n");
		$subDirectoryScores{$_} = $subDirectoryScore;
	}
	if(defined $outputFile) {
		Console->printVerbose("Writing report file $outputFile\n");
		Report->writeQueryReport($outputFile, %subDirectoryScores);
	}
	print "\nMatching author(s):\n";
	Report->printQueryResults(%subDirectoryScores);
    %$outputRef = %subDirectoryScores if defined $outputRef;
	return 1;
}

################################################################################
# Subroutine: experiment
# Return:
#   1. scalar 1 on success
################################################################################
sub experiment {
	my ($testDirectory, $trainingDirectory, $inputDirectory, $kFoldSize, $ngramSize, $ngramLimit, $reportFile) = @_[1..$#_];
    warn "Directory \"experiment\" already exists, failing to avoid loss of user data" and return if -e "experiment" && -d "experiment";
    mkdir "experiment";
    my $trialsRef;
    my $result;
    if(!defined $kFoldSize && !defined $inputDirectory && defined $testDirectory && defined $trainingDirectory) {
        (undef, undef, $trialsRef, $result) = Scap->simpleExperiment($testDirectory, $trainingDirectory, $ngramSize, $ngramLimit);
        if(defined $reportFile) {
            Console->printVerbose("Writing report file $reportFile\n");
            Report->writeExperimentReport($reportFile, @$trialsRef);
        }
    } elsif(defined $kFoldSize && defined $inputDirectory && !defined $testDirectory && !defined $trainingDirectory) {
        (undef, undef, $trialsRef, $result) = Scap->kFoldExperiment($inputDirectory, $kFoldSize, $ngramSize, $ngramLimit);
        if(defined $reportFile) {
            Console->printVerbose("Writing report file $reportFile\n");
            Report->writeKFExperimentReport($reportFile, @$trialsRef);
        }
    } elsif(!defined $kFoldSize && defined $inputDirectory && !defined $testDirectory && !defined $trainingDirectory) {
        (undef, undef, $trialsRef, $result) = Scap->leaveOneOutExperiment($inputDirectory, $ngramSize, $ngramLimit);
        if(defined $reportFile) {
            Console->printVerbose("Writing report file $reportFile\n");
            Report->writeLOOExperimentReport($reportFile, %$trialsRef);
        }
    } else {
        warn "Input does not match any known method" and return;
    }
    Directory->removeDirectory("experiment", 1);
	return $result;
}

sub simpleExperiment {
    my ($testDirectory, $trainingDirectory, $ngramSize, $ngramLimit) = @_[1..$#_];
    mkdir "experiment/temp" or warn "\"experiment/temp\" failed to be made" and return;
    Console->printVerbose("Training...\n");
    Scap->train($trainingDirectory, "experiment/temp") or return;
    Console->printVerbose("\n");
    my @trials;
    my $matches = 0;
    my $total = 0;
    my @subDirectories = Directory->getSubDirectories($testDirectory, 0);
    foreach my $subDirectory (@subDirectories) {
        my @testFiles = Directory->getFiles($testDirectory . '/' . $subDirectory, 0, qw(h c cpp java H C CPP JAVA));
        foreach my $doc (@testFiles) {
            my %scores;
            print "Querying $doc...\n";
            Scap->query("experiment/temp", $testDirectory . '/' . $subDirectory . '/' . $doc, $ngramSize, $ngramLimit, undef, \%scores);
            my $attributedAuthor = (sort{$scores{$b} <=> $scores{$a}} keys %scores)[0];
            $matches++ if $subDirectory eq $attributedAuthor;
            push(@trials, {file => $doc, author => $subDirectory, attributed => $attributedAuthor, scores => \%scores});
			print "\n";
        }
        $total += scalar @testFiles;
    }
    print "\n$matches files out of $total correctly attributed (" . ($matches / $total) * 100 . "%)\n";
    Directory->removeDirectory("experiment/temp", 1);
    return ($matches, $total, \@trials, 1);
}

sub kFoldExperiment {
    my ($inputDirectory, $kFoldSize, $ngramSize, $ngramLimit) = @_[1..$#_];
    mkdir "experiment/test" or warn "\"experiment/test\" failed to be made" and return;
    mkdir "experiment/train" or warn "\"experiment/train\" failed to be made" and return;
    my @folds = Validate->createKFolds($inputDirectory, $kFoldSize);
    my @trials;
    my $matches = 0;
    my $total = 0;
    for(my $i = 0; $i < $kFoldSize; ++$i) {
        Validate->populateFolds($inputDirectory, $i, @folds) or return;
        my ($thisMatches, $thisTotal, $thisTrialsRef) = Scap->simpleExperiment("experiment/test", "experiment/train", $ngramSize, $ngramLimit);
		print "\n";
        $matches += $thisMatches;
        $total += $thisTotal;
        push(@trials, $thisTrialsRef);
    }
    print "$matches files out of $total correctly attributed (" . ($matches / $total) * 100 . "%) over $kFoldSize folds\n";
    Directory->removeDirectory("experiment/test", 1);
    Directory->removeDirectory("experiment/train", 1);
    return ($matches, $total, \@trials, 1);
}

sub leaveOneOutExperiment {
    my ($inputDirectory, $ngramSize, $ngramLimit) = @_[1..$#_];
    mkdir "experiment/train" or warn "\"experiment/train\" failed to be made" and return;
    my $outputDirectory = "experiment/train";
    Console->printDebug(">>>>TRAINING...\n");
    Scap->train($inputDirectory, $outputDirectory);
    my %trials;
    my $matches = 0;
    my $total = 0;
    Console->printDebug(">>>>GETTING SUB-DIRECTORIES FROM $inputDirectory...\n");
    my @subDirectories = Directory->getSubDirectories($inputDirectory);
	warn "Input directory $inputDirectory does not contain any sub-directories" and return unless @subDirectories;

    #create n-grams from each author's concatenated files (which were created during training)
    my %authorNgrams = ();
    my %authorNgrams_full = ();
    foreach my $subDirectory (@subDirectories) {
        Console->printVerbose("Creating author profile for $subDirectory...\n");
        my $ngramObject = Text::Ngrams->new(type => 'byte', windowsize => $ngramSize);
        $ngramObject->process_files("$outputDirectory/$subDirectory/$subDirectory.scap");
        my %ngrams = $ngramObject->get_ngrams(orderby => 'frequency', onlyfirst => $ngramLimit, spartan => 1);
        my %ngrams_full = $ngramObject->get_ngrams(orderby => 'frequency', spartan => 1);
        $authorNgrams{$subDirectory} = \%ngrams;
        $authorNgrams_full{$subDirectory} = \%ngrams_full;
    }
    print "\n";

	my @extensions = qw(h c cpp java H C CPP JAVA);
	foreach my $subDirectory (@subDirectories)
    {
        #get list of file names
		my @files = Directory->getFiles($inputDirectory . '/' . $subDirectory, 0, @extensions);
		warn "Sub-directory $subDirectory does not contain any matching files" and next unless @files;

        #get list of full file paths
		my @fullFiles = Directory->getFiles($inputDirectory . '/' . $subDirectory, 1, @extensions);

        #loop through each individual file in the directory
        for(my $i = 0; $i < @files; ++$i)
        {
            Console->printVerbose("Converting $files[$i] to n-grams...\n");
            my $ngramObject = Text::Ngrams->new(type => 'byte', windowsize => $ngramSize);
            $ngramObject->process_files($fullFiles[$i]);
            my %filengrams = $ngramObject->get_ngrams(orderby => 'frequency', onlyfirst => $ngramLimit, spartan => 1);
            my %filengrams_full = $ngramObject->get_ngrams(orderby => 'frequency', spartan => 1);

            my %scores = ();
            print "Omitting $files[$i] from $subDirectory profile...\n";

            #remove the query file from the corresponding author profile for the "leave-one-out" experiment
            my $hashref = $authorNgrams_full{$subDirectory};
            my %temp = %$hashref;

            foreach my $key (keys %temp)
            {
                if(exists $filengrams_full{$key})
                {
                    $temp{$key} -= $filengrams_full{$key};
                    if($temp{$key}<=0) { delete $temp{$key}; }
                }
            }
            
            #retain only the most-frequent n-grams
            my $count = 0;
            my %tempprofile = (); #this will be the author's profile with the file omitted
            foreach my $key (sort {$temp{$b} <=> $temp{$a}} keys %temp)
            {
                $tempprofile{$key} = $temp{$key};
                if(++$count==$ngramLimit) { last; }
            }
            
            #compare the file to the profile
            print "Comparing $files[$i] to $subDirectory... ";

            my %union = ();
            my %isect = ();
            foreach my $e (keys %filengrams, keys %tempprofile) { $union{$e}++ && $isect{$e}++ }

            print "found ", scalar(keys %isect), " n-grams in common.\n";
            $scores{$subDirectory} = scalar(keys %isect);

            #compare the file to the rest of the author profiles
            foreach my $author (keys %authorNgrams)
            {
                if($author ne $subDirectory)
                {
                    print "Comparing $files[$i] to $author... ";
                    
                    %union = ();
                    %isect = ();

                    my $profile = $authorNgrams{$author};

                    #compare the file to the profile
                    foreach my $e (keys %filengrams, keys %$profile) { $union{$e}++ && $isect{$e}++ }
                    print "found ", scalar(keys %isect), " n-grams in common.\n";
                    $scores{$author} = scalar(keys %isect);
                }
            }

            my $attributedAuthor = (sort{$scores{$b} <=> $scores{$a}} keys %scores)[0];
            print "Attributed author: $attributedAuthor\n\n";

            $matches++ if $subDirectory eq $attributedAuthor;
            push(@{$trials{$subDirectory}}, {file => $files[$i], author => $subDirectory, attributed => $attributedAuthor, scores => \%scores});
        }
        $total += @files;
	}
    print "$matches files out of $total correctly attributed (" . ($matches / $total) * 100 . "%)\n";
    Console->printDebug(">>>>REMOVING /train...\n");
    Directory->removeDirectory("experiment/train", 1);
    Console->printDebug(">>>>DONE.\n");
    return ($matches, $total, \%trials, 1);
}

return 1;
