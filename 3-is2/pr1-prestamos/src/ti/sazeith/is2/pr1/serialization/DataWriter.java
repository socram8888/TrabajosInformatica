package ti.sazeith.is2.pr1.serialization;

import java.io.Closeable;
import java.io.IOException;
import java.io.Writer;
import java.util.Stack;

public class DataWriter implements Closeable {
	private final Writer writer;
	private final Stack<Object> stack = new Stack<>();
	private int depth = 0;

	public DataWriter(Writer writer) {
		this.writer = writer;
	}

	public void enterObject() throws IOException {
		head();
		writer.write('{');
		tail();
		depth++;
	}

	public void leaveObject() throws IOException {
		if (depth == 0) {
			throw new IllegalStateException("We're not inside any object!");
		}

		depth--;
		head();
		writer.write('}');
		tail();
	}

	public void writeChar(char val) throws IOException {
		head();
		charesc(val);
		tail();
	}

	public void writeBoolean(boolean val) throws IOException {
		head();
		writer.write(Boolean.toString(val));
		tail();
	}

	public void writeByte(byte val) throws IOException {
		head();
		writer.write(Byte.toString(val));
		tail();
	}

	public void writeShort(short val) throws IOException {
		head();
		writer.write(Short.toString(val));
		tail();
	}

	public void writeInt(int val) throws IOException {
		head();
		writer.write(Integer.toString(val));
		tail();
	}

	public void writeLong(long val) throws IOException {
		head();
		writer.write(Long.toString(val));
		tail();
	}

	public void writeFloat(float val) throws IOException {
		head();
		writer.write(Float.toString(val));
		tail();
	}

	public void writeDouble(double val) throws IOException {
		head();
		writer.write(Double.toString(val));
		tail();
	}

	public void writeString(String str) throws IOException {
		head();
		for (int i = 0; i < str.length(); i++) {
			charesc(str.charAt(i));
		}
		tail();
	}

	public void writeObject(Object obj) throws IOException {
		int stackPos = -1;
		if (obj == null) {
			stackPos = 0;
		} else {
			stackPos = stack.indexOf(obj);
			if (stackPos >= 0) {
				stackPos++;
			}
		}
		if (stackPos != -1) {
			head();
			writer.write('$');
			writer.write(Integer.toString(stackPos));
			tail();
			return;
		}

		if (!(obj instanceof DataSerializable)) {
			throw new UnsupportedOperationException("Generic object serialization not yet implemented");
		}

		DataSerializable ser = (DataSerializable) obj;

		enterObject();
		writeString(obj.getClass().getCanonicalName());
		stack.push(obj);
		ser.write(this);
		stack.pop();
		leaveObject();
	}

	@Override
	public void close() throws IOException {
		writer.close();
	}

	private void head() throws IOException {
		for (int i = 0; i < depth; i++) {
			writer.write('\t');
		}
	}

	private void tail() throws IOException {
		writer.write('\n');
	}

	private void charesc(char c) throws IOException {
		switch (c) {
			case '\\':
				writer.write("\\\\");
				return;
			case '\n':
				writer.write("\\n");
				return;
			case '\r':
				writer.write("\\r");
				return;
			case '\0':
				writer.write("\\0");
				return;
			case '\t':
				writer.write("\\t");
				return;
		}

		/* TODO: Handle Unicode */
		writer.write(c);
	}
}
