import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Random;

public class SortText {
	
	private static ArrayList<Sort<String>> sortList = new ArrayList<Sort<String>>();
	private static TextSequence sequence = null;

	public static void main(String[] args) {
		if(args.length < 2){
			System.out.println("Usage: java SortText <InputFile> <SortingAlgorithm>");
			System.out.println("      <SortingAlgorithm>:= {Bubble| Selection| Insertion| Shell| Quick}");
			System.exit(1);
		}

		try {
			File inputFile = new File(args[0]);
			sequence = new TextSequence(inputFile);
	
			Sort<String> sort = null;
			if(args[1].equals("Bubble")){
 				sort = new BubbleSort<String>();
			}
			else if(args[1].equals("Selection")){
 				sort = new SelectionSort<String>();
			}
			else if(args[1].equals("Insertion")){
 				sort = new InsertionSort<String>();
			}
			else if(args[1].equals("Shell")){
 				sort = new ShellSort<String>();
			}
			else if(args[1].equals("Quick")){
 				sort = new QuickSort<String>();
			}
			else{
				System.out.println("Usage: java SortText <InputFile> <SortingAlgorithm>");
				System.out.println("      <SortingAlgorithm>:= {Bubble| Selection| Insertion| Shell| Quick}");
				System.exit(1);
			}
			
			System.out.println("Sorting...");
			for(int i=0;i<sequence.size();i++){
				System.out.println(sequence.get(i));
			}
			
			sort.sort(sequence, new Comparator<String>() {
				public int compare(String o1, String o2) {
					return o1.compareTo(o2);
				}
			});
			
			System.out.println("\nDone sorting");
			for(int i=0;i<sequence.size();i++){
				System.out.println(sequence.get(i));
			}
	
			System.out.println("Number Of Operations: " + sequence.getNumOperations());
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
}

