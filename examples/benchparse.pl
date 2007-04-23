#!/usr/bin/perl -w

use strict;

my %DATA;

open PIPE,"| gnuplot";

for my $file (@ARGV) {
  open FILE,"<$file";
  while (<FILE>) {
    chomp;
    if ($_ =~ /\A\s*(\w+)\/(\w+):(\d+)\s+\(([^,]+),([^\)]+)\)\*(\d+)\s+/) {
      my ($sys,$bench,$num,$val,$low,$mul)=($1,$2,$3,$4,$5,$6);
      if (!defined($DATA{$bench}->{$sys}->{0}) || $low<$DATA{$bench}->{$sys}->{low}) {
        $DATA{$bench}->{$sys}->{low}=$low;
      }
      my $emul=0;
      my $eval=0;
      if (defined($DATA{$bench}->{$sys}->{$num}->[0])) {
        $eval=$DATA{$bench}->{$sys}->{$num}->[0];
	$emul=$DATA{$bench}->{$sys}->{$num}->[1];
      }
      $emul += $mul;
      $eval += (($val+$low)*$mul);
      $DATA{$bench}->{$sys}->{$num}->[0]=$eval;
      $DATA{$bench}->{$sys}->{$num}->[1]=$emul;
    }
  }
  close FILE;
}

print PIPE "set terminal postscript enhanced color\n";
print PIPE "set xlabel \"problem size\"\n";
print PIPE "set ylabel \"time\"\n";

for my $bench (keys %DATA) {
  my $benchdata=$DATA{$bench};
  print PIPE "set output \"bench-$bench.ps\"\n";
  print PIPE "set title \"Benchmark $bench\"\n";
  my @plots;
  for my $sys (keys %{$benchdata}) {
    my $data=$benchdata->{$sys};
    my $low=$data->{low};
    open FILE,">bench-$bench-$sys.dat";
    for my $num (sort { $a <=> $b } (grep {/^\d/} (keys %{$data}))) {
      printf FILE ("%i %.16f %i\n",$num,$data->{$num}->[0]/$data->{$num}->[1],$data->{$num}->[1]);
    }
    close FILE;
    push @plots,"\"bench-$bench-$sys.dat\" using 1:2 title \"$sys\"";
  }
  print PIPE "plot ".join(', ',@plots)."\n";
}
close PIPE;
