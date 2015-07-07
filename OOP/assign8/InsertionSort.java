
import java.util.Comparator;

/**
 * Insertion sort algorithm.
 *
 * @param <E> type of element to be sorted
 */
public class InsertionSort<E> implements Sort<E> {

	public void sort(Sequence<E> sequence, Comparator<E> comparator) {
		// TODO: implement

		for (int i = 1; i < sequence.size(); i++) {
                        E temp = sequence.get(i);
			int j;
			boolean isAct = false;
			for (j = i - 1; j >= 0; j--) {
                                if (comparator.compare(sequence.get(j), temp) > 0) {
					isAct = true;
                                        sequence.put(j + 1, sequence.get(j));
                                }
                                else {
                                        break;
                                }
                        }
			if (isAct)
				sequence.put(j + 1, temp);
                }
	}

	public String toString() {
		return "Insertion Sort";
	}
	
}
