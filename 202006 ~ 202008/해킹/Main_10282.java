import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main_10282 {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		
		int tc = Integer.parseInt(br.readLine());
		
		for (int test = 0; test < tc; test++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int N = Integer.parseInt(st.nextToken()); // 컴퓨터 수 
			int D = Integer.parseInt(st.nextToken()); // 의존성 수 
			int C = Integer.parseInt(st.nextToken()); // 시작 컴퓨터
			
			ArrayList<Edge>[] weights = new ArrayList[N+1]; // 인접리스트
			for (int i = 1; i <= N; i++) {
				weights[i] = new ArrayList<Edge>();
			}
			
			for (int i = 0; i < D; i++) {
				st = new StringTokenizer(br.readLine());
				
				int v = Integer.parseInt(st.nextToken()); // 끝
				int u = Integer.parseInt(st.nextToken()); // 시작 
				int w = Integer.parseInt(st.nextToken()); // 가중치
				weights[u].add(new Edge(v,w));
			}
			
			int[] dist = new int[N+1]; // 걸리는 시간
			Arrays.fill(dist, Integer.MAX_VALUE); // 초기화
			dist[C] = 0; // 시작 컴퓨터는 해킹 당하고 시작
			
			PriorityQueue<Edge> pq = new PriorityQueue<Edge>();
			pq.add(new Edge(C, 0));
			
			boolean[] visited = new boolean[N+1]; // 방문 체크
	
			Edge edge = null;
			
			while(!pq.isEmpty()) {
				edge = pq.poll();
				if(visited[edge.v]) continue; // 방문했던 정점이라면? 
				
				visited[edge.v] = true; // 방문 체크
				
				for (int i = 0; i < weights[edge.v].size(); i++) {
					Edge e = weights[edge.v].get(i); // 현재 정점과 연결되어 있는 경유지 정점
					if(!visited[e.v] && dist[e.v] > dist[edge.v] + e.w) {
						dist[e.v] = dist[edge.v] + e.w;
						pq.add(new Edge(e.v , dist[e.v]));
					}
				}
            }
            
			int cnt = 0;
			int max = -1;
			for (int i = 1; i <= N; i++) {
				if(visited[i]) { // 해킹 당한 컴퓨터라면
					cnt++;
					if(max < dist[i]) max = dist[i]; // 마지막 컴퓨터 감염 시간 체크
				}
			}
			sb.append(cnt).append(" ").append(max).append("\n");
		} // end of test case
		System.out.println(sb);
    }
    
    static class Edge implements Comparable<Edge> {
		int v, w;

		public Edge(int v, int w) {
			this.v = v;
			this.w = w;
		}

		@Override
		public int compareTo(Edge o) {
			return this.w - o.w;
		}
	}
}
