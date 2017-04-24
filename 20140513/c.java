// 必须单次输入，因为最后l*n个数会没有的输入= =  P.S: 一个钟就这样没了。。。

import java.io.File;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {

    /**
     *
     */
    public static void run() {
        try {
            Scanner in = new Scanner(new File("casino.in"));
            try (PrintWriter out = new PrintWriter(new File("casino.out"))) {
                //while (in.hasNext()) {
                    int n, m, k, c, l;
                    n = in.nextInt();
                    m = in.nextInt();
                    k = in.nextInt();
                    c = in.nextInt();
                    l = in.nextInt();
                    String[] wheel = new String[n];
                    for (int i = 0; i < n; i++) {
                        wheel[i] = in.next();
                    }
                    String[] combination = new String[c];
                    int[] value = new int[c];
                    for (int i = 0; i < c; i++) {
                        combination[i] = in.next();
                        value[i] = in.nextInt();
                    }
                    System.out.println("akljfklasf");
                    int[][] line = new int[l][];
                    /*
                    for (int i = 0; i < l; i++) {
                        line[i] = new int[n];
                        for (int j = 0; j < n; j++) {
                            line[i][j] = in.nextInt();
                        }
                    }
                    */
                    System.out.println("Input Endes.");
                    Factor answer = new Factor(0, 1);
                    for (int i = 0; i < c; i++) {
                        Factor temp = new Factor(1, 1);
                        for (int j = 0; j < n; j++) {
                            char ch;
                            if ((ch = combination[i].charAt(j)) == '*') {
                                continue;
                            } else {
                                int cnt = 0;
                                for (int o = 0; o < m; o++) {
                                    if (wheel[j].charAt(o) == ch) {
                                        ++cnt;
                                    }
                                }
                                temp = temp.multiply(new Factor(cnt, m));
                            }
                        }
                        answer = answer.add(temp.multiply(new Factor(value[i], 1)));
                    }
                    System.out.println(answer.toString());
                    if (answer.compareTo(new Factor(1, 1)) > 0) {
                        out.println(answer.subtract(new Factor(1, 1)).toString());
                        out.println(1);
                        out.println(1);
                    } else {
                        out.println((new Factor(0, 1)).toString());
                        out.println(0);
                    }
                //}
            }
        } catch (Exception e) {
            System.out.println(e.toString());
            while (true) {}
        }

    }

    public static void main(String[] args) {
        Main.run();
    }
}

class Factor {

    private BigInteger x, y;

    public Factor() {
    }

    public Factor(int x, int y) {
        this.x = BigInteger.valueOf(x);
        this.y = BigInteger.valueOf(y);
        BigInteger g = this.x.gcd(this.y);
        this.x = this.x.divide(g);
        this.y = this.y.divide(g);
    }

    public Factor(BigInteger x, BigInteger y) {
        this.x = x;
        this.y = y;
        BigInteger g = this.x.gcd(this.y);
        this.x = this.x.divide(g);
        this.y = this.y.divide(g);
    }

    public Factor add(Factor a) {
        BigInteger nx = this.x.multiply(a.y).add(a.x.multiply(this.y));
        BigInteger ny = this.y.multiply(a.y);
        return new Factor(nx, ny);
    }

    public Factor subtract(Factor a) {
        BigInteger nx = this.x.multiply(a.y).subtract(a.x.multiply(this.y));
        BigInteger ny = this.y.multiply(a.y);
        return new Factor(nx, ny);
    }

    public Factor multiply(Factor a) {
        BigInteger nx = this.x.multiply(a.x);
        BigInteger ny = this.y.multiply(a.y);
        return new Factor(nx, ny);
    }

    public Factor divide(Factor a) {
        BigInteger nx = this.x.multiply(a.y);
        BigInteger ny = this.y.multiply(a.x);
        return new Factor(nx, ny);
    }
    
    public int compareTo(Factor a) {
        return this.x.multiply(a.y).compareTo(this.y.multiply(a.x));
    }

    @Override
    public String toString() {
        return x.toString() + "/" + y.toString();
    }
}
