package ti.sazeith.is2.pr1;

import java.io.IOException;
import java.io.PrintStream;
import java.util.Calendar;
import java.util.LinkedList;
import java.util.List;

import ti.sazeith.is2.pr1.serialization.DataReader;
import ti.sazeith.is2.pr1.serialization.DataSerializable;
import ti.sazeith.is2.pr1.serialization.DataWriter;

import static org.apache.commons.lang3.Validate.*;

public class Item implements DataSerializable {
	private final int id;
	private Owner owner;
	private String description;
	private Calendar availabilityStart;
	private Calendar availabilityEnd;
	private double pricing;
	private List<Loan> loans = new LinkedList<>();

	public Item(int id, Owner owner, String description) {
		this.id = id;
		setOwner(owner);
		setDescription(description);
	}

	public Item(int id, Owner owner, String description, Calendar start, Calendar end, double pricing) {
		this.id = id;
		setOwner(owner);
		setDescription(description);
		setAvailability(start, end);
		setPricing(pricing);
	}

	public Loan loan(Calendar start, Calendar end) {
		if (!isAvailable()) {
			throw new IllegalStateException("Cannot loan");
		}

		Loan loan = new Loan(this, start, end, getPricing());
		loans.add(loan);
		return loan;
	}

	public boolean isAvailable() {
		return availabilityStart != null;
	}

	public void retire() {
		availabilityStart = null;
		availabilityEnd = null;
	}

	public int getId() {
		return id;
	}

	public Owner getOwner() {
		return owner;
	}

	public void setOwner(Owner owner) {
		notNull(owner, "Owner cannot be null");
		this.owner = owner;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		notBlank(description, "Description not set");
		this.description = description;
	}

	public Calendar getAvailabilityStart() {
		return availabilityStart;
	}

	public Calendar getAvailabilityEnd() {
		return availabilityEnd;
	}

	public void setAvailability(Calendar start, Calendar end) {
		notNull(start, "Start date is null");
		notNull(end, "End date is null");
		isTrue(start.compareTo(end) <= 0, "Start date is smaller than end date");
		this.availabilityStart = start;
		this.availabilityEnd = end;
	}

	public double getPricing() {
		return pricing;
	}

	public void setPricing(double pricing) {
		isTrue(pricing >= 0, "Pricing can't be negative");
		this.pricing = pricing;
	}

	public void printReadable(PrintStream str, boolean recurse) throws IOException {
		if (isAvailable()) {
			str.format(
				"==== Objeto %05d ====\n" +
				"Descripción:    %s\n" +
				"Disponibilidad: %s - %s\n" +
				"Coste por día:  %.2f€\n" +
				"\n",
				getId(),
				getDescription(),
				Conversion.unparseDate(getAvailabilityStart()),
				Conversion.unparseDate(getAvailabilityEnd()),
				getPricing()
			);
		} else {
			str.format(
				"==== Objeto %05d ====\n" +
				"Descripción:    %s\n" +
				"Disponibilidad: no\n" +
				"\n",
				getId(),
				getDescription()
			);
		}

		if (recurse) {
			for (Loan loan : loans) {
				loan.printReadable(str, true);
			}
		}
	}

	private static final int VER = 5;

	public Item(DataReader reader) throws IOException {
		reader.beginRead(this);

		if (reader.readInt() != VER) {
			throw new IOException("Invalid version");
		}
		id = reader.readInt();
		setOwner((Owner) reader.readObject());
		setDescription(reader.readString());
		if (reader.readBoolean()) {
			setAvailability(
						Conversion.parseDate(reader.readString()),
						Conversion.parseDate(reader.readString())
		    );
			setPricing(reader.readDouble());
		}

		reader.enterObject();
		int count = reader.readInt();
		while (count-- > 0) {
			Loan loan = (Loan) reader.readObject();
			loans.add(loan);
		}
		reader.leaveObject();
	}

	public void write(DataWriter writer) throws IOException {
		writer.writeInt(VER);
		writer.writeInt(getId());
		writer.writeObject(getOwner());
		writer.writeString(getDescription());
		writer.writeBoolean(isAvailable());
		if (isAvailable()) {
			writer.writeString(Conversion.unparseDate(getAvailabilityStart()));
			writer.writeString(Conversion.unparseDate(getAvailabilityEnd()));
			writer.writeDouble(getPricing());
		}

		writer.enterObject();
		writer.writeInt(loans.size());
		for (Loan loan : loans) {
			writer.writeObject(loan);
		}
		writer.leaveObject();
	}
}
