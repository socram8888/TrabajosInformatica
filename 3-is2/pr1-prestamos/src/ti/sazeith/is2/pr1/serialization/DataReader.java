package ti.sazeith.is2.pr1.serialization;

import java.io.Closeable;
import java.io.EOFException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.Stack;

public class DataReader implements Closeable {
	private final Reader reader;
	private final Stack<DataSerializable> stack = new Stack<>();
	private int depth = 0;

	public DataReader(InputStream stream) {
		this(new InputStreamReader(stream));
	}

	public DataReader(Reader reader) {
		this.reader = reader;
	}

	public void enterObject() throws IOException {
		head();
		if (inp() != '{') {
			throw new IOException("Not a leader object marker");
		}
		tail();
		depth++;
	}

	public void leaveObject() throws IOException {
		if (depth == 0) {
			throw new IllegalStateException("We're not inside any object!");
		}
		depth--;
		head();
		if (inp() != '}') {
			throw new IOException("Not a leaving object marker");
		}
		tail();
	}

	public char readChar() throws IOException {
		head();
		char c = inp();
		if (c == '\\') {
			c = unescape();
		}
		tail();
		return c;
	}

	public boolean readBoolean() throws IOException {
		try {
			return Boolean.parseBoolean(readString());
		} catch (NumberFormatException e) {
			throw new IOException("Invalid boolean", e);
		}
	}

	public byte readByte() throws IOException {
		try {
			return Byte.parseByte(readString());
		} catch (NumberFormatException e) {
			throw new IOException("Invalid byte", e);
		}
	}

	public short readShort() throws IOException {
		try {
			return Short.parseShort(readString());
		} catch (NumberFormatException e) {
			throw new IOException("Invalid short", e);
		}
	}

	public int readInt() throws IOException {
		try {
			return Integer.parseInt(readString());
		} catch (NumberFormatException e) {
			throw new IOException("Invalid integer", e);
		}
	}

	public long readLong() throws IOException {
		try {
			return Integer.parseInt(readString());
		} catch (NumberFormatException e) {
			throw new IOException("Invalid long", e);
		}
	}

	public float readFloat() throws IOException {
		try {
			return Float.parseFloat(readString());
		} catch (NumberFormatException e) {
			throw new IOException("Invalid float", e);
		}
	}

	public double readDouble() throws IOException {
		try {
			return Double.parseDouble(readString());
		} catch (NumberFormatException e) {
			throw new IOException("Invalid double", e);
		}
	}

	public String readString() throws IOException {
		head();
		return tillNL();
	}

	public Object readObject() throws IOException {
		head();

		switch (inp()) {
			case '$':
				int pos = Integer.parseInt(tillNL());
				if (pos == 0) {
					return null;
				}
				return stack.get(pos - 1);

			case '{':
				tail();
				depth++;

				// TODO: Catch ClassNotFoundException
				Class<?> clazz;
				try {
					clazz = Class.forName(readString());
				} catch (ClassNotFoundException e) {
					throw new IOException("Attempted to deserialize non-existant class", e);
				}

				Constructor<?> constructor;
				try {
					constructor = clazz.getConstructor(DataReader.class);
				} catch (NoSuchMethodException e) {
					throw new RuntimeException("Missing constructor for deserialization for " + clazz.getCanonicalName(), e);
				}

				Object obj;
				try {
					obj = constructor.newInstance(this);
				} catch (InvocationTargetException e) {
					Throwable cause = e.getCause();
					if (cause instanceof IOException) {
						throw (IOException) cause;
					}
					throw (RuntimeException) cause;
				} catch (InstantiationException | IllegalAccessException | IllegalArgumentException e) {
					throw new RuntimeException(e);
				}

				leaveObject();
				stack.pop();
				return obj;
		}

		throw new IOException("Missing object marker");
	}

	public void beginRead(DataSerializable ser) {
		stack.push(ser);
	}

	@Override
	public void close() throws IOException {
		reader.close();
	}

	private char inp() throws IOException {
		int c = reader.read();
		if (c < 0) {
			throw new EOFException();
		}
		return (char) c;
	}

	private void head() throws IOException {
		for (int i = 0; i < depth; i++) {
			if (inp() != '\t') {
				throw new IOException("Missing leading tabs");
			}
		}
	}

	private void tail() throws IOException {
		char c = inp();
		if (c == '\n' || c == '\r' && inp() == '\n') {
			return;
		}
		throw new IOException("Missing newline");
	}

	private char unescape() throws IOException {
		char c = inp();
		switch (c) {
			case '\\':
				return '\\';
			case 'n':
				return '\n';
			case 'r':
				return '\r';
			case '\0':
				return '\0';
			case '\t':
				return '\t';
		}

		/* TODO: Handle Unicode */
		return c;
	}

	private String tillNL() throws IOException {
		StringBuilder sb = new StringBuilder(16);
		while (true) {
			char c = inp();
			if (c == '\n' || c == '\r' && inp() == '\n') {
				break;
			}
			if (c == '\\') {
				c = unescape();
			}
			sb.append(c);
		}

		return sb.toString();
	}
}
