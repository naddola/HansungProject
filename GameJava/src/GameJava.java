import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.net.URL;
import java.util.*;



/* <applet code="GameJava" width="500" height="500"></applet>*/

public class GameJava extends Applet implements Runnable {
	String msg = "";

	// 게임 관련
	ET et;
	Thread clock;

	Image img;  // 배경화면
	Image hansung;   // 처음화면 로고
	BufferedImage off;  // 가상이미지
	Graphics offG;  
	MediaTracker tracker;
	Color al;  // 투명색
	Color red;  // 빨강색

	int board[][];  // 100x100 픽셀이며 현재 땅의 상태를 나타냄
	/*
	 board = 0  // 차지하지 않은 땅(회색)
	 board = 1  // 차지한 땅
	 board = 2  // 움직일 수 있는 라인(파랑)
	 board = 3  // 개척 중인 라인(빨강)
	 */	
	int checkBoard[][];  // ET의 위치를 찾기 위한 100x100배열
	
	// 빨간 라인의 경로를 저장
	int xBuf[];
	int yBuf[];
	int Bufc;
	
	int width;
	int height;
	int checkE;

	// 메뉴 관련
	
	// 현재 개척한 땅의 양을 나타내기 위한 변수
	int per;
	double perl;
	
	//폰트
	Font ftStart;
	Font ftGameover;
	Font ftPercent;

	// Man 위치 저장
	int x = 0;
	int y = 0;
	// 개척하러 나갈때 시작위치
	int xs;
	int ys;

	int runGame; // 게임모드 변수 1-play, 2-Title
	int status; // 평소에는 0인데 CRTL키르 누르면 1이 되면서 땅 먹으러 나갈 수 있다.
	int gameover;  // gameOver 검사 변수

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
		// 제일처음 겉에 라인 그리기
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
			tracker.waitForID(0); // ID가 0번인 이미지 로딩 보장
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

	// 제일 처음 화면
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
		offG.drawString("0891039 전현철", 250, 280);
		offG.drawString("0891039 김종용", 250, 310);
	}

	//GameOver 메소드
	public void drawGameOver() {
		// 게임 실패시
		if (gameover == 1) {
			offG.setFont(ftGameover);
			String over = "Game Over";
			offG.setColor(Color.RED);
			offG.drawString(over, 150, 200);
			offG.drawString("Press Enter to Start", 100, 400);
		}
		// 게임 성공시
		else if (gameover ==0 && perl >= 80){
			offG.setFont(ftGameover);
			offG.setColor(red);
			offG.drawString("You Win ! ! !", 150, 200);
			offG.drawString("Press Enter to Start", 100, 400);
		}
	}
	
	// 개척한 땅의 %를 바꾸는 메소드
	public void changePercent() {
		perl = (double)per*100 / (98*98);
		perl = Math.round(perl*100)/100.0;
	}

	// 개척한 땅의 % 그리기
	public void drawPercent() {
		offG.setFont(ftPercent);
		offG.setColor(Color.orange);
		offG.drawString(""+perl+"%", 420, 420);
	}

	// 게임오버시 초기화 함수
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
	
	// 캐릭터 그리기
	public void drawMan() {
		msg = "drawMan";
		offG.setColor(Color.green);
		offG.fillOval(x - 5, y - 5, 15, 15);
	}
	
	// 각 픽셀별 색깔 채우기
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

	//개척 성공시 빨간라인 파란색으로 바꾸기
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

	// 개척 성공시 원래 파란 라인 없애기
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
	
	// 배경 그리기
	public void drawMap() {
		offG.drawImage(img, 0, 0, this);
	}

	// 홍수 채우기 알고리즘을 통한 개척한땅 지우기
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

	// 홍수 채우기 알고리즘을 응용하여 현재 ET가 있는 위치를 확인하기
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

	//CheckET 초기화 메소드
	public void initCheckET() {
		checkE = 0;
		for (int i = 1; i < 99; i++)
			for (int j = 1; j < 99; j++) {
				checkBoard[i][j] = 0;
			}
	}

	// ET와 충돌 검사
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

	//ET 클래스
	class ET implements Runnable {

		Thread clockE;
		int speed;   //ET속도
		int xe;		//ET의 x좌표
		int ye;		//ET의 y좌표
		int xr;		//ET의 이동증가량
		int yr;
		int rr;
		int widthE;
		int heightE;

		//초기화
		public ET() {
			speed = 30;
			xe = 200;
			ye = 100;
			xr = 5;
			yr = 5;
			widthE = 50;
			heightE = 50;
		}

		// ET를 이동시키기
		public void moveET() {
			for (int i = 10; i < 40; i++) {
				// 오른쪽 충돌
				if (board[(xe + 45 + xr) / 5][(ye + i) / 5] != 0) {
					xr = -xr;
				}
				// 왼쪽 충돌
				else if (board[(xe + xr + 5) / 5][(ye + i) / 5] != 0) {
					xr = -xr;
				}
				// 아래쪽 충돌
				else if (board[(xe + i) / 5][(ye + 45 + yr) / 5] != 0) {
					yr = -yr;
				}
				// 위쪽 충돌
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

		// ET그리기
		public void drawET() {
			offG.fillOval(xe, ye, 50, 50);
		}
		
		//ET의 속도 조절
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
				
				// 왼쪽키 입력시
				if (keyCode == KeyEvent.VK_LEFT) {
					if (x > 0) {
						// 파란색 라인 위에서만 움직이기
						if (status == 0 && board[x / 5][y / 5] == 2
								&& board[x / 5 - 1][y / 5] == 2) {
							x = x - 5;
						}
						// CRTL 누른 상태 : 파란라인 -> 미개척땅
						else if (status == 1 && board[x / 5][y / 5] == 2
								&& board[x / 5 - 1][y / 5] == 0) {
							x = x - 5;
							xBuf[Bufc] = x;
							yBuf[Bufc++] = y;
						}
						// CRTL 누른 상태 : 개척 중 -> 미개척땅으로
						else if (status == 1 && board[x / 5][y / 5] == 3
								&& board[x / 5 - 1][y / 5] == 0) {
							x = x - 5;
							xBuf[Bufc] = x;
							yBuf[Bufc++] = y;
						}
						// CRTL 누른 상태 : 개척 중 -> 파란라인 (개척 성공시)
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

				// 오른쪽키 입력시
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

				// 아래쪽키 입력시
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

				// 위쪽키 입력시
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

				// CRTL키 입력시
				else if (keyCode == 17) {
					status = 1;
					if (board[x / 5][y / 5] == 2) {
						xs = x;
						ys = y;
					}
				}

				// Enter키 입력시
				else if (keyCode == 10) {
					//제일 처음 화면에서 Enter키 입력
					if (runGame == 2) {
						et.start();
						runGame = 1;
						gameover = 0;
					}
					
					//게임 실패 후 화면에서 Enter키 입력 후 재시작
					else if (gameover == 1){
						et.xe = 100;
						et.ye = 100;
						gameover = 0;
						reset();
						et.start();
					}
					
					//게임 성공 후 화면에서 Enter키 입력 후 재시작
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

		// CRTL키를 누른후 놓을때
		public void keyReleased(KeyEvent e) {
			keyCode = e.getKeyCode();
			if (keyCode == 17) {
				status = 0;
			}
		}
	}
}
