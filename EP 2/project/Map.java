import java.util.ArrayList;

public class Map {
	private String _name;
	private String _shape = "";
	private int _width;
	private int _height;
	private int _size;
	private int _centerX;
	private int _centerY;
	private String[] _data;
	private int[] _dirElement = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	// 0 1 2
	// 3   5
	// 6 7 8
	public Map(String name, String[] fileContent) {
		_name = name;
		_width = Integer.parseInt(fileContent[0]);
		_height = Integer.parseInt(fileContent[1]);
		_data = fileContent[2].split("\\,");
		
		// 크기를 획득
		_size = 0;
		for (int y = 0; y < _height; y++) {
			for (int x = 0; x < _width; x++) {
				if (!getData(x, y)) {
					_size++;
				}
			}
		}
		
		// 내부를 비우자
		cleanInside();
		
		findCenter();
		
		// 모든 가장자리 점의 DirElement를 획득
		for (int y = 0; y < _height; y++) {
			for (int x = 0; x < _width; x++) {
				if (!getData(x, y)) {
					getDirElement(x, y);
				}
			}
		}
	}
	
	public String getShape() {
		if (_shape.equals("")) {
			// dirElement의 평균을 구하자
			int avg = 0;
			for (int i = 0; i < 9; i++) {
				if (i != 4)
					avg += _dirElement[i];
			}
			avg /= 8;
			
			// 주된 방향을 검출
			boolean[] div = new boolean[9];
			for (int i = 0; i < 9; i++) {
				if (i != 4 && _dirElement[i] > avg) {
					div[i] = true;
				}
			}
			
			_shape = "Cannot Recognize";
			
			if (div[1] && div[3]) {
				_shape = "Square";
			}
			else if (div[0] && div[2]){
				_shape = "Diamond";
			}
			
			boolean flag = true;
			for (int i = 0; i < 9; i++) {
				if (i != 4 && !isSimilar(avg, _dirElement[i])){
					flag = false;
				}
			}
			if (flag) {
				flag = false;
				
				int std = 0;
				for (int y = 0; y < _height; y++) {
					for (int x = 0; x < _width; x++) {
						if (!getData(x, y)) {
							if (std == 0) {
								std = (int) Math.sqrt(Math.pow(_centerX - x, 2) + Math.pow(_centerY - y, 2));
							}
							else {
								int r = (int) Math.sqrt(Math.pow(_centerX - x, 2) + Math.pow(_centerY - y, 2));
								if (!isSimilar(std, r)) {
									flag = true;
								}
							}
						}
					}
				}
				if (!flag)
					_shape = "Circle";
			}
		}
		
		return _shape;
	}
	
	public String getName() {
		return _name;
	}
	
	public int getSize() {
		return _size;
	}
	
	public void printShape() {
		for (int y = 0; y < _height; y++) {
			for (int x = 0; x < _width; x++) {
				System.out.print(_data[y * _width + x] + " ");
			}
			System.out.println("");
		}
	}
	
	public boolean getData(int x, int y) {
		// 외부 : 흰색, true : 흰색, false : 검정색
		if (x < 0 || x >= _width || y < 0 || y >= _height) {
			return true;
		}
		if (_data[y * _width + x].equals("1"))
			return true;
		return false;
	}
	
	public void getDirElement(int x, int y) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				int new_x = x - 1 + j;
				int new_y = y - 1 + i;
				if (!getData(new_x, new_y)) {
					_dirElement[i * 3 + j]++;
				}
			}
		}
	}
	
	public boolean isSimilar(int a, int b) {
		return (Math.abs(a - b) < 5);
	}
	
	public void cleanInside() {
		ArrayList<Integer> clean = new ArrayList<Integer>();
		for (int y = 0; y < _height; y++) {
			for (int x = 0; x < _width; x++) {
				if (!getData(x - 1, y) && !getData(x + 1, y) && !getData(x, y - 1) && !getData(x, y + 1)) {
					clean.add(y * _width + x);
				}
			}
		}
		for (int i : clean) {
			_data[i] = "1";
		}
	}
	
	public void findCenter() {
		boolean flag = false;
		for (int y = 0; y < _height; y++) {
			for (int x = 0; x < _width; x++) {
				if (!getData(x, y)) {
					_centerY += y;
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
		flag = false;
		for (int y = _height - 1; y >= 0; y--) {
			for (int x = 0; x < _width; x++) {
				if (!getData(x, y)) {
					_centerY += y;
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
		flag = false;
		for (int x = 0; x < _width; x++) {
			for (int y = 0; y < _height; y++) {
				if (!getData(x, y)) {
					_centerX += x;
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
		flag = false;
		for (int x = _width - 1; x >= 0; x--) {
			for (int y = 0; y < _height; y++) {
				if (!getData(x, y)) {
					_centerX += x;
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
		
		_centerX /= 2;
		_centerY /= 2;
	}
}
