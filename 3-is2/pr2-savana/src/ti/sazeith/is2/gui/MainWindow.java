package ti.sazeith.is2.gui;

import java.awt.BorderLayout;
import java.awt.GridLayout;

import javax.swing.*;

public class MainWindow extends JFrame {
	public JMenu file;
	public JMenuItem newGame;
	public JMenuItem exit;
	public JMenuItem load;
	public JMenuItem save;

	// Menu distasters
	public JMenu disasters;
	public JMenuItem drought;
	public JMenuItem deluge;
	public JMenuItem epidemy;
	
	// Panel Resumen
	public JPanel resumen;
	public JLabel date;
	public JLabel grass;
	public JLabel rain;
	public JLabel gazelles;
	public JLabel lions;
	public JLabel zebras;
	public JLabel leopards;
	public JLabel disasterType;
	
	// Panel Actions
	public JPanel actions;
	public JButton nextDay;
	public JButton details;

	public MainWindow() {
		setTitle("Savanna");
		setSize(400, 300);

		JMenu file = new JMenu("File");

		newGame = new JMenuItem("New game");
		load = new JMenuItem("Load");
		save = new JMenuItem("Save");
		exit = new JMenuItem("Exit");
		file.add(newGame);
		file.add(load);
		file.add(save);
		file.add(exit);
		
		disasters = new JMenu("Disasters");
		drought = new JMenuItem("Drought");
		deluge = new JMenuItem("Deluge");
		epidemy = new JMenuItem("Epidemy");
		disasters.add(drought);
		disasters.add(deluge);
		disasters.add(epidemy);

		JMenuBar bar = new JMenuBar();
		bar.add(file);
		bar.add(disasters);
		setJMenuBar(bar);
		

		
		
		// Resumen Panel
		resumen = new JPanel();
		resumen.setLayout(new GridLayout(9,2));
		
		date = new JLabel("---");
		grass = new JLabel("---");
		rain = new JLabel("---");
		disasterType = new JLabel("---");
		gazelles = new JLabel("---");
		lions = new JLabel("---");
		zebras = new JLabel("---");
		leopards = new JLabel("---");
		
		resumen.add(new JLabel("Date"));
		resumen.add(date);
		resumen.add(new JLabel("Grass"));
		resumen.add(grass);
		resumen.add(new JLabel("Rain"));
		resumen.add(rain);
		resumen.add(new JLabel("Disaster Type"));
		resumen.add(disasterType);
		resumen.add(new JLabel(""));
		resumen.add(new JLabel(""));
		resumen.add(new JLabel("Gazelles"));
		resumen.add(gazelles);
		resumen.add(new JLabel("Lions"));
		resumen.add(lions);
		resumen.add(new JLabel("Zebras"));
		resumen.add(zebras);
		resumen.add(new JLabel("Leopards"));
		resumen.add(leopards);

		add(resumen, BorderLayout.CENTER);

		// Actions Panel
		actions = new JPanel();
		
		nextDay = new JButton("Next Day");
		details = new JButton("Details");
		actions.add(nextDay);
		actions.add(details);
		
		add(actions, BorderLayout.SOUTH);
	}
}
