package ti.sazeith.is2.pr1;

import static org.apache.commons.lang3.Validate.*;

import java.io.IOException;
import java.io.PrintStream;
import java.util.Calendar;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

import ti.sazeith.is2.pr1.serialization.DataReader;
import ti.sazeith.is2.pr1.serialization.DataSerializable;
import ti.sazeith.is2.pr1.serialization.DataWriter;

public class Owner implements DataSerializable {
	private final int id;
	private String name;
	private String email;
	private Map<Integer, Item> items = new HashMap<>();

	public Owner(int id, String name, String email) {
		this.id = id;
		setName(name);
		setEmail(email);
	}

	public int getId() {
		return id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		notBlank(name, "Name not set");
		this.name = name;
	}

	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		notEmpty(email, "Email not set");
		this.email = Conversion.parseEmail(email);
	}

	public Item newItem(int id, String description, Calendar start, Calendar end, double pricing) {
		Item item = new Item(id, this, description, start, end, pricing);
		items.put(id,  item);
		return item;
	}

	public Map<Integer, Item> getItems() {
		return items;
	}

	public void printReadable(PrintStream str, boolean recurse) throws IOException {
		str.format(
			"==== Propietario %05d ====\n" +
			"Nombre: %s\n" +
			"Email:  %s\n" +
			"\n",
			getId(),
			getName(),
			getEmail()
		);

		if (recurse) {
			for (Item item : items.values()) {
				item.printReadable(str, true);
			}
		}
	}

	private static final int VER = 2;

	public Owner(DataReader reader) throws IOException {
		reader.beginRead(this);

		if (reader.readInt() != VER) {
			throw new IOException("Invalid version");
		}
		id = reader.readInt();
		setName(reader.readString());
		setEmail(reader.readString());

		reader.enterObject();
		int count = reader.readInt();
		while (count-- > 0) {
			Item item = (Item) reader.readObject();
			items.put(item.getId(), item);
		}
		reader.leaveObject();
	}

	public void write(DataWriter writer) throws IOException {
		writer.writeInt(VER);
		writer.writeInt(id);
		writer.writeString(name);
		writer.writeString(email);

		writer.enterObject();
		Collection<Item> items = this.items.values();
		writer.writeInt(items.size());
		for (Item item : items) {
			writer.writeObject(item);
		}
		writer.leaveObject();
	}
}
