package ti.sazeith.is2.pr1.iface;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Calendar;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

import ti.sazeith.is2.pr1.*;
import ti.sazeith.is2.pr1.serialization.*;

public class Main {
	private final File database;

	int nextOwnerId = 0;
	int nextItemId = 0;

	private Map<Integer, Owner> owners = new HashMap<>();
	private Map<Integer, Item> items = new HashMap<>();

	boolean keepGoing = true;

	public Main(String database) {
		this.database = new File(database);
		loadStuff();

		Menu menu = new Menu(
				new Menu.Entry("Alta de propietario", new Runnable() {
					@Override
					public void run() {
						@SuppressWarnings("resource")
						DataReader rd = new DataReader(System.in);
						try {
							System.out.print("Nombre: ");
							String name = rd.readString();

							System.out.print("Email: ");
							String email = rd.readString();

							Owner owner = new Owner(nextOwnerId, name, email);
							nextOwnerId++;

							owners.put(owner.getId(), owner);
							System.out.println("Registrado. ID: " + owner.getId());
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				}),

				new Menu.Entry("Alta de objeto/s", new Runnable() {
					@Override
					public void run() {
						@SuppressWarnings("resource")
						DataReader rd = new DataReader(System.in);
						try {
							System.out.print("Id del propietario: ");
							int ownerId = rd.readInt();

							Owner owner = owners.get(ownerId);
							if (owner == null) {
								System.err.println("Propietario " + ownerId + " inexistente");
								return;
							}

							System.out.print("Descripcion ");
							String desc = rd.readString();

							System.out.print("Inicio disponibilidad (DD/MM/AAAA): ");
							Calendar avSt = Conversion.parseDate(rd.readString());

							System.out.print("Fin disponibilidad (DD/MM/AAAA): ");
							Calendar avEnd = Conversion.parseDate(rd.readString());

							System.out.print("Coste (€/día): ");
							double pricing = rd.readDouble();

							Item item = owner.newItem(nextItemId, desc, avSt, avEnd, pricing);
							nextItemId++;

							items.put(item.getId(), item);
							System.out.println("Registrado. ID: " + item.getId());
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				}),

				new Menu.Entry("Contratación de préstamo", new Runnable() {
					@Override
					public void run() {
						@SuppressWarnings("resource")
						DataReader rd = new DataReader(System.in);
						try {
							System.out.print("Id del objeto: ");
							int itemId = rd.readInt();

							Item item = items.get(itemId);
							if (item == null) {
								System.err.println("Objeto no encontrado");
								return;
							}

							item.printReadable(System.out, false);
							if (!item.isAvailable()) {
								System.err.println("Objeto no disponible para préstamo");
								return;
							}

							System.out.print("Inicio (DD/MM/AAAA): ");
							Calendar start = Conversion.parseDate(rd.readString());

							if (item.getAvailabilityStart().compareTo(start) > 0) {
								System.err.println("La fecha de inicio es anterior al inicio de disponibilidad");
								return;
							}

							System.out.print("Fin (DD/MM/AAAA): ");
							Calendar end = Conversion.parseDate(rd.readString());

							if (item.getAvailabilityEnd().compareTo(end) < 0) {
								System.err.println("La fecha de fin es posterior al fin de disponibilidad");
								return;
							}

							Loan loan = item.loan(start, end);
							loan.printReadable(System.out, false);
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				}),

				new Menu.Entry("Listar todos los objetos", new Runnable() {
					@Override
					public void run() {
						try {
							Collection<Owner> owners = Main.this.owners.values();
							for (Owner owner : owners) {
								owner.printReadable(System.out, true);
							}
						} catch (IOException e) {
							e.printStackTrace();
						}
					}
				}),

				new Menu.Entry("Baja de objeto", new Runnable() {
					@Override
					public void run() {
						@SuppressWarnings("resource")
						DataReader rd = new DataReader(System.in);
						try {
							System.out.print("Id del objeto: ");
							int itemId = rd.readInt();

							Item item = items.remove(itemId);
							if (item == null) {
								System.err.println("No se encuentra el objeto especificado");
								return;
							}
							
							System.out.println("Objeto eliminado satisfactoriamente");
							item.retire();

						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				}),

				new Menu.Entry("Mostrar saldos y salir", new Runnable() {
					@Override
					public void run() {
						try {
							Collection<Owner> owners = Main.this.owners.values();
							for (Owner owner : owners) {
								owner.printReadable(System.out, true);
							}
						} catch (IOException e) {
							e.printStackTrace();
						}

						Main.this.saveStuff();
						Main.this.keepGoing = false;
					}
				})
		);
		
		while (keepGoing) {
			menu.display();
		}
	}

	private static final int VER = 0;

	public void loadStuff() {
		owners.clear();
		nextOwnerId = 0;

		items.clear();
		nextItemId = 0;

		DataReader rd;
		try {
			rd = new DataReader(new FileReader(database));
		} catch (FileNotFoundException e) {
			System.err.println("No database found. Using blank one.");
			return;
		}

		try {
			rd.enterObject();
			if (rd.readInt() != VER) {
				throw new IOException("Invalid object version");
			}

			owners.clear();
			rd.enterObject();
			int ownerCount = rd.readInt();
			while (ownerCount-- > 0) {
				Owner owner = (Owner) rd.readObject();
				owners.put(owner.getId(), owner);
				nextOwnerId = Math.max(nextOwnerId, owner.getId() + 1);

				for (Item item : owner.getItems().values()) {
					items.put(item.getId(), item);
					nextItemId = Math.max(nextItemId, item.getId() + 1);
				}
			}
			rd.leaveObject();

			rd.leaveObject();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				rd.close();
			} catch (Exception e) { }
		}
	}

	public void saveStuff() {
		DataWriter wr = null;

		try {
			wr = new DataWriter(new FileWriter(database));

			wr.enterObject();
				wr.writeInt(VER);
	
				wr.enterObject();
					Collection<Owner> owners = this.owners.values();
					wr.writeInt(owners.size());
					for (Owner owner : owners) {
						wr.writeObject(owner);
					}
				wr.leaveObject();
			wr.leaveObject();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				wr.close();
			} catch (Exception e) { }
		}
	}

	public static void main(String[] args) {
		new Main("database.txt");
	}
}
