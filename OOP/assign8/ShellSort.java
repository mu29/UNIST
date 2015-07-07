
import java.util.Comparator;

/**
 * Shell sort algorithm.
 * 
 * @param <E> type of element to be sorted
 */
public class ShellSort<E> implements Sort<E> {

	public void sort(Sequence<E> sequence, Comparator<E> comparator) {
		// TODO: implement
		int n = 1;
		int gap = sequence.size() / 2;
		while (gap > 0) {
			for (int i = gap; i < sequence.size(); i++) {
                       		E temp = sequence.get(i);
                       		int j;
                        	boolean isAct = false;
                        	for (j = i - gap; j >= 0; j -= gap) {
                                	if (comparator.compare(sequence.get(j), temp) > 0) {
                                        	isAct = true;
                                        	sequence.put(j + gap, sequence.get(j));
                                	}
                                	else {
                                        	break;
                                	}
                        	}
                        	if (isAct)
                                	sequence.put(j + gap, temp);
                	}
			gap = sequence.size() / (int)Math.pow(2, ++n);
		}
	}
	
	public String toString() {
		return "Shell Sort";
	}
}
