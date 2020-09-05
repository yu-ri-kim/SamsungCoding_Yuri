import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main_17281 {
	private static int n; // 이닝
	private static int[] order = new int[9]; // 타순
	private static int[][] score; // 각 선수가 각 이닝때 얻는 결과
	private static int maxValue = Integer.MIN_VALUE; // 점수

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		n = Integer.parseInt(br.readLine());
		score = new int[n][9];

		String tmp = "";
		for (int i = 0; i < n; i++) {
			tmp = br.readLine();
			for (int j = 0, idx = 0; j < 9; j++, idx += 2) {
				score[i][j] = tmp.charAt(idx) - '0';
			}
		} // end of input

		func(0, 0); // 타순 정하기
		System.out.println(maxValue);
	}

	private static void func(int cur, int flag) {
		if (cur == 9) { // 순서 다 정함
			baseball();
			return;
		}

		if (cur == 3) { // 4번타자는 무조건 1번선수
			order[cur] = 0;
			func(cur + 1, flag);
			return;
		}

		for (int i = 1; i < 9; i++) {
			if ((flag & (1 << i)) == 0) {
				order[cur] = i;
				func(cur + 1, (flag | (1 << i)));
			}
		}
	}

	private static void baseball() {
		int s = 0; // 점수
		int p = 0; // 현재 타자의 번호

		for (int round = 0; round < n; round++) { // 다음 이닝으로 이동
			int out = 0; // 아웃 개수
			int[] baseman = new int[3]; // 1루, 2루, 3루

			// 아웃 세번이면 다음 이닝
			while (out != 3) {
				int bmScore = score[round][order[p %= 9]];
 				
				if (bmScore == 0) { // 아웃
					out++;
				}

				else if (bmScore == 4) { // 홈런
					s++;
					for (int i = 0; i < baseman.length; i++) {
						if (baseman[i] == 1)
							s++;
					}
					Arrays.fill(baseman, 0);
				}

				else {
					if (bmScore == 3) { // 3루타
						for (int i = 0; i < baseman.length; i++) {
							if (baseman[i] == 1)
								s++;
						}
						Arrays.fill(baseman, 0);
						baseman[2] = 1;
					} else if (bmScore == 2) { // 2루타
						for (int i = 1; i < baseman.length; i++) {
							if (baseman[i] == 1) {
								s++;
							}
						}
						baseman[2] = baseman[0];
						baseman[1] = 1;
						baseman[0] = 0;
						
					} else if (bmScore == 1) { // 안타
						if (baseman[2] == 1) {
							s++;
						}
						baseman[2] = baseman[1];
						baseman[1] = baseman[0];
						baseman[0] = 1;
					}
				}
				p++; // 다음 타자
			}
		} // 모든 경기 끝남
		
		if (maxValue < s)
			maxValue = s;
	}
}
