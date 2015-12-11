package ti.sazeith.is2.pr1.iface;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import ti.sazeith.is2.pr1.serialization.DataReader;

public class Menu {
	private List<Entry> entries = new ArrayList<>();

	public Menu(Entry ... entries) {
		this(Arrays.asList(entries));
	}

	public Menu(List<Entry> entries) {
		this.entries = entries;
	}

	public void display() {
		@SuppressWarnings("resource")
		DataReader rd = new DataReader(System.in);

		while (true) {
			int i = 1;
			for (Entry entry : entries) {
				System.out.println(String.format("%2d - %s", i, entry.title));
				i++;
			}
			System.out.print(">>> ");

			int c;
			try {
				c = rd.readInt();
			} catch (NumberFormatException e) {
				System.out.println("Opción no válida");
				continue;
			} catch (IOException e) {
				try {
					rd.close();
				} catch (IOException e1) { }
				return;
			}

			if (c >= 1 && c <= entries.size()) {
				entries.get(c - 1).runnable.run();
				break;
			}
		}
	}

	public static final class Entry {
		public final String title;
		public final Runnable runnable;

		public Entry(String title, Runnable runnable) {
			this.title = title;
			this.runnable = runnable;
		}
	}
}
