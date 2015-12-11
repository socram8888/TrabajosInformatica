/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.bd;

import es.uv.bd.controller.CampamentoController;
import es.uv.bd.view.CampamentoView;

/**
 *
 * @author diaz
 */
public class Campamento {
    public static final String DRIVER = "oracle.jdbc.OracleDriver";
    public static final String DBURL = "jdbc:oracle:thin:@pokemon2.uv.es:1521:ORCL";
    public static final String USERNAME = "USUARIO_AQUI";
    public static final String PASSWORD = "PASS_AQUI";
    public static final String PFIX = "CP_";
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        CampamentoView view = new es.uv.bd.view.CampamentoView();
        CampamentoController controller = new CampamentoController(view);

        view.setVisible(true);// TODO code application logic here
    }
}
