import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main_2805 {
	private static int[] arr;
	private static int n;
	private static int m;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(br.readLine());

        arr = new int[n]; // 나무 높이를 저장할 배열

		int start = 0, end = 0;
		
		for (int i = 0; i < n; i++) {
			arr[i] = Integer.parseInt(st.nextToken());
			end = Math.max(arr[i], end); // 가장 긴 나무의 높이를 구한다
		} // end of input

		int mid = 0;
		long sum = 0;
		int ans = 0;
		
		while(start <= end) {
			mid = (start+end) / 2;
			sum = 0;
			
			for (int i = 0; i < n; i++) {
				if(arr[i] >= mid) sum += (arr[i]- mid);
			} // 나무 자르기
			
			if(sum < m) {
				end = mid-1; // 높이를 더 낮게한다
			}
			else {
				ans = Math.max(ans, mid);
				start=mid+1; // 높이를 더 높게한다
			}
		}
		
		System.out.println(ans);
	}
}
