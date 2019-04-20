import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;
import java.util.Stack;

public class Collections {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        int choice, number;

        PriorityQueue<Integer> q1 = new PriorityQueue<>();
        Stack<Integer> s1 = new Stack<>();
        LinkedList<Integer> l1 = new LinkedList<>();
        ArrayList<Integer> arrayList = new ArrayList<>();
        HashMap<String, String> hs = new HashMap<>();

        do {
            System.out.println("\n1.Queue\n2.Stack\n3.Linked List\n4.ArraList\n5.Map\n0.Exit\nEnter your choice:");
            choice = sc.nextInt();
            switch (choice) {
            case 1:
                System.out.println("1.Enqueue\n2.Dequeue\n0.Exit");
                choice = sc.nextInt();
                switch (choice) {
                case 1:
                    System.out.println("\nEnter Number: ");
                    q1.add(new Integer(sc.nextInt()));
                    System.out.println("Added :" + q1.peek());
                    break;
                case 2:
                    System.out.println("\nRemoved element:=>" + q1.remove());
                    break;
                case 0:
                    break;
                }
                break;
            case 2:
                System.out.println("\n1.Push\n2.Pop\n3.Top\n4.Exit;");
                choice = sc.nextInt();
                switch (choice) {
                case 1:
                    System.out.println("\nEnter Number: ");
                    s1.push(new Integer(sc.nextInt()));
                    break;
                case 2:
                    System.out.println("\nPopped elemet:=> " + s1.pop());
                    break;
                case 3:
                    System.out.println("\nStack top: " + s1.peek());
                    break;
                case 4:
                    break;
                }
                break;
            case 3:
                System.out.println("\n====Linked LIST =====\n1.Add\n2.Remove\n3.First\n4.LAst");
                choice = sc.nextInt();
                switch (choice) {
                case 1:
                    System.out.println("\nEnter Number: ");
                    l1.add(new Integer(sc.nextInt()));
                    break;
                case 2:
                    System.out.println("\nEnter element to remove: ");
                    System.out.println("\nRemoved element:" + l1.remove(sc.nextInt()));
                    break;
                case 3:
                    System.out.println("\nFirst Element: " + l1.getFirst());
                    break;
                case 4:
                    System.out.println("\nLast Element: " + l1.getLast());
                    break;
                case 5:
                    break;
                }
                break;
            case 4:
                System.out.println("\n====ARRAY LIST ========");
                System.out.print("\n1.Add element\n2.Remove element at particular index\n3.Size of list\n4.Exit");
                choice = sc.nextInt();
                switch (choice) {
                case 1:
                    number = sc.nextInt();
                    arrayList.add(number);
                    break;
                case 2:
                    System.out.println("Enter index:\n");
                    number = sc.nextInt();
                    arrayList.remove(number);
                    break;
                case 3:
                    System.out.println("Size:");
                    System.out.println(arrayList.size());
                    break;
                default:
                    break;
                }
                break;
            case 5:
                System.out.println("\n===== Hash Map====="); {
                System.out.println("\nEnter Key");
                sc.next();
                String key = sc.nextLine();
                System.out.println("\nEnter Value: ");
                String value = sc.nextLine();
                hs.put(key, value);
                System.out.println("\nRecord Inserted");
                hs.put("roll", "2464");
                hs.put("Div", "4");
                System.out.println("\nRemoved element (roll):" + hs.remove("roll"));
                System.out.println("\nSize: " + hs.size());
                System.out.println("\nHashcode Value for this map: " + hs.hashCode());
            }
                break;
            default:
                System.out.println("\nWrong Choice");
            }
        } while (choice != 0);
        sc.close();
    }
}
/*
 * 
 * (base) kushal@kushal-Nitro-AN515-31:ADSL13$ cd
 * "/home/kushal/eclipse-workspace/ADSL13/" && javac Collections.java && java
 * Collections
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 1
 * 1.Enqueue 2.Dequeue 0.Exit 1
 * 
 * Enter Number: 1 Added :1
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 1
 * 1.Enqueue 2.Dequeue 0.Exit 1
 * 
 * Enter Number: 2 Added :1
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 1
 * 1.Enqueue 2.Dequeue 0.Exit 1
 * 
 * Enter Number: 3 Added :1
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 1
 * 1.Enqueue 2.Dequeue 0.Exit 2
 * 
 * Removed element:=>1
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 1
 * 1.Enqueue 2.Dequeue 0.Exit 2
 * 
 * Removed element:=>2
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 1
 * 1.Enqueue 2.Dequeue 0.Exit 2
 * 
 * Removed element:=>3
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 2
 * 
 * 1.Push 2.Pop 3.Top 4.Exit; 1
 * 
 * Enter Number: 1
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 2
 * 
 * 1.Push 2.Pop 3.Top 4.Exit; 1
 * 
 * Enter Number: 1
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 2
 * 
 * 1.Push 2.Pop 3.Top 4.Exit; 1
 * 
 * Enter Number: 2
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 2
 * 
 * 1.Push 2.Pop 3.Top 4.Exit; 3
 * 
 * Stack top: 2
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 2
 * 
 * 1.Push 2.Pop 3.Top 4.Exit; 2
 * 
 * Popped elemet:=> 2
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 2
 * 
 * 1.Push 2.Pop 3.Top 4.Exit; 3
 * 
 * Stack top: 1
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 3
 * 
 * ====Linked LIST ===== 1.Add 2.Remove 3.First 4.LAst 1
 * 
 * Enter Number: 1
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 3
 * 
 * ====Linked LIST ===== 1.Add 2.Remove 3.First 4.LAst 1
 * 
 * Enter Number: 2
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 3
 * 
 * ====Linked LIST ===== 1.Add 2.Remove 3.First 4.LAst 1
 * 
 * Enter Number: 3
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 3
 * 
 * ====Linked LIST ===== 1.Add 2.Remove 3.First 4.LAst 3
 * 
 * First Element: 1
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 3
 * 
 * ====Linked LIST ===== 1.Add 2.Remove 3.First 4.LAst 4
 * 
 * Last Element: 3
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 3
 * 
 * ====Linked LIST ===== 1.Add 2.Remove 3.First 4.LAst 2
 * 
 * Enter element to remove: 2
 * 
 * Removed element:3
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 4
 * 
 * ====ARRAY LIST ========
 * 
 * 1.Add element 2.Remove element at particular index 3.Size of list 4.Exit1 1
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 4
 * 
 * ====ARRAY LIST ========
 * 
 * 1.Add element 2.Remove element at particular index 3.Size of list 4.Exit1 2
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 4
 * 
 * ====ARRAY LIST ========
 * 
 * 1.Add element 2.Remove element at particular index 3.Size of list 4.Exit1 3
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 4
 * 
 * ====ARRAY LIST ========
 * 
 * 1.Add element 2.Remove element at particular index 3.Size of list 4.Exit3
 * Size: 3
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 4
 * 
 * ====ARRAY LIST ========
 * 
 * 1.Add element 2.Remove element at particular index 3.Size of list 4.Exit2
 * Enter index:
 * 
 * 2
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 4
 * 
 * ====ARRAY LIST ========
 * 
 * 1.Add element 2.Remove element at particular index 3.Size of list 4.Exit3
 * Size: 2
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 5
 * 
 * ===== Hash Map=====
 * 
 * Enter Key kushal
 * 
 * Enter Value: student
 * 
 * Record Inserted
 * 
 * Removed element (roll):2464
 * 
 * Size: 2
 * 
 * Hashcode Value for this map: -1879077248
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 5
 * 
 * ===== Hash Map=====
 * 
 * Enter Key nikhil
 * 
 * Enter Value: student2
 * 
 * Record Inserted
 * 
 * Removed element (roll):2464
 * 
 * Size: 2
 * 
 * Hashcode Value for this map: 1876087196
 * 
 * 1.Queue 2.Stack 3.Linked List 4.ArraList 5.Map 0.Exit Enter your choice: 0
 * 
 * Wrong Choice (base) kushal@kushal-Nitro-AN515-31:ADSL13$
 */