public class BasicListIterator
                implements java.util.ListIterator {
  private BasicListInterface list;
  private int loc; // location of iterator in list

  public BasicListIterator(BasicListInterface list) {
    this.list = list;
    loc = 0;
  }  // end constructor

  protected BasicListInterface getList() {
  // This method will be needed by subclasses to access
  // the private data field list.
    return list;
  }  // end getList

  protected void setLoc(int newLoc) {
  // This method will be needed by subclasses to set
  // the private data field loc.  The method nextIndex
  // can be used to get the loc value.
    loc = newLoc;
  }  // end setLoc

  public boolean hasNext() { 
  // Returns true if this list iterator has more
  // elements when traversing the list in the forward
  // direction.
    return (loc < list.size());
  }  // end hasNext

  public Object next() throws java.util.NoSuchElementException {
  // Returns the next element in the list.
    if (hasNext()) {
      Object item = list.get(loc+1);
      loc++;
      return item;
    }
    else {
      throw new java.util.NoSuchElementException();
    }  // end if
  }  // end next

  public boolean hasPrevious() { 
  // Returns true if this list iterator has more
  // elements when traversing the list in the reverse
  // direction.
    return (loc > 0);
  }  // end hasPrevious

  public Object previous() throws java.util.NoSuchElementException {
  // Returns the previous element in the list.
    if (hasPrevious()) {
      Object item = list.get(loc);
      loc--;
      return item;
    }
    else {
      throw new java.util.NoSuchElementException();
    }  // end if
  }  // end previous

  public int nextIndex() { 
  // Returns the index of the element that would be
  // returned by a subsequent call to next. Returns 
  // list size if the list iterator is at the end of 
  // the list.
    return loc;
  }  // end nextIndex

  public int previousIndex() { 
  // Returns the index of the element that would be
  // returned by a subsequent call to previous.
  // Returns -1 if the list iterator is at the 
  // beginning of the list.
    return loc-1;
  }  // end previousIndex

  public void add(Object o) throws UnsupportedOperationException {
  // Inserts the specified element into the list
  // (optional operation).
    throw new UnsupportedOperationException();
  }  // end add   

  public void remove() throws UnsupportedOperationException {
  // Removes from the underlying collection the last
  // element returned by the iterator (optional
  // operation).
    throw new UnsupportedOperationException();
  }  // end remove

  public void set(Object o) throws UnsupportedOperationException {
  // Replaces the last element returned by next or
  // previous with the specified element (optional
  // operation).
    throw new UnsupportedOperationException();
  }  // end set
  
}  // end BasicListIterator