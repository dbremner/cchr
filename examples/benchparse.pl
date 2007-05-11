#!/usr/bin/perl -w

use strict;

my %DATA;
my %ORDER;

open PIPE,"| gnuplot";

for my $file (@ARGV) {
  open FILE,"<$file";
  while (<FILE>) {
    chomp;
    if ($_ =~ /\A\s*(\w+)\/(\w+):(\d+)\s+\(([^,]+),([^\)]+)\)\*(\d+)\s+/) {
      my ($sys,$bench,$num,$val,$low,$mul)=($1,$2,$3,$4,$5,$6);
      if (!defined($DATA{$bench}->{$sys}->{low}) || $low<$DATA{$bench}->{$sys}->{low}) {
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

for my $bench (keys %DATA) {
  my $benchdata=$DATA{$bench};
  my $bsdata=$benchdata->{c};
  my @SYS=keys %{$benchdata};
  my %uvals;
  my $nuvals=0;
  for my $sys (@SYS) {
    $uvals{$sys}=1;
  }
  for my $size (keys %{$bsdata}) {
    if ($size ne 'low') {
      my %vals;
      my $nvals=0;
      for my $sys (@SYS) {
        if (defined ($benchdata->{$sys}->{$size})) {
	  $vals{$sys}=($benchdata->{$sys}->{$size}->[0]/$benchdata->{$sys}->{$size}->[1]-$benchdata->{$sys}->{low});
	  $nvals++ if ($vals{$sys}>0.000025);
	}
      }
      if ($nvals == $#SYS+1) {
        for my $sys (@SYS) {
	  $uvals{$sys} += log($vals{$sys});
	}
	$nuvals++;
      }
    }
  }
  print "AVG $bench\[$nuvals\] : ";
  my $loww;
  for my $sys (@SYS) {
    my $lw=$uvals{$sys}/$nuvals if ($nuvals>0);
    $loww=$lw if (!defined($loww) || $lw<$loww);
  }
  for my $sys (sort { $uvals{$b}<=>$uvals{$a} } (@SYS)) {
    if ($nuvals>0) {
      print "$sys=".exp($uvals{$sys}/$nuvals-$loww)." ";
      push @{$ORDER{$bench}},$sys;
    }
  }
  print "\n";
}

print PIPE "set xlabel \"problem size\"\n";
print PIPE "set ylabel \"time\"\n";
print PIPE "set logscale xy\n";
print PIPE "set key bot right\n";

for my $bench (keys %DATA) {
  my $benchdata=$DATA{$bench};
  print PIPE "set title \"Benchmark $bench\"\n";
  my @plots;
  for my $sys (@{$ORDER{$bench}}) {
    my $data=$benchdata->{$sys};
    my $low=$data->{low};
    open FILE,">bench-$bench-$sys.dat";
    for my $num (sort { $a <=> $b } (grep {/^\d/} (keys %{$data}))) {
      printf FILE ("%i %.16f %i\n",$num,($data->{$num}->[0]/$data->{$num}->[1])-$low,$data->{$num}->[1]);
    }
    close FILE;
    push @plots,"\"bench-$bench-$sys.dat\" using 1:2 title \"$sys\" with line";
  }
  print PIPE "set terminal postscript enhanced color\n";
  print PIPE "set output \"bench-$bench.ps\"\n";
  print PIPE "plot ".join(', ',@plots)."\n";
#  system("ps2pdf14 bench-$bench.ps bench-$bench.pdf");
  print PIPE "set terminal pdf monochrome enhanced dashed\n";
  print PIPE "set output \"bench-$bench.pdf\"\n";
  print PIPE "replot\n";
}
close PIPE;
