import java.io.File;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		try {
			Scanner in = new Scanner(new File("discuss.in"));
			try (PrintWriter out = new PrintWriter(new File("discuss.out"))) {
				String n;
				while (in.hasNext()) {
					n = in.next();
					BigInteger answer = new BigInteger(n);
					BigInteger last = answer;
					for (int i = 2; i <= 200; ++i) {
						BigInteger temp = find(new BigInteger(n), i, last);
						if (temp.compareTo(BigInteger.ZERO) > 0) {
							if (answer.compareTo(temp) > 0) answer = temp;
						}
						last = answer;
					}
					out.println(answer.toString());
					System.out.println(answer.toString());
				}
			}
		} catch (Exception e) {
			System.out.println("e.toString()");
		}
	}

	static final BigInteger TWO = BigInteger.valueOf(2);
	private static BigInteger find(BigInteger target, int i, BigInteger last) {
		BigInteger L = BigInteger.valueOf(i * 2);
		BigInteger R = last;
		BigInteger mark = BigInteger.ZERO;
		while (L.compareTo(R) <= 0) {
			BigInteger M = L.add(R).divide(TWO);
			BigInteger result = combination(M, i, target);
			int compare = result.compareTo(target);
			if (compare >= 0) {
				R = M.subtract(BigInteger.ONE);
				if (compare == 0) {
					mark = M;
				}
			} else {
				L = M.add(BigInteger.ONE);
			}
		}
		return mark;
	}

	private static BigInteger combination(BigInteger M, int n, BigInteger END) {
		BigInteger result = BigInteger.ONE;
		for (int i = 0; i < n; ++i) {
			if (result.compareTo(END) > 0) return result;
			result = result.multiply(M.subtract(BigInteger.valueOf(i)));
			result = result.divide(BigInteger.valueOf(i).add(BigInteger.ONE));
		}
		return result;
	}
}
