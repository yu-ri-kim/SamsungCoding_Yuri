import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main_17472 {
	private static int n, m; 
	private static int[][] map;
	private static boolean[][] visited;
	
	private static int iCnt; // 섬의 개수
	private static ArrayList<HashSet<Pair>> hs; // 섬들의 좌표
	
	private static int[] parents; // MST

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		map = new int[n][m];

		for (int i = 0; i < n; i++) {
			String s = br.readLine();
			for (int j = 0, index = 0; j < m; j++, index += 2) {
				map[i][j] = s.charAt(index) - '0';
			}
		} // end of input

		visited = new boolean[n][m];
		hs = new ArrayList<HashSet<Pair>>();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == 1 && !visited[i][j]) {
					hs.add(new HashSet<Pair>());
					dfs(i, j);
					iCnt++;
				}
			}
		} // 섬좌표 구하기

		PriorityQueue<Pair> pq = new PriorityQueue<Pair>();

		for (int i = 0; i < iCnt; i++) {
			// 섬의 모든 좌표에서 시작
			for (Pair p : hs.get(i)) {
				for (int dir = 0; dir < 4; dir++) {
					Pair result = go(p.x, p.y, dir); // 길이, 도착 섬

					// 다리의 길이가 2보다 작거나 같은섬끼리 연결한 경우
					if (result.x < 2 || result.y == i) {
						continue;
					}

					// i번째 섬에서 도착 섬으로, x의 길이만큼의 다리 생성
					pq.add(new Pair(i, result.y, result.x));
				}
			}
		}

		parents = new int[iCnt];
		for (int i = 0; i < iCnt; i++) {
			parents[i] = i;
		} // make set

		int cnt = 0, ans = 0;
		
		while (cnt < iCnt - 1) {
			if(pq.size() == 0) { // 모든 섬을 연결하지 못했다면
				System.out.println("-1");
				return;
			}
			
			// 시작, 도착, 길이
			Pair p = pq.poll();
			int p1 = findSet(p.x);
			int p2 = findSet(p.y);

			if (p1 == p2)
				continue;
			
			parents[p1] = parents[p2];
			cnt++;
			ans += p.w;
		}
		
		System.out.println(ans);

	} // end of main

	private static int findSet(int x) {
		if (parents[x] != x) {
			parents[x] = findSet(parents[x]);
		}
		return parents[x];
	}

	private static Pair go(int x, int y, int dir) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		int length = 0;

		while (true) {
			if (nx < 0 || nx >= n || ny < 0 || ny >= m)
				break;

			if (map[nx][ny] == 1) { // 다른 섬에 도착했다면
				for (int i = 0; i < iCnt; i++) {
					if (hs.get(i).contains(new Pair(nx, ny))) {
						return new Pair(length, i);
					}
				}
			}

			length++;
			
			// 다음 칸으로 이동
			nx += dx[dir];
			ny += dy[dir];
		}

		return new Pair(0, 0); // 다리 생성 실패
	}

	static int[] dx = { 1, 0, -1, 0 };
	static int[] dy = { 0, 1, 0, -1 };

	private static void dfs(int i, int j) {
		hs.get(iCnt).add(new Pair(i, j));
		visited[i][j] = true;

		for (int dir = 0; dir < dx.length; dir++) {
			int nx = dx[dir] + i;
			int ny = dy[dir] + j;

			if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
				continue;
			}

			if (map[nx][ny] == 1 && !visited[nx][ny])
				dfs(nx, ny);
		}
	}
	
	static class Pair implements Comparable<Pair> {
		int x, y, w;

		public Pair(int x, int y) {
			this.x = x;
			this.y = y;
		}

		public Pair(int x, int y, int w) {
			this.x = x;
			this.y = y;
			this.w = w;
		}
		
		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + x;
			result = prime * result + y;
			return result;
		}

		@Override
		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (getClass() != obj.getClass())
				return false;
			Pair other = (Pair) obj;
			if (x != other.x)
				return false;
			if (y != other.y)
				return false;
			return true;
		}

		@Override
		public int compareTo(Pair o) {
			return this.w - o.w;
		}
	}

}
