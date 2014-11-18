package es.uv.eu.calculadora.vista;

class OperacionesPanel extends ButtonGridPanel {
    private static final String BUTTONS = "+-*/=";

    public OperacionesPanel() {
        super("op", BUTTONS, 1, 5);
        for (int i = 0; i < BUTTONS.length(); i++) {
            setSpecial(i);
        }
    }
}
