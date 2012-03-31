#!/usr/bin/perl

use Getopt::Long;

my $LLVM_Root = "./..";
my $LogPath = "build.report.log";
my $Options = "Echo='\@perl \$(LLVM_SRC_ROOT)/tesys/echo.pl \$(LLVM_SRC_ROOT)/tesys/build.report.log' ";

my ($cmd, $errcode, $help, $tool, $clean, $verbose);
my $usage = "Usage: build.pl --clean --tool <list>\
\tclean\t- if tool isn't set, then clean all, overwise clean specified tools\
\ttool\t- set tool list for building\n";
my %options = (
		'help|h|?' => \$help,
		'clean' => \$clean,
		'tool=s' => \$tool,
		'verbose|v' => \$verbose);

GetOptions(%options);

if ($help) {
	print $usage;
	exit;
}

chdir $LLVM_Root;

$LLVM_Root = `pwd`;

chomp $LLVM_Root;

$LogPath = ">>".$LLVM_Root."/tesys/".$LogPath;

if ($clean) {

	if ($tool) {
		@path_list = split(/,/, $tool);

		foreach $tool (@path_list) {
			$path = $LLVM_Root . "/tools/" . $tool;
			$cmd = "make -j 2 -f $path/Makefile clean $Options";# 2>&1|";

			print "Cleaning tool $tool...\n";

			open BuildReport, $LogPath;
			print BuildReport "Date:\t".`date`;
			print BuildReport "Command:\t$cmd\n";
			close BuildReport;

			chdir $path;
			system $cmd;

			$errcode = $?;

			if ($errcode) {
				open BuildReport, $LogPath;
				print BuildReport "ERROR: Cleaning tool $tool with error code $errcode\n";
				close BuildReport;

				print "ERROR: Cleaning tool $tool\n";
				exit 1;
				last;
			}
		}
	}
	else {
		$cmd = "make -j 2 -f $LLVM_Root/Makefile clean $Options";# 2>&1 ";

		print "Cleaning all...\n";

		open BuildReport, $LogPath;
		print BuildReport "Date:\t".`date`;
		print BuildReport "Command:\t$cmd\n";
		close BuildReport;

		system $cmd;

		$errcode = $?;

		if ($errcode) {
			open BuildReport, $LogPath;
			print BuildReport "ERROR: Cleaning all completed with error code $errcode\n";
			close BuildReport;

			print "ERROR: Cleaning all\n";

			exit 1;
		}
	}
	
	print "Cleaning Successfully completed!\n";
	exit 0;
}
elsif ($tool) {
	print "Tool\t\t$tool\n";
	
	$Options .= "\"ONLY_TOOLS=". join(" ", split(/,/, $tool)) . "\"";
}
else {
	system "$LLVM_Root/configure --enable-targets=host,mdsp CC=clang CXX=clang++";

	if ($?) {
		print "ERROR[$?]: Cannot configure llvm!\n";
		exit 1;
	}
}

$cmd = "make -j6 -f $LLVM_Root/Makefile $Options";

open BuildReport, $LogPath;
print BuildReport "Date:\t".`date`;
print BuildReport "Options:\t$Options\n";
print BuildReport "Command:\t$cmd\n";
close BuildReport;

chdir $LLVM_Root;
system $cmd;

$errcode = $?;

print "ErrCode: $?\n";

if ($errcode) {
	open BuildReport, $LogPath;
	print BuildReport "ERROR: Building tools was failed with error code $errcode\n";
	close BuildReport;

	print "ERROR: Building Tools!\n";
} else {
	print "Building successfully completed!\n";
}

exit $errcode;


