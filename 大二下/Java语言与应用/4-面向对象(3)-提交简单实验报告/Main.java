import java.util.*;
import java.net.*;
import java.io.*;

class NetworkMessage implements Serializable {
    private static final long serialVersionUID = 1L;
    static final int TYPE_ACTION = 1;
    static final int TYPE_STATE = 2;

    int messageType;
    String content;
    int currentBlood;

    public NetworkMessage(int type, String content, int blood) {
        this.messageType = type;
        this.content = content;
        this.currentBlood = blood;
    }
}

abstract class OnlineGame extends Game {
    protected Socket socket;
    protected ObjectInputStream ois;
    protected ObjectOutputStream oos;
    protected boolean isServer;

    public void startNetwork(boolean asServer) throws IOException {
        isServer = asServer;
        if (asServer) {
            ServerSocket server = new ServerSocket(12345);
            System.out.println("等待玩家连接...");
            socket = server.accept();
            oos = new ObjectOutputStream(socket.getOutputStream());
            System.out.println("输出流已创建");
            ois = new ObjectInputStream(socket.getInputStream());
            System.out.println("输入流已创建");
            System.out.println("玩家已连接！");
        } else {
            System.out.print("请输入主机 IP 地址：");
            Scanner scanner = new Scanner(System.in);
            String ip = scanner.nextLine();
            try {
                socket = new Socket(ip, 12345);
                ois = new ObjectInputStream(socket.getInputStream());
                System.out.println("输入流已创建");
                oos = new ObjectOutputStream(socket.getOutputStream());
                System.out.println("输出流已创建");
                System.out.println("已连接到主机！");
            } catch (IOException e) {
                System.err.println("连接失败: " + e.getMessage());
                System.exit(1);
            }
        }
    }
}

interface CanPlay {
    void attack(Actor a);
    void defense();
}

abstract class Actor implements CanPlay, Serializable {
    private static final long serialVersionUID = 1L;
    protected int attackPower;
    protected int defensePower;
    protected String name;
    protected volatile int blood;
    protected int state; // 0:正常 1:防御

    public Actor(String name, int blood, int attackPower, int defensePower) {
        this.name = name;
        this.blood = blood;
        this.attackPower = attackPower;
        this.defensePower = defensePower;
    }

    public synchronized int getBlood() {
        return blood;
    }

    public String getName() {
        return name;
    }

    public synchronized void setBlood(int blood) {
        this.blood = blood;
    }

}

abstract class Game {
    protected Actor a1; //player
    protected Actor a2;

    public abstract Actor randomActor();
    public abstract void setActor(String type);
    public abstract void play(boolean userDefense, boolean robotDefense);
}

class Game1 extends Game {

    private class Master extends Actor {
        public Master(String name) {
            super(name, 100, 500, 10);
        }

        @Override
        public void attack(Actor target) {
            int damage;
            if (target instanceof Master) {
                damage = attackPower / target.defensePower;
            } else {
                damage = (attackPower * 2) / target.defensePower;
            }

            if (target.state == 1) {
                damage = 0;
                target.state = 0;
                System.out.println(target.name + "正在防御,你空大了！");
            }

            target.blood -= damage;
            System.out.println(name + "对" + target.name + "造成" + damage + "伤害！");
        }

        @Override
        public void defense() {
            state = 1;
            System.out.println(name + "开始防御");
        }
    }

    private class Warrior extends Actor {
        public Warrior(String name) {
            super(name, 300, 300, 50);
        }

        @Override
        public void attack(Actor target) {
            int damage;
            if (target instanceof Warrior) {
                damage = (attackPower * 2) / target.defensePower;
            } else {
                damage = attackPower / target.defensePower;
            }

            if (target.state == 1) {
                damage = 0;
                target.state = 0;
                System.out.println(target.name + "正在防御,你空大了！");
            }

            target.blood -= damage;
            System.out.println(name + "对" + target.name + "造成" + damage + "伤害！");
        }

        @Override
        public void defense() {
            state = 1;
            System.out.println(name + "开始防御");
        }
    }

    @Override
    public Actor randomActor() {
        Random rand = new Random();
        if (rand.nextBoolean()) {
            return new Master("妖姬");
        } else {
            return new Warrior("剑魔");
        }
    }

    @Override
    public void setActor(String type) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("请输入你的名字：");
        String name = scanner.nextLine();
        if ("Master".equalsIgnoreCase(type)) {
            a1 = new Master(name);
        } else if ("Warrior".equalsIgnoreCase(type)) {
            a1 = new Warrior(name);
        } else {
            System.out.println("请选择正确的角色");
        }

        a2 = randomActor();
    }

    @Override
    public void play(boolean userDefense, boolean robotDefense) {
        System.out.println("\n====== 回合开始 ======");
        System.out.println(a1.getName() + "剩余血量:" + a1.getBlood());
        System.out.println(a2.getName() + "剩余血量:" + a2.getBlood());
        if (userDefense) a1.defense();
        if (robotDefense) a2.defense();
        //这里采用列表存储要进攻的对象，然后逐个发起进攻
        List<Actor> attackers = new ArrayList<>();
        if (!userDefense) attackers.add(a1);
        if (!robotDefense) attackers.add(a2);
        for (Actor attacker : attackers) {
            if (attacker == a1) {
                a1.attack(a2);
            } else {
                a2.attack(a1);
            }
        }

        System.out.println("\n====== 本轮结果 ======");
        System.out.println(a1.getName() + "剩余血量:" + a1.getBlood());
        System.out.println(a2.getName() + "剩余血量:" + a2.getBlood());
        System.out.println();
        if (a1.getBlood() > a2.getBlood()) {
            System.out.println(a1.getName() + "获胜");
        } else if (a2.getBlood() > a1.getBlood()) {
            System.out.println(a2.getName() + "获胜");
        } else {
            System.out.println("平局");
        }
    }
}

class Game2 extends OnlineGame {
    private static final int RESPONSE_TIMEOUT = 30000;
    private boolean gameRunning = true;
    private final Object lock = new Object();
    private final Object responseLock = new Object();
    private boolean responseReceived = false;
    private boolean localActionSent = false;
    private boolean remoteActionReceived = false;
    private NetworkMessage remoteActionMessage;

    public boolean isGameRunning() {
        return gameRunning;
    }

    private static class Archer extends Actor {
        public Archer(String name) {
            super(name, 150, 400, 20);
        }

        @Override
        public void attack(Actor target) {
            int damage = (target instanceof Archer) ?
                    (attackPower * 3) / target.defensePower :
                    (attackPower / 2) / target.defensePower;

            applyDamage(target, damage);
        }

        @Override
        public void defense() {
            state = 1;
            System.out.println(name + " 进入弓箭手防御姿态！");
        }
    }

    private static class Knight extends Actor {
        public Knight(String name) {
            super(name, 250, 500, 30);
        }

        @Override
        public void attack(Actor target) {
            int damage = (target instanceof Knight) ?
                    (attackPower / 2) / target.defensePower :
                    (attackPower * 3) / target.defensePower;

            applyDamage(target, damage);
        }

        @Override
        public void defense() {
            state = 1;
            System.out.println(name + " 举起盾牌防御！");
        }
    }

    private static void applyDamage(Actor target, int damage) {
        synchronized (target) {
            if (target.state == 1) {
                damage = Math.max(damage / 2, 1);
                target.state = 0;
                System.out.println(target.name + " 的防御状态减半伤害！");
            }
            target.setBlood(target.getBlood() - damage);
        }
        System.out.println(Thread.currentThread().getName() + " 攻击 " + target.name + "，造成 " + damage + " 伤害！");
    }

    @Override
    public Actor randomActor() {
        return null; // 联机模式下不使用随机角色
    }

    @Override
    public void setActor(String type) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("请输入角色名字：");
        String name = scanner.nextLine();

        if ("Archer".equalsIgnoreCase(type)) {
            a1 = new Archer(name);
        } else if ("Knight".equalsIgnoreCase(type)) {
            a1 = new Knight(name);
        } else {
            throw new IllegalArgumentException("无效角色类型");
        }

        System.out.print("是否作为主机？(Y/N) ");
        boolean asServer = scanner.nextLine().equalsIgnoreCase("Y");
        try {
            startNetwork(asServer);
            System.out.println("正在交换角色信息...");
            if (isServer) {
                oos.writeObject(a1);
                oos.flush();
                a2 = (Actor) ois.readObject();
                System.out.println("接收到对方角色：" + a2.name + " | 血量：" + a2.blood);
            } else {
                a2 = (Actor) ois.readObject();
                System.out.println("接收到对方角色：" + a2.name + " | 血量：" + a2.blood);
                oos.writeObject(a1);
                oos.flush();
            }
            System.out.println("已连接到对手角色: " + a2.name);
        } catch (Exception e) {
            System.err.println("网络连接错误: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }

    @Override
    public void play(boolean userDefense, boolean dummy) {
        Thread receiveThread = new Thread(this::receiveUpdates);
        receiveThread.start();

        try {
            while (gameRunning) {
                sendMessage(new NetworkMessage(
                        NetworkMessage.TYPE_STATE,
                        "UPDATE",
                        a1.getBlood()
                ));
                NetworkMessage actionMsg = new NetworkMessage(
                        NetworkMessage.TYPE_ACTION,
                        userDefense ? "DEFENSE" : "ATTACK",
                        a1.getBlood()
                );
                sendMessage(actionMsg);
                localActionSent = true;
                waitForBothActions();
                executeRound(userDefense, remoteActionMessage.content.equals("DEFENSE"));
                if (a1.getBlood() <= 0 || a2.getBlood() <= 0) {
                    sendFinalResult();
                    gameRunning = false;
                    showFinalResult();
                    break;
                }
                System.out.printf("%s (你) 剩余血量: %d\n", a1.name, a1.getBlood());
                System.out.printf("%s (对手) 剩余血量: %d\n", a2.name, a2.getBlood());

                System.out.print("\n准备下一回合...（Q 退出/其他继续）");
                String input = new Scanner(System.in).nextLine();
                if (input.equalsIgnoreCase("Q")) {
                    sendMessage(new NetworkMessage(NetworkMessage.TYPE_STATE, "QUIT", 0));
                    gameRunning = false;
                    break;
                }
                System.out.print("请选择行动（A:攻击/D:防御）：");
                userDefense = new Scanner(System.in).nextLine().equalsIgnoreCase("D");
                localActionSent = false;
                remoteActionReceived = false;
            }
        } catch (Exception e) {
            System.err.println("对战错误: " + e.getMessage());
        } finally {
            try {
                receiveThread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            closeResources();
        }
    }

    private void sendMessage(NetworkMessage msg) throws IOException {
        if (socket.isClosed()) {
            throw new IOException("连接已关闭");
        }

        synchronized (lock) {
            oos.reset();
            oos.writeObject(msg);
            oos.flush();
            System.out.println("消息发送成功：" + msg.content);
        }
    }

    private void sendFinalResult() throws IOException {
        synchronized (lock) {
            oos.reset();
            oos.writeObject(new NetworkMessage(
                    NetworkMessage.TYPE_STATE,
                    "GAME_OVER",
                    a1.blood
            ));
        }
    }

    private void closeResources() {
        try {
            synchronized (lock) {
                if (ois != null) ois.close();
                if (oos != null) oos.close();
                if (socket != null && !socket.isClosed()) {
                    socket.shutdownInput();
                    socket.shutdownOutput();
                    socket.close();
                }
            }
        } catch (IOException e) {
            System.err.println("资源关闭异常: " + e.getMessage());
        }
    }

    private void handleActionMessage(NetworkMessage msg) {
        synchronized (responseLock) {
            a2.setBlood(msg.currentBlood);
            remoteActionMessage = msg;
            remoteActionReceived = true;
            responseLock.notifyAll();
        }
    }

    private void handleStateMessage(NetworkMessage msg) {
        if ("GAME_OVER".equals(msg.content)) {
            gameRunning = false;
            showFinalResult();
        }
        System.out.println("更新对手血量：" + msg.currentBlood);
        a2.setBlood(msg.currentBlood);
    }

    private void receiveUpdates() {
        try {
            while (gameRunning) {
                Object obj = ois.readObject();
                if (obj instanceof NetworkMessage) {
                    NetworkMessage msg = (NetworkMessage) obj;
                    switch (msg.messageType) {
                        case NetworkMessage.TYPE_ACTION:
                            handleActionMessage(msg);
                            break;
                        case NetworkMessage.TYPE_STATE:
                            handleStateMessage(msg);
                            break;
                    }
                }
            }
        } catch (EOFException e) {
            System.out.println("连接正常关闭");
        } catch (Exception e) {
            if (gameRunning) {
                System.err.println("连接异常中断：" + e.getMessage());
            }
        }
    }

    private void showFinalResult() {
        System.out.println("=== 最终战绩 ===");
        System.out.println(a1.name + " 血量: " + a1.blood);
        System.out.println(a2.name + " 血量: " + a2.blood);

        if (a1.blood <= 0 && a2.blood <= 0) {
            System.out.println("双方同归于尽！");
        } else if (a1.blood > a2.blood) {
            System.out.println(a1.name + " 获胜！");
        } else {
            System.out.println(a2.name + " 获胜！");
        }
    }

    private void waitForBothActions() throws InterruptedException {
        synchronized (responseLock) {
            while (!(localActionSent && remoteActionReceived)) {
                responseLock.wait();
            }
        }
    }

    private void executeRound(boolean localDefense, boolean remoteDefense) {
        int initialBlood1 = a1.getBlood();
        int initialBlood2 = a2.getBlood();
        System.out.println("\n=== 回合开始 ===");
        System.out.printf("%s (你) 血量: %d 状态: %s\n",
                a1.name, a1.getBlood(), localDefense ? "防御" : "进攻");
        System.out.printf("%s (对手) 血量: %d 状态: %s\n",
                a2.name, a2.getBlood(), remoteDefense ? "防御" : "进攻");

        // 防御
        if (localDefense) a1.defense();
        if (remoteDefense) a2.defense();

        if (!localDefense) {
            System.out.println("\n>>> 你的攻击回合 <<<");
            a1.attack(a2);
        }
        if (!remoteDefense) {
            System.out.println("\n>>> 对手攻击回合 <<<");
            a2.attack(a1);
        }

        // 显示结果
        System.out.println("\n=== 回合结束 ===");
        System.out.printf("%s (你) 剩余血量: %d\n", a1.name, a1.getBlood());
        System.out.printf("%s (对手) 剩余血量: %d\n", a2.name, a2.getBlood());
        if (a1.getBlood() == initialBlood1 && a2.getBlood() == initialBlood2) {
            System.out.println("警告：本回合没有发生任何伤害！");
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Lol.LOLtest();
    }
}

class Lol {
    public static void LOLtest() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请选择游戏：输入数字1或者数字2");
        int gameChoice;
        while (true) {
            gameChoice = scanner.nextInt();
            scanner.nextLine();
            if (gameChoice == 1) {
                Game game = new Game1();
                System.out.println("请选择角色类型Master或者Warrior");
                String type = scanner.nextLine();
                game.setActor(type);

                System.out.println("请选择本回合行动（A:攻击 / D:防御）：");
                String action = scanner.nextLine().toUpperCase();
                boolean userDefense = action.equals("D");
                Random rand = new Random();
                boolean systemDefense = rand.nextBoolean();
                System.out.println("对手选择：" + (systemDefense ? "防御" : "攻击"));

                game.play(userDefense, systemDefense);
                break;
            } else if (gameChoice == 2) {
                Game game = new Game2();
                System.out.println("请选择角色类型 Archer 或者 Knight");
                String type = scanner.nextLine();
                game.setActor(type);

                System.out.println("请选择本回合行动（A:攻击/D:防御）：");
                String action = scanner.nextLine().toUpperCase();
                boolean userDefense = action.equals("D");

                game.play(userDefense, false);
                break;
            } else {
                System.out.println("无效选择，请重新输入");
            }
        }
    }
}       