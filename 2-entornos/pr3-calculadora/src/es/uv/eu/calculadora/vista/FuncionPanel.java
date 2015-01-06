
package es.uv.eu.calculadora.vista;

/**
 *
 * @author Marcos Vives Del Sol
 */
class FuncionPanel extends ButtonGridPanel {
    private static final String[] BUTTONS = new String[] { "CLEAR" };

    public FuncionPanel() {
        super("func", BUTTONS, 1, 1);
        setSpecial(0);
    }
}
