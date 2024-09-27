package shifumi;

public enum Attack {

	PIERRE, FEUILLE, CISEAUX;

	public int compare(Attack a) {
		if (this == PIERRE && a == CISEAUX) {
			return 1;
		} else if (this == CISEAUX && a == PIERRE) {
			return -1;
		} else {
			return this.compareTo(a);
		}
	}

}
