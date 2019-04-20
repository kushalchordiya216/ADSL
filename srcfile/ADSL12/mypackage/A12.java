/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mypackage;

import java.util.Stack;

abstract class MyStack {
	public final void pushTemplateMethod() {
		show();
		push();
		display();
	}

	abstract protected void push();

	abstract protected void display();

	protected void show() {
		System.out.println("Stack implementation");
	}
}

class IntStack extends MyStack {
	Stack<Integer> s = new Stack<Integer>();

	protected void push() {
		s.push(10);
		s.push(20);
		s.push(30);
	}

	protected void display() {
		while (!s.isEmpty()) {
			System.out.print(s.pop() + " ");
		}
		System.out.println("");
	}
}

public class A12 {
	public static void main(String[] args) {
		IntStack object = new IntStack();
		object.pushTemplateMethod();
	}
}
/*
 * Stack implementation 
 * 30 20 10
 */