
import java.util.Comparator;

/**
 * Quick sort algorithm.
 *
 * @param <E> type of element to be sorted
 */
public class QuickSort<E> implements Sort<E> {

	public void sort(Sequence<E> sequence, Comparator<E> comparator) {
		// TODO: implement
		quickSort(sequence, comparator, 0, sequence.size() - 1);
	}

	private void quickSort(Sequence<E> sequence, Comparator<E> comparator, int left, int right) {
		if (left >= right)
			return;

		int l = left;
		int r = right;
		int pivot = (left + right) / 2;
		E pivotValue = sequence.get(pivot);
		sequence.swap(left, pivot);
		while (l < r) {
			while (l < r && comparator.compare(sequence.get(r), pivotValue) > 0)
				r--;
                        while (l < r && comparator.compare(sequence.get(l), pivotValue) <= 0)
                                l++;

			if (l >= r) break;
			sequence.swap(l, r);
		}
		sequence.swap(left, l);

		quickSort(sequence, comparator, left, l - 1);
		quickSort(sequence, comparator, l + 1, right);
	}

	public String toString() {
		return "Quick Sort";
	}
}
