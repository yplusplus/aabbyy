import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	static final int N = 1 << 7;
	static BigInteger[] fac = new BigInteger[N];
	static final BigInteger b1 = BigInteger.ONE;
	static final BigInteger b0 = BigInteger.ZERO;
	static final BigInteger b10 = BigInteger.TEN;

	static void pre() {
		fac[0] = b1;
		for (int i = 1; i < N; ++i) {
			fac[i] = fac[i - 1].multiply(BigInteger.valueOf(i));
		}
	}

	public static void main(String[] args) {
		pre();
		BigInteger[] f = new BigInteger[N];
		Scanner in = new Scanner(System.in);
		while (in.hasNext()) {
			int n = in.nextInt();
			for (int i = 1; i <= n; ++i) {
				f[i] = b0;
				for (int j = i; j < n; ++j) {
					BigInteger temp = fac[j - 1].divide(fac[i - 1].multiply(fac[j - i])).multiply(fac[i]);
					BigInteger sum = b0;
					for (int k = 0; k <= j - i; ++k) {
						sum = sum.add(fac[j - i].multiply(fac[n - k - i - 1]).divide(fac[j - i - k]));
					}
					f[i] = f[i].add(sum.multiply(temp));
				}
			}
			int mk = 1;
			for (int i = 1; i <= n; ++i) {
				if (f[mk].compareTo(f[i]) < 0) {
					mk = i;
				}
			}
			System.out.println(mk);
		}
	}
}
