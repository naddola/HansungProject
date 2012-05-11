import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

/* <applet code="GameJava" width="500" height="500"></applet>*/

public class GameJava extends Applet implements Runnable {
	String msg = "";

	Thread clock;

	Image off;
	Graphics offG;

	// Man ��ġ ����
	int x = 0;
	int y = 0;
	// CRTL�� ������ �����϶� �� ��ġ ����
	int[] x2;
	int[] y2;
	int xc;

	// ���� ��ġ ����
	int w = 50;
	int z = 50;

	// ���� ������ ��ġ ����
	int w2 = 200;
	int z2 = 200;
	
	int wr=(int) (Math.random()*7-3.5);
	int zr=(int) (Math.random()*7-3.5);
	
	int rr;
	
	int runGame; // ���Ӹ�� ����
	int status; // ��ҿ��� 0�ε� CRTLŰ�� ������ 1�� �Ǹ鼭 �� ������ ���� �� �ִ�.

	
	
	public void init() {
		msg = "init";
		off = createImage(500, 500);
		offG = off.getGraphics();

		x2 = new int[100];
		y2 = new int[100];
		xc = 0;

		runGame = 1;
		status = 0;

		drawMap();
		drawMan();
		addKeyListener(new MyKeyHandler());
	}

	public void start() {
		System.out.println("start");
		if (clock == null) {
			clock = new Thread(this);
			clock.start();
		}
	}

	public void run() {
		while (true) {

			try {
				clock.sleep(10);
			} catch (InterruptedException ie) {
			}

			switch (runGame) {
			case 1:
				play();
				break;
			case 2:
				break;
			default:
				break;
			}
			repaint();
		}
	}

	public void drawTitle() {
		offG.fillOval(150, 150, 300, 300);
	}

	public void play() {
		drawMap();
		drawMan();
		moveET();
		drawET();
		drawLine();
	}

	public void drawMan() {
		msg = "drawMan";
		offG.setColor(Color.green);
		offG.fillOval(x - 5, y - 5, 10, 10);
	}

	public void drawLine() {
		offG.setColor(Color.red);
		if (xc >= 1) {
			// System.out.println("============================ "+xc);
			for (int i = 0; i < xc; i++) {
				// System.out.println(x2[i]+"  "+y2[i]+"  "+ x2[i + 1]+"   "+
				// y2[i + 1]);
				offG.drawLine(x2[i], y2[i], x2[i + 1], y2[i + 1]);

			}
		}
	}

	public void drawMap() {
		offG.setColor(Color.white);
		offG.fillRect(0, 0, 500, 500);
	}

	public void drawET() {
		offG.setColor(Color.MAGENTA);
		offG.fillOval(w, z, 50, 50);
	}

	public void moveET() {
		rr=(int) (Math.random()*3+1);
		System.out.print(rr);
		if(w>0 && w<450 && z>0 &&z<450 ){
				if(wr==0 && zr==0){
					while(wr==0&&zr==0){
						wr=(int) (Math.random()*7-3.5);
						zr=(int) (Math.random()*7-3.5);
					}
				}
			
			w=w+wr;
			z=z+zr;
		}
		else{
			if(w==0 && z!=0){
				wr=(int) (Math.random()*3+1);
				zr=(int) (Math.random()*7-3.5);
			}
			else if(w!=0 && z==0){
				wr=(int) (Math.random()*7-3.5);
				zr=(int) (Math.random()*3+1);
			}
			else if(w==450 && z!=450){
				wr=(int) (Math.random()*2-3.5);
				zr=(int) (Math.random()*7-3.5);
			}
			else if(w!=450 && z==450){
				wr=(int) (Math.random()*7-3.5);
				zr=(int) (Math.random()*2-3.5);
			}
			else{
				wr=(int) (Math.random()*7-3.5);
				zr=(int) (Math.random()*7-3.5);
			}
			w=w+wr;
			z=z+zr;
		}
	}

	public void moveSetET() {
		w2 = (int) (Math.random() * 500);
		z2 = (int) (Math.random() * 500);
	}

	public void paint(Graphics g) {
		g.drawImage(off, 0, 0, this);
	}

	class MyKeyHandler extends KeyAdapter {
		int keyCode;
		int before = 0;

		public void keyPressed(KeyEvent e) {
			{
				keyCode = e.getKeyCode();
				// System.out.println(keyCode+"   "+before+"   "+xc);

				if (keyCode == KeyEvent.VK_LEFT) {
					x = x - 2;
				}

				else if (keyCode == KeyEvent.VK_RIGHT) {
					x = x + 2;
				}

				else if (keyCode == KeyEvent.VK_DOWN) {
					y = y + 2;
				}

				else if (keyCode == KeyEvent.VK_UP) {
					y = y - 2;
				}

				else if (keyCode == 17) {

					status = 1;
					x2[xc] = x;
					y2[xc++] = y;
					x2[xc] = x;
					y2[xc] = y;

					System.out.println("17������     " + x2[xc - 1] + "   " + x);
				}

				// CRTL ������ �� �� ������ ����
				if (status == 1 && before == keyCode && before != 17) {
					x2[xc] = x;
					y2[xc] = y;
				} else if (status == 1 && before != keyCode && keyCode != 17
						&& before != 17) {
					System.out.println("=================");
					if (x2[xc] != x)
						x = x - 2;
					else if (y2[xc] != y)
						y = y - 2;
					x2[++xc] = x;
					y2[xc] = y;
					System.out.println(x2[xc] + "  " + y2[xc]);
				}

				before = keyCode;

				drawMap();
				drawMan();
				drawET();
				drawLine();
				repaint();
			}
		}

		public void keyReleased(KeyEvent e) {
			keyCode = e.getKeyCode();
			if (keyCode == 17) {
				System.out.println(keyCode + "Released");
				status = 0;
				xc = 0;
			}
		}
	}
}
