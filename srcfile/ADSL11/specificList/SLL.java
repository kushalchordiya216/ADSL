/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package specificList;

import common.commonList;
import java.util.Scanner;

class Node {

    public int data;
    public Node link;

    public Node() {
        link = null;
        data = 0;
    }

    public Node(int d, Node n) {
        data = d;
        link = n;
    }
}

public class SLL implements commonList {

    Node start;
    Node end;
    int size;

    SLL() {
        start = null;
        end = null;
        size = 0;
    }

    public boolean isEmpty() {
        return start == null;
    }

    public void add(int val) {
        Node nptr = new Node(val, null);
        size++;
        if (start == null) {
            start = nptr;
            end = nptr;
        } else {
            end.link = nptr;
            end = nptr;
        }
    }

    public int size() {
        return size();
    }

    public void display() {
        System.out.print("\nSingly Linked List = ");
        if (size == 0) {
            System.out.print("empty\n");
            return;
        }
        if (start.link == null) {
            System.out.println(start.data);
            return;
        }

        Node ptr = start;
        while (ptr.link != null) {
            System.out.print(ptr.data + "->");
            ptr = ptr.link;
        }
        System.out.print(ptr.data);
    }

    public void delete(int val) {
        Node ptr = start;
        if (start.data == val) {
            start = start.link;
        }
        while (ptr.link != null && ptr.link.data != val) {
            ptr = ptr.link;
        }
        if (ptr.link != null && ptr.link.data == val) {
            ptr.link = ptr.link.link;
        } else {
            System.out.println("Given node is not present in list!\n");
        }
    }

    public static void main(String[] args) {
        SLL sl = new SLL();
        Scanner sc = new Scanner(System.in);
        while (sc.hasNextInt()) {
            int no = sc.nextInt();
            sl.add(no);
        }

        sl.display();
        sl.add(6);
        sl.display();
        sl.delete(5);
        sl.display();
        sc.close();
    }
}
/*
 * java specificList.SLL 1 2 3 4 5 r
 * 
 * Singly Linked List = 1->2->3->4->5 Singly Linked List = 1->2->3->4->5->6
 * Singly Linked List = 1->2->3->4->6(base)
 * 
 */