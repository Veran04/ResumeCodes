import java.io.File;
import java.lang.reflect.Array;
import java.util.*;
public class SkipListSet <T extends Comparable<T>> implements SortedSet<T> {
	int h;												//height of the list
	SkipListSetItem head, tail;  
	int n;												//# of elements in list
	Random RNG;											//RNG to coinflip for adding values or rebalancing
		public SkipListSet()							//empty list constructor
	    {
			head = new SkipListSetItem();
			tail = new SkipListSetItem();
			
			head.right=tail;
			tail.left=head;
			n=0;
			h=1;
			RNG = new Random();  						 
			
	    }
	    public SkipListSet(Collection<T> list)			//Collection Constructor
	    {
	    	RNG = new Random();    					
			head = new SkipListSetItem();
			tail = new SkipListSetItem();
			head.right=tail;
	    	h = 1;
	    	n = 0;
			tail.left=head;
			
			addAll(list);
														
	    	}
	    public void reBalance() {							//Rebalances the list, coinflipping every element including the 
	    													//newly added one that prompted the method to be called.
	    	SkipListSetItem insert = head;
	    	while(insert.down!=null) {
	    		insert=insert.down;
	    	}
	    	SkipListSetItem baseInsert = insert;
	    	for(int j=0; j<n+1; j++ ) {
	    		baseInsert=baseInsert.right;
	    		insert=baseInsert;
		    	for(int i=1;i<h;i++) {
					if(RNG.nextInt(2)==0) {
						SkipListSetItem insertLayer = insert;
						SkipListSetItem biggieInsert = new SkipListSetItem(insert.data);
	    		    	biggieInsert.down=insertLayer;
	    		    	insertLayer.up=biggieInsert;
	    		    	SkipListSetItem leftFinder = insertLayer;
	    		    	while(leftFinder.left!=null && leftFinder.left.up==null) {
	    		    		leftFinder=leftFinder.left;
	    		    	}
	    		    	leftFinder=leftFinder.left;
	    		    	biggieInsert.left=leftFinder.up;
	    		    	biggieInsert.right=leftFinder.up.right;
	    		    	leftFinder.up.right.left=biggieInsert;
	    		    	leftFinder.up.right=biggieInsert;
					}
					else {
						break;
					}
				}
	    	}
	    }
	    @Override
	    public boolean equals(Object val) {						//compares the hashcode of the object to the list, returning true iff they match
	    	SkipListSetItem temp = head;
	    	if(temp.hashCode()==val.hashCode()) {
	    		return true;
	    	}
	    	return false;
	    }
	    @Override
	    public int hashCode() {									//combines use of iterator with built in hashCode method to be used for equals
	    	int hashCode = 0;
	    	Iterator<T> iter = iterator();
	    	while(iter.hasNext()) {
	    		hashCode +=iter.next().hashCode();
	    	}
	    	return hashCode;
	    	
}
	   private class SkipListSetItem {							//Class for Nodes
		   T data;
		   SkipListSetItem left, right, up, down;
		   public SkipListSetItem(T val) {						//Constructor containing a T val
			   data = val;
			   left=null;
			   right=null;
			   up=null;
			   down=null;
		   }
		   public SkipListSetItem() {							//Empty node
			   data = null;
			   left=null;
			   right=null;
			   up=null;
			   down=null;
		   }
	   }
		@Override
		public int size() {										//returns number of elements in the list		
			
			return n;
		}
		@Override
		public boolean isEmpty() {								//returns true if there are no elements in the list
			if(n==0) {
				return true;
			}
			return false;
		}
		@SuppressWarnings("unchecked")
		@Override
		public boolean contains(Object val) {					//returns true if the list contains the object passed in as the parameter.
			SkipListSetItem temp = head;
			SkipListSetItem node = new SkipListSetItem((T) val);
	    	while(true) {
	    		temp = temp.right;
	    		while(temp.data!=null && temp.data.compareTo(node.data) < 0  ) {
	    				temp = temp.right;
	    		}
	    		if(temp.data!=null && temp.data.compareTo(node.data) == 0) {
	    				return true;
	    		}
	    		temp = temp.left;
	    		if(temp.down!=null) {
	    			temp = temp.down;
	    			
	    		}
	    		else  {
	    	return false;
	    	}
	    	}
		}
		@Override
		public Iterator<T> iterator() {											//instantiates a new iterator class, returning it.
			  SkipListSetIterator<T> iter = new SkipListSetIterator<T>();
			  return iter;
		}
		@Override
		public Object[] toArray() {												//Converts the list to an object array
			int tempN=0;
			Object listArray[] = new Object[n];
			Iterator<T> iter = iterator();
	    	while(iter.hasNext()) {
	    		listArray[tempN]= (iter.next());
	    		tempN++;
	    	}
			return listArray;
		}
		@SuppressWarnings("unchecked")	
		@Override
		public <T> T[] toArray(T[] a) {											//Converts the list to an array of type T
			if (a.length < n) { 
				  a = (T[]) Array.newInstance(a.getClass().getComponentType(), n);
				} else if (a.length > n) {
				  a[n] = null;
				}
			return a;
		}
		@Override
		public boolean add(T val) {												//Adds the passed in T val to the list returning true if it 
																				//does so, or else returns false
																				//also calls rebalance if necessary, and coinflips vals to heights
			SkipListSetItem temp = head;
			SkipListSetItem node = new SkipListSetItem(val);
	    	while(true) {
	    		temp = temp.right;
	    		while(temp.data!=null && temp.data.compareTo(node.data) < 0  ) {
	    		temp = temp.right;		
	    		}
	    		if(temp.data!=null && temp.data.equals(node.data)) {
	    				return false;
	    		}
	    		temp = temp.left;
	    		if(temp.down!=null) {
	    			temp = temp.down;
	    			
	    		}
	    		else  {
	    				SkipListSetItem insert = new SkipListSetItem(node.data);
	    				SkipListSetItem placeholder = temp.right;
	    				insert.left = temp;
	    				temp.right = insert;
	    				insert.right = placeholder;
	    				placeholder.left = insert;
	    				
	    				for(int i=1;i<h;i++) {
	    					if(RNG.nextInt(2)==0) {
	    						SkipListSetItem insertLayer = insert;
	    						insert = new SkipListSetItem(insert.data);
	    	    		    	insert.down=insertLayer;
	    	    		    	insertLayer.up=insert;
	    	    		    	SkipListSetItem leftFinder = insertLayer;
	    	    		    	while(leftFinder.left!=null && leftFinder.left.up==null) {
	    	    		    		leftFinder=leftFinder.left;
	    	    		    	}
	    	    		    	leftFinder=leftFinder.left;
	    	    		    	insert.left=leftFinder.up;
	    	    		    	insert.right=leftFinder.up.right;
	    	    		    	leftFinder.up.right.left=insert;
	    	    		    	leftFinder.up.right=insert;
	    					}
	    					else {
	    						break;
	    					}
	    				}
	    				
	    				
	    				
	    				
	    				
	    				
	    				int tempN=n+1;
	    				do {
	    					if(n==0) {
	    						tempN=-1;
	    						break;
	    					}
	    					if(tempN%2==0 ) {
	    						if(tempN/2>=0) {
	    							tempN=tempN/2;
	    						}
	    					}
	    				else {
	    					break;
	    				}
	    			} 
	    			while(tempN!=1);
	    			if(tempN==1) {
	    				h++;
	    				SkipListSetItem insertHead = head;
	    		    	SkipListSetItem insertTail = tail;
	    		    	head = new SkipListSetItem();
	    		    	tail = new SkipListSetItem();
	    		    	head.down=insertHead;
	    		    	tail.down=insertTail;
	    		    	insertHead.up=head;
	    		    	insertTail.up=tail;
	    		    	tail.left=head;
	    		    	head.right=tail;
	    		    	reBalance();
	    			}
	    			n++;
	    	    	return true;
	    	    }
	    	}
		}
		@SuppressWarnings("unchecked")
		@Override
		public boolean remove(Object val) {									//removes the passed in val if it exists in the list, returning true.
																			//returns false if the value does not exist in the list.
																			//also calls rebalance if necessary
			SkipListSetItem temp = head;
			SkipListSetItem node = new SkipListSetItem((T) val);
	    	while(true) {
	    		temp = temp.right;
	    		while(temp.data!=null && temp.data.compareTo(node.data) < 0  ) {
	    		temp = temp.right;		
	    		}
	    		if(temp.data!=null && temp.data.equals(node.data)) {
	    			while(temp.down!=null) {
	    				 SkipListSetItem temp1 = temp.left;
	    				 SkipListSetItem temp2 = temp.right;
	    		    	 temp1.right=temp2;
	    		    	 temp2.left=temp1;
	    				temp.up=null;
	    				temp=temp.down;
	    			}
	    			
	    			SkipListSetItem temp1 = temp.left;
   				 SkipListSetItem temp2 = temp.right;
   		    	 temp1.right=temp2;
   		    	 temp2.left=temp1;
    				temp.up=null;
	    			int tempN=n-1;
    				do {
    					if(n==0) {
    						tempN=-1;
    						break;
    					}
    					if(tempN%2==0 ) {
    						if(tempN/2>=0) {
    							tempN=tempN/2;
    						}
    					}
    				else {
    					break;
    				}
    			} 
    			while(tempN!=1);
    			if(tempN==1) {
    				h--;
    				head=head.down;
    				tail=tail.down;
    				head.up=null;
    				tail.up=null;
    				reBalance();
    			}
	    				n--;
	    				return true;
	    		}
	    		temp = temp.left;
	    		if(temp.down!=null) {
	    			temp = temp.down;
	    			
	    		}
	    		else  {
	    	    	return false;
	    	    	}
	    	    	}
			
		}
		@Override
		public boolean containsAll(Collection<?> c) {				//uses the contains method to see if the list contains every item in the
																//passed in collection. Returns true IFF every item is contained in our list.
			for(Object val: c) {
				if(!contains(val)) {
					return false;
				}
			}
			return true;
		}
		
		
		@Override
		public boolean addAll(Collection<? extends T> c) {			//Passes in a collection, adding all to the list. Returns true if the list is changed.
					boolean test=false;												
			for(Object val: c) {
				if(add((T) val)) {
					test=true;
				}
			}
			return test;
		}
		
		
		@Override
		public boolean retainAll(Collection<?> c) {					//Passes in a collection, deleting every item from the list that is not present
																	//in the collection, returning true if the list is changed in any way.
			 Iterator<T> itr = iterator(); 
			    int counter=0;
			    while(itr.hasNext())
			    {   
			        if(!c.contains(itr.next()))
			        {
			            itr.remove(); 
			            counter++; 
			        }
			    }

			    if(counter==0) {
			    	return false;
			    }
			    return true;
		}
		@Override 
		public boolean removeAll(Collection<?> c) {				//Works the same way as AddAll, except for remove. If the list is changed it returns true.
					boolean test=false;											
			for(Object val: c) {
				if(remove((T) val)) {
					test=true;
				}
			}
			
			return test;
		}
		@Override
		public void clear() {									//Splits the head off from the rest of the list reconnecting it to tail.
			head.right=tail;
			tail.left=head;
			head.up=null;
			head.down=null;
			tail.up=null;
			tail.down=null;
			n=0;
		}
		@Override
		public java.util.Comparator<? super T> comparator() {		//simply returns null
			return null;
		}
		@Override
		public SortedSet<T> subSet(T fromElement, T toElement) {	//Throws an exception since we were told not to do this method
			try {
	    		throw new UnsupportedOperationException();
	    	}
	    	catch(Exception ex) {
	    		System.out.println("Unsupported operation detected.");
	    	}
			return null;
		}
		@Override
		public SortedSet<T> headSet(T toElement) {					//Throws an exception since we were told not to do this method
			try {
	    		throw new UnsupportedOperationException();
	    	}
	    	catch(Exception ex) {
	    		System.out.println("Unsupported operation detected.");
	    	}
			return null;
		}
		@Override
				public SortedSet<T> tailSet(T fromElement) {		//Throws an exception since we were told not to do this method
			try {
	    		throw new UnsupportedOperationException();
	    	}
	    	catch(Exception ex) {
	    		System.out.println("Unsupported operation detected.");
	    	}
			return null;
		}
		@Override
		public T first() {											//Returns the first item in the list, using the bottom as a reference.
			 SkipListSetItem temp = head;
			    	 while(temp.down!=null) {
			    	 temp=temp.down;
			    	 }
			    	 temp = temp.right;
			    	 T min = temp.data;
			    	 
			    	 return min;
		}
		@Override
		public T last() {											//returns the last item in the list, using the bottom as a reference.
			 SkipListSetItem temp = head;
			    	 while(temp.down!=null) {
			    	 temp=temp.down;
			    	 }
			    	 while(temp.right.data!=null) {
			    	 temp=temp.right;
			    	 }
			    	 T max = temp.data;
			    	 
			    	 return max;
		}
		private class SkipListSetIterator<T extends Comparable<T>> implements Iterator<T> {		//Iterator class
			int index;
			public SkipListSetIterator() {
				index=0;
			}
			@Override
			public boolean hasNext() {				//checks if the list has a node to the right.
				 SkipListSetItem temp = head;
		    	 while(temp.down!=null) {
		    	 temp=temp.down;
		    	 }
		    	 for(int i=0; i<=index; i++) {
		    		 temp = temp.right;
		    	 }
		    	 if(temp.data!=null) {
		    		 return true;
		    	 }
				
				return false;
			}
			@Override
			public T next() {					//returns the next node in the lists data.
				SkipListSetItem temp = head;
		    	 while(temp.down!=null) {
		    	 temp=temp.down;
		    	 }
		    	 for(int i=0; i<=index; i++) {
		    		 temp = temp.right;
		    	 }
		    	 index++;
		    	 return (T) temp.data;						
			}
			@Override
			public void remove() {			//can only be called after next, removes the previous node called by next.
				index--;
				SkipListSetItem temp = head;
		    	 while(temp.down!=null) {
		    	 temp=temp.down;
		    	 }
		    	 for(int i=0; i<=index; i++) {
		    		 temp = temp.right;
		    	 }
		    	 SkipListSetItem temp1 = temp;
		    	 temp1=temp1.left;
		    	 temp=temp.right;
		    	 temp1.right=temp;
		    	 temp.left=temp1; 
			}
		}
}
