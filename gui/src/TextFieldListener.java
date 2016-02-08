import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

class TextFieldListener extends KeyAdapter {   

    public javax.swing.JTextField text;
    public javax.swing.JSlider slider;
    
    TextFieldListener(javax.swing.JTextField txt, javax.swing.JSlider slide){
        text = txt; 
        slider = slide;
        
        text.setText(slider.getValue() + "");
    }
    
    @Override
    public void keyReleased(KeyEvent ke) {
        String typed = text.getText();
        slider.setValue(0);
        if(!typed.matches("\\d+") || typed.length() > 3) {
                return;
        }
        
        text.setEnabled(true);
        int testValTF = Integer.parseInt(text.getText());
        if((testValTF < slider.getMinimum()) || (testValTF > slider.getMaximum())){
            slider.setEnabled(false);
            //text.setEnabled(true);
        } else {
            slider.setEnabled(true);
            int value = Integer.parseInt(typed);
            slider.setValue(value);
            //text.setEnabled(false);
        }
    }
}