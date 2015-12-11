package ti.sazeith.is2.pr1.serialization;

import java.io.IOException;

public interface DataSerializable {
	public void write(DataWriter writer) throws IOException;
}
