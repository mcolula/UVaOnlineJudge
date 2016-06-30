import java.util.*;
import java.math.*;

public class Main {

  public static final int A =   10001;
  public static final int B =     101;
  
  public static BigInteger memo[][] = new BigInteger[A][B];
  public static int test[][] = new int[A][B];
  public static String  s;
  public static String  t;
  public static int T = 0;
  
  public static BigInteger count(int n, int m) {
    if (m == t.length())
      return BigInteger.ONE;
    if (n == s.length())
      return BigInteger.ZERO;
    if (test[n][m] == T)
      return memo[n][m];
    BigInteger ans = count(n + 1, m);
    if (s.charAt(n) == t.charAt(m))
      ans = ans.add(count(n + 1, m + 1));
    test[n][m] = T;
    return memo[n][m] = ans;
  }
  
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt(); in.nextLine();
    for (T = 1; T <= n; T++) {
      s = in.nextLine();
      t = in.nextLine();
      System.out.println(count(0, 0));
    }
  }

}
