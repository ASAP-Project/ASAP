package Validate;

################################################################################
# Title:   Validate
# Authors: Ethan Hill
# Date:    21 February 2014
# Version: 1.0.1
################################################################################

use strict;
use warnings;

use Directory;
use File;

sub createKFolds {
    my ($directory, $kFoldSize) = @_[1..$#_];
    warn "Directory is undefined" and return unless defined $directory;
    warn "K-fold size is undefined" and return unless defined $kFoldSize;
    warn "Directory $directory does not exist" and return unless -e $directory;
    warn "Directory $directory is not a valid directory" and return unless -d $directory;
    warn "K-fold size of $kFoldSize is not a valid size" and return unless $kFoldSize =~ /^0*[1-9]\d*$/;
    my @folds;
    for(my $i = 0; $i < $kFoldSize; ++$i) {
        $folds[$i] = {};
    }
    my @subDirectories = Directory->getSubDirectories($directory, 0);
    warn "Directory $directory does not contain any sub-directories" and return unless @subDirectories;
    my $foldIndex = 0;
    foreach my $subDirectory (@subDirectories) {
        my @files = Directory->getFiles($directory . '/' . $subDirectory, 0, qw(h c cpp java H C CPP JAVA));
        warn "Sub-directory $subDirectory does not contain any matching files, skipping" and next unless @files;
        warn "Sub-directory $subDirectory does not contain enough files to create a k-fold size of $kFoldSize" and return unless scalar @files >= $kFoldSize;
        for(my $i = 0; $i < $kFoldSize; ++$i) {
            $folds[$i]->{$subDirectory} = [];
        }
        while(@files) {
            push(@{$folds[$foldIndex]->{$subDirectory}}, splice(@files, int(rand scalar @files), 1));
            $foldIndex = ($foldIndex + 1) % $kFoldSize;
        }
    }
    return @folds;
}

sub createLeaveOneOutFolds {
    my ($directory) = @_[1..$#_];
    warn "Directory is undefined" and return unless defined $directory;
    warn "Directory $directory does not exist" and return unless -e $directory;
    warn "Directory $directory is not a valid directory" and return unless -d $directory;
    my @folds;
    my @subDirectories = Directory->getSubDirectories($directory, 0);
    warn "Directory $directory does not contain any sub-directories" and return unless @subDirectories;
    foreach my $subDirectory (@subDirectories) {
        my @files = Directory->getFiles($directory . '/' . $subDirectory, 0, qw(h c cpp java H C CPP JAVA));
        warn "Sub-directory $subDirectory does not contain any matching files, skipping" and next unless @files;
        foreach my $file (@files) {
            push(@folds, {$subDirectory => [$file]});
        }
    }
    return @folds;
}

sub populateFolds {
    my ($directory, $testFoldIndex, @folds) = @_[1..$#_];
    warn "Test-fold index is undefined" and return unless defined $testFoldIndex;
    warn "Folds are missing" and return unless @folds;
    warn "Test-fold index $testFoldIndex is not a valid index" and return unless $testFoldIndex =~ /^\d+$/;
    warn "Test-fold index $testFoldIndex is an illegal index" and return unless $testFoldIndex < @folds;
    my @subDirectories = Directory->getSubDirectories("experiment/test", 1);
    foreach my $subDirectory (@subDirectories) {
        Directory->removeDirectory($subDirectory, 0) or warn "Removal of test files failed" and return;
    }
    @subDirectories = Directory->getSubDirectories("experiment/train", 1);
    foreach my $subDirectory (@subDirectories) {
        Directory->removeDirectory($subDirectory, 0) or warn "Removal of training files failed" and return;
    }
    for(my $i = 0; $i < @folds; ++$i) {
        my $targetDirectory = $i == $testFoldIndex ? "experiment/test" : "experiment/train";
        foreach my $author (keys %{$folds[$i]}) {
            mkdir $targetDirectory . '/' . $author if !-e $targetDirectory . '/' . $author;
            foreach my $file (@{$folds[$i]->{$author}}) {
                my @contents = File->readContents($directory . '/' . $author . '/' . $file, ':raw');
                File->writeContents($targetDirectory . '/' . $author . '/' . $file, ':raw', @contents);
            }
        }
    }
    return 1;
}

return 1;
