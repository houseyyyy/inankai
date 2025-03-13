import java.util.Scanner;
import java.util.Arrays;
import java.util.Random;
class ThreeDLottery{
    private int[] winNumber;
    public int[] bonus;
    ThreeDLottery(int[] winNumber){
        this.winNumber=winNumber;
    }
    
    public int[] getWinNumber() {
        int[] WinNumber = Arrays.copyOf(winNumber, winNumber.length);
        return WinNumber;
    }
    int getWins(int[] userNumber){
        return 0;
    }
    public boolean isAvailable(String userNum,int userloop){
        if(userNum.length() != userloop)return false;
        for(int i = 0;i < userloop;i++)
        {
            if(userNum.charAt(i) < '0' || userNum.charAt(i) > '9')return false;
        }
        return true;
    }
}

class SingleMode extends ThreeDLottery{
SingleMode(int[] winNumber){
    super(winNumber);
    bonus = new int[]{1040};
}
int getWins(int[] userNumber){
    int[] winNumber = super.getWinNumber();
    for(int i = 0;i < 3;i++)
    {
        if(userNumber[i] != winNumber[i])return 0;
    }
    return bonus[0];
}
}
class GroupMode extends ThreeDLottery{
    GroupMode(int[] winNumber){
        super(winNumber);
        bonus = new int[]{346,173};
    }
    int getWins(int[] userNumber){
        int[] winNumber = super.getWinNumber();
        boolean group3 = false;
        if(userNumber[0] == userNumber[1] || userNumber[0] == userNumber[2] || userNumber[1] == userNumber[2])group3 = true;
        Arrays.sort(userNumber);Arrays.sort(winNumber);
        for(int i = 0;i < 3;i++)
        {
            if(userNumber[i] != winNumber[i])return 0;
        }
        return group3 == true ? bonus[0]:bonus[1];
    }
}
class OnedMode extends ThreeDLottery{
    OnedMode(int[] winNumber){
        super(winNumber);
        bonus = new int[]{10};
    }
    int getWins(int[] userNumber){
        int[] winNumber = super.getWinNumber();
        for(int i = 0;i < 3;i++)
        {
            if(userNumber[i] != ('*' - '0') && userNumber[i] == winNumber[i])return bonus[0];
        }
        return 0;
    }
    public boolean isAvailable(String userNum,int userloop){
        if(userNum.length() != userloop)return false;
        int starNum = 0;
        for(int i = 0;i < userloop;i++)
        {
            if(userNum.charAt(i) == '*')starNum ++;
            else
            {
                if(userNum.charAt(i) < '0' || userNum.charAt(i) > '9')return false;
            }
        }
        if(starNum != 2)return false;
        return true;
    }
}
class Guess1dMode extends ThreeDLottery{
    Guess1dMode(int[] winNumber){
        super(winNumber);
        bonus = new int[]{2,12,230};
    }
    int getWins(int[] userNumber){
        int[] winNumber = super.getWinNumber();
        int sameNumber = -1;
        for(int i = 0;i < 3;i++)
        {
            if(userNumber[0] == winNumber[i])sameNumber ++;
        }
        return sameNumber == -1 ? 0 : bonus[sameNumber];
    }
}
class TowdMode extends ThreeDLottery{
    TowdMode(int[] winNumber){
        super(winNumber);
        bonus = new int[]{104};
    }
    int getWins(int[] userNumber){
        int[] winNumber = super.getWinNumber();
        int sameNumber = 0;
        for(int i = 0;i < 3;i++)
        {
            if(userNumber[i] != ('*' - '0') && userNumber[i] == winNumber[i])sameNumber ++;
        }
        if(sameNumber == 2)return bonus[0];
        else return 0;
    }
    public boolean isAvailable(String userNum,int userloop){
        if(userNum.length() != userloop)return false;
        int starNum = 0;
        for(int i = 0;i < userloop;i++)
        {
            if(userNum.charAt(i) == '*')starNum ++;
            else
            {
                if(userNum.charAt(i) < '0' || userNum.charAt(i) > '9')return false;
            }
        }
        if(starNum != 1)return false;
        return true;
    }
}
class Guess2dMode extends ThreeDLottery{
    Guess2dMode(int[] winNumber){
        super(winNumber);
        bonus = new int[]{37,19};
    }
    int getWins(int[] userNumber){
        int[] winNumber = super.getWinNumber();
        boolean isSameNum = userNumber[0] == userNumber[1];
        int sameNumber = 0;
        for(int i = 0;i < (isSameNum ? 1:2);i++)
        {
            for(int j = 0;j < 3;j++)
            {
                if(winNumber[j] == userNumber[i])
                {
                    sameNumber++;
                    break;
                }
            }
        }
        if(sameNumber == 1 && isSameNum)return bonus[0];
        else if(sameNumber == 2 && !isSameNum)return bonus[1];
        else return 0;
    }
}
class GeneralMode extends ThreeDLottery{
    GeneralMode(int[] winNumber){
        super(winNumber);
        bonus = new int[]{470,21};
    }
    int getWins(int[] userNumber){
        int[] winNumber = super.getWinNumber();
        int sameNumber = 0;
        for(int i = 0;i < 3;i++)
        {
            if(userNumber[i] == winNumber[i])sameNumber++;
        }
        if(sameNumber == 3)return bonus[0];
        else if(sameNumber == 2)return bonus[1];
        else return 0;
    }
}
class SumMode extends ThreeDLottery{
    SumMode(int[] winNumber){
        super(winNumber);
        bonus = new int[]{1040,345,172,104,69,49,37,29,23,19,16,15,15,14};
    }
    int getWins(int[] userNumber){
        int[] winNumber = super.getWinNumber();
        int winSum = 0,userSum = userNumber[0];
        for(int i:winNumber)winSum += i;
        if(userSum == winSum)
        {
            return winSum > 13 ? bonus[27-winSum]:bonus[winSum];
        }
        return 0;
    }
    public boolean isAvailable(String userNum,int userloop){
        for(int i = 0;i < userNum.length();i++)
        {
            if(userNum.charAt(i) < '0' || userNum.charAt(i) > '9')return false;
        }
        int user = Integer.parseInt(userNum);
        if(user < 0 || user > 27)return false;
        return true;
    }
}
class PackageMode extends ThreeDLottery{
    PackageMode(int[] winNumber){
        super(winNumber);
        bonus = new int[]{693,173,606,86};
    }
    int getWins(int[] userNumber){
        int[] winNumber = super.getWinNumber();
        boolean isSameNumInUser = false;
        if(userNumber[0] == userNumber[1] || userNumber[0] == userNumber[2] || userNumber[1] == userNumber[2])isSameNumInUser = true;
        boolean isMapSame = true;
        for(int i = 0;i < 3;i++)
        {
            if(userNumber[i] != winNumber[i])isMapSame = false;
        }
        if(isSameNumInUser && isMapSame)return bonus[0];
        else if(!isSameNumInUser && isMapSame)return bonus[2];
        Arrays.sort(userNumber);Arrays.sort(winNumber);
        isMapSame = true;
        for(int i = 0;i < 3;i++)
        {
            if(userNumber[i] != winNumber[i])isMapSame = false;
        }
        if(isSameNumInUser && isMapSame)return bonus[1];
        else if(!isSameNumInUser && isMapSame)return bonus[3];
        else return 0;
    }
}
class GuessSizeMode extends ThreeDLottery{
    GuessSizeMode(int[] winNumber){
        super(winNumber);
        bonus = new int[]{6};
    }
    int getWins(int[] userNumber){
        int[] winNumber = super.getWinNumber();
        int winSum = 0,userSum = 0;
        for(int i:userNumber)userSum += i;
        for(int i:winNumber)winSum += i;
        if((winSum >= 19 && winSum <= 27) && (userSum >= 19 && userSum <= 27))return bonus[0];
        if((winSum >= 0 && winSum <= 8) && (userSum >= 0 && userSum <= 8))return bonus[0];
        return 0;
    }
}
class GuessThreeSameMode extends ThreeDLottery{
    GuessThreeSameMode(int[] winNumber){
        super(winNumber);
        bonus = new int[]{104};
    }
    int getWins(int[] userNumber){
        int[] winNumber = super.getWinNumber();
        boolean isSameNumInWin = false;
        if(winNumber[0] == winNumber[1] && winNumber[0] == winNumber[2])isSameNumInWin = true;
        if(isSameNumInWin)return bonus[0];
        else return 0;
    }
}
class TractorMode extends ThreeDLottery{
    TractorMode(int[] winNumber){
        super(winNumber);
        bonus = new int[]{65};
    }
    int getWins(int[] userNumber){
        int[] winNumber = super.getWinNumber();
        if(winNumber[1] == 0 || winNumber[1] == 9)return 0;
        boolean isTractor = false;
        //Arrays.sort(winNumber);
        int sub1 = winNumber[1] - winNumber[0],sub2 = winNumber[2] - winNumber[1];
        if((sub1 == sub2 && sub1 == 1) || (sub1 == sub2 && sub1 == -1))return bonus[0];
        return 0;
    }
}
class GuessPartiyMode extends ThreeDLottery{
    GuessPartiyMode(int[] winNumber){
        super(winNumber);
        bonus = new int[]{8};
    }
    int getWins(int[] userNumber){
        int[] winNumber = super.getWinNumber();
        boolean isUserOdd = (userNumber[0] & 1) == 1;
        boolean isWinOdd = true,isWinEven = true;
        for(int i = 0;i < 3;i++)
        {
            if((winNumber[i] & 1) == 0)isWinOdd = false;
            if((winNumber[i] & 1) == 1)isWinEven = false;
        }
        if(isUserOdd && isWinOdd)return bonus[0];
        else if(!isUserOdd && isWinEven)return bonus[0];
        else return 0;
    }
}
public class Main {

    public static void main(String [] arg){
        LotteryTestModule.runTests();
    }
}

class LotteryTestModule {
    public static void runTests() {
        Scanner cin = new Scanner(System.in);
        Random random = new Random();
        String temp;
        int[] winNumber = new int[3];
        System.out.println("投注方式有如下几种:");
        System.out.println("single group oned guess1d towd guess2d general sum package tractor guessSize guessThreeSame guessParity");
        System.out.println("若想退出,请输入quitgame\n");
        while (true) {
            System.out.println("请输入投注方式");
            for(int i = 0;i < 3;i++)
            {
                winNumber[i] = random.nextInt(10); // [0,9]
            }
            String modeName;
            modeName = cin.next();
            ThreeDLottery gambler = null;
            int[] userNumber = new int[3];

            int userloop = 3;
            switch (modeName) {
                case "single":
                    gambler = new SingleMode(winNumber);
                    break;
                case "group":
                    gambler = new GroupMode(winNumber);
                    break;
                case "oned":
                    gambler = new OnedMode(winNumber);
                    break;
                case "guess1d":
                    gambler = new Guess1dMode(winNumber);
                    userloop = 1;
                    break;
                case "towd":
                    gambler = new TowdMode(winNumber);
                    break;
                case "guess2d":
                    gambler = new Guess2dMode(winNumber);
                    userloop = 2;
                    break;
                case "general":
                    gambler = new GeneralMode(winNumber);
                    break;
                case "sum":
                    gambler = new SumMode(winNumber);
                    userloop = -1;
                    break;
                case "package":
                    gambler = new PackageMode(winNumber);
                    break;
                case "tractor":
                    gambler = new TractorMode(winNumber);
                    userloop = 0;
                    break;
                case "guessSize":
                    gambler = new GuessSizeMode(winNumber);
                    break;
                case "guessThreeSame":
                    gambler = new GuessThreeSameMode(winNumber);
                    userloop = 0;
                    break;
                case "guessParity":
                    gambler = new GuessPartiyMode(winNumber);
                    break;
                case "quitgame":
                    System.out.println("成功退出");
                    return;
                default:
                    System.out.println("您输入的投注方式不存在，请重新输入");
                    continue;
            }

            System.out.print("中奖号为：");
            for(int i : winNumber)System.out.print(String.format("%d ",i));
            System.out.println();

            if (userloop != 0) {
                if(modeName.intern() == "oned")System.out.println("请输入确定位置的一个数字，其他位输入*，例如，如果确定个位数为2，请输入**2");
                else if(modeName.intern() == "guess1d")System.out.println("请输入0-9之间的整数");
                else if(modeName.intern() == "towd")System.out.println("请输入确定位置的两个数字，其他位输入*，例如确定百位为1和个位为2，请输入*12");
                else if(modeName.intern() == "guess2d")System.out.println("请输入00-99之间的整数");
                else if(modeName.intern() == "sum")System.out.println("请输入0-27之间的整数");
                else System.out.println("请输入000-999之间的整数");
                while(true)
                {
                    temp = cin.next();
                    if(temp.intern() == "quitgame")
                    {
                        System.out.println("成功退出");
                        return;
                    }
                    if(gambler.isAvailable(temp,userloop) == false)
                    {
                        System.out.println("请输入正确的投注内容");
                    }
                    else break;
                }
                if (userloop == -1) {
                    userNumber[0] = Integer.parseInt(temp);
                } else {
                    for (int i = 0; i < userloop; i++) {
                        userNumber[i] = temp.charAt(i) - '0';
                    }
                }

            }
            int money = gambler.getWins(userNumber);
            System.out.println(String.format("您获得的奖金为 %d 元\n",money));

        }
    }
}