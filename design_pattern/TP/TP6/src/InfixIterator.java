

import java.util.Iterator;

public class InfixIterator<V> implements Iterator<V> {
    private Tree<V> next;
    public void Infix(Tree<V> root) {
        if(root.getLeft() != null){
            this.next = root.getLeft();
        }else{
            this.next = root;
        }
    }

    @Override
    public boolean hasNext() {
        return next != null;
    }

    @Override
    public V next(){
        System.out.println(this.next);
        V currentNode = (V) this.next.getValue();
        if(currentNode == null){
            return null;
        }
        if(this.next.getLeft() != null){
            this.next = this.next.getLeft();
            return currentNode;
        }else if(this.next.getRight() != null){
            this.next = this.next.getRight();
            return currentNode;
        }
        else if (next.getParent().getRight() == this.next) {
        next = null;
        return (currentNode);
        }
        return currentNode;
    }
}

