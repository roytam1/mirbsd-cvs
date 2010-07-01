/* $MirOS$ */

class bottles {

static String
nomore(int howmany, String en) {
	if (howmany == 0)
		return (en + "o more");
	return ("" + howmany);
}

public static void
main(String args[]) {
	String s = "s";

	for (int beers = 99; beers > -1; /* nothing */) {
		System.out.println(nomore(beers, "N") + " bottle" + s +
		    " of beer on the wall, " + nomore(beers, "n") +
		    " bottle" + s + " of beer.");
		if (beers == 0) {
			System.out.print("Go to the store and buy some more, ");
			System.out.println("99 bottles of beer on the wall.");
			System.exit(0);
		} else
			System.out.print("Take one down and pass it around, ");
		s = (--beers == 1) ? "" : "s";
		System.out.println(nomore(beers, "n") +
		    " bottle" + s + " of beer on the wall.\n");
	}
}

}
