import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.FileHandler;
import java.util.logging.SimpleFormatter;
import java.util.logging.*;
import java.io.IOException;

class Main {
    //获取logger实例
    public static final Logger Exceptionlog = Logger.getLogger("Exception");
    public static final Logger calculatelog = Logger.getLogger("calculate");
    public static void main(String args[]) {
        FileHandler fileHandler1 = null;
        FileHandler fileHandler2 = null;
        try
        {
            //禁用继承，防止console
            Exceptionlog.setUseParentHandlers(false);
            calculatelog.setUseParentHandlers(false);
            Handler[] handlers = Exceptionlog.getHandlers();
            for (Handler handler : handlers) {
                Exceptionlog.removeHandler(handler);
            }
            fileHandler1 = new FileHandler("Exceptionlog.txt",true);
            fileHandler1.setFormatter(new SimpleFormatter());
            Exceptionlog.addHandler(fileHandler1);
            //日志记录级别
            Exceptionlog.setLevel(Level.ALL);
            fileHandler2 = new FileHandler("calculatelog.txt",true);
            fileHandler2.setFormatter(new SimpleFormatter());
            calculatelog.addHandler(fileHandler2);
            calculatelog.setLevel(Level.ALL);

        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        Scanner scan = new Scanner(System.in);
        String midFix = "";
        String temp = "";
        while(scan.hasNextLine()){
        	temp = scan.nextLine();
        	if(temp.charAt(temp.length() - 1) == '?')break;
        	midFix += temp;
        }
        String[] variables = midFix.split(";");
        Map<String,Object> varMap = new HashMap<>();
        //key : variable name ,value : type
        Map<String,String> typeMap = new HashMap<>();
        //分割变量和值
        for(String variable : variables)
        {
            if(variable.contains(" "))
            {
        	    String[] parts = variable.split(" ");
                if(parts[1].contains("="))
                {            
                    String[] varAndNumber = parts[1].split("=");
                    if(parts[0].equals("int"))
                    {
                        typeMap.put("int",varAndNumber[0]);
                        varMap.put(varAndNumber[0],Integer.parseInt(varAndNumber[1]));
                    }
                    else if(parts[0].equals("float"))
                    {
                        typeMap.put("float",varAndNumber[0]);
                        varMap.put(varAndNumber[0],Float.parseFloat(varAndNumber[1]));
                    }
                }
                else
                {
                    if(parts[0].equals("int"))
                    {
                        typeMap.put(parts[1],"int");
                    }
                    else if(parts[0].equals("float"))
                    {
                        typeMap.put(parts[1],"float");
                    }                
                }
            }
            else
            {
                String[] varAndNumber = variable.split("=");
                if(typeMap.get(varAndNumber[0]).equals("int"))
                {
                    varMap.put(varAndNumber[0],Integer.parseInt(varAndNumber[1]));
                }
                else if(typeMap.get(varAndNumber[0]).equals("float"))
                {
                    varMap.put(varAndNumber[0],Float.parseFloat(varAndNumber[1]));
                }

            }
        }
		midFix = "";
		//替换值，小数自动补0，float b = 11,替换后为 11.0
        try
        {
    		for(int i = 0;i < temp.length() - 2;i++)
    		{
    			if(varMap.get(String.valueOf(temp.charAt(i))) == null)
    			{
                    if(Character.isLetter(temp.charAt(i)))
                    {
                        if(typeMap.get(String.valueOf(temp.charAt(i))) != null)
                        {
                            throw new Exception ("wrong - variable unassigned");
                        }
                        else
                        {
                            throw new Exception ("wrong - variable undefined");
                        }
                    }
    				midFix += temp.charAt(i);
    				continue;
    			}
    			else
    			{
    				midFix += varMap.get(String.valueOf(temp.charAt(i)));
    			}
    		}
        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());
            Exceptionlog.info(e.getMessage());
            return;
        }
        Fix myFix = new Fix(midFix);
        //转为后缀表达式
        String postFixResult = myFix.toPostFix();
        String res = myFix.result();
        if(res.contains("."))System.out.println(String.format("%.2f",Float.parseFloat(res)));
        else System.out.println(res); 
        if(!res.contains("-"))calculatelog.info(res);   
        fileHandler1.close();
        fileHandler2.close();
        scan.close();
    }

}

class Fix {
    private String fix;

    Fix(String fix) {
        this.fix = fix.trim();
    }

    boolean isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
    }

    int opLevel(char op) {
        if (op == '*' || op == '/' || op == '%') return 3;
        else if (op == '+' || op == '-') return 2;
        else return 0;
    }

    public String toPostFix() {
        String temp = "";
        String postFix = "";
        Stack<Character> opStack = new Stack<>();

        for (int i = 0; i < fix.length(); i++) {
            if (fix.charAt(i) == ' ') continue;
            if (fix.charAt(i) >= '0' && fix.charAt(i) <= '9') {
                temp += fix.charAt(i);
            } else if (fix.charAt(i) == '.') {
                temp += fix.charAt(i);
            } 
            else 
            {
                if (fix.charAt(i) == '(') opStack.push('(');
                else if (opLevel(fix.charAt(i)) > 0) {
                    temp += " ";
                    if (!opStack.empty()) {
                        if (opLevel(fix.charAt(i)) > opLevel(opStack.peek())) {
                            opStack.push(fix.charAt(i));
                        } else {
                            while (!opStack.empty() && (opLevel(fix.charAt(i)) <= opLevel(opStack.peek()))) {
                                temp += opStack.pop();
                                temp += " ";
                            }
                            opStack.push(fix.charAt(i));
                        }
                    } else {
                        opStack.push(fix.charAt(i));
                    }
                } else if (fix.charAt(i) == ')') {
                    while (opStack.peek() != '(') {
                        temp += " ";
                        temp += opStack.pop();
                    }
                    opStack.pop();
                }
            }
        }
        while (!opStack.empty()) {
            temp += " ";
            temp += opStack.pop();
        }
       	fix = temp;
        return temp;
    }

    public String result() {
    	Stack<String> numStack = new Stack<>();
        String[] tokens = fix.split(" ");

        for (String token : tokens) {
            if (token.isEmpty()) continue; // 跳过空Token
            try{
                if(token.charAt(0) == '(')
                {
                     throw new Exception();
                }
            }
            catch(Exception e)
            {
                Main.Exceptionlog.info("wrong - error expression");
                return "wrong - error expression";
            }
            if (opLevel(token.charAt(0)) > 0) {
                String t1 = numStack.pop();
                String t2 = numStack.pop();
                Number x1 = t1.contains(".") ? Float.parseFloat(t1) : Integer.parseInt(t1);
                Number y1 = t2.contains(".") ? Float.parseFloat(t2) : Integer.parseInt(t2);
                if(t1.contains(".") || t2.contains("."))
                {
                	double x = x1.doubleValue();
                	double y = y1.doubleValue();
	                switch (token) {
	                    case "+":
	                        numStack.push(String.valueOf(y + x));
	                        break;
	                    case "-":
	                        numStack.push(String.valueOf(y - x));
	                        break;
	                    case "*":
	                        numStack.push(String.valueOf(y * x));
	                        break;
	                    case "/":
	                        numStack.push(String.valueOf(y / x));
	                        break;
	                    case "%":
	                        numStack.push(String.valueOf(y % x));
	                        break;
	                }
                }
                else
                {
					int x = x1.intValue();
                	int y = y1.intValue();
	                switch (token) {
	                    case "+":
	                        numStack.push(String.valueOf(y + x));
	                        break;
	                    case "-":
	                        numStack.push(String.valueOf(y - x));
	                        break;
	                    case "*":
	                        numStack.push(String.valueOf(y * x));
	                        break;
	                    case "/":
	                        numStack.push(String.valueOf(y / x));
	                        break;
	                    case "%":
	                        numStack.push(String.valueOf(y % x));
	                        break;
	                }
                }

            } 
            else 
            {
                numStack.push(token);
            }
        }
        return numStack.pop();
    }
}    