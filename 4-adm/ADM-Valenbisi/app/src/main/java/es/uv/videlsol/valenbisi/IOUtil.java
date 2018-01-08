package es.uv.videlsol.valenbisi;

import android.content.Context;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;

/**
 * Created by alumno on 21/02/2017.
 */

public final class IOUtil {
    private IOUtil() {
    }

    public static String readResourceAsString(Context ctx, int res) {
        try (InputStream is = ctx.getResources().openRawResource(res)) {
            return readAsString(is);
        } catch (IOException e) {
            // Should never happen in a built-in resource
            throw new RuntimeException(e);
        }
    }

    public static String readAsString(InputStream is) throws IOException {
        return readAsString(new InputStreamReader(is));
    }

    public static String readAsString(Reader reader) throws IOException {
        StringBuilder sb = new StringBuilder();
        char[] buf = new char[8192];

        while (true) {
            int read = reader.read(buf);
            if (read <= 0) {
                break;
            }
            sb.append(buf, 0, read);
        }

        return sb.toString();
    }
}
