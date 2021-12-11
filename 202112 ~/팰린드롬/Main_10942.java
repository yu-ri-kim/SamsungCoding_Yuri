import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main_10942 {
    /**
     * 팰린드롬?
     * N : 수열의 크기 (각 숫자는 100000 보다 작은 수)
     * S, E : 질문 시작, 종료 index
     * M : 질문 개수
     *
     * @param args
     */
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();

        int n = Integer.parseInt(br.readLine());
        int[] numbers = new int[n + 1];

        StringTokenizer sts = new StringTokenizer(br.readLine());

        for (int i = 1; i <= n; i++) {
            numbers[i] = Integer.parseInt(sts.nextToken());
        } // end of input

        boolean[][] isPalindrome = new boolean[n + 1][n + 1];

        for (int i = 1; i <= n; i++) {
            isPalindrome[i][i] = true;
        }

        for (int i = 1; i < n; i++) {
            isPalindrome[i][i + 1] = (numbers[i] == numbers[i + 1]);
        }

        for (int range = 3; range <= n; range++) {
            for (int i = 1; i <= n - range + 1; i++) {
                if (numbers[i] == numbers[i + range - 1]) {
                    isPalindrome[i][i + range - 1] = isPalindrome[i + 1][i + range - 2];
                }
            }
        }

        int m = Integer.parseInt(br.readLine());

        for (int i = 0; i < m; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int start = Integer.parseInt(st.nextToken());
            int end = Integer.parseInt(st.nextToken());

            sb.append(isPalindrome[start][end] ? "1\n" : "0\n");
        }

        System.out.println(sb.toString());

    } // end of main
}
