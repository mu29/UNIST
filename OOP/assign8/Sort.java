
import java.util.Comparator;

/**
 * A sorting algorithm.
 *
 * @param <E> the type of element being sorted
 */
public interface Sort<E> {
	/**
	 * Sort the given Sequence.
	 * 
	 * @param sequence   the Sequence to sort
	 * @param comparator the Comparator used to compare elements in the sequence
	 */
	public void sort(Sequence<E> sequence, Comparator<E> comparator);
}
