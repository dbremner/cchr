 # bla

cchr {

constraint gcd(int);

triv @ gcd(0) <=> true;
doub @ gcd(N) \ gcd(N) <=> true;
dec @ gcd(N) \ gcd(M) <=> M>=N | gcd(M-N);

}

testje
