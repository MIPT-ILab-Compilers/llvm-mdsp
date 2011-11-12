#!/usr/bin/perl

use Getopt::Long;

my $Url;
my ($help, $commit, $msg);
$usage = "Usage test.pl -commit -msg <string>\n\tcommit - commit repository\n\tmsg - send msg <string>\n";

if ($#ARGV == -1) {
	print $usage;
}

GetOptions('help' => \$help, 'commit' => \$commit, 'msg=s' => \$msg);

if ($commit) {
	print "Commit\t\t[Ok]\n";
}
elsif ($msg) {
	print "Message:\t$msg\n";
}
else {
	print $usage;
	exit;
}

