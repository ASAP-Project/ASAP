package File;

################################################################################
# Title:   File
# Authors: Ethan Hill
# Date:    22 January 2014
# Version: 1.0.0
################################################################################

use strict;
use warnings;

################################################################################
# Subroutine: readContents
# Params:
#   1. file
#        - scalar name of the file to be read
#        - name must be defined, fails otherwise
#        - actual file must exist, fails otherwise
#        - name must refer to a valid file, fails otherwise
#   2. inputMode
#        - scalar representation of the file input mode
#        - representation must consist of the following modes:
#            :raw  :bytes  :crlf  :utf8  :std  :locale  :encoding(...)
#        - modes can be combined in the form of ':mode1:mode2...'
#        - representation may be undefined, file is read in the default text
#            (:crlf) mode in this case
# Return:
#   1. list of lines of text read from the file if the caller expects a list
#   2. scalar content of the file if the caller expects a scalar
################################################################################
sub readContents {
	my ($file, $inputMode) = @_[1..$#_];
	warn "File not specified" and return unless defined $file;
	warn "$file does not exist" and return unless -e $file;
	warn "$file is an invalid file" and return unless -f $file;
	my @contentList = ();
	open(my $fileHandle, "<", $file) or warn "Failed to open $file" and return;
	binmode($fileHandle, $inputMode) if defined $inputMode;
	until(eof $fileHandle) {
		my $fileItem = <$fileHandle>;
		warn "Failed while reading $file" and return unless defined $fileItem;
		push(@contentList, $fileItem);
	}
	close $fileHandle or warn "Failed to close $file";
	return wantarray ? @contentList : join("", @contentList);
}

################################################################################
# Subroutine: writeContents
# Params:
#   1. file
#        - scalar name of the file to be written
#        - name must be defined, fails otherwise
#        - name must refer to a valid file, fails otherwise
#   2. outputMode
#        - scalar representation of the file output mode
#        - representation must consist of the following modes:
#            :raw  :bytes  :crlf  :utf8  :std  :locale  :encoding(...)
#        - modes can be combined in the form of ':mode1:mode2...'
#        - representation may be undefined, file is written in the default text
#            (:crlf) mode in this case
#   3. contents
#        - list of contents to write to the file
#        - contents may be undefined, empty file is written in this case
# Return:
#   1. scalar 1 on success
################################################################################
sub writeContents {
	my ($file, $outputMode, @contents) = @_[1..$#_];
	warn "File not specified" and return unless defined $file;
	warn "$file is an invalid file" and return unless !-e $file || -f $file;
	open(my $fileHandle, ">", $file) or warn "Failed to open $file" and return;
	binmode($fileHandle, $outputMode) if defined $outputMode;
	foreach my $contentItem (@contents) {
		print $fileHandle $contentItem or warn "Failed while writing $file" and return;
	}
	close $fileHandle or warn "Failed to close $file";
	return 1;
}

################################################################################
# Subroutine: appendContents
# Params:
#   1. file
#        - scalar name of the file to be appened
#        - name must be defined, fails otherwise
#        - name must refer to a valid file, fails otherwise
#        - actual file may not exist, new file is created in this case
#   2. outputMode
#        - scalar representation of the file output mode
#        - representation must consist of the following modes:
#            :raw  :bytes  :crlf  :utf8  :std  :locale  :encoding(...)
#        - modes can be combined in the form of ':mode1:mode2...'
#        - representation may be undefined, file is written in the default text
#            (:crlf) mode in this case
#   3. contents
#        - list of contents to append to the file
#        - contents may be undefined, nothing is appended in this case
# Return:
#   1. scalar 1 on success
################################################################################
sub appendContents {
	my ($file, $inputMode, @contents) = @_[1..$#_];
	warn "File not specified" and return unless defined $file;
	warn "$file is an invalid file" and return unless !-e $file || -f $file;
	open(my $fileHandle, ">>", $file) or warn "Failed to open $file" and return;
	binmode($fileHandle, $inputMode) if defined $inputMode;
	foreach my $contentItem (@contents) {
		print $fileHandle $contentItem or warn "Failed while writing $file" and return;
	}
	close $fileHandle or warn "Failed to close $file";
	return 1;
}

################################################################################
# Subroutine: joinContents
# Params:
#   1. separator
#        - scalar symbol(s) inserted between the file contents
#        - symbol(s) may be undefined, nothing is inserted in this case
#   2. inputMode
#        - scalar representation of the file input mode
#        - representation must consist of the following modes:
#            :raw  :bytes  :crlf  :utf8  :std  :locale  :encoding(...)
#        - modes can be combined in the form of ':mode1:mode2...'
#        - representation may be undefined, file is read in the default text
#            (:crlf) mode in this case
#   3. files
#        - list of names of files to be joined
#        - list of names must be defined, fails otherwise
#        - any actual file may not exist or may be invalid, skips it in this case
# Return:
#   1. scalar content of the valid files joined together in the order listed
################################################################################
sub joinContents {
	my ($separator, $inputMode, @files) = @_[1..$#_];
	warn "Files not specified" and return unless @files;
	my $joinedContents = File->readContents($files[0], $inputMode);
	foreach my $file (@files[1..$#files]) {
		$joinedContents .= $separator . File->readContents($file, $inputMode);
	}
	return $joinedContents;
}

return 1;
