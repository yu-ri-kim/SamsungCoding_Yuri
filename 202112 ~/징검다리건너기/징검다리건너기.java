public class 징검다리건너기 {
    /**
     * 징검다리건너기
     * 디딤돌의 숫자는 한 번 밟을 때마다 1씩 줄어든다.
     * 최대 몇 명까지 건널 수 있는지?
     * input : 징검다리 디딤돌 , 한 번에 건너뛸 수 있는 디딤돌의 최대 칸수
     */
    static class Solution {
        public static int solution(int[] stones, int k) {
            int answer = 0;
            int min = 1;
            int max = 200000000;

            while (min <= max) {
                int currentIdx = (min + max) / 2;
                int zeroCnt = 0;
                boolean isSuccessful = true;

                for (int stone : stones) {
                    if (stone - currentIdx < 0) { // currentIdx번째로 징검다리를 건널 때 디딤돌의 상태가 0이하라면
                        zeroCnt++; // 건너지 못하는 디딤돌이여서 cnt를 증기시킨다
                    } else { // 건널 수 있다면
                        zeroCnt = 0;
                    }
                    if (zeroCnt == k) { // 만약, 연속으로 k만큼 건너지 못하는 디딤돌일 때
                        max = currentIdx - 1; // 탐색 범위를 줄인다
                        isSuccessful = false;
                        break;
                    }
                }

                if (isSuccessful) { // currentIdx번째의 니니즈가 건넜다면
                    min = currentIdx + 1;
                    answer = currentIdx; // 현재 기준으로 최대 currentIdx명의 니니즈가 건널 수 있다.
                }
            }
            return answer;
        }
    }

    public static void main(String[] args) {
        int[] stones = {2, 4, 5, 3, 2, 1, 4, 2, 5, 1};
        int k = 3;

        System.out.println(Solution.solution(stones, k));
    }
}
