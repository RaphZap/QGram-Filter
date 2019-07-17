package qgram;

import java.util.HashMap;
import java.util.Hashtable;

public class OpenAdd {
	
	public static void main(String[] args) {
//		String s = "ttatctctta";
		String s = "TTATCTCTTATAGTGACTCGTAGTCGATCGTACGCTAGTACGCTACGTATCGCTAGAACGTTGCTCGGTCTAGCTCGCATGCAGCTAGACTCAGGCATCGACATGCATACGGCATCGACATCAGT";
		String alphabet = "ACGT";
		int q = 2;
		String grams[];		
		
		double r = Math.pow(alphabet.length(), q);
		int range = (int) (r+1);
		// initialize
		grams = getCombinations(alphabet, range);
//		int dir[] = new int[range];
		
		// added
		double alpha = 0.8;
		double tableSize = Math.pow(alpha, -1) * s.length();
		int codeTableSize = (int) Math.floor(tableSize);
		int C[] = new int[codeTableSize];
		for (int i=0 ; i<C.length; i++)
			C[i] = -1;
		
		int dir[] = new int[codeTableSize + 1];
		
		// count q-grams
		for (int j=0; j<s.length() - q + 1; j++) {
			String c = s.substring(j, j+q);
			int index = getIndex(c, grams);
			index = reqBucket(index, C); // added
			dir[index]++;
		}
		
		// cumulative sum
		int sum = Math.max(0, s.length() - q + 1);
		for (int i=dir.length-1; i>=0; i--) {
			sum = sum - dir[i];
			dir[i] = sum;
		}
		
//		System.out.println(); 
//		for (String gram:grams) 
//			System.out.print(gram +"\t");
//		System.out.println();
//		for (int d:dir)
//			System.out.print(d +" | ");
		
		
		// fill pos table
		int pos[] = new int[Math.max(0, s.length() - q + 1)];
		for (int j=0; j<s.length() - q + 1; j++) {
			String c = s.substring(j, j+q);
			int index = getIndex(c, grams);
			index = getBucket(index, C); // added
			pos[dir[index]] = j;
			dir[index]++;
		}

		// Added: fix the dir table
		for (int j=0; j<s.length() - q + 1; j++) {
			String c = s.substring(j, j+q);
			int index = getIndex(c, grams);
			index = getBucket(index, C); // added
			dir[index]--;
		}

		System.out.println("alpha = "+alpha);
		
//		System.out.println();
//		for (String gram:grams) 
//			System.out.print(gram +" | ");
		System.out.println("\ndir size: " +dir.length);
		for (int d:dir) 
			System.out.print(d +" | ");

		
		System.out.println("\n\npos table size: " +pos.length );
		for (int i:pos) {
			System.out.print(i +" | ");
		}

		System.out.println("\n\nCode Table size: " +C.length);
		for (int i:C)
			System.out.print(i +" | ");
		System.out.println();

		System.out.println("\ns = " +s);

		String query = "AT";
		System.out.println("\nWhere's "+query +"?");
		int codeValue = getIndex(query, grams);
		int dirIndex = getBucket(codeValue, C);
		int numOfGrams = dir[dirIndex+1] - dir[dirIndex];
//		int indices[] = new int[numOfGrams];
//		System.out.println("test: " +numOfGrams);
		System.out.print("Found in: ");
		while (numOfGrams>0) {
			System.out.print(pos[dirIndex] +", ");
			dirIndex++;
			numOfGrams--;
		}
		System.out.println();
		
		// OUTPUT: pos table & gram table
		// return pos, dir, code table
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
	
	// params: c = code value, C = code table
	private static int getBucket(int c, int[] C) {		
		if (C.length == 0) {
			return c;
		}
		// i = index of initial hash
		int i = hash(c) % C.length;		// hash(c) = c
		int d = 0;
		while (C[i] != c && C[i] != -1) {	// use quadratic probing
			i = (int) ((i + 2d + 1) % C.length);
			d++;
		}
		return i;
		// return index
	}
	
	// params: c = code value, C = code table
	private static int reqBucket(int c, int[] C) {
		if (C.length == 0)
			return c;
		int i = getBucket(c, C);
		
		// occupy bucket, then return position
		C[i] = c;
		return i;
	}
	
	private static int hash(int c) {

		return c;
	}
	

	private static int getBucket(int c, Hashtable<Integer, Integer> C) {		
		if (C.size() == 0) {
			return c;
		}
		int i = hash(c) % C.size();
//		int i = c;
		int d = 0;
		while (C.get(c) != c && C.get(c) != -1) {	// use quadratic probing
			i = (int) ((i + 2d + 1) % C.size());
			d++;
		}
		return i;
		// return index entry in dir
	}
	
	private static int reqBucket(int c, Hashtable<Integer, Integer> C) {
		if (C.size() == 0)
			return c;
		int i = getBucket(c, C);
		
		// occupy bucket, then return position
		C.replace(c, c);
		return i;
	}
}
