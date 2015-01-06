package es.uv.eu.calculadora.vista;

class NumerosPanel extends ButtonGridPanel {
    private static final String BUTTONS = "0123456789.C";

    public NumerosPanel() {
        super("num", BUTTONS, 3, 4);
        setSpecial(11);
    }
}
