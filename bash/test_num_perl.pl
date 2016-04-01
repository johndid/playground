#!/usr/bin/perl

my $num = '0x414946364';
my $v1 = substr $num, 2,2;
my $v2 = substr $num, 4,2;

#printf "-> 0x%d", substr $num, 2,2;
#printf "\n";
#my $tal = sprintf "%d", substr $num, 2,2;
#printf "-> %c", hex($tal);
#printf "\n";
printf "Muh:> %c%c%c%c\n", hex(substr $num, 2,2),hex(substr $num, 4,2),hex(substr $num, 6,2),hex(substr $num, 8,2);
