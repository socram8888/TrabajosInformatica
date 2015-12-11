package ti.sazeith.is2.pr1.serialization;

import java.io.FilterReader;
import java.io.IOException;
import java.io.Reader;
import java.nio.CharBuffer;

public class CountingReader extends FilterReader {
	private int counter = 0;
	private int markCounter = 0;

	public CountingReader(Reader parent) {
		super(parent);
	}

	public int getPosition() {
		return counter;
	}

	@Override
	public void mark(int readAheadLimit) throws IOException {
		in.mark(readAheadLimit);
		markCounter = 0;
	}

	@Override
	public int read() throws IOException {
		int c = in.read();
		if (c != -1) {
			counter++;
			markCounter++;
		}
		return c;
	}

	@Override
	public int read(char[] cbuf) throws IOException {
		int count = in.read(cbuf);
		if (count > 0) {
			counter += count;
			markCounter += count;
		}
		return count;
	}

	@Override
	public int read(char[] cbuf, int off, int len) throws IOException {
		int count = in.read(cbuf, off, len);
		if (count > 0) {
			counter += count;
			markCounter += count;
		}
		return count;
	}

	@Override
	public int read(CharBuffer target) throws IOException {
		int count = in.read(target);
		if (count > 0) {
			counter += count;
			markCounter += count;
		}
		return count;
	}

	@Override
	public void reset() throws IOException {
		in.reset();
		counter -= markCounter;
		markCounter = 0;
	}

	@Override
	public long skip(long n) throws IOException {
		long count = in.skip(n);
		counter += count;
		markCounter += count;
		return count;
	}
}
