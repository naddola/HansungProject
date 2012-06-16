import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.net.URL;
import java.util.*;



/* <applet code="GameJava" width="500" height="500"></applet>*/

public class GameJava extends Applet implements Runnable {
	String msg = "";

	// ���� ����
	ET et;
	Thread clock;

	Image img;  // ���ȭ��
	Image hansung;   // ó��ȭ�� �ΰ�
	BufferedImage off;  // �����̹���
	Graphics offG;  
	MediaTracker tracker;
	Color al;  // �����
	Color red;  // ������

	int board[][];  // 100x100 �ȼ��̸� ���� ���� ���¸� ��Ÿ��
	/*
	 board = 0  // �������� ���� ��(ȸ��)
	 board = 1  // ������ ��
	 board = 2  // ������ �� �ִ� ����(�Ķ�)
	 board = 3  // ��ô ���� ����(����)
	 */	
	int checkBoard[][];  // ET�� ��ġ�� ã�� ���� 100x100�迭
	
	// ���� ������ ��θ� ����
	int xBuf[];
	int yBuf[];
	int Bufc;
	
	int width;
	int height;
	int checkE;

	// �޴� ����
	
	// ���� ��ô�� ���� ���� ��Ÿ���� ���� ����
	int per;
	double perl;
	
	//��Ʈ
	Font ftStart;
	Font ftGameover;
	Font ftPercent;

	// Man ��ġ ����
	int x = 0;
	int y = 0;
	// ��ô�Ϸ� ������ ������ġ
	int xs;
	int ys;

	int runGame; // ���Ӹ�� ���� 1-play, 2-Title
	int status; // ��ҿ��� 0�ε� CRTLŰ�� ������ 1�� �Ǹ鼭 �� ������ ���� �� �ִ�.
	int gameover;  // gameOver �˻� ����

	public void init() {
		width = 500;
		height = 500;
		setLayout(new BorderLayout());
		board = new int[100][100];
		checkBoard = new int[100][100];
		xBuf = new int[500];
		yBuf = new int[500];
		Bufc = 0;
		checkE = 0;
		gameover = 0;
		al = new Color(0.0f, 0.0f, 0.0f, 0.0f);
		red = new Color(1.0f,0.0f,0.0f, 1.0f);

		per = 0;
		perl = 0;
		ftGameover = new Font("TimesRoaman", Font.BOLD, 40);
		ftStart = new Font("TimesRoman", Font.BOLD, 20);
		ftPercent = new Font("TimesRoma", Font.BOLD, 20);

		et = new ET();

		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++) {
				board[i][j] = 0;
				checkBoard[i][j] = 0;
			}
		// ����ó�� �ѿ� ���� �׸���
		for (int i = 0; i < 100; i++) {
			board[0][i] = 2;
			board[i][0] = 2;
			board[99][i] = 2;
			board[i][99] = 2;
		}
		setSize(width + 200, height);
		img = Toolkit.getDefaultToolkit().createImage("image.jpg");
		hansung = Toolkit.getDefaultToolkit().createImage("hansung.jpg");
		tracker = new MediaTracker(this);
		tracker.addImage(img, 0);
		tracker.addImage(hansung, 1);
		try {
			tracker.waitForID(0); // ID�� 0���� �̹��� �ε� ����
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		off = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		offG = off.getGraphics();
		offG.drawImage(img, 0, 0, this);

		runGame = 2;
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
		clock.setPriority(5);
	}

	public void run() {
		while (true) {
			try {
				clock.sleep(100);
			} catch (InterruptedException ie) {
			}

			switch (runGame) {
			case 1:
				play();
				break;
			case 2:
				drawTitle();
				break;
			default:
				break;
			}
			repaint();
		}
	}

	// ���� ó�� ȭ��
	public void drawTitle() {
		drawLine();
		et.drawET();
		drawMan();
		offG.setColor(Color.white);
		offG.fillRect(100, 100, 300, 200);
		offG.drawImage(hansung, 100, 100, this);
		offG.setColor(red);
		offG.setFont(ftStart);
		offG.drawString("Press Enter to Start!!", 170, 180);
		offG.setColor(Color.magenta);
		offG.drawString("0891039 ����ö", 250, 280);
		offG.drawString("0891039 ������", 250, 310);
	}

	//GameOver �޼ҵ�
	public void drawGameOver() {
		// ���� ���н�
		if (gameover == 1) {
			offG.setFont(ftGameover);
			String over = "Game Over";
			offG.setColor(Color.RED);
			offG.drawString(over, 150, 200);
			offG.drawString("Press Enter to Start", 100, 400);
		}
		// ���� ������
		else if (gameover ==0 && perl >= 80){
			offG.setFont(ftGameover);
			offG.setColor(red);
			offG.drawString("You Win ! ! !", 150, 200);
			offG.drawString("Press Enter to Start", 100, 400);
		}
	}
	
	// ��ô�� ���� %�� �ٲٴ� �޼ҵ�
	public void changePercent() {
		perl = (double)per*100 / (98*98);
		perl = Math.round(perl*100)/100.0;
	}

	// ��ô�� ���� % �׸���
	public void drawPercent() {
		offG.setFont(ftPercent);
		offG.setColor(Color.orange);
		offG.drawString(""+perl+"%", 420, 420);
	}

	// ���ӿ����� �ʱ�ȭ �Լ�
	public void reset() {
		x = 0;
		y = 0;
		per = 0;
		perl = 0;
		for (int i = 1; i < 99; i++) {
			for (int j = 1; j < 99; j++) {
				board[i][j] = 0;
				checkBoard[i][j] = 0;
			}
		}
		for (int i = 0; i < 100; i++) {
			board[0][i] = 2;
			board[i][0] = 2;
			board[99][i] = 2;
			board[i][99] = 2;
		}
		drawLine();
		drawMan();
		et.drawET();
	}

	public void play() {
		// drawMap();
		// drawGrid();
		drawLine();
		drawMan();
		et.drawET();
		drawPercent();
		drawGameOver();
	}
	
	// ĳ���� �׸���
	public void drawMan() {
		msg = "drawMan";
		offG.setColor(Color.green);
		offG.fillOval(x - 5, y - 5, 15, 15);
	}
	
	// �� �ȼ��� ���� ä���
	public void drawLine() {
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				if (board[i][j] == 3) {
					offG.setColor(red);
					offG.fillRect(i * 5, j * 5, 5, 5);
				} else if (board[i][j] == 2) {
					offG.setColor(Color.blue);
					offG.fillRect(i * 5, j * 5, 5, 5);
				} else if (board[i][j] == 0) {
					offG.setColor(Color.gray);
					offG.fillRect(i * 5, j * 5, 5, 5);
				} else if (board[i][j] == 1) {
					offG.setColor(al);
					offG.fillRect(i * 5, j * 5, 5, 5);
				}
			}
		}
	}

	//��ô ������ �������� �Ķ������� �ٲٱ�
	public void changeRed() {
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				if (board[i][j] == 3) {
					board[i][j] = 2;
				}
			}
		}
		Bufc = 0;
	}

	// ��ô ������ ���� �Ķ� ���� ���ֱ�
	public void removeBlue() {
		for (int i = 1; i < 99; i++) {
			for (int j = 1; j < 99; j++) {
				if (board[i][j] == 2) {
					if (board[i + 1][j] == 1 && board[i - 1][j] == 1) {
						board[i][j] = 1;
					} else if (board[i][j + 1] == 1 && board[i][j - 1] == 1) {
						board[i][j] = 1;
					}
				}
			}
		}
	}
	
	// ��� �׸���
	public void drawMap() {
		offG.drawImage(img, 0, 0, this);
	}

	// ȫ�� ä��� �˰����� ���� ��ô�Ѷ� �����
	public void fillLine(int i, int j, int thisBox, int chan) {
		if (board[i][j] != thisBox)
			return;
		board[i][j] = chan;
		per++;
		fillLine(i - 1, j, thisBox, chan);
		fillLine(i + 1, j, thisBox, chan);
		fillLine(i, j - 1, thisBox, chan);
		fillLine(i, j + 1, thisBox, chan);
	}

	// ȫ�� ä��� �˰����� �����Ͽ� ���� ET�� �ִ� ��ġ�� Ȯ���ϱ�
	public void checkET(int i, int j) {

		int iET, jET;
		iET = (et.xe + 25) / 5;
		jET = (et.ye + 25) / 5;

		if (checkBoard[i][j] != 0) {
			return;
		}
		checkBoard[i][j] = 1;

		if (checkE == 1) {
			return;
		}
		if (i == iET && j == jET || i == iET - 1 && j == jET - 1
				|| i == iET + 1 && j == jET + 1 || i == iET - 2 && j == jET
				|| i == iET && j == jET - 2) {
			checkE = 1;
			return;
		}
		if (board[i][j] != 0) {
			return;
		}

		checkET(i - 1, j);
		checkET(i + 1, j);
		checkET(i, j - 1);
		checkET(i, j + 1);
	}

	//CheckET �ʱ�ȭ �޼ҵ�
	public void initCheckET() {
		checkE = 0;
		for (int i = 1; i < 99; i++)
			for (int j = 1; j < 99; j++) {
				checkBoard[i][j] = 0;
			}
	}

	// ET�� �浹 �˻�
	public void killMan() {
		if (board[et.xe / 5][et.ye / 5] == 3
				|| board[(et.xe + 50) / 5][(et.ye + 50) / 5] == 3
				|| board[(et.xe + 50) / 5][et.ye / 5] == 3
				|| board[et.xe / 5][(et.ye + 50) / 5] == 3) {
			gameover = 1;
		}
	}

	public void paint(Graphics g) {
		g.drawImage(off, 0, 0, this);
	}

	//ET Ŭ����
	class ET implements Runnable {

		Thread clockE;
		int speed;   //ET�ӵ�
		int xe;		//ET�� x��ǥ
		int ye;		//ET�� y��ǥ
		int xr;		//ET�� �̵�������
		int yr;
		int rr;
		int widthE;
		int heightE;

		//�ʱ�ȭ
		public ET() {
			speed = 30;
			xe = 200;
			ye = 100;
			xr = 5;
			yr = 5;
			widthE = 50;
			heightE = 50;
		}

		// ET�� �̵���Ű��
		public void moveET() {
			for (int i = 10; i < 40; i++) {
				// ������ �浹
				if (board[(xe + 45 + xr) / 5][(ye + i) / 5] != 0) {
					xr = -xr;
				}
				// ���� �浹
				else if (board[(xe + xr + 5) / 5][(ye + i) / 5] != 0) {
					xr = -xr;
				}
				// �Ʒ��� �浹
				else if (board[(xe + i) / 5][(ye + 45 + yr) / 5] != 0) {
					yr = -yr;
				}
				// ���� �浹
				else if (board[(xe + i) / 5][(ye + yr + 5) / 5] != 0) {
					yr = -yr;
				}
			}
			xe += xr;
			ye += yr;
		}

		public void start() {
			if (clockE == null) {
				clockE = new Thread(this);
				clockE.start();
			}
			clockE.setPriority(1);
		}

		// ET�׸���
		public void drawET() {
			offG.fillOval(xe, ye, 50, 50);
		}
		
		//ET�� �ӵ� ����
		public void changeSpeed() {
			speed = 30 - (int)perl/4;
		}

		public void run() {
			while (true) {
				while (gameover != 1) {
					try {
						clockE.sleep(speed);
					} catch (InterruptedException ie) {
					}
					if(perl >= 80){
						break;
					}
					changeSpeed();
					moveET();
					killMan();
					drawET();
				}
			}
		}
	}

	class MyKeyHandler extends KeyAdapter {
		int keyCode;
		int before = 0;

		public void keyPressed(KeyEvent e) {
			{
				keyCode = e.getKeyCode();
				
				// ����Ű �Է½�
				if (keyCode == KeyEvent.VK_LEFT) {
					if (x > 0) {
						// �Ķ��� ���� �������� �����̱�
						if (status == 0 && board[x / 5][y / 5] == 2
								&& board[x / 5 - 1][y / 5] == 2) {
							x = x - 5;
						}
						// CRTL ���� ���� : �Ķ����� -> �̰�ô��
						else if (status == 1 && board[x / 5][y / 5] == 2
								&& board[x / 5 - 1][y / 5] == 0) {
							x = x - 5;
							xBuf[Bufc] = x;
							yBuf[Bufc++] = y;
						}
						// CRTL ���� ���� : ��ô �� -> �̰�ô������
						else if (status == 1 && board[x / 5][y / 5] == 3
								&& board[x / 5 - 1][y / 5] == 0) {
							x = x - 5;
							xBuf[Bufc] = x;
							yBuf[Bufc++] = y;
						}
						// CRTL ���� ���� : ��ô �� -> �Ķ����� (��ô ������)
						else if (status == 1 && board[x / 5][y / 5] == 3
								&& board[x / 5 - 1][y / 5] == 2) {
							x = x - 5;
							if (ys < y) {
								checkET(x / 5 + 1, y / 5 - 1);
								if (checkE == 1) {
									fillLine(x / 5 + 1, y / 5 + 1, 0, 1);
								} else
									fillLine(x / 5 + 1, y / 5 - 1, 0, 1);
							} else {
								checkET(x / 5 + 1, y / 5 + 1);
								if (checkE == 1) {
									fillLine(x / 5 + 1, y / 5 - 1, 0, 1);
								} else {
									fillLine(x / 5 + 1, y / 5 + 1, 0, 1);
								}
							}
							initCheckET();
							changeRed();
							removeBlue();
							changePercent();
						}
					}
				}

				// ������Ű �Է½�
				else if (keyCode == KeyEvent.VK_RIGHT) {
					if (x < width - 5) {
						if (status == 0 && board[x / 5][y / 5] == 2
								&& board[x / 5 + 1][y / 5] == 2) {
							x = x + 5;
						} else if (status == 1 && board[x / 5][y / 5] == 2
								&& board[x / 5 + 1][y / 5] == 0) {
							x = x + 5;
							xBuf[Bufc] = x;
							yBuf[Bufc++] = y;
						} else if (status == 1 && board[x / 5][y / 5] == 3
								&& board[x / 5 + 1][y / 5] == 0) {
							x = x + 5;
							xBuf[Bufc] = x;
							yBuf[Bufc++] = y;
						} else if (status == 1 && board[x / 5][y / 5] == 3
								&& board[x / 5 + 1][y / 5] == 2) {
							x = x + 5;
							if (ys > y) {
								checkET(x / 5 - 1, y / 5 + 1);
								if (checkE == 1) {
									fillLine(x / 5 - 1, y / 5 - 1, 0, 1);
								} else
									fillLine(x / 5 - 1, y / 5 + 1, 0, 1);
							} else {
								checkET(x / 5 - 1, y / 5 - 1);
								if (checkE == 1) {
									System.out
											.println("=====================j");
									fillLine(x / 5 - 1, y / 5 + 1, 0, 1);
								} else {
									fillLine(x / 5 - 1, y / 5 - 1, 0, 1);
								}
							}
							initCheckET();
							changeRed();
							removeBlue();
							changePercent();
						}
					}
				}

				// �Ʒ���Ű �Է½�
				else if (keyCode == KeyEvent.VK_DOWN) {
					if (y < height - 5) {
						if (status == 0 && board[x / 5][y / 5] == 2
								&& board[x / 5][y / 5 + 1] == 2) {
							y = y + 5;
						} else if (status == 1 && board[x / 5][y / 5] == 2
								&& board[x / 5][y / 5 + 1] == 0) {
							y = y + 5;
							xBuf[Bufc] = x;
							yBuf[Bufc++] = y;
						} else if (status == 1 && board[x / 5][y / 5] == 3
								&& board[x / 5][y / 5 + 1] == 0) {
							y = y + 5;
							xBuf[Bufc] = x;
							yBuf[Bufc++] = y;
						} else if (status == 1 && board[x / 5][y / 5] == 3
								&& board[x / 5][y / 5 + 1] == 2) {
							y = y + 5;

							if (xs > x) {
								checkET(x / 5 + 1, y / 5 - 1);
								if (checkE == 1) {
									fillLine(x / 5 - 1, y / 5 - 1, 0, 1);
								} else
									fillLine(x / 5 + 1, y / 5 - 1, 0, 1);
							} else {
								checkET(x / 5 - 1, y / 5 - 1);
								if (checkE == 1) {
									System.out
											.println("=====================j");
									fillLine(x / 5 + 1, y / 5 - 1, 0, 1);
								} else {
									fillLine(x / 5 - 1, y / 5 - 1, 0, 1);
								}
							}
							initCheckET();
							changeRed();
							removeBlue();
							changePercent();
						}
					}
				}

				// ����Ű �Է½�
				else if (keyCode == KeyEvent.VK_UP) {
					if (y > 0) {
						if (status == 0 && board[x / 5][y / 5] == 2
								&& board[x / 5][y / 5 - 1] == 2) {
							y = y - 5;
						} else if (status == 1 && board[x / 5][y / 5] == 2
								&& board[x / 5][y / 5 - 1] == 0) {
							y = y - 5;
							xBuf[Bufc] = x;
							yBuf[Bufc++] = y;
						} else if (status == 1 && board[x / 5][y / 5] == 3
								&& board[x / 5][y / 5 - 1] == 0) {
							y = y - 5;
							xBuf[Bufc] = x;
							yBuf[Bufc++] = y;
						} else if (status == 1 && board[x / 5][y / 5] == 3
								&& board[x / 5][y / 5 - 1] == 2) {
							y = y - 5;

							if (xs > x) {
								checkET(x / 5 + 1, y / 5 + 1);
								if (checkE == 1) {
									fillLine(x / 5 - 1, y / 5 + 1, 0, 1);
								} else
									fillLine(x / 5 + 1, y / 5 + 1, 0, 1);
							} else {
								checkET(x / 5 - 1, y / 5 + 1);
								if (checkE == 1) {
									fillLine(x / 5 + 1, y / 5 + 1, 0, 1);
								} else {
									fillLine(x / 5 - 1, y / 5 + 1, 0, 1);
								}
							}
							initCheckET();
							changeRed();
							removeBlue();
							changePercent();
						}
					}
				}

				// CRTLŰ �Է½�
				else if (keyCode == 17) {
					status = 1;
					if (board[x / 5][y / 5] == 2) {
						xs = x;
						ys = y;
					}
				}

				// EnterŰ �Է½�
				else if (keyCode == 10) {
					//���� ó�� ȭ�鿡�� EnterŰ �Է�
					if (runGame == 2) {
						et.start();
						runGame = 1;
						gameover = 0;
					}
					
					//���� ���� �� ȭ�鿡�� EnterŰ �Է� �� �����
					else if (gameover == 1){
						et.xe = 100;
						et.ye = 100;
						gameover = 0;
						reset();
						et.start();
					}
					
					//���� ���� �� ȭ�鿡�� EnterŰ �Է� �� �����
					else if (gameover == 0 && perl >= 80){
						et.xe = 100;
						et.ye = 100;
						reset();
						et.start();
					}
				}
				
				if (status == 1) {
					if (board[x / 5][y / 5] == 2) {

					} else
						board[x / 5][y / 5] = 3;
				}
				drawMap();
				drawLine();
				drawPercent();
				drawMan();
				et.drawET();
				
				repaint();
			}
		}

		// CRTLŰ�� ������ ������
		public void keyReleased(KeyEvent e) {
			keyCode = e.getKeyCode();
			if (keyCode == 17) {
				status = 0;
			}
		}
	}
}
