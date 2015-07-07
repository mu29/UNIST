
import java.util.Comparator;

/**
 * Insertion sort algorithm.
 *
 */
public class SelectionSort<E> implements Sort<E> {

	public void sort(Sequence<E> sequence, Comparator<E> comparator) {
		for(int i=0;i<sequence.size()-1;i++){
                    int minIndex = i;
		    for(int j=i+1;j<sequence.size();j++){
		        if( comparator.compare(sequence.get(minIndex), sequence.get(j)) > 0 ){
				minIndex = j;
			}
		    }
		    if(minIndex != i){
			sequence.swap(minIndex, i);
		    }
		}
	}

	public String toString() {
		return "Selection Sort";
	}
	
}
