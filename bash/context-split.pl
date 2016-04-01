#!/usr/bin/perl

#print "$ARGV[0]\n";
#print "$ARGV[1]\n";
#print "$ARGV[2]\n";

open(FI,"$ARGV[0]") or die;
$cur=0;
$res=$ARGV[2];
open(FO,">$res.$cur.tlg") or die;
while(<FI>)
{
    print FO $_;
    if(/^$ARGV[1]/)
    {
        close(FO);
        $cur++;
        open(FO,">$res.$cur.tlg") or die;
    }
}
close(FO);
close(FI);
