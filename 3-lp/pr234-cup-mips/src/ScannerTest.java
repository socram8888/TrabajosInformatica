
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.util.HashMap;
import java.util.Map;
import java_cup.runtime.Scanner;
import java_cup.runtime.Symbol;

public class ScannerTest {

    private static Map<Integer, String> SYMBOL_NAMES;
    private static String getSymbolName(int id) {
        if (SYMBOL_NAMES == null) {
            Field[] fields = sym.class.getFields();
            SYMBOL_NAMES = new HashMap<>();
            for (Field field : fields) {
                try {
                    Integer val = (Integer) field.get(null);
                    SYMBOL_NAMES.put(val, field.getName());
                    
                } catch (NullPointerException e) {
                    // Not a static field
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
        return SYMBOL_NAMES.get(id);
    }

    public static void printSymbol(java_cup.runtime.Symbol s) {
        if (s.value != null) {
            System.out.print(getSymbolName(s.sym) + "(" + s.value + ") ");
        } else {
            System.out.print(getSymbolName(s.sym) + " ");
        }

        if (s.sym == sym.TERM || s.sym == sym.EOF) {
            System.out.println();
        }
    }

    public static void testScanner(java_cup.runtime.Scanner scanner) {
        java_cup.runtime.Symbol s;
        do {
            try {
                s = scanner.next_token();
                printSymbol(s);
            } catch (Exception e) {
                e.printStackTrace();
                break;
            }
        } while (s.sym != sym.EOF);
        System.out.println();
    }

    public static void main(String argv[]) {
        if (argv.length != 2) {
            System.out.println("Usage : java <clase> <inputfile> ");
            return;
        }

        Class<? extends Scanner> parserClass;
        try {
            parserClass = (Class<? extends Scanner>) Class.forName(argv[0]);
        } catch (ClassNotFoundException e) {
            System.out.println("Clase no encontrada");
            return;
        }

        Reader reader;
        try {
            reader = new FileReader(argv[1]);
        } catch (FileNotFoundException e) {
            System.out.println("Archivo no encontrado");
            return;
        }

        Scanner scanner = new LexicalAnalyzerMIPS(reader);
        /*try {
            Constructor<? extends Scanner> constructor = parserClass.getConstructor(java.io.Reader.class);
            scanner = constructor.newInstance(reader);
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("Clase no generada correctamente");
            return;
        }*/

        Symbol s = null;
        do {
            try {
                s = scanner.next_token();
                printSymbol(s);
            } catch (Exception e) {
                e.printStackTrace();
            }
        } while (s == null || s.sym != sym.EOF);
    }
}
