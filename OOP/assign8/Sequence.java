
/**
 * A Sequence of elements to be sorted.
 * 
 * @param <E> the type of element in the Sequence
 */
public interface Sequence<E> {
	/**
	 * Return the number of elements in the Sequence.
	 * 
	 * @return number of elements
	 */
	public int size();
	
	/**
	 * Put a value in the Sequence at the given index.
	 * 
	 * @param index the index indicating where in the Sequence to put the value
	 * @param value the value
	 */
	public void put(int index, E value);

	/**
	 * Get a value from the sequence at the given index.
	 * 
	 * @param index the index of the value to get
	 * @return the value
	 */
	public E get(int index);

	/**
	 * Swap the values at the given indices.
	 * 
	 * @param index1 the index of the first value
	 * @param index2 the index of the second value
	 */
	public void swap(int index1, int index2);
}
