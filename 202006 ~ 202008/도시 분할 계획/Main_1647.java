import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.PriorityQueue;
import java.util.StringTokenizer;
import java.util.StringTokenizer;

public class Main_1647 {
	static class Edge implements Comparable<Edge>{
		int from;
		int to;
		int weight; // 유지비

		public Edge(int from, int to, int weight) {
			super();
			this.from = from;
			this.to = to;
			this.weight = weight;
		}

		@Override
		public int compareTo(Edge o) {
			return this.weight - o.weight;
		}
	}

	private static int[] parent;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(st.nextToken()); // vertex 
		int m = Integer.parseInt(st.nextToken()); // edge

		PriorityQueue<Edge> pq = new PriorityQueue<Edge>(); 
		parent = new int[n+1];
		
		for (int i = 0; i < n; i++) { // make set
			parent[i] = i;
		}
		
		for (int i = 0; i < m; i++) {
			st = new StringTokenizer(br.readLine());
			int from = Integer.parseInt(st.nextToken());
			int to = Integer.parseInt(st.nextToken());
			int weight = Integer.parseInt(st.nextToken());
			pq.add(new Edge(from,to,weight));
		}
		
		int cnt = 0;
		int sum = 0;
		
		while(cnt < n-2) { // 마을을 나누기 위해서 1개의 정점은 쓰지 않는다
			Edge cur = pq.poll();
			int p1 = find(cur.from);
			int p2 = find(cur.to);
			
			if(p1!=p2) { // 서로 다른 집합이라면
				parent[p1] = parent[p2]; // union 한다
				cnt++;
				sum+=cur.weight;
			}
		}
		System.out.println(sum);
	}

	private static int find(int v) {
		if(parent[v] != v) {
			parent[v] = find(parent[v]);
		}
		return parent[v];
	}
	
}
