#!/usr/bin/perl

my ($arg, $delim);

$arg = shift @ARGV;

open Log, ">>$arg";

$arg = shift @ARGV;

if ($arg == "Building") {
	$delim = " ";
}
else {
	$delim = "";
}

do {
	print Log "$arg$delim";
} while ($arg = shift @ARGV);


print Log "\n";
close Log;


