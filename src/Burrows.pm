package Burrows;

################################################################################
# Title:   Burrows
# Authors: Ethan Hill, Justin Sassine, Jacob Siegers
# Date:    4 April 2014
# Version: 1.0.5
################################################################################

use strict;
use warnings;

use IPC::Cmd qw(run);
use Console;
use Directory;
use File;
use Validate;
use Report;
use Strip;

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
#   3. ngramSize
#        - scalar size of each n-gram generated
#        - size must be defined, fails otherwise
#        - size must be numeric, fails otherwise
#        - size must be greater than 0, fails otherwise
#   4. keywordFile
#        - scalar name of the file of keywords to parse by
#        - name must be defined, undefined results otherwise
#        - actual file must exist, undefined results otherwise
#        - name must refer to a valid file, undefined results otherwise
# Return:
#   1. scalar 1 on success
################################################################################
sub train {
	my ($inputDirectory, $outputDirectory, $ngramSize, $keywordFile) = @_[1..$#_];
	warn "Input directory is undefined" and return unless defined $inputDirectory;
	warn "Output directory is undefined" and return unless defined $outputDirectory;
	warn "N-gram size is undefined" and return unless defined $ngramSize;
	warn "Input directory $inputDirectory does not exist" and return unless -e $inputDirectory;
	warn "Input directory $inputDirectory is not a valid directory" and return unless -d $inputDirectory;
	warn "N-gram size $ngramSize is not a valid size" and return unless $ngramSize =~ /^[1-9]\d*$/;
	mkdir $outputDirectory unless -e $outputDirectory;
	my @subDirectories = Directory->getSubDirectories($inputDirectory);
	warn "Input directory $inputDirectory does not contain any sub-directories" and return unless @subDirectories;
	my @extensions = qw(h c cpp java H C CPP JAVA);
	my @keywords = File->readContents($keywordFile);
	chomp @keywords;
	my %tokens = Burrows->generateTokens(@keywords);        # Select only one of these (standard)
#	my %tokens = Burrows->generateFixedJavaTokens();        # Select only one of these
#	my %tokens = Burrows->generateFixedCPPTokens();         # Select only one of these
    my $keywordsRegex = Burrows->makeKeywordsRegex(@keywords);
    my $zettairCommand = "\"res/zet\" -i -f \"$outputDirectory/index/index\"";
    my $fileCount = 0;
	foreach my $subDirectory (@subDirectories) {
		Console->printVerbose("Working on $subDirectory...\n");
		mkdir $outputDirectory . '/' . $subDirectory unless -e $outputDirectory . '/' . $subDirectory;
		my @files = Directory->getFiles($inputDirectory . '/' . $subDirectory, 0, @extensions);
		warn "Sub-directory $subDirectory does not contain any matching files" and next unless @files;
        $fileCount += scalar @files;
		my $trecContents = "";
		foreach my $file (@files) {
            Console->printVerbose("Tokenizing file $file\n");
			my @windowedContents = Burrows->tokenizeFile($inputDirectory . '/' . $subDirectory . '/' . $file, $ngramSize, $keywordsRegex, Console->isDebug(), %tokens);
			my $trecLine = Burrows->formatTrecLine($subDirectory . '/' . $file, @windowedContents);
			$trecContents .= $trecLine . "\n";
		}
		Console->printVerbose("Creating TREC file $outputDirectory/$subDirectory/$subDirectory.trec\n\n");
		File->writeContents($outputDirectory . '/' . $subDirectory . '/' . $subDirectory . '.trec', '', $trecContents);
        $zettairCommand .= " \"$outputDirectory/$subDirectory/$subDirectory.trec\"";
	}
	mkdir $outputDirectory . "/index" unless -e $outputDirectory . "/index";
    if(my @prevIndexFiles = Directory->getFiles($outputDirectory . "/index", 1, "0")) {
        unlink @prevIndexFiles or warn "Could not delete previous index" and return;
    }
    Console->printVerbose("Creating index file $outputDirectory/index/index\n\n");
    my $buffer;
    scalar run(command => $zettairCommand, buffer => \$buffer) or warn "Run $zettairCommand failed: $buffer" and return;
    File->writeContents("$outputDirectory/index/index.meta.0", undef, "ngramSize=$ngramSize\n", "keywordFile=$keywordFile\n", "fileCount=$fileCount\n");
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
#   3. outputFile
#        - scalar name of file to be written
#        - name must refer to a valid file, fails otherwise
#        - name may be undefined, no output file is written in this case
# Return:
#   1. scalar 1 on success
################################################################################
sub query {
	my ($inputDirectory, $inputFile, $outputFile, $outputRef) = @_[1..$#_];
	warn "Input directory is undefined" and return unless defined $inputDirectory;
	warn "Input file is undefined" and return unless defined $inputFile;
	warn "Input directory $inputDirectory does not exist" and return unless -e $inputDirectory;
	warn "Input file $inputFile does not exist" and return unless -e $inputFile;
	warn "Input directory $inputDirectory is not a valid directory" and return unless -d $inputDirectory;
	warn "Input file $inputFile is not a valid file" and return unless -f $inputFile;
    my ($ngramSize, $keywordFile, $fileCount) = File->readContents("$inputDirectory/index/index.meta.0");
    chomp ($ngramSize, $keywordFile, $fileCount);
    $ngramSize =~ s/^ngramSize=(\d+)$/$1/;
    $keywordFile =~ s/^keywordFile=(.+)$/$1/;
    $fileCount =~ s/^fileCount=(\d+)$/$1/;
    my @keywords = File->readContents($keywordFile);
    chomp @keywords;
	my %tokens = Burrows->generateTokens(@keywords);        # Select only one of these (standard)
#	my %tokens = Burrows->generateFixedJavaTokens();        # Select only one of these
#	my %tokens = Burrows->generateFixedCPPTokens();         # Select only one of these
    my $keywordsRegex = Burrows->makeKeywordsRegex(@keywords);
    Console->printVerbose("Tokenizing query file $inputFile\n");
    my @windowedContents = Burrows->tokenizeFile($inputFile, $ngramSize, $keywordsRegex, undef, %tokens);
    File->writeContents("$inputDirectory/index/query.temp.0", undef, join(" ", @windowedContents));
    my $zettairCommand = "\"res/zet\" --okapi -f \"$inputDirectory/index/index\" -n $fileCount --query-list=\"$inputDirectory/index/query.temp.0\"";
    my $buffer;
    Console->printVerbose("Running zettair search engine query\n");
    my $result = scalar run(command => $zettairCommand, buffer => \$buffer);
    unlink "$inputDirectory/index/query.temp.0" or warn "Failed to delete $inputDirectory/index/query.temp.0";
    warn "Run $zettairCommand failed: $buffer" and return unless $result;
    my @subDirectories = Directory->getSubDirectories($inputDirectory, 0);
    my %subDirectoryScores;
    foreach my $subDirectory (@subDirectories) {
        next if $subDirectory eq 'index';
        $subDirectoryScores{$subDirectory} = 0;
    }
    # Console->printVerbose($buffer);
    while($buffer =~ /\d+\. (.*?)\/.* \(score (.*), docid/g) {
        warn "Could not find sub-directory $1, skipping..." and next unless exists $subDirectoryScores{$1};
        $subDirectoryScores{$1} = $2 if $2 > $subDirectoryScores{$1};
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
	my ($testDirectory, $trainingDirectory, $inputDirectory, $kFoldSize, $ngramSize, $keywordFile, $reportFile) = @_[1..$#_];
    warn "Directory \"experiment\" already exists, failing to avoid loss of user data" and return if -e "experiment" && -d "experiment";
    mkdir "experiment";
    my $trialsRef;
    my $result;
    if(!defined $kFoldSize && !defined $inputDirectory && defined $testDirectory && defined $trainingDirectory) {
        (undef, undef, $trialsRef, $result) = Burrows->simpleExperiment($testDirectory, $trainingDirectory, $ngramSize, $keywordFile);
        if(defined $reportFile) {
            Console->printVerbose("Writing report file $reportFile\n");
            Report->writeExperimentReport($reportFile, @$trialsRef);
        }
    } elsif(defined $kFoldSize && defined $inputDirectory && !defined $testDirectory && !defined $trainingDirectory) {
        (undef, undef, $trialsRef, $result) = Burrows->kFoldExperiment($inputDirectory, $kFoldSize, $ngramSize, $keywordFile);
        if(defined $reportFile) {
            Console->printVerbose("Writing report file $reportFile\n");
            Report->writeKFExperimentReport($reportFile, @$trialsRef);
        }
    } elsif(!defined $kFoldSize && defined $inputDirectory && !defined $testDirectory && !defined $trainingDirectory) {
        (undef, undef, $trialsRef, $result) = Burrows->leaveOneOutExperiment($inputDirectory, $ngramSize, $keywordFile);
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
    my ($testDirectory, $trainingDirectory, $ngramSize, $keywordFile) = @_[1..$#_];
    mkdir "experiment/temp" or warn "\"experiment/temp\" failed to be made" and return;
    Console->printVerbose("Training...\n");
    Burrows->train($trainingDirectory, "experiment/temp", $ngramSize, $keywordFile) or return;
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
            Burrows->query("experiment/temp", $testDirectory . '/' . $subDirectory . '/' . $doc, undef, \%scores);
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
    my ($inputDirectory, $kFoldSize, $ngramSize, $keywordFile) = @_[1..$#_];
    mkdir "experiment/test" or warn "\"experiment/test\" failed to be made" and return;
    mkdir "experiment/train" or warn "\"experiment/train\" failed to be made" and return;
    my @folds = Validate->createKFolds($inputDirectory, $kFoldSize);
    my @trials;
    my $matches = 0;
    my $total = 0;
    for(my $i = 0; $i < $kFoldSize; ++$i) {
        Validate->populateFolds($inputDirectory, $i, @folds) or return;
        my ($thisMatches, $thisTotal, $thisTrialsRef) = Burrows->simpleExperiment("experiment/test", "experiment/train", $ngramSize, $keywordFile);
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
    my ($inputDirectory, $ngramSize, $keywordFile) = @_[1..$#_];
    mkdir "experiment/test" or warn "\"experiment/test\" failed to be made" and return;
    mkdir "experiment/train" or warn "\"experiment/train\" failed to be made" and return;
    my $outputDirectory = "experiment/train";
    Burrows->train($inputDirectory, $outputDirectory, $ngramSize, $keywordFile);
    my %trials;
    my $matches = 0;
    my $total = 0;
    
    my @subDirectories = Directory->getSubDirectories($inputDirectory);
	warn "Input directory $inputDirectory does not contain any sub-directories" and return unless @subDirectories;
	my @extensions = qw(h c cpp java H C CPP JAVA);
	my @keywords = File->readContents($keywordFile);
	chomp @keywords;
	my %tokens = Burrows->generateTokens(@keywords);        # Select only one of these (standard)
#	my %tokens = Burrows->generateFixedJavaTokens();        # Select only one of these
#	my %tokens = Burrows->generateFixedCPPTokens();         # Select only one of these
    my $keywordsRegex = Burrows->makeKeywordsRegex(@keywords);
    my (undef, undef, $fileCount) = File->readContents("$outputDirectory/index/index.meta.0");
    chomp $fileCount;
    $fileCount =~ s/^fileCount=(\d+)$/$1/;
    --$fileCount;
    mkdir $outputDirectory . "/index" unless -e $outputDirectory . "/index";
    my $zettairCommand = "\"res/zet\" -i -f \"$outputDirectory/index/index\"";
    
    foreach my $subDirectory (@subDirectories) {
        $zettairCommand .= " \"$outputDirectory/$subDirectory/$subDirectory.trec\"";
    }
    
	foreach my $subDirectory (@subDirectories) {
		Console->printVerbose("Working on $subDirectory...\n");
		mkdir $outputDirectory . '/' . $subDirectory unless -e $outputDirectory . '/' . $subDirectory;
		my @files = Directory->getFiles($inputDirectory . '/' . $subDirectory, 0, @extensions);
		warn "Sub-directory $subDirectory does not contain any matching files" and next unless @files;
        my @trecLines;
        
        foreach my $file (@files) {
            Console->printVerbose("Tokenizing file $file\n");
            my @windowedContents = Burrows->tokenizeFile($inputDirectory . '/' . $subDirectory . '/' . $file, $ngramSize, $keywordsRegex, Console->isDebug(), %tokens);
            push(@trecLines, Burrows->formatTrecLine($subDirectory . '/' . $file, @windowedContents));
        }
		Console->printVerbose("\n");
        
        for(my $i = 0; $i < @trecLines; ++$i) {
            my @looLines = @trecLines;
            splice(@looLines, $i, 1);
            my $trecContents = join("\n", @looLines) . "\n";
            Console->printVerbose("Creating TREC file $outputDirectory/$subDirectory/$subDirectory.trec with $files[$i] omitted\n");
            File->writeContents($outputDirectory . '/' . $subDirectory . '/' . $subDirectory . '.trec', '', $trecContents);
            if(my @prevIndexFiles = Directory->getFiles($outputDirectory . "/index", 1, "0")) {
                unlink @prevIndexFiles or warn "Could not delete previous index" and return;
            }
            Console->printVerbose("Creating index file $outputDirectory/index/index\n");
            my $buffer;
            scalar run(command => $zettairCommand, buffer => \$buffer) or warn "Run $zettairCommand failed: $buffer" and return;
            File->writeContents("$outputDirectory/index/index.meta.0", undef, "ngramSize=$ngramSize\n", "keywordFile=$keywordFile\n", "fileCount=$fileCount\n");
            
            my %scores;
            print "Querying $files[$i]...\n";
            Burrows->query("experiment/train", $inputDirectory . '/' . $subDirectory . '/' . $files[$i], undef, \%scores);
            my $attributedAuthor = (sort{$scores{$b} <=> $scores{$a}} keys %scores)[0];
            $matches++ if $subDirectory eq $attributedAuthor;
            
            print "\n";
            $trials{$subDirectory} = [] if !exists $trials{$subDirectory};
            push(@{$trials{$subDirectory}}, {file => $files[$i], author => $subDirectory, attributed => $attributedAuthor, scores => \%scores});
        }
        
        $total += @files;
        Console->printVerbose("Resetting $subDirectory.trec\n");
        my $trecContents = join("\n", @trecLines) . "\n";
        Console->printVerbose("Creating TREC file $outputDirectory/$subDirectory/$subDirectory.trec\n\n");
        File->writeContents($outputDirectory . '/' . $subDirectory . '/' . $subDirectory . '.trec', '', $trecContents);
        
	}
    
    print "$matches files out of $total correctly attributed (" . ($matches / $total) * 100 . "%)\n";
    Directory->removeDirectory("experiment/test", 1);
    Directory->removeDirectory("experiment/train", 1);
    return ($matches, $total, \%trials, 1);
}

sub tokenizeFile {
    my ($file, $ngramSize, $keywordsRegex, $writeIntermediates, %tokens) = @_[1..$#_];
    my $contents = File->readContents($file, ':raw');
    my $anonymizedContents = Burrows->anonymizeContents($contents);
    my @keywordContents = Burrows->retainKeywords($anonymizedContents, $keywordsRegex);
    my @tokenizedContents = Burrows->tokenizeKeywords(\@keywordContents, %tokens);
    my @windowedContents = Burrows->alignWindow($ngramSize, @tokenizedContents);
    if($writeIntermediates) {
        File->writeContents($file . '.1', ':raw', $anonymizedContents);
        File->writeContents($file . '.2', ':raw', @keywordContents);
        File->writeContents($file . '.3', undef, join("\n", @tokenizedContents));
        File->writeContents($file . '.4', undef, join(' ', @windowedContents));
    }
    return @windowedContents;
}

sub anonymizeContents {
	if(defined wantarray) {
		my $contents = $_[1];
		$contents = Strip->removeCComments($contents);
		$contents = Strip->removeCPPComments($contents);
		$contents = Strip->removeStringLiterals($contents);
		return $contents;
	} else {
		Strip->removeCComments($_[1]);
		Strip->removeCPPComments($_[1]);
		Strip->removeStringLiterals($_[1]);
	}
	return 1;
}

sub retainKeywords {
	my ($contents, $keywordsRegex) = @_[1..$#_];
	warn "Contents are undefined" and return unless defined $contents;
	warn "Keywords regular expression is undefined" and return unless $keywordsRegex;
	my @retainedKeywords;
	while($contents =~ /\G.*?($keywordsRegex)/gs) {
		push(@retainedKeywords, $1);
	}
	return @retainedKeywords;
}

sub tokenizeKeywords {
	my ($keywordsRef, %tokens) = @_[1..$#_];
	warn "Keywords are undefined" and return unless defined $keywordsRef;
	warn "Keywords are invalid" and return unless ref $keywordsRef eq 'ARRAY';
	warn "Tokens are undefined" and return unless %tokens;
	my @tokenizedContents;
	foreach(@$keywordsRef) {
		my $keyword = $_;		# Don't change this! Needed to keep from altering
		                        # the values in the passed array!
		if($keyword eq "\r\n") {
			$keyword = "\\r\\n";
		} elsif($keyword eq "\r") {
			$keyword = "\\r";
		} elsif($keyword eq "\n") {
			$keyword = "\\n";
		} elsif($keyword eq "\t") {
			$keyword = "\\t";
		}
		push(@tokenizedContents, $tokens{$keyword});
	}
	return @tokenizedContents;
}

sub alignWindow {
	my ($windowSize, @tokenizedContents) = @_[1..$#_];
	warn "Tokenized contents are undefined" and return unless @tokenizedContents;
	warn "Window size is undefined" and return unless defined $windowSize;
	warn "Window size is invalid" and return unless $windowSize =~ /^[1-9]\d*$/;
	my @windowedContents;
	for(my $i = 0; $i < $#tokenizedContents - $windowSize; $i++) {
		my $window = "";
		for(my $j = 0; $j < $windowSize; $j++) {
			$window .= $tokenizedContents[$i + $j];
		}
		push(@windowedContents, $window);
	}
	return @windowedContents;
}

sub formatTrecLine {
	my ($filename, @windowedContents) = @_[1..$#_];
	warn "File name is undefined" and return unless defined $filename;
	warn "Windowed contents are undefined" and return unless @windowedContents;
	return "<DOC><DOCNO>" . $filename . "</DOCNO>" . join(" ", @windowedContents) . "</DOC>";
}

sub generateTokens {
	my (@keywords) = @_[1..$#_];
	warn "Keywords are undefined" and return unless @keywords;
	my $width = log($#keywords) / log(26);
	$width = int($width) + 1 if $width - int($width) != 0;
	my $token;
	for(1..$width) {
		$token .= 'A';
	}
	my %tokens;
	foreach my $keyword (@keywords) {
		$tokens{$keyword} = $token++;
	}
	return %tokens;
}

sub generateFixedCPPTokens {
	my %tokens = (
        #keywords
        "reinterpret_cast" => "QA",
        "static_cast" => "QB",
        "namespace" => "QC",
        "operator" => "QD",
        "template" => "QE",
        "typename" => "QF",
        "virtual" => "QG",
        "wchar_t" => "QH",
        "typeid" => "QI",
        "using" => "QJ",
        "true" => "QK",
        "const_cast" => "ZE",
        "dynamic_cast" => "ZF",
        "auto" => "ZG",
        "extern" => "ZH",
        "register" => "ZI",
        "unsigned" => "ZJ",
        "signed" => "ZK",
        "sizeof" => "ZL",
        "struct" => "ZM",
        "typedef" => "ZN",
        "union" => "ZO",
        "asm" => "ZP",
        "bool" => "ZQ",
        "delete" => "ZR",
        "explicit" => "ZS",
        "export" => "ZT",
        "false" => "ZU",
        "friend" => "ZV",
        "inline" => "ZW",
        "mutable" => "ZX",
        "break" => "BR",
        "case" => "CA",
        "catch" => "CT",
        "char" => "CH",
        "class" => "CL",
        "const" => "CN",
        "continue" => "CO",
        "default" => "DF",
        "do" => "DO",
        "double" => "DU",
        "else" => "EL",
        "enum" => "EN",
        "float" => "FL",
        "for" => "FO",
        "goto" => "GO",
        "if" => "IF",
        "int" => "IN",
        "long" => "LO",
        "new" => "NW",
        "private" => "PR",
        "protected" => "PT",
        "public" => "PU",
        "return" => "RN",
        "short" => "SH",
        "static" => "ST",
        "switch" => "SW",
        "this" => "TH",
        "throw" => "TR",
        "try" => "TY",
        "void" => "VO",
        "volatile" => "VL",
        "while" => "WH",

        #operators
        "->*" => "ZA",
        '.*' => "ZB",
        "::" => "ZC",
        "->" => "ZD",
        "<<=" => "SE",
        ">>=" => "RE",
        ">>" => "RS",
        "<<" => "LS",
        "||" => "OR",
        "&&" => "AN",
        "==" => "EQ",
        "!=" => "NE",
        ">=" => "GE",
        "<=" => "LE",
        "++" => "IC",
        "--" => "DC",
        "+=" => "PE",
        "-=" => "UE",
        "*=" => "TE",
        "/=" => "DE",
        "%=" => "ME",
        "&=" => "AE",
        "^=" => "EE",
        "|=" => "OE",
        "=" => "AS",
        "+" => "AD",
        "-" => "SU",
        "*" => "MU",
        "/" => "DI",
        "%" => "MD",
        "!" => "NO",
        ">" => "GT",
        "<" => "LT",
        "?" => "II",
        "~" => "BC",
        "&" => "BA",
        "^" => "BE",
        "|" => "BO",
        "[" => "OI",
        "(" => "OP",
        "," => "CM",
        "." => "DT",

        #whitespace
        "\\n" => "XN",
        "\\r" => "XR",
        "\\t" => "XT",
        " " => "XS",
    );
	return %tokens;
}

sub generateFixedJavaTokens {
	my %tokens = (
        #keywords
        "abstract" => "AB",
        "assert" => "AT",
        "boolean" => "BL",
        "break" => "BR",
        "byte" => "BY",
        "case" => "CA",
        "catch" => "CT",
        "char" => "CH",
        "class" => "CL",
        "const" => "CN",
        "continue" => "CO",
        "default" => "DF",
        "do" => "DO",
        "double" => "DU",
        "else" => "EL",
        "enum" => "EN",
        "extends" => "EX",
        "final" => "FI",
        "finally" => "FY",
        "float" => "FL",
        "for" => "FO",
        "goto" => "GO",
        "if" => "IF",
        "implements" => "IM",
        "import" => "IP",
        "instanceof" => "IO",
        "int" => "IN",
        "interface" => "IE",
        "long" => "LO",
        "native" => "NA",
        "new" => "NW",
        "package" => "PA",
        "private" => "PR",
        "protected" => "PT",
        "public" => "PU",
        "return" => "RN",
        "short" => "SH",
        "static" => "ST",
        "strictfp" => "SR",
        "super" => "SP",
        "switch" => "SW",
        "synchronized" => "SY",
        "this" => "TH",
        "throw" => "TR",
        "throws" => "TS",
        "transient" => "TA",
        "try" => "TY",
        "void" => "VO",
        "volatile" => "VL",
        "while" => "WH",

        #operators
        ">>>=" => "XX",
        ">>>" => "US",
        "<<=" => "SE",
        ">>=" => "RE",
        ">>" => "RS",
        "<<" => "LS",
        "||" => "OR",
        "&&" => "AN",
        "==" => "EQ",
        "!=" => "NE",
        ">=" => "GE",
        "<=" => "LE",
        "++" => "IC",
        "--" => "DC",
        "+=" => "PE",
        "-=" => "UE",
        "*=" => "TE",
        "/=" => "DE",
        "%=" => "ME",
        "&=" => "AE",
        "^=" => "EE",
        "|=" => "OE",
        "=" => "AS",
        "+" => "AD",
        "-" => "SU",
        "*" => "MU",
        "/" => "DI",
        "%" => "MD",
        "!" => "NO",
        ">" => "GT",
        "<" => "LT",
        "?" => "II",
        "~" => "BC",
        "&" => "BA",
        "^" => "BE",
        "|" => "BO",
        "[" => "OI",
        "(" => "OP",
        "." => "DT",

        #whitespace
        "\\n" => "XN",
        "\\r" => "XR",
        "\\t" => "XT",
        " " => "XS",
    );
	return %tokens;
}

sub makeKeywordsRegex {
	my (@keywords) = @_[1..$#_];
    warn "Keywords are undefined" and return unless @keywords;
	my $keywordsRegex;
	foreach my $keyword (sort{length $b <=> length $a} @keywords) {
		$keywordsRegex .= '|' if defined $keywordsRegex;
		if($keyword =~ /^\w+$/) {
			$keywordsRegex .= '\\b' . $keyword . '\\b';
		} elsif($keyword =~ /^(\\\w)+$/) {
			$keywordsRegex .= $keyword;
		} else {
			$keyword =~ s/([^\w\s\\])(.*?)/\\$1$2/gs;
			$keywordsRegex .= $keyword;
		}
	}
	return $keywordsRegex;
}

sub countAllFiles {
    my ($directory) = @_[1..$#_];
    warn "Directory is undefined" and return unless defined $directory;
    warn "Directory $directory does not exist" and return unless -e $directory;
    warn "Directory $directory is not a valid directory" and return unless -d $directory;
    my @subDirectories = Directory->getSubDirectories($directory, 1);
    my $fileCount = 0;
    foreach my $subDirectory (@subDirectories) {
        my @files = Directory->getFiles($subDirectory, 1, 'trec');
        foreach my $file (@files) {
            my @contents = File->readContents($file);
            $fileCount += scalar @contents;
        }
    }
    return $fileCount;
}

return 1;
