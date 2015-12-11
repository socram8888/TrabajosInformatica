package ti.sazeith.is2.pr1;

import java.io.IOException;
import java.io.PrintStream;
import java.util.Calendar;

import ti.sazeith.is2.pr1.serialization.DataReader;
import ti.sazeith.is2.pr1.serialization.DataSerializable;
import ti.sazeith.is2.pr1.serialization.DataWriter;

import static org.apache.commons.lang3.Validate.*;

public class Loan implements DataSerializable {
	private final Item item;
	private Calendar start;
	private Calendar end;
	private double pricing;

	public Loan(Item item, Calendar start, Calendar end, double pricing) {
		notNull(item, "Item cannot be null");
		this.item = item;
		setDates(start, end);
		setPricing(pricing);
	}

	public Item getItem() {
		return item;
	}

	public Calendar getStart() {
		return start;
	}

	public Calendar getEnd() {
		return end;
	}

	public void setDates(Calendar start, Calendar end) {
		notNull(start, "Start date is null");
		notNull(end, "End date is null");

		if (start.compareTo(end) > 0) {
			throw new IllegalArgumentException("Invalid loan dates: end date is previous to start date");
		}

		this.start = start;
		this.end = end;
	}

	public double getPricing() {
		return pricing;
	}

	public void setPricing(double pricing) {
		isTrue(pricing >= 0, "Pricing can't be negative");
		this.pricing = pricing;
	}

	public double getTotalCost() {
		return pricing * getDays();
	}

	public int getDays() {
		return (int) (end.getTimeInMillis() - start.getTimeInMillis()) / (24 * 60 * 60 * 1000) + 1;
	}

	public void printReadable(PrintStream str, boolean recurse) throws IOException {
		str.format(
			"==== Préstamo ====\n" +
			"Fechas: %s - %s\n" +
			"Coste:  %.2f€\n" +
			"\n",
			Conversion.unparseDate(getStart()),
			Conversion.unparseDate(getEnd()),
			getTotalCost()
		);
	}

	private static final int VER = 2;

	public Loan(DataReader reader) throws IOException {
		reader.beginRead(this);

		if (reader.readInt() != VER) {
			throw new IOException("Invalid version");
		}
		item = (Item) reader.readObject();
		setDates(
					Conversion.parseDate(reader.readString()),
					Conversion.parseDate(reader.readString())
	    );
		setPricing(reader.readDouble());
	}

	public void write(DataWriter writer) throws IOException {
		writer.writeInt(VER);
		writer.writeObject(item);
		writer.writeString(Conversion.unparseDate(getStart()));
		writer.writeString(Conversion.unparseDate(getEnd()));
		writer.writeDouble(getPricing());
	}
}
