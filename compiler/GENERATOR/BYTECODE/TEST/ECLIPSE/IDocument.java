package org.eclipse.jface.text;

public interface IDocument {
    public String get();
    public int    getLineOffset();
    public void   replace(int x, int y, String s);
}
