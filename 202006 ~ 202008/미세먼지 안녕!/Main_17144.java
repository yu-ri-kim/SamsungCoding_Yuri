import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main_17144 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
        
        // 배열 크기, 시간
        int r = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());
		int t = Integer.parseInt(st.nextToken());

		int[][] map = new int[r][c];
		int[][] copymap = new int[r][c];

		for (int i = 0; i < r; i++) {
			st = new StringTokenizer(br.readLine(), " ");
			for (int j = 0; j < c; j++) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		} // end of input

		int mx1 = 0, mx2 = 0;
		for (int i = 0; i < r; i++) {
			if (map[i][0] == -1) { 
				mx1 = i;
				mx2 = i + 1;
				break;
			}
		} // 공청기 위치

		int[] dx = { 1, 0, -1, 0 };
		int[] dy = { 0, 1, 0, -1 };

		while (t-- > 0) {
			for (int i = 0; i < r; i++) {
				copymap[i] = map[i].clone();
			} // 배열 복사

			for (int i = 0; i < r; i++) {
				for (int j = 0; j < c; j++) {
					if (copymap[i][j] > 0) {
						int next = copymap[i][j] / 5; // 다음 전파될 양
						if (next == 0)
							continue;

						for (int dir = 0; dir < dx.length; dir++) {
							int nx = i + dx[dir];
							int ny = j + dy[dir];

							if (nx < 0 || nx >= r || ny < 0 || ny >= c)
								continue;

							if (map[nx][ny] != -1) { // 공기청정기가 아니라면
								map[nx][ny] += next; // 먼지 확산
								map[i][j] -= next; // 남은 미세먼지 양
							}
						}
					}
				}
			}

			// 공청기 돌기(위)
			for (int i = mx1 - 2; i >= 0; i--)
				map[i + 1][0] = map[i][0]; // ↓

			for (int i = 0; i < c - 1; i++) { // 왼쪽 방향
				map[0][i] = map[0][i + 1];
			}
			for (int i = 0; i < mx1; i++) { // 위 방향
				map[i][c - 1] = map[i + 1][c - 1];
			}
			for (int i = c - 1; i > 0; i--) { // 오른쪽 방향
				map[mx1][i] = map[mx1][i - 1];
			}
			map[mx1][1] = 0; // 공청기에서 나온 바람은 미세먼지가 없다

			// 공청기 돌기(아래)
			for (int i = mx2 + 1; i < r - 1; i++) { // 위 방향
				map[i][0] = map[i + 1][0];
			}
			for (int i = 0; i < c - 1; i++) { // 왼쪽 방향
				map[r - 1][i] = map[r - 1][i + 1];
			}
			for (int i = r - 1; i > mx2; i--) { // 아래 방향
				map[i][c - 1] = map[i - 1][c - 1];
			}
			for (int i = c - 1; i > 0; i--) { // 오른쪽 방향
				map[mx2][i] = map[mx2][i - 1];
			}
			map[mx2][1] = 0; // 공청기에서 나온 바람은 미세먼지가 없다
		} // after t seconds

		int total = 2;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				total += map[i][j];
			}
		}
		System.out.println(total);
	}
}
