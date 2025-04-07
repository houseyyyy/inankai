import java.util.*;
import java.util.Scanner;
/*
双向链表，保存头结点和尾节点，和一个HashMap<key,Node>
put思路：
    首先检查是否为空，为空直接插入
    否则判断是否已经存满
        假如存满
            将尾结点删除，同步在map中删除
        否则
            将这个结点插入头结点
put时间复杂度分析:
    插入链表头，删除尾结点，Hashmap删除键值对都是常量，总时间复杂度为O(1)

get思路：
    首选在map中找到对应Node temp
        判断temp是否为空
            为空返回null
            不为空，将temp插入到head前，返回temp.v
get时间复杂度分析：
    HashMap 查找，头插都是常量，总时间复杂度为O(1)
*/
class Lru <K,V>{
    class Node{
        Node pre;
        Node next;
        K key;
        V value;
        Node(K key,V value){
            this.key = key;
            this.value = value;
        }
    }
    Node head;
    Node tail;
    private int capacity;
    private HashMap<K,Node> map;
    Lru(int capacity)
    {
        this.capacity = capacity;
        map = new HashMap<K,Node> (capacity);

    }
    private void Tohead(Node temp)
    {
        if(temp == head)
        {
            return;
        }
        if (temp.pre != null) {
            temp.pre.next = temp.next;
        }
        if (temp.next != null) {
            temp.next.pre = temp.pre;
        }
        if (temp == tail) {
            tail = temp.pre;
        }
        temp.pre = null;
        temp.next = head;
        if (head != null) {
            head.pre = temp;
        } else {
            tail = temp;
        }
        head = temp;
    }
    public V get(K key)
    {
        Node temp = map.get(key);
        if(temp == null)
        {
            return (V)"null";
        }
        Tohead(temp);
        return temp.value;
    }
    void put(K key,V value)
    {
        if(head == null)
        {
            Node temp = new Node(key,value);
            head = temp;
            tail = temp;
            map.put(key,temp);
            return;
        }
        //delete tail node
        Node t = map.get(key);
        if(t != null)
        {
            t.value = value;
            Tohead(t);
        }
        else{
            if(isfull())
            {
                map.remove(tail.key);
                if(head == tail)
                {
                    head = tail = null;
                }
                else
                {
                    tail = tail.pre;
                    tail.next = null;
                }
            }
            Node temp = new Node(key,value);
            Tohead(temp);
            map.put(key,temp);
        }
    }
    boolean isfull(){
        return map.size() == capacity ? true : false;
    }
    public void putCommand(String in)
    {
        String[] kvs = in.split(";");
        for (String kv : kvs) {
            if (kv.trim().isEmpty()) continue;
            String[] pair = kv.split(",", 2);
            K key = (K)pair[0];
            V value = (V)pair[1];
            this.put(key,value);
        }
    }
    public void getCommand(String in)
    {
        String[] kvs = in.split(";");
        for (String kv : kvs) {
            if (kv.trim().isEmpty()) continue;
            K key = (K)kv;
            //get(key);
            System.out.print(this.get(key));
            System.out.print(";");
        }
        System.out.println();
    }
}


public class Main{
    public static void main(String args[])
    {
        Scanner scan = new Scanner(System.in);
        int n,m;
        n = scan.nextInt();
        m = scan.nextInt();
        String temp = scan.nextLine();
        Lru<String,String> mylru = new Lru<String,String> (n);
        while(m-- != 0)
        {
            String line = scan.nextLine().trim();
            String[] parts = line.split("\\s+", 2);
            String command = parts[0].toLowerCase();
            String arguments = parts.length > 1 ? parts[1] : "";
            switch (command) {
                case "put":
                    mylru.putCommand(arguments);
                    break;
                case "get":
                    mylru.getCommand(arguments);
                    break;
            }
        }     
    }
}