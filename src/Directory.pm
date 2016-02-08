package Directory;

################################################################################
# Title:   Directory
# Authors: Ethan Hill
# Date:    14 February 2014
# Version: 1.0.2
################################################################################

use strict;
use warnings;

################################################################################
# Subroutine: getSubDirectories
# Params:
#   1. directory
#        - scalar name of a directory to search for sub-directories in
#        - name must be defined, fails otherwise
#        - actual directory must exist, fails otherwise
#        - name must refer to a valid directory, fails otherwise
#   2. fullName
#        - scalar value to determine how sub-directory names are returned
#        - value must be either 1 or 0, undefined results otherwise
#        - if value is 1, names are returned as 'directory/sub-directory'
#        - if value is 0, names are returned as 'sub-directory'
# Return:
#   1. list of names of sub-directories in the directory
################################################################################
sub getSubDirectories {
	my ($directory, $fullName) = @_[1..$#_];
	warn "Directory is undefined" and return unless defined $directory;
	warn "$directory does not exist" and return unless -e $directory; 
	warn "$directory is an invalid directory" and return unless -d $directory;
	my @subDirectories = ();
	opendir(my $directoryHandle, $directory) or warn "Failed to open $directory" and return;
	while(my $directoryItem = readdir $directoryHandle) {
		next unless -d $directory . "/" . $directoryItem;
		next if $directoryItem eq '.' || $directoryItem eq '..';
		push(@subDirectories, $fullName ? $directory . "/" . $directoryItem : $directoryItem);
	}
	closedir $directoryHandle or warn "Failed to close $directory";
	return @subDirectories;
}

################################################################################
# Subroutine: removeDirectory
# Params:
#   1. directory
#        - scalar name of a directory to remove
#        - name must be defined, fails otherwise
#        - actual directory must exist, fails otherwise
#        - name must refer to a valid directory, fails otherwise
#   2. removeSubDirectories
#        - scalar value to determine whether sub-directories should be removed
#        - value must be either 1 or 0, fails otherwise
#        - if value is 1, sub-directories are removed recursively
#        - if value is 0, fails if sub-directories are present
#        - value may be undefined, sub-directories will not be removed in this case
# Return:
#   1. scalar 1 on success
################################################################################
sub removeDirectory {
    my ($directory, $removeSubDirectories) = @_[1..$#_];
    warn "Directory is undefined" and return unless defined $directory;
    warn "Directory $directory does not exist" and return unless -e $directory;
    warn "Directory $directory is not a valid directory" and return unless -d $directory;
    warn "Remove sub-directories flag $removeSubDirectories is not a valid flag" and return unless !defined $removeSubDirectories || $removeSubDirectories =~ /^(1|0)$/;
    my @subDirectories = Directory->getSubDirectories($directory, 1);
    if(@subDirectories) {
        if(!defined $removeSubDirectories || !$removeSubDirectories) {
            warn "Directory $directory contains sub-directories and could not be removed" and return;
        } else {
            foreach my $subDirectory (@subDirectories) {
                Directory->removeDirectory($subDirectory, $removeSubDirectories) or warn "Directory $directory failed to remove its sub-directories and could not be removed" and return;
            }
        }
    }
    my @files = Directory->getFiles($directory, 1);
    unlink @files or warn "Directory $directory failed to unlink its files and could not be removed" and return if @files;
    rmdir $directory or warn "Directory $directory could not be removed" and return;
    return 1;
}

################################################################################
# Subroutine: getFiles
# Params:
#   1. directory
#        - scalar name of a directory to search for files in
#        - name must be defined, fails otherwise
#        - actual directory must exist, fails otherwise
#        - name must refer to a valid directory, fails otherwise
#   2. fullName
#        - scalar value to determine how file names are returned
#        - value must be either 1 or 0, undefined results otherwise
#        - if value is 1, names are returned as 'directory/file'
#        - if value is 0, names are returned as 'file'
#   3. extensions
#        - list of file extensions to filter the search by
#        - extensions must not contain '.', undefined results otherwise
#        - list may be undefined, search is not filtered in this case
# Return:
#   1. list of files in the directory with the specified extensions
#   2. list of all files in the directory if no extensions were specified
################################################################################
sub getFiles {
	my ($directory, $fullName, @extensions) = @_[1..$#_];
	warn "Directory is undefined" and return unless defined $directory;
	warn "$directory does not exist" and return unless -e $directory; 
	warn "$directory is an invalid directory" and return unless -d $directory;
	my $extensionRegex;
	if(@extensions) {
		$extensionRegex = "\\." . join("\$|\\.", @extensions) . "\$";
	} else {
		$extensionRegex = ".";
	}
	my @files = ();
	opendir(my $directoryHandle, $directory) or warn "Failed to open $directory" and return;
	while(my $directoryItem = readdir $directoryHandle) {
		next unless -f $directory . "/" . $directoryItem;
		next unless $directoryItem =~ /$extensionRegex/;
		push(@files, $fullName ? $directory . "/" . $directoryItem : $directoryItem);
	}
	closedir $directoryHandle or warn "Failed to close $directory";
	return @files;
}

return 1;
