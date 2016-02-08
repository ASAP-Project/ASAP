import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;

class StreamGobbler extends Thread
{
    InputStream is;
    javax.swing.JTextArea textArea;
    String type;
    
    StreamGobbler(InputStream is, javax.swing.JTextArea textArea, String type)
    {
        this.is = is;
        this.textArea = textArea;
        this.type = type;
    }
    
    public void run()
    {
        try
        {
            InputStreamReader isr = new InputStreamReader(is);
            BufferedReader br = new BufferedReader(isr);
            String line=null;
            while ( (line = br.readLine()) != null)
                textArea.append(type+line+"\n"); 
            } catch (IOException ioe)
            {
              ioe.printStackTrace();  
            }
    }
}