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
	system "./build.pl";

	if ($?) {
		print "Cannot commit because build.pl completed with fail!\n";
		exit 1;
	}
	else {
	}
}
elsif ($msg) {
	print "Message:\t$msg\n";
}
else {
	print $usage;
	exit;
}

