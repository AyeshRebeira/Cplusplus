
/*Ayesh Rebeira 
  Assignment 2 
  11/22/2021
*/
package wordprocessor;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.FileWriter;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;


public class WordProcessor extends JFrame implements ActionListener {
    JPanel cardPanel, cd1, cd2;
    CardLayout cards;
    GridLayout gribl;
    JLabel userName, password;
    JTextField userNameField, passwordField;
    JButton ok, cancel;
    JMenu file;
    JMenuItem save, exit;
    JTextArea card2textArea;
    JScrollPane scrollPane;
    JMenuBar menuBar;
    BorderLayout bl;
    public WordProcessor(){
        super("My Word Processor - AyeshRebeira");
        setSize(260,110);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLookAndFeel();
        cards = new CardLayout();
        cardPanel = new JPanel();
        cardPanel.setLayout(cards);
        //First card
        cd1 = new JPanel();
        gribl = new GridLayout(3,2);
        cd1.setLayout(gribl);
        userName = new JLabel("User Name:");
        password = new JLabel("Password:");
        userNameField = new JTextField();
        passwordField = new JTextField();
        ok = new JButton("OK");
        cancel = new JButton("cancel");
        cd1.add(userName);
        cd1.add(userNameField);
        cd1.add(password);
        cd1.add(passwordField);
        cd1.add(ok);
        cd1.add(cancel);
        ok.addActionListener(this);
        cancel.addActionListener(this);
        cd2 = new JPanel();
        menuBar = new JMenuBar();
        file = new JMenu("File");
        menuBar.add(file);
        save = new JMenuItem("Save");
        exit = new JMenuItem("Exit");
        file.add(save);
        save.addActionListener(this);
        exit.addActionListener(this);
        file.addSeparator();
        file.add(exit);
        card2textArea = new JTextArea(400,400);
        card2textArea.setEditable(true);
        scrollPane = new JScrollPane(card2textArea);
        bl = new BorderLayout();
        cd2.setLayout(bl);
        cd2.add(menuBar, BorderLayout.NORTH);
        cd2.add(scrollPane, BorderLayout.CENTER);
        cardPanel.add(cd1, "CARD1");
        cardPanel.add(cd2, "CARD2");
        add(cardPanel);
        setVisible(true);

}

public void actionPerformed(ActionEvent event) {
       Object source = event.getSource();
       if (source == ok) {
           
           cards.show(cardPanel, "CARD2");
           setResizable(true);
           setSize(700,600);
           
       }
       if (source == save){
           try(FileWriter myWriter = new FileWriter("myFile.txt")){
               myWriter.write(card2textArea.getText());
               System.out.println("Written to file");
           } catch(IOException ex){
               Logger.getLogger(WordProcessor.class.getName()).log(Level.SEVERE, null, ex);
           }
       }
       if (source == exit){
           System.exit(0);
       }
}
private static void setLookAndFeel() {
       try {
            UIManager.setLookAndFeel(
                "javax.swing.plaf.nimbus.NimbusLookAndFeel"
            );
       } catch (Exception exc) {
            System.err.println(exc);
       }
   }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        WordProcessor sah = new WordProcessor();
        // TODO code application logic here
    }
    
}
