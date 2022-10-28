package tdJava;

import javax.swing.*;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.*;

/**
 * @author PHAM Vu Hoang Anh
 *         <p>
 *         Java class with 1 JTextArea and 1 JPanel that contains 3 JButtons
 *         <p>
 *         JTextArea is in the center of the JFrame JPanel is in the South of
 *         the JFrame 
 *         <p>
 *         Button1 adds a line of text to JTextArea 
 *         <p>
 *         Button2 adds a line of text to JTextArea 
 *         <p>
 *         Button3 terminate the program
 */
public class fenetre extends JFrame implements ActionListener {
    JTextArea area;
    JButton   addText1;
    JButton   addText2;
    JButton   terminer;

    // Attributs supl�mentaires pour la connection et fonctionnement Client-Server 
    Client client;
	JTextField target = new JTextField();

    /**
     * Version of this class = 1
     */
    private static final long serialVersionUID = 1L;

    /**
     * Class constructor
     * <p>
     * Add a JPanel to contain the buttons
     * <p>
     * and a JScrollPane to scroll through the text area
     */
    public fenetre(Client clnt, String msg) {
    	// Lier client
    	client = clnt;
    	
        // Déclarer des nouvelles attributs 
                    area    = new JTextArea(msg, 20, 10);
        JPanel      panl    = new JPanel(new GridLayout(3,1));
        JScrollPane scroll  = new JScrollPane(area);
        JMenuBar    menuBar = new JMenuBar();
        JMenu       menu    = new JMenu("Menu");
        JToolBar    toolBar = new JToolBar();
        scroll.setViewportView(area);
        scroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        
        // Ajouter les attributs à la fenêtre principale
        add(scroll);
        add(toolBar, BorderLayout.NORTH);
        add(panl, BorderLayout.SOUTH);
        panl.add(addText1 = new JButton("Button1"));
        panl.add(addText2 = new JButton("Button2"));
        panl.add(terminer = new JButton("Terminer"));
        panl.add(target,BorderLayout.SOUTH);
        this.setJMenuBar(menuBar);
        menuBar.add(menu);

        // Faire fonctionner les boutons
        addText1.addActionListener(this);
        addText2.addActionListener(this);
        terminer.addActionListener(this);

        // Ajouter des "actions" à toolBar et menu  
        toolBar.add(new but1Listener("Find"));
        toolBar.add(new but2Listener("Play"));
        toolBar.add(new but3Listener("Quit"));
        menu.add(new but1Listener("Find"));
        menu.add(new but2Listener("Play"));
        menu.add(new but3Listener("Quit"));
        
        // Réglages de la fenêtre
        this.setPreferredSize( new Dimension(300, 500) );
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    /**
     * Listen to the action of buttons
     * @see fenetre
     */
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == addText1)
            area.append("Button1 clicked !\n");
        else if (e.getSource() == addText2)
            area.append("Button2 clicked !\n");
        else if (e.getSource() == terminer)
            System.exit(0);
    }
    
    private class but1Listener extends AbstractAction {
        private static final long serialVersionUID = 1L;
        
        public but1Listener ( String name ) {
            super(name);
        }
        
        @Override
        public void actionPerformed(ActionEvent e) {
        	String media    = target.getText();
        	String response = client.send("find" + media);
            area.append(response + "\n");
        }
    }
    
    private class but2Listener extends AbstractAction {
        private static final long serialVersionUID = 1L;

        public but2Listener ( String name ) {
            super(name);
        }
        
        @Override
        public void actionPerformed(ActionEvent e) {
        	String media    = target.getText();
        	String response = client.send("play" + media);
            area.append(response + "\n");
        }
    }
    
    private class but3Listener extends AbstractAction {
        private static final long serialVersionUID = 1L;

        public but3Listener ( String name ) {
            super(name);
        }
        
        @Override
        public void actionPerformed(ActionEvent e) {
        	String response = client.send("quit");
            area.append(response + "\n");
            System.exit(0);
        }
    }

    public static void main(String[] args) {
    	String DEFAULT_HOST = "localhost";
    	int    DEFAULT_PORT = 3331;
        // TODO Auto-generated method stub
    	Client client = null;
/*    	try {
    		client = new Client(DEFAULT_HOST, DEFAULT_PORT);
    	}
    	catch ( Exception e) {
    		System.err.println("Errow when creating client !");
    		System.exit(1);
    	}*/
    	String msg = "Connecting to " + DEFAULT_HOST + " at port " + DEFAULT_PORT+"\n"; 
        new fenetre(client, msg);
    }
}
