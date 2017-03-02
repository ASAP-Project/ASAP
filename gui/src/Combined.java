import java.io.File;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import java.io.IOException;
import java.util.ArrayList;

public class Combined extends javax.swing.JFrame {
    
    private boolean trainAgain;
    private ArrayList<String> lastCommand;
    private File currentWorkingDirectory; 
    public Combined() {
        initComponents();
        setTrainAgain(false);
        lastCommand = new ArrayList();
        /*
        Runnable runnable = new Runnable() {
            public void run () {
                while(true) {
                    if (queryExperimentTabbedPane.getSelectedIndex() == 0) {
                        ArrayList<String> list = getTrainingCommandLineStr();
                        if (list.equals(lastCommand))
                            setTrainAgain(false);
                        else
                            setTrainAgain(true);
                    } else
                        setTrainAgain(false);
                }
            }
        };
        (new Thread(runnable)).start();
        */
        
        scapNSlider.addChangeListener(new SliderListener(scapNTextField, scapNSlider));
        scapNTextField.addKeyListener(new TextFieldListener(scapNTextField, scapNSlider));
        
        scapLValue.addChangeListener(new SliderListener(scapLTextField, scapLValue));
        scapLTextField.addKeyListener(new TextFieldListener(scapLTextField, scapLValue));
        
        burrowsNSlider.addChangeListener(new SliderListener(burrowsNTextField, burrowsNSlider));
        burrowsNTextField.addKeyListener(new TextFieldListener(burrowsNTextField, burrowsNSlider));
        
        kFoldKValueSlider.addChangeListener(new SliderListener(kFoldKValueTextField, kFoldKValueSlider));
        kFoldKValueTextField.addKeyListener(new TextFieldListener(kFoldKValueTextField, kFoldKValueSlider));
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        progressBar = new javax.swing.JProgressBar();
        progressLabel = new javax.swing.JLabel();
        testTypePanel = new javax.swing.JPanel();
        queryExperimentTabbedPane = new javax.swing.JTabbedPane();
        directoryPanel = new javax.swing.JPanel();
        trainingOutputButton = new javax.swing.JButton();
        trainingInputTextField = new javax.swing.JTextField();
        queryTipLabel = new javax.swing.JLabel();
        trainingOutputTextField = new javax.swing.JTextField();
        trainingInputButton = new javax.swing.JButton();
        testFileTextField = new javax.swing.JTextField();
        testFileButton = new javax.swing.JButton();
        testFileCheckmark = new javax.swing.JLabel();
        trainingInputCheckmark = new javax.swing.JLabel();
        trainingOutputCheckmark = new javax.swing.JLabel();
        testMethodPanel = new javax.swing.JPanel();
        testMethodTabbedPane = new javax.swing.JTabbedPane();
        defaultSplitPanel = new javax.swing.JPanel();
        defaultSplitTestDirTextField = new javax.swing.JTextField();
        defaultSplitTestDirButton = new javax.swing.JButton();
        defaultSplitTrainingDirTextField = new javax.swing.JTextField();
        defaultSplitTrainingDirButton = new javax.swing.JButton();
        defaultSplitLabel = new javax.swing.JLabel();
        defaultSplitTestDirCheckmark = new javax.swing.JLabel();
        defaultSplitTrainingDirCheckmark = new javax.swing.JLabel();
        kFoldPanel = new javax.swing.JPanel();
        kFoldKValueLabel = new javax.swing.JLabel();
        kFoldKValueSlider = new javax.swing.JSlider();
        kFoldTipLabel = new javax.swing.JLabel();
        kFoldTestDirTextField = new javax.swing.JTextField();
        kFoldTestDirButton = new javax.swing.JButton();
        kFoldTestDirCheckmark = new javax.swing.JLabel();
        kFoldKValueTextField = new javax.swing.JTextField();
        leaveOneOutPanel = new javax.swing.JPanel();
        leaveOneOutTestDirTextField = new javax.swing.JTextField();
        leaveOneOutTestDirButton = new javax.swing.JButton();
        leaveOneOutTipLabel = new javax.swing.JLabel();
        leaveOneOutTestDirCheckmark = new javax.swing.JLabel();
        experimentTipLabel = new javax.swing.JLabel();
        testTypeTipLabel = new javax.swing.JLabel();
        attMethodPanel = new javax.swing.JPanel();
        methodTabbedPane = new javax.swing.JTabbedPane();
        scapPanel = new javax.swing.JPanel();
        scapNSlider = new javax.swing.JSlider();
        scapNLabel = new javax.swing.JLabel();
        scapLLabel = new javax.swing.JLabel();
        scapLValue = new javax.swing.JSlider();
        scapTipLabel = new javax.swing.JLabel();
        scapNTextField = new javax.swing.JTextField();
        scapLTextField = new javax.swing.JTextField();
        burrowsPanel = new javax.swing.JPanel();
        jLabel8 = new javax.swing.JLabel();
        burrowsNSlider = new javax.swing.JSlider();
        tokenFileTextField = new javax.swing.JTextField();
        tokenFileButton = new javax.swing.JButton();
        burrowsTipLabel = new javax.swing.JLabel();
        tokenFileCheckmark = new javax.swing.JLabel();
        burrowsNTextField = new javax.swing.JTextField();
        attMethodTipLabel = new javax.swing.JLabel();
        runProgramButton = new javax.swing.JButton();
        openSpreadsheet = new javax.swing.JButton();
        clearBtn = new javax.swing.JButton();
        trainingWarningLabel = new javax.swing.JLabel();
        jScrollPane1 = new javax.swing.JScrollPane();
        resultsTextArea = new javax.swing.JTextArea();

        progressBar.setValue(65);

        progressLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        progressLabel.setText("Querying... (65%)");

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        addWindowStateListener(new java.awt.event.WindowStateListener() {
            public void windowStateChanged(java.awt.event.WindowEvent evt) {
                formWindowStateChanged(evt);
            }
        });

        queryExperimentTabbedPane.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                queryExperimentTabbedPaneStateChanged(evt);
            }
        });

        trainingOutputButton.setText("Browse ");
        trainingOutputButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                trainingOutputButtonActionPerformed(evt);
            }
        });

        trainingInputTextField.setText("Training input directory... ");
        trainingInputTextField.setEnabled(false);
        trainingInputTextField.setPreferredSize(new java.awt.Dimension(292, 22));
        trainingInputTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                trainingInputTextFieldActionPerformed(evt);
            }
        });
        trainingInputTextField.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                trainingInputTextFieldPropertyChange(evt);
            }
        });

        queryTipLabel.setText("<html>Select your test file and training directories below. The program will use the training input directory to determine the author of the test file. The training output directory will store files created by the training process.</html>");

        trainingOutputTextField.setText("Training output directory...");
        trainingOutputTextField.setEnabled(false);
        trainingOutputTextField.setMinimumSize(new java.awt.Dimension(292, 22));
        trainingOutputTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                trainingOutputTextFieldActionPerformed(evt);
            }
        });
        trainingOutputTextField.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                trainingOutputTextFieldPropertyChange(evt);
            }
        });

        trainingInputButton.setText("Browse ");
        trainingInputButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                trainingInputButtonActionPerformed(evt);
            }
        });

        testFileTextField.setText("Test file...");
        testFileTextField.setEnabled(false);
        testFileTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                testFileTextFieldActionPerformed(evt);
            }
        });
        testFileTextField.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                testFileTextFieldPropertyChange(evt);
            }
        });

        testFileButton.setText("Browse ");
        testFileButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                testFileButtonActionPerformed(evt);
            }
        });

        testFileCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/close.png"))); // NOI18N

        trainingInputCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/close.png"))); // NOI18N

        trainingOutputCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/close.png"))); // NOI18N

        javax.swing.GroupLayout directoryPanelLayout = new javax.swing.GroupLayout(directoryPanel);
        directoryPanel.setLayout(directoryPanelLayout);
        directoryPanelLayout.setHorizontalGroup(
            directoryPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(directoryPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(directoryPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(directoryPanelLayout.createSequentialGroup()
                        .addGroup(directoryPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(testFileCheckmark)
                            .addComponent(trainingInputCheckmark)
                            .addComponent(trainingOutputCheckmark))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(directoryPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(directoryPanelLayout.createSequentialGroup()
                                .addGroup(directoryPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(trainingInputTextField, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                    .addComponent(trainingOutputTextField, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(directoryPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(trainingInputButton, javax.swing.GroupLayout.PREFERRED_SIZE, 81, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(trainingOutputButton, javax.swing.GroupLayout.PREFERRED_SIZE, 81, javax.swing.GroupLayout.PREFERRED_SIZE)))
                            .addGroup(directoryPanelLayout.createSequentialGroup()
                                .addComponent(testFileTextField)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(testFileButton, javax.swing.GroupLayout.PREFERRED_SIZE, 81, javax.swing.GroupLayout.PREFERRED_SIZE))))
                    .addComponent(queryTipLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
                .addContainerGap())
        );
        directoryPanelLayout.setVerticalGroup(
            directoryPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(directoryPanelLayout.createSequentialGroup()
                .addGap(12, 12, 12)
                .addComponent(queryTipLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(directoryPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(directoryPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(testFileTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(testFileButton))
                    .addComponent(testFileCheckmark))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(directoryPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(trainingInputCheckmark)
                    .addGroup(directoryPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(trainingInputTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(trainingInputButton)))
                .addGroup(directoryPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(directoryPanelLayout.createSequentialGroup()
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(trainingOutputCheckmark, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, directoryPanelLayout.createSequentialGroup()
                        .addGap(8, 8, 8)
                        .addGroup(directoryPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(trainingOutputTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 22, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(trainingOutputButton))))
                .addContainerGap(68, Short.MAX_VALUE))
        );

        queryExperimentTabbedPane.addTab("Query", directoryPanel);

        testMethodTabbedPane.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                testMethodTabbedPaneStateChanged(evt);
            }
        });

        defaultSplitTestDirTextField.setText("Test directory...");
        defaultSplitTestDirTextField.setEnabled(false);

        defaultSplitTestDirButton.setText("Browse ");
        defaultSplitTestDirButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                defaultSplitTestDirButtonActionPerformed(evt);
            }
        });

        defaultSplitTrainingDirTextField.setText("Training directory...");
        defaultSplitTrainingDirTextField.setEnabled(false);

        defaultSplitTrainingDirButton.setText("Browse ");
        defaultSplitTrainingDirButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                defaultSplitTrainingDirButtonActionPerformed(evt);
            }
        });

        defaultSplitLabel.setText("<html>Queries all the files in the test directory, using the files in the training directory to determine authorship.</html>");

        defaultSplitTestDirCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/close.png"))); // NOI18N

        defaultSplitTrainingDirCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/close.png"))); // NOI18N

        javax.swing.GroupLayout defaultSplitPanelLayout = new javax.swing.GroupLayout(defaultSplitPanel);
        defaultSplitPanel.setLayout(defaultSplitPanelLayout);
        defaultSplitPanelLayout.setHorizontalGroup(
            defaultSplitPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(defaultSplitPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(defaultSplitPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(defaultSplitLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)
                    .addGroup(defaultSplitPanelLayout.createSequentialGroup()
                        .addGroup(defaultSplitPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(defaultSplitTestDirCheckmark)
                            .addComponent(defaultSplitTrainingDirCheckmark))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(defaultSplitPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(defaultSplitTestDirTextField)
                            .addComponent(defaultSplitTrainingDirTextField, javax.swing.GroupLayout.DEFAULT_SIZE, 355, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(defaultSplitPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(defaultSplitTestDirButton, javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(defaultSplitTrainingDirButton, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addContainerGap())
        );
        defaultSplitPanelLayout.setVerticalGroup(
            defaultSplitPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, defaultSplitPanelLayout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(defaultSplitLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(7, 7, 7)
                .addGroup(defaultSplitPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(defaultSplitPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(defaultSplitTestDirTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(defaultSplitTestDirButton))
                    .addComponent(defaultSplitTestDirCheckmark))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(defaultSplitPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(defaultSplitPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(defaultSplitTrainingDirButton)
                        .addComponent(defaultSplitTrainingDirTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(defaultSplitTrainingDirCheckmark))
                .addGap(74, 74, 74))
        );

        testMethodTabbedPane.addTab("Default Split", defaultSplitPanel);

        kFoldKValueLabel.setText("K-Value");

        kFoldKValueSlider.setMajorTickSpacing(4);
        kFoldKValueSlider.setMaximum(30);
        kFoldKValueSlider.setMinimum(2);
        kFoldKValueSlider.setMinorTickSpacing(1);
        kFoldKValueSlider.setPaintLabels(true);
        kFoldKValueSlider.setPaintTicks(true);
        kFoldKValueSlider.setValue(2);

        kFoldTipLabel.setText("<html>Splits the files in the test directory into k partitions, then goes through and queries the files in each one, using the others to determine authorship.</html>");

        kFoldTestDirTextField.setText("Test directory...");
        kFoldTestDirTextField.setEnabled(false);
        kFoldTestDirTextField.setPreferredSize(new java.awt.Dimension(283, 22));

        kFoldTestDirButton.setText("Browse\n");
        kFoldTestDirButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                kFoldTestDirButtonActionPerformed(evt);
            }
        });

        kFoldTestDirCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/close.png"))); // NOI18N

        javax.swing.GroupLayout kFoldPanelLayout = new javax.swing.GroupLayout(kFoldPanel);
        kFoldPanel.setLayout(kFoldPanelLayout);
        kFoldPanelLayout.setHorizontalGroup(
            kFoldPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(kFoldPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(kFoldPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(kFoldTipLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)
                    .addGroup(kFoldPanelLayout.createSequentialGroup()
                        .addGroup(kFoldPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(kFoldPanelLayout.createSequentialGroup()
                                .addComponent(kFoldKValueLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 59, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(kFoldKValueSlider, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                            .addGroup(kFoldPanelLayout.createSequentialGroup()
                                .addComponent(kFoldTestDirCheckmark)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(kFoldTestDirTextField, javax.swing.GroupLayout.DEFAULT_SIZE, 359, Short.MAX_VALUE)))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(kFoldPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(kFoldTestDirButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(kFoldKValueTextField))))
                .addContainerGap())
        );
        kFoldPanelLayout.setVerticalGroup(
            kFoldPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, kFoldPanelLayout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(kFoldTipLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(kFoldPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(kFoldPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(kFoldTestDirTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(kFoldTestDirButton))
                    .addComponent(kFoldTestDirCheckmark))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(kFoldPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(kFoldPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                        .addComponent(kFoldKValueLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(kFoldKValueSlider, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(kFoldKValueTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(85, 85, 85))
        );

        testMethodTabbedPane.addTab("K-Fold", kFoldPanel);

        leaveOneOutTestDirTextField.setText("Test directory...");
        leaveOneOutTestDirTextField.setEnabled(false);

        leaveOneOutTestDirButton.setText("Browse\n");
        leaveOneOutTestDirButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                leaveOneOutTestDirButtonActionPerformed(evt);
            }
        });

        leaveOneOutTipLabel.setText("<html>Goes through each file in the test directory, using the other files to determine authorship.</html>");

        leaveOneOutTestDirCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/close.png"))); // NOI18N

        javax.swing.GroupLayout leaveOneOutPanelLayout = new javax.swing.GroupLayout(leaveOneOutPanel);
        leaveOneOutPanel.setLayout(leaveOneOutPanelLayout);
        leaveOneOutPanelLayout.setHorizontalGroup(
            leaveOneOutPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(leaveOneOutPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(leaveOneOutPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(leaveOneOutPanelLayout.createSequentialGroup()
                        .addComponent(leaveOneOutTestDirCheckmark)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(leaveOneOutTestDirTextField)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(leaveOneOutTestDirButton))
                    .addGroup(leaveOneOutPanelLayout.createSequentialGroup()
                        .addComponent(leaveOneOutTipLabel, javax.swing.GroupLayout.DEFAULT_SIZE, 395, Short.MAX_VALUE)
                        .addGap(0, 65, Short.MAX_VALUE)))
                .addContainerGap())
        );
        leaveOneOutPanelLayout.setVerticalGroup(
            leaveOneOutPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, leaveOneOutPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(leaveOneOutTipLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGroup(leaveOneOutPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, leaveOneOutPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(leaveOneOutTestDirTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(leaveOneOutTestDirButton))
                    .addComponent(leaveOneOutTestDirCheckmark, javax.swing.GroupLayout.Alignment.TRAILING))
                .addGap(103, 103, 103))
        );

        testMethodTabbedPane.addTab("Leave One Out", leaveOneOutPanel);

        experimentTipLabel.setText("<html> Select the experiment method below. The experiment will test the program's accuracy by testing files whose authors are already known. </html>");

        javax.swing.GroupLayout testMethodPanelLayout = new javax.swing.GroupLayout(testMethodPanel);
        testMethodPanel.setLayout(testMethodPanelLayout);
        testMethodPanelLayout.setHorizontalGroup(
            testMethodPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(testMethodPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(testMethodPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(experimentTipLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)
                    .addComponent(testMethodTabbedPane, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
                .addContainerGap())
        );
        testMethodPanelLayout.setVerticalGroup(
            testMethodPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(testMethodPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(experimentTipLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(testMethodTabbedPane, javax.swing.GroupLayout.PREFERRED_SIZE, 148, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        queryExperimentTabbedPane.addTab("Experiment", testMethodPanel);

        testTypeTipLabel.setText("Select the type of test you would like to perform.");

        javax.swing.GroupLayout testTypePanelLayout = new javax.swing.GroupLayout(testTypePanel);
        testTypePanel.setLayout(testTypePanelLayout);
        testTypePanelLayout.setHorizontalGroup(
            testTypePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(testTypePanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(testTypePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(queryExperimentTabbedPane, javax.swing.GroupLayout.DEFAULT_SIZE, 510, Short.MAX_VALUE)
                    .addGroup(testTypePanelLayout.createSequentialGroup()
                        .addComponent(testTypeTipLabel)
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
        );
        testTypePanelLayout.setVerticalGroup(
            testTypePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(testTypePanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(testTypeTipLabel)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(queryExperimentTabbedPane))
        );

        methodTabbedPane.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                methodTabbedPaneStateChanged(evt);
            }
        });

        scapPanel.setMaximumSize(new java.awt.Dimension(459, 138));
        scapPanel.setMinimumSize(new java.awt.Dimension(459, 138));

        scapNSlider.setMajorTickSpacing(5);
        scapNSlider.setMaximum(25);
        scapNSlider.setMinimum(5);
        scapNSlider.setMinorTickSpacing(1);
        scapNSlider.setPaintLabels(true);
        scapNSlider.setPaintTicks(true);
        scapNSlider.setValue(6);

        scapNLabel.setText("N-Value");

        scapLLabel.setText("L-Value");

        scapLValue.setMajorTickSpacing(2000);
        scapLValue.setMaximum(10000);
        scapLValue.setMinimum(500);
        scapLValue.setMinorTickSpacing(500);
        scapLValue.setPaintLabels(true);
        scapLValue.setPaintTicks(true);
        scapLValue.setValue(2000);

        scapTipLabel.setText("<html>\nSCAP is a language-agnostic method that only compares groups of tokens in the file(s). <b>N</b> is the token length, <b>L</b> is the maxium number of tokens to store.\n</html>");

        scapNTextField.setMaximumSize(new java.awt.Dimension(96, 20));
        scapNTextField.setMinimumSize(new java.awt.Dimension(96, 20));
        scapNTextField.setPreferredSize(new java.awt.Dimension(96, 20));
        scapNTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                scapNTextFieldActionPerformed(evt);
            }
        });

        scapLTextField.setMaximumSize(new java.awt.Dimension(96, 20));
        scapLTextField.setMinimumSize(new java.awt.Dimension(96, 20));
        scapLTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                scapLTextFieldActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout scapPanelLayout = new javax.swing.GroupLayout(scapPanel);
        scapPanel.setLayout(scapPanelLayout);
        scapPanelLayout.setHorizontalGroup(
            scapPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(scapPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(scapPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(scapPanelLayout.createSequentialGroup()
                        .addGroup(scapPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                            .addComponent(scapLLabel, javax.swing.GroupLayout.DEFAULT_SIZE, 59, Short.MAX_VALUE)
                            .addComponent(scapNLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(scapPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(scapLValue, javax.swing.GroupLayout.DEFAULT_SIZE, 347, Short.MAX_VALUE)
                            .addComponent(scapNSlider, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addGap(2, 2, 2))
                    .addComponent(scapTipLabel, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(scapPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(scapLTextField, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(scapNTextField, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap())
        );
        scapPanelLayout.setVerticalGroup(
            scapPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, scapPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(scapTipLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(scapPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(scapPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                        .addComponent(scapNLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(scapNSlider, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(scapNTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(scapPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(scapLValue, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(scapLLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 26, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(scapLTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        methodTabbedPane.addTab("SCAP", scapPanel);

        jLabel8.setText("N-Value");

        burrowsNSlider.setMajorTickSpacing(5);
        burrowsNSlider.setMaximum(25);
        burrowsNSlider.setMinimum(5);
        burrowsNSlider.setMinorTickSpacing(1);
        burrowsNSlider.setPaintLabels(true);
        burrowsNSlider.setPaintTicks(true);
        burrowsNSlider.setValue(6);
        burrowsNSlider.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                burrowsNSliderPropertyChange(evt);
            }
        });

        tokenFileTextField.setText("Token File... ");
        tokenFileTextField.setEnabled(false);
        tokenFileTextField.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                tokenFileTextFieldPropertyChange(evt);
            }
        });

        tokenFileButton.setText("Browse ");
        tokenFileButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                tokenFileButtonActionPerformed(evt);
            }
        });

        burrowsTipLabel.setText("<html>\nBurrows is fast, non-language-agnostic method. <b>N</b> is the token length, the <b>Token File</b> is a file containing all relevant tokens (hence why it is not language-agnostic).\n</html>");

        tokenFileCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/close.png"))); // NOI18N

        burrowsNTextField.setPreferredSize(new java.awt.Dimension(96, 20));

        javax.swing.GroupLayout burrowsPanelLayout = new javax.swing.GroupLayout(burrowsPanel);
        burrowsPanel.setLayout(burrowsPanelLayout);
        burrowsPanelLayout.setHorizontalGroup(
            burrowsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(burrowsPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(burrowsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(burrowsTipLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)
                    .addGroup(burrowsPanelLayout.createSequentialGroup()
                        .addGroup(burrowsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(burrowsPanelLayout.createSequentialGroup()
                                .addComponent(jLabel8, javax.swing.GroupLayout.PREFERRED_SIZE, 59, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(burrowsNSlider, javax.swing.GroupLayout.DEFAULT_SIZE, 372, Short.MAX_VALUE))
                            .addGroup(burrowsPanelLayout.createSequentialGroup()
                                .addComponent(tokenFileCheckmark)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(tokenFileTextField)))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(burrowsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(tokenFileButton)
                            .addComponent(burrowsNTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addContainerGap())
        );
        burrowsPanelLayout.setVerticalGroup(
            burrowsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, burrowsPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(burrowsTipLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(burrowsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(burrowsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                        .addComponent(jLabel8, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(burrowsNSlider, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(burrowsNTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(burrowsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(tokenFileCheckmark, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, burrowsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(tokenFileTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(tokenFileButton)))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        methodTabbedPane.addTab("Burrows", burrowsPanel);

        attMethodTipLabel.setText("Select the attribution search method you would like to use.");

        runProgramButton.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        runProgramButton.setText("Query");
        runProgramButton.setEnabled(false);
        runProgramButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                runProgramButtonActionPerformed(evt);
            }
        });

        openSpreadsheet.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        openSpreadsheet.setText("Open Spreadsheet");
        openSpreadsheet.setEnabled(false);
        openSpreadsheet.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                openSpreadsheetStateChanged(evt);
            }
        });
        openSpreadsheet.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                openSpreadsheetActionPerformed(evt);
            }
        });

        clearBtn.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        clearBtn.setText("Clear Output");
        clearBtn.setMaximumSize(new java.awt.Dimension(95, 31));
        clearBtn.setMinimumSize(new java.awt.Dimension(95, 31));
        clearBtn.setPreferredSize(new java.awt.Dimension(135, 34));
        clearBtn.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                clearBtnMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout attMethodPanelLayout = new javax.swing.GroupLayout(attMethodPanel);
        attMethodPanel.setLayout(attMethodPanelLayout);
        attMethodPanelLayout.setHorizontalGroup(
            attMethodPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(attMethodPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(attMethodTipLabel)
                .addGap(0, 0, Short.MAX_VALUE))
            .addGroup(attMethodPanelLayout.createSequentialGroup()
                .addGroup(attMethodPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(attMethodPanelLayout.createSequentialGroup()
                        .addComponent(runProgramButton, javax.swing.GroupLayout.PREFERRED_SIZE, 149, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(openSpreadsheet, javax.swing.GroupLayout.PREFERRED_SIZE, 145, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(clearBtn, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(attMethodPanelLayout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(methodTabbedPane)))
                .addContainerGap())
        );
        attMethodPanelLayout.setVerticalGroup(
            attMethodPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(attMethodPanelLayout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(attMethodTipLabel)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(methodTabbedPane, javax.swing.GroupLayout.PREFERRED_SIZE, 193, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(attMethodPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(runProgramButton, javax.swing.GroupLayout.PREFERRED_SIZE, 34, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(openSpreadsheet, javax.swing.GroupLayout.PREFERRED_SIZE, 34, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(clearBtn, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
        );

        trainingWarningLabel.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/warning.png"))); // NOI18N
        trainingWarningLabel.setText("<html> Warning: Training has to be completed before the test can begin. The test will take some extra time to complete. </html>");

        resultsTextArea.setEditable(false);
        resultsTextArea.setColumns(20);
        resultsTextArea.setRows(5);
        resultsTextArea.setMinimumSize(new java.awt.Dimension(100, 100));
        jScrollPane1.setViewportView(resultsTextArea);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(testTypePanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(attMethodPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addComponent(jScrollPane1))
                .addContainerGap())
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(trainingWarningLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 593, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(249, 249, 249))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(testTypePanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(attMethodPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(trainingWarningLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 203, Short.MAX_VALUE)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void defaultSplitTestDirButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_defaultSplitTestDirButtonActionPerformed
        try
        {
            String filename = openDirectory();
            defaultSplitTestDirTextField.setText(filename);
            defaultSplitTestDirCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/checkmark.png")));
        }
        catch(Exception e)
        {
            JOptionPane.showMessageDialog(null,"Please specify the Path");
        }
        queryExperimentButtonUnlock();
    }//GEN-LAST:event_defaultSplitTestDirButtonActionPerformed

    private void defaultSplitTrainingDirButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_defaultSplitTrainingDirButtonActionPerformed
        try
        {
            String filename = openDirectory();
            defaultSplitTrainingDirTextField.setText(filename);
            defaultSplitTrainingDirCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/checkmark.png")));
        }
        catch(Exception e)
        {
            JOptionPane.showMessageDialog(null,"Please specify the Path");
        }
        queryExperimentButtonUnlock();
    }//GEN-LAST:event_defaultSplitTrainingDirButtonActionPerformed

    private void kFoldTestDirButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_kFoldTestDirButtonActionPerformed
        try
        {
            String filename = openDirectory();
            kFoldTestDirTextField.setText(filename);
            kFoldTestDirCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/checkmark.png")));
        }
        catch(Exception e)
        {
            JOptionPane.showMessageDialog(null,"Please specify the Path");
        }
        queryExperimentButtonUnlock();
    }//GEN-LAST:event_kFoldTestDirButtonActionPerformed

    private void leaveOneOutTestDirButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_leaveOneOutTestDirButtonActionPerformed
        try
        {
            String filename = openDirectory();
            leaveOneOutTestDirTextField.setText(filename);
            leaveOneOutTestDirCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/checkmark.png")));
        }

        catch(Exception e)
        {
            JOptionPane.showMessageDialog(null,"Please specify the Path");
        }
        queryExperimentButtonUnlock();
    }//GEN-LAST:event_leaveOneOutTestDirButtonActionPerformed

    private ArrayList<String> getTrainingCommandLineStr() {
        int currentMethod = methodTabbedPane.getSelectedIndex();
        int currentExpType = testMethodTabbedPane.getSelectedIndex();
        boolean generateSpreadsheet = true;
        String [] methods = {"scap","burrows"};
        ArrayList<String> list = new ArrayList<>();
        
        list.add("-train");
        list.add("-"+methods[currentMethod]);
        list.add("-inputdir="+trainingInputTextField.getText());
        list.add("-outputdir="+trainingOutputTextField.getText());

        if (currentMethod == 1) { //burrows
            list.add("-n="+burrowsNSlider.getValue());
            list.add("-tokenfile="+tokenFileTextField.getText());
        }
        
        //list.add(0, "perl");
        //list.add(1, "Asap.pl");
        //list.add("-verbose");
        
        return list;
    }
    
    private boolean checkFileTextInput() //TODO scap and burrows pane need to be seperate in check
    { 
        if(methodTabbedPane.getSelectedIndex() == 0 && scapNSlider.getValue() != 0 && queryExperimentPaneFileCheck())
            return true;
        if(methodTabbedPane.getSelectedIndex() == 1 && burrowsNSlider.getValue() != 0 && !tokenFileTextField.getText().isEmpty() && !tokenFileTextField.getText().equals("Token File... ") && queryExperimentPaneFileCheck())
            return true;
        return false;     
    }
    
    private boolean queryExperimentPaneFileCheck()
    {
        if(queryExperimentTabbedPane.getSelectedIndex() == 0 && !testFileTextField.getText().isEmpty() && !testFileTextField.getText().equals("Test File...") && 
                    !trainingInputTextField.getText().isEmpty() && !trainingInputTextField.getText().equals("Training input directory...") && 
                    !trainingOutputTextField.getText().isEmpty() && !trainingOutputTextField.getText().equals("Training output directory..."))
            return true;
        else if(queryExperimentTabbedPane.getSelectedIndex() == 1)
        {
            if(testMethodTabbedPane.getSelectedIndex() == 0 && !defaultSplitTestDirTextField.getText().isEmpty() && !defaultSplitTestDirTextField.getText().equals("Test directory...") &&
                    !defaultSplitTrainingDirTextField.getText().isEmpty() && !defaultSplitTrainingDirTextField.getText().equals("Training directory..."))
                return true;
            else if(testMethodTabbedPane.getSelectedIndex() == 1 && !kFoldTestDirTextField.getText().isEmpty() && !kFoldTestDirTextField.getText().equals("Test directory..."))
                return true;
            else if(testMethodTabbedPane.getSelectedIndex() == 2 && !leaveOneOutTestDirTextField.getText().isEmpty() && !leaveOneOutTestDirTextField.getText().equals("Test directory..."))
                return true;
        }
        return false;
    }
    
    private void runProgramButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_runProgramButtonActionPerformed
        runProgramButton.setEnabled(false);
        Runnable runnable = new Runnable() {
            public void run () {
                int currentMethod = methodTabbedPane.getSelectedIndex();
                int currentExpType = testMethodTabbedPane.getSelectedIndex();
                boolean generateSpreadsheet = true;
                String [] methods = {"scap","burrows"};
                ArrayList<String> list = new ArrayList<>();
                
                openSpreadsheet.setEnabled(false);
                
                if (queryExperimentTabbedPane.getSelectedIndex() == 0) {
                        lastCommand = getTrainingCommandLineStr();
                        resultsTextArea.append("Training..."+"\n");
                        executeCommand(lastCommand);
                    
                    
                    list = new ArrayList<>();
                    list.add("-query");
                    list.add("-"+methods[currentMethod]);
                    list.add("-inputdir="+trainingOutputTextField.getText());
                    list.add("-doc="+testFileTextField.getText());
                    
                    if (currentMethod == 0) { //scap
                        list.add("-n="+scapNSlider.getValue());
                        list.add("-L="+scapLValue.getValue());
                    }
                    
                    if (generateSpreadsheet)
                        list.add("-report=results.xls");
                    
                    resultsTextArea.append("Querying..."+"\n");
                    executeCommand(list);
                } else {
                    list = new ArrayList();
                    list.add("-experiment");
                    list.add("-"+methods[currentMethod]);
                    
                    if (currentExpType == 0) { //default split
                        list.add("-testdir="+defaultSplitTestDirTextField.getText());
                        list.add("-trainingdir="+defaultSplitTrainingDirTextField.getText());
                    } else if (currentExpType == 1) { //k fold
                        list.add("-inputdir="+kFoldTestDirTextField.getText());
                        list.add("-k="+kFoldKValueSlider.getValue());
                    } else // leave one out
                        list.add("-inputdir="+leaveOneOutTestDirTextField.getText());
                    
                    if (currentMethod == 0) { //scap
                        list.add("-n="+scapNSlider.getValue());
                        list.add("-L="+scapLValue.getValue());
                    } else { //burrows
                        list.add("-n="+burrowsNSlider.getValue());
                        list.add("-tokenfile="+tokenFileTextField.getText());
                    }
                    
                    if (generateSpreadsheet)
                        list.add("-report=results.xls");
                    
                    resultsTextArea.append("Experiment..."+"\n");
                    executeCommand(list);
                }
                runProgramButton.setEnabled(true);
                openSpreadsheet.setEnabled(true);
            }
        };
        (new Thread(runnable)).start();
    }//GEN-LAST:event_runProgramButtonActionPerformed

    private void tokenFileButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_tokenFileButtonActionPerformed
        try
        {
            String filename=openFile();
            tokenFileTextField.setText(filename);
            tokenFileCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/checkmark.png")));
        }
        catch(Exception e)
        {
            JOptionPane.showMessageDialog(null,"Please specify the Path");
        } 
        queryExperimentButtonUnlock();
    }//GEN-LAST:event_tokenFileButtonActionPerformed

    private void testFileButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_testFileButtonActionPerformed

        try
        {
            String filename = openFile();
            testFileTextField.setText(filename);
            testFileCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/checkmark.png")));
        }
        catch(Exception e)
        {
            JOptionPane.showMessageDialog(null,"Please specify the Path");
        }
        queryExperimentButtonUnlock();
    }//GEN-LAST:event_testFileButtonActionPerformed

    private void testFileTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_testFileTextFieldActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_testFileTextFieldActionPerformed

    private void trainingInputButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_trainingInputButtonActionPerformed
        try
        {
            String filename = openDirectory();
            trainingInputTextField.setText(filename);
            trainingInputCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/checkmark.png")));
        }
        catch(Exception e)
        {
            JOptionPane.showMessageDialog(null,"Please specify the Path");
        }
        queryExperimentButtonUnlock();
    }//GEN-LAST:event_trainingInputButtonActionPerformed

    private void trainingOutputTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_trainingOutputTextFieldActionPerformed
       
    }//GEN-LAST:event_trainingOutputTextFieldActionPerformed

    private void trainingInputTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_trainingInputTextFieldActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_trainingInputTextFieldActionPerformed

    private void trainingOutputButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_trainingOutputButtonActionPerformed
        try
        {
            String filename = openDirectory();
            trainingOutputTextField.setText(filename);
            trainingOutputCheckmark.setIcon(new javax.swing.ImageIcon(getClass().getResource("/guisample/checkmark.png")));
        }
        catch(Exception e)
        {
            JOptionPane.showMessageDialog(null,"Please specify the Path");
        }
        queryExperimentButtonUnlock();
    }//GEN-LAST:event_trainingOutputButtonActionPerformed

    private void openSpreadsheetActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_openSpreadsheetActionPerformed

        try
        {
            java.awt.Desktop.getDesktop().open(new File("results.xls"));           
        }
        catch(IOException e)
        {
            JOptionPane.showMessageDialog(null,"Error");
        }
    }//GEN-LAST:event_openSpreadsheetActionPerformed

    private void queryExperimentButtonUnlock()
    {
        runProgramButton.setEnabled(checkFileTextInput());
    }
    
    private void queryExperimentTabbedPaneStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_queryExperimentTabbedPaneStateChanged
        if (queryExperimentTabbedPane.getSelectedIndex() == 0)
            runProgramButton.setText("Query");
        else
            runProgramButton.setText("Experiment");
         queryExperimentButtonUnlock();
    }//GEN-LAST:event_queryExperimentTabbedPaneStateChanged

    private void tokenFileTextFieldPropertyChange(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_tokenFileTextFieldPropertyChange
        //setTrainAgain(true);
    }//GEN-LAST:event_tokenFileTextFieldPropertyChange

    private void burrowsNSliderPropertyChange(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_burrowsNSliderPropertyChange
        //setTrainAgain(true);
    }//GEN-LAST:event_burrowsNSliderPropertyChange

    private void testFileTextFieldPropertyChange(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_testFileTextFieldPropertyChange
        //setTrainAgain(true);
    }//GEN-LAST:event_testFileTextFieldPropertyChange

    private void trainingInputTextFieldPropertyChange(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_trainingInputTextFieldPropertyChange
        //setTrainAgain(true);
    }//GEN-LAST:event_trainingInputTextFieldPropertyChange

    private void trainingOutputTextFieldPropertyChange(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_trainingOutputTextFieldPropertyChange
        //setTrainAgain(true);
    }//GEN-LAST:event_trainingOutputTextFieldPropertyChange

    private void formWindowStateChanged(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowStateChanged
        
    }//GEN-LAST:event_formWindowStateChanged

    private void scapLTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_scapLTextFieldActionPerformed

    }//GEN-LAST:event_scapLTextFieldActionPerformed

    private void scapNTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_scapNTextFieldActionPerformed

    }//GEN-LAST:event_scapNTextFieldActionPerformed

    private void openSpreadsheetStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_openSpreadsheetStateChanged

    }//GEN-LAST:event_openSpreadsheetStateChanged

    private void clearBtnMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_clearBtnMouseClicked
        resultsTextArea.setText("");
    }//GEN-LAST:event_clearBtnMouseClicked

    private void methodTabbedPaneStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_methodTabbedPaneStateChanged
        queryExperimentButtonUnlock();
    }//GEN-LAST:event_methodTabbedPaneStateChanged

    private void testMethodTabbedPaneStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_testMethodTabbedPaneStateChanged
        queryExperimentButtonUnlock();
    }//GEN-LAST:event_testMethodTabbedPaneStateChanged

    
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Windows".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Combined.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Combined.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Combined.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Combined.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                Combined c = new Combined();
                c.setVisible(true);
            }
        });
    }
    
    public void executeCommand(ArrayList<String> list) {
        try {
            // fill a string array with the command line arguments
            //String installDir = System.getenv("ASAPLIB");
            String [] args = new String [list.size() + 3];
            list.add(0, "perl");
            list.add(1,System.getProperty("user.dir") + "/Asap.pl");
            list.add("-verbose");
            list.toArray(args);
            
            String outPut = "";
            for(int i = 0; i< args.length; i++)
                    outPut += args[i] +" ";
            
            //for(int i = 0; i < args.length; i++)
                //resultsTextArea.append(args[i]+" ");
            resultsTextArea.append("\n");
            resultsTextArea.append("Executing: " + outPut + "\n");
            
            // run the process and intercept its output
            //ProcessBuilder builder = new ProcessBuilder(args);
            //final Process process = builder.start();
            
            Process process = Runtime.getRuntime().exec(args);
 
            StreamGobbler errorGobbler = new StreamGobbler(process.getErrorStream(),resultsTextArea,"ERROR: ");
            StreamGobbler inputGobbler = new StreamGobbler(process.getInputStream(),resultsTextArea,"");
            
            inputGobbler.start();
            errorGobbler.start();

        } catch (Throwable t) {
        }
    }
    
    public String openDirectory() {
        JFileChooser chooser = new JFileChooser();
        File workingDirectory = new File(System.getProperty("user.dir"));
        chooser.setCurrentDirectory(workingDirectory);
        chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        chooser.showOpenDialog(null);
        File f1=chooser.getSelectedFile();
        return f1.getAbsolutePath();
    }
    
    public String openFile() {
        JFileChooser chooser=new JFileChooser();
        File workingDirectory = new File(System.getProperty("user.dir"));
        chooser.setCurrentDirectory(workingDirectory);
        chooser.showOpenDialog(null);
        File f=chooser.getSelectedFile();
        return f.getAbsolutePath();
    }
    
    public void setTrainAgain(boolean t) {
        trainAgain = t;
        trainingWarningLabel.setVisible(t);
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel attMethodPanel;
    private javax.swing.JLabel attMethodTipLabel;
    private javax.swing.JSlider burrowsNSlider;
    private javax.swing.JTextField burrowsNTextField;
    private javax.swing.JPanel burrowsPanel;
    private javax.swing.JLabel burrowsTipLabel;
    private javax.swing.JButton clearBtn;
    private javax.swing.JLabel defaultSplitLabel;
    private javax.swing.JPanel defaultSplitPanel;
    private javax.swing.JButton defaultSplitTestDirButton;
    private javax.swing.JLabel defaultSplitTestDirCheckmark;
    private javax.swing.JTextField defaultSplitTestDirTextField;
    private javax.swing.JButton defaultSplitTrainingDirButton;
    private javax.swing.JLabel defaultSplitTrainingDirCheckmark;
    private javax.swing.JTextField defaultSplitTrainingDirTextField;
    private javax.swing.JPanel directoryPanel;
    private javax.swing.JLabel experimentTipLabel;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JLabel kFoldKValueLabel;
    private javax.swing.JSlider kFoldKValueSlider;
    private javax.swing.JTextField kFoldKValueTextField;
    private javax.swing.JPanel kFoldPanel;
    private javax.swing.JButton kFoldTestDirButton;
    private javax.swing.JLabel kFoldTestDirCheckmark;
    private javax.swing.JTextField kFoldTestDirTextField;
    private javax.swing.JLabel kFoldTipLabel;
    private javax.swing.JPanel leaveOneOutPanel;
    private javax.swing.JButton leaveOneOutTestDirButton;
    private javax.swing.JLabel leaveOneOutTestDirCheckmark;
    private javax.swing.JTextField leaveOneOutTestDirTextField;
    private javax.swing.JLabel leaveOneOutTipLabel;
    private javax.swing.JTabbedPane methodTabbedPane;
    private javax.swing.JButton openSpreadsheet;
    private javax.swing.JProgressBar progressBar;
    private javax.swing.JLabel progressLabel;
    private javax.swing.JTabbedPane queryExperimentTabbedPane;
    private javax.swing.JLabel queryTipLabel;
    private javax.swing.JTextArea resultsTextArea;
    private javax.swing.JButton runProgramButton;
    private javax.swing.JLabel scapLLabel;
    private javax.swing.JTextField scapLTextField;
    private javax.swing.JSlider scapLValue;
    private javax.swing.JLabel scapNLabel;
    private javax.swing.JSlider scapNSlider;
    private javax.swing.JTextField scapNTextField;
    private javax.swing.JPanel scapPanel;
    private javax.swing.JLabel scapTipLabel;
    private javax.swing.JButton testFileButton;
    private javax.swing.JLabel testFileCheckmark;
    private javax.swing.JTextField testFileTextField;
    private javax.swing.JPanel testMethodPanel;
    private javax.swing.JTabbedPane testMethodTabbedPane;
    private javax.swing.JPanel testTypePanel;
    private javax.swing.JLabel testTypeTipLabel;
    private javax.swing.JButton tokenFileButton;
    private javax.swing.JLabel tokenFileCheckmark;
    private javax.swing.JTextField tokenFileTextField;
    private javax.swing.JButton trainingInputButton;
    private javax.swing.JLabel trainingInputCheckmark;
    private javax.swing.JTextField trainingInputTextField;
    private javax.swing.JButton trainingOutputButton;
    private javax.swing.JLabel trainingOutputCheckmark;
    private javax.swing.JTextField trainingOutputTextField;
    private javax.swing.JLabel trainingWarningLabel;
    // End of variables declaration//GEN-END:variables
}