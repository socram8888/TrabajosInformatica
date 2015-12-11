package es.uv.bd.test;

import es.uv.bd.model.Campista;
import es.uv.bd.model.CampistaDAO;
import java.sql.SQLException;
import java.text.ParseException;
import java.util.Arrays;

/**
 *
 * @author diaz
 */
public class CampistaDaoTest {
    private static String modulo = "CampistaDaoTest::";
    private CampistaDAO campistaDao;
    private Campista tobi, pipo;
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        CampistaDaoTest campistaDaoTest = new CampistaDaoTest();
        campistaDaoTest.doTest();
    }

    public CampistaDaoTest() {
        campistaDao = new CampistaDAO();
        
    }
    
    public void doTest() {

        try {
            print("Test 1: Crear campista");
            // (int id, String nombre, String apellidos, int dni, String direccion, int sip, Date fechaNacimiento, List<String> telefonos)
            tobi = new Campista(9999, "Tobi", "Pedrosa Del Monte", 52478642, "Calle Villanueva 9", 12547897, new java.util.Date(), Arrays.asList("964577889", "618589476"));
            campistaDao.crearCampista(tobi);
            print("Test 1: " + tobi + " creada.");
            
            print("Test 2: Buscar campista");
            pipo = campistaDao.leerCampista(tobi.getId());
            print("Test 2: " + pipo + " leído.");
            
            print("Test 3: Cambiar nombre del campista");
            pipo.setNombre("Pipo");
            campistaDao.actualizarCampista(pipo);
            tobi = campistaDao.leerCampista(pipo.getId());
            print("Test 3: " + tobi + " modificada.");
            
            print("Test 4: Borrar campista " + tobi.getId() + " (" + tobi.getNombre() + ")");
            campistaDao.borrarCampista(tobi.getId());
            print("Test 4: Campista borrado");
            
            print("Todos los test correctos");
            
        } catch (ParseException | ClassNotFoundException | InstantiationException | IllegalAccessException | SQLException ex) {
            print("Error ejecutando tests *************************");
            print(" Excepción: " + ex.getMessage());
            print("");
            ex.printStackTrace();
        }
    }
    
    private void print(String string) {
        System.out.println(modulo + string);
    }
}
