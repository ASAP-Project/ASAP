public interface BasicListInterface { 
  public int size();
  public boolean isEmpty();
  public void removeAll();
  public Object get(int index)
                throws ListIndexOutOfBoundsException;
}  // end BasicListInterface
