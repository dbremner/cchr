import java.util.Collection;

public class Fib {

    public static void main(String[] args) throws Exception {
    if (args.length != 1) printUsage();
    else try {
    final int i0 = Integer.parseInt(args[0]);

if (i0 < 0) {                
printUsage();
return;
}

for (int i=0; i<100; i++) {
// First we create a new JCHR constraint handler:
FibBoAllHandler handler = new FibBoAllHandler();

// Next we tell the JCHR handler the following two constraints:             
handler.tellInit(i0);
}
// Afterwards we can lookup the constraints in the 
// resulting constraint store: 
/*Collection<FibBoAllHandler.FibConstraint> fibs = handler.getFibConstraints();

for (FibBoAllHandler.FibConstraint f : fibs) {
  System.out.println("fib("+f.getM()+") = "+f.getN());
}*/


} catch (NumberFormatException e) {
System.err.println(e.getMessage());
printUsage();
}
}
    
public final static void printUsage() {
System.out.println(
"Usage: java Fib <positive int>"
);
}
}
