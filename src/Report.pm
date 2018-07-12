package Report;

################################################################################
# Title:   Report
# Authors: Ethan Hill
# Date:    21 February 2014
################################################################################

use strict;
use warnings;

use Spreadsheet::WriteExcel;

################################################################################
# Subroutine: printQueryResults
# Params:
#   1. subDirectoryScores
#        - hash of author names and their respective scores
#        - hash of authors must be defined, fails otherwise
# Return:
#   1. scalar 1 on success
################################################################################
sub printQueryResults {
    my (%subDirectoryScores) = @_[1..$#_];
    warn "Sub-directory scores are undefined" and return unless %subDirectoryScores;
    my $highestScore;
	foreach(sort{$subDirectoryScores{$b} <=> $subDirectoryScores{$a}} keys %subDirectoryScores) {
		$highestScore = $subDirectoryScores{$_} if !defined $highestScore || $subDirectoryScores{$_} > $highestScore;
		last if $subDirectoryScores{$_} < $highestScore;
		print $_ . "\n";
	}
    return 1;
}

################################################################################
# Subroutine: writeQueryReport
# Params:
#   1. outputFile
#        - scalar name of file to output to
#        - name must be defined, fails otherwise
#        - name must refer to a valid file, fails otherwise
#   2. subDirectoryScores
#        - hash of author names and their respective scores
#        - hash of authors must be defined, fails otherwise
# Return:
#   1. scalar 1 on success
################################################################################
sub writeQueryReport {
	my ($outputFile, %subDirectoryScores) = @_[1..$#_];
    warn "Output file is undefined" and return unless defined $outputFile;
    warn "Sub-directory scores are undefined" and return unless %subDirectoryScores;
    warn "Output file $outputFile is not a valid file" and return unless !-e $outputFile || -f $outputFile;
	my $workbook = Spreadsheet::WriteExcel->new($outputFile);
	warn "Failed to create output file $outputFile" and return unless defined $workbook;
	my $worksheet = $workbook->add_worksheet();
	my $headerFormat = $workbook->add_format(bold => 1);
	my $winnerFormat = $workbook->add_format(color => 'green', bg_color => 'lime');
	$worksheet->set_row(0, undef, $headerFormat);
	$worksheet->set_column(0, 1, 20);
	$worksheet->write(0, 0, "Author");
	$worksheet->write(0, 1, "Score");
	my $highestScore;
	my $row = 1;
	foreach(sort{$subDirectoryScores{$b} <=> $subDirectoryScores{$a}} keys %subDirectoryScores) {
		$highestScore = $subDirectoryScores{$_} if !defined $highestScore || $subDirectoryScores{$_} > $highestScore;
		if($subDirectoryScores{$_} >= $highestScore) {
			$worksheet->write($row, 0, $_, $winnerFormat);
			$worksheet->write($row++, 1, $subDirectoryScores{$_}, $winnerFormat);
		} else {
			$worksheet->write($row, 0, $_);
			$worksheet->write($row++, 1, $subDirectoryScores{$_});
		}
	}
	$workbook->close() or warn "Failed to close output file $outputFile";
	return 1;
}

################################################################################
# Subroutine: writeExperimentReport
# Params:
#   1. outputFile
#        - scalar name of file to output to
#        - name must be defined, fails otherwise
#        - name must refer to a valid file, fails otherwise
#   2. trials
#        - array of experimental trials
#        - array of trials must be defined, fails otherwise
# Return:
#   1. scalar 1 on success
################################################################################
sub writeExperimentReport {
	my ($outputFile, @trials) = @_[1..$#_];
    warn "Output file is undefined" and return unless defined $outputFile;
    warn "Trials are undefined" and return unless @trials;
    warn "Output file $outputFile is not a valid file" and return unless !-e $outputFile || -f $outputFile;
	my $workbook = Spreadsheet::WriteExcel->new($outputFile);
	warn "Failed to create output file $outputFile" and return unless defined $workbook;
	my $worksheet = $workbook->add_worksheet();
	my $headerFormat = $workbook->add_format(bold => 1);
	$worksheet->set_row(0, undef, $headerFormat);
	$worksheet->set_column(0, 3, 20);
	$worksheet->write(0, 0, "File Name");
	$worksheet->write(0, 1, "True Author");
    $worksheet->write(0, 2, "Attributed Author");
    $worksheet->write(0, 3, "Correctly Attributed?");
	my $rowIndex = 1;
    my $matches = 0;
	foreach my $trial (@trials) {
		$worksheet->write($rowIndex, 0, $trial->{file});
        $worksheet->write($rowIndex, 1, $trial->{author});
        $worksheet->write($rowIndex, 2, $trial->{attributed});
        $worksheet->write($rowIndex, 3, "=EXACT(B" . ($rowIndex + 1) . ",C" . ($rowIndex + 1) . ")");
        $matches += $trial->{author} eq $trial->{attributed} ? 1 : 0;
        ++$rowIndex;
	}
    $worksheet->write($rowIndex, 3, ($matches / @trials) * 100 . '%');
	$workbook->close() or warn "Failed to close output file $outputFile";
	return 1;
}

################################################################################
# Subroutine: writeKFExperimentReport
# Params:
#   1. outputFile
#        - scalar name of file to output to
#        - name must be defined, fails otherwise
#        - name must refer to a valid file, fails otherwise
#   2. folds
#        - array of experimental trials sorted by fold index
#        - array of trials must be defined, fails otherwise
# Return:
#   1. scalar 1 on success
################################################################################
sub writeKFExperimentReport {
    my ($outputFile, @folds) = @_[1..$#_];
    warn "Output file is undefined" and return unless defined $outputFile;
    warn "Folds are undefined" and return unless @folds;
    warn "Output file $outputFile is not a valid file" unless !-e $outputFile || -f $outputFile;
    my $workbook = Spreadsheet::WriteExcel->new($outputFile);
    warn "Failed to create output file $outputFile" and return unless defined $workbook;
    
    my $dark_green = $workbook->set_custom_color(63, 0, 97, 0);
    my $light_green = $workbook->set_custom_color(62, 198, 239, 206);
    
    my $normalFormat = $workbook->add_format(
            font => 'Arial',
            size => 10,
            align => 'center'
    );
    my $headerFormat = $workbook->add_format(
            font => 'Calibri',
            size => 11,
            bold => 1,
            align => 'center'
    );
    my $footerFormat = $workbook->add_format(
            font => 'Calibri',
            size => 11,
            bold => 1,
            align => 'center'
    );
    my $normalLeftFormat = $workbook->add_format();
        $normalLeftFormat->copy($normalFormat);
        $normalLeftFormat->set_align('left');
    my $headerLeftFormat = $workbook->add_format();
        $headerLeftFormat->copy($headerFormat);
        $headerLeftFormat->set_align('left');
    my $footerLeftFormat = $workbook->add_format();
        $footerLeftFormat->copy($footerFormat);
        $footerLeftFormat->set_align('left');
    my $normalPercentFormat = $workbook->add_format();
        $normalPercentFormat->copy($normalFormat);
        $normalPercentFormat->set_num_format('0.0%');
    my $footerPercentFormat = $workbook->add_format();
        $footerPercentFormat->copy($footerFormat);
        $footerPercentFormat->set_num_format('0.0%');
    my $normalMatchFormat = $workbook->add_format();
        $normalMatchFormat->copy($normalFormat);
        $normalMatchFormat->set_color($dark_green);
        $normalMatchFormat->set_bg_color($light_green);
    
    my %authorsSummary;
    foreach my $author (keys %{$folds[0]->[0]->{scores}}) {
        $authorsSummary{$author} = {num_files => 0, num_correct => 0};
    }
    
    my $worksheetTotal = $workbook->add_worksheet('TOTAL');
    $worksheetTotal->set_row(0, undef, $headerFormat);
    $worksheetTotal->set_column(0, 0, 12, $headerLeftFormat);
    $worksheetTotal->set_column(1, 2, 12, $normalFormat);
    $worksheetTotal->set_column(3, 3, 12, $normalPercentFormat);
    $worksheetTotal->write(0, 0, 'Author', $headerLeftFormat);
    $worksheetTotal->write(0, 1, 'NumFiles');
    $worksheetTotal->write(0, 2, 'NumCorrect');
    $worksheetTotal->write(0, 3, 'Percentage');
    
    # Loop through folds
    for(my $foldIndex = 0; $foldIndex < @folds; ++$foldIndex) {
        
        my @entries = @{$folds[$foldIndex]};
        my $row;
        my $col;
        my $worksheet = $workbook->add_worksheet('Fold ' . ($foldIndex + 1));
        $worksheet->set_row(0, undef, $headerFormat);
        $worksheet->set_column(0, 0, 40, $normalFormat);
        $worksheet->set_column(1, 1, 10, $normalFormat);
        $worksheet->write(0, 0, 'File', $headerLeftFormat);
        $worksheet->write(0, 1, 'Author');
        $col = 2;
        foreach my $author (sort{$a cmp $b} keys %{$entries[0]->{scores}}) {
            $worksheet->set_column($col, $col, 10, $normalFormat);
            $worksheet->write(0, $col, $author);
            ++$col;
        }
        $worksheet->set_column($col, $col, 10, $normalFormat);
        $worksheet->write(0, $col, 'Correct?');
        
        $row = 1;
        # Loop through entries
        foreach my $entry (@entries) {
            
            my %properties = %$entry;
            my %scores = %{$properties{scores}};
            $worksheet->write($row, 0, $properties{file}, $normalLeftFormat);
            $worksheet->write($row, 1, $properties{author});
            $col = 2;
            foreach my $author (sort{$a cmp $b} keys %scores) {
                if($author eq $properties{attributed}) {
                    $worksheet->write($row, $col, $scores{$author}, $normalMatchFormat);
                } else {
                    $worksheet->write($row, $col, $scores{$author});
                }
                ++$col;
            }
            $worksheet->write($row, $col, ($properties{author} eq $properties{attributed} ? 1 : 0));
            ++$row;
            
            ++$authorsSummary{$properties{author}}->{num_files};
            ++$authorsSummary{$properties{author}}->{num_correct} if $properties{author} eq $properties{attributed};
            
        } # End loop through entries
        
    } # End loop through folds
    
    my $row = 1;
    foreach my $author (sort{$a cmp $b} keys %authorsSummary) {
        $worksheetTotal->write($row, 0, $author);
        $worksheetTotal->write($row, 1, $authorsSummary{$author}->{num_files});
        $worksheetTotal->write($row, 2, $authorsSummary{$author}->{num_correct});
        $worksheetTotal->write($row, 3, '=C' . ($row + 1) . '/B' . ($row + 1));
        ++$row;
    }
    $worksheetTotal->set_row($row, undef, $footerFormat);
    $worksheetTotal->write($row, 0, 'TOTAL', $footerLeftFormat);
    $worksheetTotal->write($row, 1, '=SUM(B2:B' . $row . ')');
    $worksheetTotal->write($row, 2, '=SUM(C2:C' . $row . ')');
    $worksheetTotal->write($row, 3, '=C' . ($row + 1) . '/B' . ($row + 1), $footerPercentFormat);
    
    $workbook->close() or warn "Failed to close output file $outputFile" and return;
    return 1;
}

################################################################################
# Subroutine: writeLOOExperimentReport
# Params:
#   1. outputFile
#        - scalar name of file to output to
#        - name must be defined, fails otherwise
#        - name must refer to a valid file, fails otherwise
#   2. authors
#        - hash of experimental trials sorted by author
#        - hash of trials must be defined, fails otherwise
# Return:
#   1. scalar 1 on success
################################################################################
sub writeLOOExperimentReport {
    my ($outputFile, %authors) = @_[1..$#_];
    warn "Output file is undefined" and return unless defined $outputFile;
    warn "Authors are undefined" and return unless %authors;
    warn "Output file $outputFile is not a valid file" unless !-e $outputFile || -f $outputFile;
    my $workbook = Spreadsheet::WriteExcel->new($outputFile);
    warn "Failed to create output file $outputFile" and return unless defined $workbook;
    
    my $dark_green = $workbook->set_custom_color(63, 0, 97, 0);
    my $light_green = $workbook->set_custom_color(62, 198, 239, 206);
    
    my $normalFormat = $workbook->add_format(
            font => 'Arial',
            size => 10,
            align => 'center'
    );
    my $headerFormat = $workbook->add_format(
            font => 'Calibri',
            size => 11,
            bold => 1,
            align => 'center'
    );
    my $footerFormat = $workbook->add_format(
            font => 'Calibri',
            size => 11,
            bold => 1,
            align => 'center'
    );
    my $normalLeftFormat = $workbook->add_format();
        $normalLeftFormat->copy($normalFormat);
        $normalLeftFormat->set_align('left');
    my $headerLeftFormat = $workbook->add_format();
        $headerLeftFormat->copy($headerFormat);
        $headerLeftFormat->set_align('left');
    my $footerLeftFormat = $workbook->add_format();
        $footerLeftFormat->copy($footerFormat);
        $footerLeftFormat->set_align('left');
    my $normalPercentFormat = $workbook->add_format();
        $normalPercentFormat->copy($normalFormat);
        $normalPercentFormat->set_num_format('0.0%');
    my $footerPercentFormat = $workbook->add_format();
        $footerPercentFormat->copy($footerFormat);
        $footerPercentFormat->set_num_format('0.0%');
    my $normalMatchFormat = $workbook->add_format();
        $normalMatchFormat->copy($normalFormat);
        $normalMatchFormat->set_color($dark_green);
        $normalMatchFormat->set_bg_color($light_green);
    
    my %authorsSummary;
    foreach my $author (keys %authors) {
        $authorsSummary{$author} = {num_files => 0, num_correct => 0};
    }
    
    my $worksheetTotal = $workbook->add_worksheet('TOTAL');
    $worksheetTotal->set_row(0, undef, $headerFormat);
    $worksheetTotal->set_column(0, 0, 12, $headerLeftFormat);
    $worksheetTotal->set_column(1, 2, 12, $normalFormat);
    $worksheetTotal->set_column(3, 3, 12, $normalPercentFormat);
    $worksheetTotal->write(0, 0, 'Author', $headerLeftFormat);
    $worksheetTotal->write(0, 1, 'NumFiles');
    $worksheetTotal->write(0, 2, 'NumCorrect');
    $worksheetTotal->write(0, 3, 'Percentage');
    
    # Loop through authors
    foreach my $author (sort{$a cmp $b} keys %authors) {
        
        my @entries = @{$authors{$author}};
        my $row;
        my $col;
        my $worksheet = $workbook->add_worksheet($author);
        $worksheet->set_row(0, undef, $headerFormat);
        $worksheet->set_column(0, 0, 40, $normalFormat);
        $worksheet->set_column(1, 1, 10, $normalFormat);
        $worksheet->write(0, 0, 'File', $headerLeftFormat);
        $worksheet->write(0, 1, $author);
        $col = 2;
        foreach my $author2 (sort{$a cmp $b} keys %{$entries[0]->{scores}}) {
            next if $author2 eq $author;
            $worksheet->set_column($col, $col, 10, $normalFormat);
            $worksheet->write(0, $col, $author2);
            ++$col;
        }
        $worksheet->set_column($col, $col, 10, $normalFormat);
        $worksheet->write(0, $col, 'Correct?');
        
        $row = 1;
        # Loop through entries
        foreach my $entry (@entries) {
            
            my %properties = %$entry;
            my %scores = %{$properties{scores}};
            $worksheet->write($row, 0, $properties{file}, $normalLeftFormat);
            if($author eq $properties{attributed}) {
                $worksheet->write($row, 1, $scores{$author}, $normalMatchFormat);
            } else {
                $worksheet->write($row, 1, $scores{$author});
            }
            $col = 2;
            foreach my $author2 (sort{$a cmp $b} keys %scores) {
                next if $author2 eq $author;
                if($author2 eq $properties{attributed}) {
                    $worksheet->write($row, $col, $scores{$author2}, $normalMatchFormat);
                } else {
                    $worksheet->write($row, $col, $scores{$author2});
                }
                ++$col;
            }
            $worksheet->write($row, $col, ($author eq $properties{attributed} ? 1 : 0));
            ++$row;
            
            ++$authorsSummary{$author}->{num_files};
            ++$authorsSummary{$author}->{num_correct} if $author eq $properties{attributed};
            
        } # End loop through entries
        
    } # End loop through authors
    
    my $row = 1;
    foreach my $author (sort{$a cmp $b} keys %authorsSummary) {
        $worksheetTotal->write($row, 0, $author);
        $worksheetTotal->write($row, 1, $authorsSummary{$author}->{num_files});
        $worksheetTotal->write($row, 2, $authorsSummary{$author}->{num_correct});
        $worksheetTotal->write($row, 3, '=C' . ($row + 1) . '/B' . ($row + 1));
        ++$row;
    }
    $worksheetTotal->set_row($row, undef, $footerFormat);
    $worksheetTotal->write($row, 0, 'TOTAL', $footerLeftFormat);
    $worksheetTotal->write($row, 1, '=SUM(B2:B' . $row . ')');
    $worksheetTotal->write($row, 2, '=SUM(C2:C' . $row . ')');
    $worksheetTotal->write($row, 3, '=C' . ($row + 1) . '/B' . ($row + 1), $footerPercentFormat);
    
    $workbook->close() or warn "Failed to close output file $outputFile" and return;
    return 1;
}

return 1;
