
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Candidate {
	public static String JOLLY = "Jolly";
	public static String NOT_JOLLY = "Not jolly";

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		StringTokenizer tokenizer;
		int numberOfItems;
		while (scanner.hasNextLine()) {
			tokenizer = new StringTokenizer(scanner.nextLine());
			numberOfItems = Integer.parseInt(tokenizer.nextToken());
			int[] numbers = new int[numberOfItems];
			for (int i = 0; i < numberOfItems; i++) {
				numbers[i] = Integer.parseInt(tokenizer.nextToken());
			}
			System.out.println(isJolly(numbers));
		}
		System.exit(0);
	}

	private static String isJolly(int[] numbers) {
		List results = new ArrayList();
		for (int i = 0; i < numbers.length - 1; i++) {
			int result = Math.abs(numbers[i] - numbers[i + 1]);
			if ((result == 0) || (result >= numbers.length)) {
				return NOT_JOLLY;
			}
			
			if (results.contains(result)) {
				return NOT_JOLLY;
			}
			results.add(result);
		}
		return JOLLY;
	}
}
