import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.StringTokenizer;

public class Main_15961 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		int n = Integer.parseInt(st.nextToken()); // 접시의 수
		int m = Integer.parseInt(st.nextToken()); // 초밥의 가짓수
		int k = Integer.parseInt(st.nextToken()); // 연속해서 먹는 접시 수
		int c = Integer.parseInt(st.nextToken()); // 쿠폰으로 주는 초밥
		int ans = 0; // 정답

		int[] sushi = new int[n]; // 회전초밥 벨트

		for (int i = 0; i < n; i++) {
			sushi[i] = Integer.parseInt(br.readLine());
		} // end of input

		int[] selected = new int[m + 1]; // 지금까지 먹은 초밥 개수

		// 처음부터 k개까지 연속으로 먹음
		selected[sushi[0]] = 1;
		int cnt = 1;
		int end = 0;
		
		for (int next = 1, tmp = 1; tmp < k; next++, tmp++) {
			if (next == n) next = 0; // 다시 처음으로 돌아감
			if (selected[sushi[next]]++ == 0)
				cnt++;
			end = next; 
		}
		
		if(selected[c]++ == 0) cnt++;		
		ans = cnt;

		for (int i = 1; i < n; i++) {
			if(--selected[sushi[i-1]]==0) cnt--;
			if(++end == n) end= 0;

			if(selected[sushi[end]]++ == 0) cnt++;
			if(cnt > ans) ans = cnt;
		}

		System.out.println(ans);

	} // end of main
}
