package ti.sazeith.is2.controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Calendar;

import ti.sazeith.is2.gui.*;
import ti.sazeith.is2.savana.*;
import ti.sazeith.is2.savana.specie.*;

public class Main {
	private static Savanna savanna;
	private static MainWindow view;

	public static void main(String[] args) {
		view = new MainWindow();
		view.nextDay.setEnabled(false);
		view.details.setEnabled(false);
		view.setVisible(true);

		view.newGame.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				savanna = new Savanna();
				view.nextDay.setEnabled(true);
				view.details.setEnabled(true);
				Main.renderView();
			}
		});

		view.nextDay.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				savanna.doTick();
				Main.renderView();
			}
		});
	}

	public static void renderView() {
		Calendar date = savanna.getDate();
		view.date.setText(String.format("%02d/%02d/%04d", date.get(Calendar.DATE), date.get(Calendar.MONTH) + 1, date.get(Calendar.YEAR)));
		view.grass.setText(Integer.toString(savanna.getGrass()));
		view.rain.setText(savanna.getRain().toString());

		AnimalSpeciesMap animals = savanna.getAnimals();
		view.gazelles.setText(Integer.toString(animals.get(Gazelle.class).size()));
		view.zebras.setText(Integer.toString(animals.get(Zebra.class).size()));
		view.leopards.setText(Integer.toString(animals.get(Leopard.class).size()));
		view.lions.setText(Integer.toString(animals.get(Lion.class).size()));
	}
}
