package qgram;

public class ConstructQGram {
	
	public static void main(String[] args) {
		String s = "ttatctctta";
//		String s = "TTATCTCTTATAGTGACTCGTAGTCGATCGTACGCTAGTACGCTACGTATCGCTAGAACGTTGCTCGGTCTAGCTCGCATGCAGCTAGACTCAGGCATCGACATGCATACGGCATCGACATCAGT";
		String alphabet = "ACGT";
		int q = 2;
		String grams[];		
		
		double r = Math.pow(alphabet.length(), q);
		int range = (int) (r+1);
		// initialize
		grams = getCombinations(alphabet, range);
		int dir[] = new int[range];
				
		// count q-grams
		for (int j=0; j<s.length() - q + 1; j++) {
			String c = s.substring(j, j+q);
			int index = getIndex(c, grams);
			dir[index]++;
		}
		
		// cumulative sum
		int sum = Math.max(0, s.length() - q + 1);
		for (int i=dir.length-1; i>=0; i--) {
			sum = sum - dir[i];
			dir[i] = sum;
		}
		
		// fill pos table
		int pos[] = new int[Math.max(0, s.length() - q + 1)];
		for (int j=0; j<s.length() - q + 1; j++) {
			String c = s.substring(j, j+q);
			int index = getIndex(c, grams);
			pos[dir[index]] = j;
			dir[index]++;
		}
		for (int j=0; j<s.length() - q + 1; j++) {
			String c = s.substring(j, j+q);
			int index = getIndex(c, grams);
			dir[index]--;
		}
		
		System.out.println(); 
		for (int i=0; i<grams.length; i++) {
			if (i>9)
				System.out.print(i +" | ");
			else
				System.out.print("0" +i +" | ");
		}
		System.out.println();
		for (String gram:grams) 
			System.out.print(gram +" | ");
		System.out.println();
		for (int d:dir) 
			System.out.print("0" +d +" | ");
		System.out.println("\ndir size: " +dir.length);

		System.out.println("\npos table size: " +pos.length );
		for (int i:pos) {
			System.out.print(i +" | ");
		}
		
		System.out.println("\n\ns = " +s);
		
		// OUTPUT: pos table & gram table
		// return pos,dir
	}
	
//	// gets the rank of the q gram.
//	private static int code(String gram) {
//		
//		
//		return -1;
//	}
	
	public static String[] getCombinations(String letters, double range) {		
		String gram[] = new String[(int)range];
		int gramIndex = 0;
//		gram[0] = "-";
		
		for (int i = 0; i < 4; i++) {
			String test = "";
			char c = letters.charAt(i);				
			test = test.concat(""+c);
			String first = test;
			for (int k = 0; k < 4; k++) {
				if (k>0)
					test = first; 
				c = letters.charAt(k);				
				test = test.concat(""+c);
				gram[gramIndex] = test;
				gramIndex++;
//				list.add(test);
			}			
		}
		gram[gramIndex] = "empty";
		return gram;
//		return list;
	}

	private static int getIndex(String input, String sets[]) {
		for (int i=0; i<sets.length; i++) {
			if (input.equalsIgnoreCase(sets[i]))
				return i;
		}
		return -1;
	}
	
	private static int getBucket(int c, int[] C) {
		
		if (C.length == 0) {
			return c;
		}
		int i = hash(c) % C.length;
//		int i = c;
		int d = 0;
		while (C[i] != c && C[i] != -1) {	// use quadratic probing
			i = (int) ((i + 2d + 1) % C.length);
			d++;
		}
		
		return i;
		// return index entry in dir
	}
	
	private static int reqBucket(int c, int[] C) {
		if (C.length == 0)
			return c;
		int i = getBucket(c, C);
		
		// occupy bucket, then return position
		C[i] = c;
		return i;
	}
	
	private static int hash(int c) {
//		Hashtable<c, V>
		return c;
	}
}
