import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
import javax.swing.Timer;

class SortDemoSequence implements Sequence<Integer> {
	private Integer[] storage;
	private int highlighted;
	private boolean write;
	private SortDemo sortDemo;
	private int numOperations =0;
	
	public SortDemoSequence(int size, SortDemo demo) {
		storage = new Integer[size];
		randomize();
		sortDemo = demo;
	}
	
	public Integer get(int index) {
		highlighted = index;
		write = false;
		animateOneStep();
		return storage[index];
	}
	
	public Integer peek(int index) {
		return storage[index];
	}
	
	public void put(int index, Integer value) {
		storage[index] = value;
		highlighted = index;
		write = true;
		animateOneStep();
	}
	
	public void swap(int index1, int index2) {
		Integer tmp = get(index1);
		put(index1, get(index2));
		put(index2, tmp);
	}
	
	public int size() {
		return storage.length;
	}
	
	public int getHighlighted() {
		return highlighted;
	}
	
	public boolean isWrite() {
		return write;
	}
	
	private void animateOneStep() {
		//System.out.println("Tick");
		SwingUtilities.invokeLater(new Runnable(){
			public void run() {
				sortDemo.animationCanvas.repaint();
			}
		});
		++numOperations;
		sortDemo.operationCountBox.setText("" + numOperations);
		synchronized (sortDemo) {
			long now = sortDemo.tick;
			while (sortDemo.tick < now + 1) {
				try {
					sortDemo.wait();
				} catch (InterruptedException e) {
					// ignore
				}
			}
		}
	}

	public void randomize() {
		ArrayList<Integer> contents = new ArrayList<Integer>();
		for (int i = 0; i < size(); i++) {
			contents.add(i + 1);
		}
		Collections.shuffle(contents);
		
		storage = contents.toArray(new Integer[size()]);
		highlighted = -1;
		numOperations = 0;
	}
}
