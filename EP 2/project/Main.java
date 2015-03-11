import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.Collections;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Vector;


public class Main {
	public static final void main(String[] args) throws Exception {
		Hashtable<Integer, Map> mapData = new Hashtable<Integer, Map>();
		Hashtable<Integer, Map> circleData = new Hashtable<Integer, Map>();
		File dir = new File("./");
		File[] fileList = dir.listFiles();
		BufferedReader reader = null;
		
		// 모든 파일을 읽자
		for (File file : fileList) {
			if (!file.getName().endsWith("txt")) {
				continue;
			}
			
			reader = new BufferedReader(new FileReader(file));
			String fileContent = reader.readLine();
			Map map = new Map(file.getName(), fileContent.split("\\|"));
			int key = Integer.parseInt(file.getName().replace(".txt", ""));
			mapData.put(key, map);
		}
		
		// 모든 값 출력후 원만 따로 읽어들여서 기준값(최소)를 구함
		int min = 0;
		for (int i = 0; i < mapData.size(); i++) {
	        Map map = mapData.get(i);
	        map.printShape();
			System.out.println(map.getName() + " : " + map.getShape());
			System.out.println();
			
			if (map.getShape().equals("Circle")) {
				int key = Integer.parseInt(map.getName().replace(".txt", ""));
				circleData.put(key, map);
				if (min == 0) {
					min = map.getSize();
				} else if (min > map.getSize()) {
					min = map.getSize();
				}
			}
		}
		System.out.println("");

		// 같은 도형을 모두 찾자
		for (int i = 0; i < mapData.size(); i++) {
			for (int j = 1; j < mapData.size() - i; j++) {
				Map map1 = mapData.get(i);
				Map map2 = mapData.get(i + j);
				if (map1.getShape().equals(map2.getShape())) {
					if (Math.abs(map1.getSize() - map2.getSize()) < (map1.getSize() / 5)) {
						System.out.println(map1.getName() + " and " + map2.getName() + " are same.");
					}
				}
			}
		}
		System.out.println("");

		// 원의 크기를 비교하자
		Vector<Integer> v = new Vector<Integer>(circleData.keySet());
	    Collections.sort(v);
	    Iterator<Integer> it = v.iterator();
	    while (it.hasNext()) {
	    	int key = (int) it.next();
	    	Map map = circleData.get(key);
			if ((double)map.getSize() / min == 1) {
				System.out.println(map.getName() + " is the smallest circle.");
			} else {
				System.out.println(map.getName() + " is " + (((double)map.getSize() / min * 100) - 100) + "% bigger than smallest circle.");
			}
	    }
	}
}
