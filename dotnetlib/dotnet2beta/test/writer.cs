// csc -t:exe writer.cs

using System;
using System.IO;
class MyStream 
{
    private const string FILE_NAME = "Test.data";
    public static void Main(String[] args) 
    {
        // Create the new, empty data file.
        FileStream fs = new FileStream(FILE_NAME, FileMode.Create);
        // Create the writer for data.
        BinaryWriter w = new BinaryWriter(fs);
        // Write data to Test.data.
        for (int i = 0; i < 4; i++) 
        {
            w.Write( (sbyte) i);
        }
        w.Close();
        fs.Close();
        // Create the reader for data.
        fs = new FileStream(FILE_NAME, FileMode.Open, FileAccess.Read);
        BinaryReader r = new BinaryReader(fs);
        // Read data from Test.data.
        for (int i = 0; i < fs.Length; i++) 
        {
            Console.WriteLine(r.ReadSByte());
        }
        w.Close();
    }
}
