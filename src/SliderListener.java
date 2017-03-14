import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

class SliderListener implements ChangeListener {    
    public javax.swing.JTextField text;
    public javax.swing.JSlider slider;
    
    SliderListener(javax.swing.JTextField txt, javax.swing.JSlider slide){
        text = txt; 
        slider = slide; 
    }
    
    @Override
    public void stateChanged(ChangeEvent e) {
        text.setText(String.valueOf(slider.getValue()));
        
        slider.setEnabled(true);
   
        int testValTF = Integer.parseInt(text.getText());
        
    }
}