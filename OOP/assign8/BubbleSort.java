import java.util.Comparator;

/**
 * Bubble sort algorithm.
 * 
 * @param <E> type of element to be sorted
 */
public class BubbleSort<E> implements Sort<E> {

	public void sort(Sequence<E> sequence, Comparator<E> comparator) {
		// TODO: implement
		for (int i = 0; i < sequence.size() - 1; i++) {
			for (int j = sequence.size() - 1; j > i; j--) {
				if (comparator.compare(sequence.get(j - 1), sequence.get(j)) > 0) {
					sequence.swap(j, j - 1);
				}
			}
		
		}
	}
	
	public String toString() {
		return "Bubble Sort";
	}

}
