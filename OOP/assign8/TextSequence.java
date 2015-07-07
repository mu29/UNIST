import java.io.*;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Random;

class TextSequence implements Sequence<String> {
	private String[] storage;
	private SortText sortText;
	private int numOperations;
	
	public TextSequence(int size) {
		storage = new String[size];
		randomize();
	}

	public TextSequence(File inputFile) throws FileNotFoundException {
		Scanner inputScan = new Scanner(inputFile);

		ArrayList<String> contents = new ArrayList<String>();

		while(inputScan.hasNext()){
			contents.add(inputScan.nextLine());
		}

		storage = contents.toArray(new String[contents.size()]);
		numOperations = 0;
		inputScan.close();
	}
	
	public String get(int index) {
		return storage[index];
	}
	
	public String peek(int index) {
		return storage[index];
	}
	
	public void put(int index, String value) {
		storage[index] = value;
		numOperations++;
	}
	
	public void swap(int index1, int index2) {
		String tmp = get(index1);
		put(index1, get(index2));
		put(index2, tmp);
	}
	
	public int size() {
		return storage.length;
	}

	public int getNumOperations() {
		return numOperations;
	}
	
	public void randomize() {
		RandomString stringGenerator = new RandomString(20);

		ArrayList<String> contents = new ArrayList<String>();
		for (int i = 0; i < size(); i++) {
			contents.add(stringGenerator.nextString());
		}
		
		storage = contents.toArray(new String[size()]);
		numOperations = 0;
	}
}

