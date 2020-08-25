import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main_17471 {
	private static int n;
	private static int[] arr;
	private static int[][] edges;
	private static boolean[] selected;
	private static boolean[] visited1;
	private static boolean[] visited2;
	private static int min = Integer.MAX_VALUE;

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		n = Integer.parseInt(br.readLine());
		arr = new int[n + 1];
		edges = new int[n + 1][n + 1];
		visited1 = new boolean[n + 1];
		visited2 = new boolean[n + 1];

		StringTokenizer st = new StringTokenizer(br.readLine());
		for (int i = 1; i <= n; i++) {
			arr[i] = Integer.parseInt(st.nextToken());
		}

		for (int i = 1, j = 1; i <= n; i++, j = 1) {
			st = new StringTokenizer(br.readLine());

			st.nextToken(); // edge 수 날리기
			while (st.hasMoreTokens()) {
				edges[i][j++] = Integer.parseInt(st.nextToken());
			}

		} // end of input

		for (int i = 1; i <= n / 2; i++) {
			selected = new boolean[n + 1];
			func(0, 1, i);
		}

		if (min == Integer.MAX_VALUE)
			System.out.println("-1");
		else
			System.out.println(min);

	} // end of main

	private static void func(int cur, int idx, int m) {
		if (cur == m) {
			if (check()) { // 만약 두 팀 다 연결되었다면
				min = Math.min(cal(), min); // 최소값 갱신
			}
			return;
		}

		for (int i = 1; i <= n; i++) {
			if (selected[i])
				continue;

			selected[i] = true;
			func(cur + 1, i + 1, m);
			selected[i] = false;
		}
	}

	private static int cal() {
		int sum1 = 0, sum2 = 0;

		for (int i = 1; i <= n; i++) {
			if (selected[i])
				sum1 += arr[i];
			else
				sum2 += arr[i];
		}

		return Math.abs(sum1 - sum2);
	}

	private static boolean check() {
		for (int i = 1; i <= n; i++) {
			visited1[i] = false;
			visited2[i] = false;
		} // 초기화

		boolean flag1 = false, flag2 = false;

		for (int i = 1; i <= n; i++) {
			if (selected[i]) {
				if (!visited1[i]) {
					if (!flag1) { // 처음이라면
						dfs(i, 1, true);
						flag1 = true;
					} else
						return false; // 연결되어 있지 않다면 (1 선거구)
				}
			} else {
				if (!visited2[i]) {
					if (!flag2) {// 처음이라면
						dfs(i, 2, false);
						flag2 = true;
					} else
						return false; // 연결되어 있지 않다면 (2 선거구)
				}
			}
		}

		return true; // 잘 연결되어 있는 경우
	}

	private static void dfs(int i, int type, boolean chk) {
		if (type == 1) { // 1 선거구
			visited1[i] = true;
			int idx = 1;
			while (edges[i][idx] != 0) {
				if (!visited1[edges[i][idx]] && selected[edges[i][idx]] == chk)
					dfs(edges[i][idx], type, true); // 다음꺼 방문
				idx++;
			}
		} else { // 2 선거구
			visited2[i] = true;
			int idx = 1;
			while (edges[i][idx] != 0) {
				if (!visited2[edges[i][idx]] && selected[edges[i][idx]] == chk)
					dfs(edges[i][idx], type, false); // 다음꺼 방문
				idx++;
			}
		}
	}
}
