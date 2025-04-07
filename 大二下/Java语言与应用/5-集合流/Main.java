import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.*;

class Main {
    public static void main(String args[]) {
        Scanner scan = new Scanner(System.in);
        String midFix = scan.nextLine();

        Fix myFix = new Fix(midFix);
        String postFixResult = myFix.toPostFix();

        if (postFixResult.startsWith("ERROR")) {
            System.out.println(postFixResult);
        } else {
            BigDecimal ans = myFix.result();
            if (ans == null) {
                System.out.println("计算错误");
            } else {
                // 格式化输出
                String output;
                if (myFix.allIntegers && isInteger(ans)) {
                    output = ans.toBigInteger().toString();
                } else {
                    output = ans.setScale(10, RoundingMode.HALF_UP)
                            .stripTrailingZeros()
                            .toPlainString();
                }
                System.out.println(output);
            }
        }
        scan.close();
    }

    private static boolean isInteger(BigDecimal num) {
        return num.scale() <= 0 || num.stripTrailingZeros().scale() <= 0;
    }
}

class Fix {
    public boolean allIntegers = true;
    private String fix;
    private String postFix;

    Fix(String fix) {
        this.fix = fix.replaceAll("=", "").trim();
    }

    boolean isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
    }

    int priority(String op) {
        if (op.equals("u-")) return 4;
        else if (op.equals("*") || op.equals("/") || op.equals("%")) return 3;
        else if (op.equals("+") || op.equals("-")) return 1;
        else return 0;
    }

    public String toPostFix() {
        StringBuilder postFix = new StringBuilder();
        StringBuilder tmpString = new StringBuilder();
        Deque<String> opStack = new ArrayDeque<>();
        int size = fix.length();

        for (int i = 0; i < size; i++) {
            char c = fix.charAt(i);
            if (Character.isDigit(c) || c == '.' || (c == '-' && (i == 0 || fix.charAt(i - 1) == '(' || isOperator(fix.charAt(i - 1))))) {
                // 处理数字和一元负号
                tmpString.append(c);
            } else if (c == ' ') {
                continue; // 忽略空格
            } else {
                // 处理已累积的数字
                if (tmpString.length() > 0) {
                    String num = tmpString.toString();
                    if (!num.matches("^-?\\d+\\.?\\d*$|^-?\\.\\d+$")) {
                        return "ERROR IN INFIX NOTATION";
                    }
                    if (num.contains(".") && num.length() > 1) {
                        allIntegers = false;
                    }
                    postFix.append(num).append(" ");
                    tmpString.setLength(0);
                }

                if (c == '(') {
                    opStack.push("(");
                } else if (c == ')') {
                    while (!opStack.isEmpty() && !opStack.peek().equals("(")) {
                        postFix.append(opStack.pop()).append(" ");
                    }
                    if (opStack.isEmpty()) {
                        return "ERROR IN INFIX NOTATION";
                    }
                    opStack.pop();
                } else if (isOperator(c)) {
                    // 判断是否为一元负号
                    boolean isUnary = (c == '-') && (i == 0 || fix.charAt(i - 1) == '(' || isOperator(fix.charAt(i - 1)));
                    String currentOp = isUnary ? "u-" : String.valueOf(c);

                    while (!opStack.isEmpty() && priority(currentOp) <= priority(opStack.peek())) {
                        postFix.append(opStack.pop()).append(" ");
                    }
                    opStack.push(currentOp);
                } else {
                    return "ERROR IN INFIX NOTATION";
                }
            }
        }

        // 处理剩余数字
        if (tmpString.length() > 0) {
            String num = tmpString.toString();
            if (!num.matches("^-?\\d+\\.?\\d*$|^-?\\.\\d+$")) {
                return "ERROR IN INFIX NOTATION";
            }
            if (num.contains(".")) {
                allIntegers = false;
            }
            postFix.append(num).append(" ");
        }

        // 处理剩余运算符
        while (!opStack.isEmpty()) {
            if (opStack.peek().equals("(")) {
                return "ERROR IN INFIX NOTATION";
            }
            postFix.append(opStack.pop()).append(" ");
        }
        this.postFix = postFix.toString().trim();
        return this.postFix;
    }

    public BigDecimal result() {
        Deque<BigDecimal> stack = new ArrayDeque<>();
        StringTokenizer tokenizer = new StringTokenizer(postFix);

        while (tokenizer.hasMoreTokens()) {
            String token = tokenizer.nextToken();
            if (token.equals("u-")) {
                if (stack.isEmpty()) return null;
                stack.push(stack.pop().negate());
            } else if (isOperator(token.charAt(0)) && token.length() == 1) {
                if (stack.size() < 2) return null;
                BigDecimal b = stack.pop();
                BigDecimal a = stack.pop();
                switch (token.charAt(0)) {
                    case '+':
                        stack.push(a.add(b));
                        break;
                    case '-':
                        stack.push(a.subtract(b));
                        break;
                    case '*':
                        stack.push(a.multiply(b));
                        break;
                    case '/':
                        if (b.compareTo(BigDecimal.ZERO) == 0) return null;
                        // 整数除法处理
                        if (allIntegers && isInteger(a) && isInteger(b)) {
                            stack.push(a.divide(b, 0, RoundingMode.DOWN));
                        } else {
                            stack.push(a.divide(b, 10, RoundingMode.HALF_UP));
                        }
                        break;
                    case '%':
                        if (b.compareTo(BigDecimal.ZERO) == 0) return null;
                        stack.push(a.remainder(b));
                        break;
                }
            } else {
                try {
                    stack.push(new BigDecimal(token));
                } catch (NumberFormatException e) {
                    return null;
                }
            }
        }
        return stack.isEmpty() ? null : stack.pop();
    }

    private boolean isInteger(BigDecimal num) {
        return num.scale() <= 0 || num.stripTrailingZeros().scale() <= 0;
    }
}    