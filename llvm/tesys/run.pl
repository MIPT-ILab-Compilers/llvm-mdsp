#!/usr/bin/perl

use Getopt::Long;

my ($help, $suite, $test, $optset, $tools);
my $usage = "\
Usage: run.pl -suite <name> -test <name> -optset <opts> -tools <dir>
\tsuite\t- group of tests\
\ttest\t- testing
\toptset\t- set optimisation
\ttools\t- set binary directory\n";

my %options = (	'help|h|?' => \$help,
		'suite=s' => \$suite,
		'test=s' => \$test,
		'optset=s' => \$optset,
		'tools=s' => \$tools);

if  ($#ARGV == -1) {
	print $usage;
	exit;
}

GetOptions(%options);

if ($help) {
	print $usage;
	exit;
}

if ($suite) {
	print "Suite\t\t$suite\n";
}

if ($test) {
	print "Test\t\t$test\n";
}

if ($optset) {
	print "OptSet\t\t$optset\n";
}

if ($tools) {
	print "Tools bin dir\t$tools\n";
}
