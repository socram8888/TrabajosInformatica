package es.uv.bd.model;

import java.sql.*;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;
import javax.swing.table.DefaultTableModel;

/**
 *
 * @author diaz
 */
public class CampistaDAO {
    private final String driver;
    private final String dburl;
    private final String username;
    private final String password;

    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     * Los parámetros de configuración de la DB se han movido a es.uv.bd.Campamento
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

    public CampistaDAO() {
        this(
                es.uv.bd.Campamento.DRIVER,
                es.uv.bd.Campamento.DBURL,
                es.uv.bd.Campamento.USERNAME,
                es.uv.bd.Campamento.PASSWORD,
                es.uv.bd.Campamento.PFIX
        );
    }

    public CampistaDAO(String driver, String dburl, String username, String password, String pfix) {
        this.driver = driver;
        this.dburl = dburl;
        this.username = username;
        this.password = password;
        
        // Esto se ha movido al constructor por el prefijo de la base de datos
        READALL =
            "SELECT id, nombre, apellidos, dni, direccion, sip, fechanacimiento, tel1, tel2, tel3" +
            "  FROM " + pfix + "CAMPISTA" +
            "  ORDER BY id";
        
        CREATE = 
            "INSERT INTO " + pfix + "CAMPISTA (id, nombre, apellidos, dni, direccion, sip, fechanacimiento, tel1, tel2, tel3) " +
            "VALUES (?,?,?,?,?,?,?,?,?,?)";
        
        READ = 
            "SELECT nombre, apellidos, dni, direccion, sip, fechanacimiento, tel1, tel2, tel3" +
            "  FROM " + pfix + "CAMPISTA" +
            " WHERE id = ?";

        UPDATE =
            "UPDATE " + pfix + "CAMPISTA" +
            "   SET nombre = ?, apellidos = ?, dni = ?, direccion = ?, sip = ?, fechanacimiento = ?, tel1 = ?, tel2 = ?, tel3 = ?" +
            " WHERE id = ?";

        DELETE =
            "DELETE FROM " + pfix + "CAMPISTA" +
            " WHERE id = ?";
    }

    private final String CREATE;

    public void crearCampista(Campista campista) throws 
            ClassNotFoundException, InstantiationException, IllegalAccessException, SQLException {

        /*
        * Conexion a la base de datos
        */
        Class.forName(driver);
        Connection oracleConn = DriverManager.getConnection(dburl,username,password);

        oracleConn.setAutoCommit(false);
        // Sentencia de insert
        PreparedStatement insert = oracleConn.prepareStatement(CREATE);
        prepareWriteStatement(insert, campista, 1, 2);
        insert.executeUpdate();
        
        oracleConn.commit();
        oracleConn.setAutoCommit(true);
        oracleConn.close();
    }
    
    private final String READ;
    
    public Campista leerCampista(int id) throws ClassNotFoundException, InstantiationException, IllegalAccessException, SQLException, ParseException {
        Class.forName(driver);
        Connection oracleConn = DriverManager.getConnection(dburl,username,password);

        // Sentencia de insert
        PreparedStatement read = oracleConn.prepareStatement(READ);
        read.setInt(1, id);
        ResultSet rs = read.executeQuery();
        
        Campista campista = null;

        if (rs.next()) {
            campista = readResultSet(rs, -1, 1);
            campista.setId(id);
        }

        return campista;
    }
    
    private final String UPDATE;
    
    public void actualizarCampista(Campista campista) throws ClassNotFoundException, 
           InstantiationException, IllegalAccessException, SQLException {

        /*
        * Conexion a la base de datos
        */
        Class.forName(driver);
        Connection oracleConn = DriverManager.getConnection(dburl,username,password);
           
        oracleConn.setAutoCommit(false);
        // Sentencia de insert
        PreparedStatement update = oracleConn.prepareStatement(UPDATE);
        prepareWriteStatement(update, campista, 10, 1);
        update.executeUpdate();
        
        oracleConn.commit();
        oracleConn.setAutoCommit(true);
        oracleConn.close();
    }

    private final String DELETE;

    public void borrarCampista(int id) throws ClassNotFoundException, 
           InstantiationException, IllegalAccessException, SQLException {
        /*
        * Conexion a la base de datos
        */
        Class.forName(driver);
        Connection oracleConn = DriverManager.getConnection(dburl,username,password);
            
        oracleConn.setAutoCommit(false);
        
        // Sentencia de borrado
        PreparedStatement delete = oracleConn.prepareStatement(DELETE);
        delete.setInt(1, id);
        delete.executeUpdate();
        
        oracleConn.commit();
        oracleConn.setAutoCommit(true);
        oracleConn.close();
    }

    private final String READALL;

    private static final String[] COLUMNAS = {
        "ID",
        "Nombre",
        "Apellidos",
        "NIF",
        "Dirección",
        "SIP",
        "Fecha de nacimiento",
        "Teléfono 1",
        "Teléfono 2",
        "Teléfono 3"
    };

    public DefaultTableModel getTabla() {
        
        DefaultTableModel tablaMascotas = new DefaultTableModel();
        tablaMascotas.setColumnIdentifiers(COLUMNAS);
        System.out.println(READALL);
        try {
            /*
            * Conexion a la base de datos
            */
            Class.forName(driver);
            Connection oracleConn = DriverManager.getConnection(dburl,username,password);
            
            PreparedStatement s = oracleConn.prepareStatement(READALL);
            ResultSet rs = s.executeQuery();

            //Creando las filas para el JTable
            while (rs.next()) {
                Campista campista = readResultSet(rs, 1, 2);

                Object[] fila = new Object[COLUMNAS.length];
                fila[0] = campista.getId();
                fila[1] = campista.getNombre();
                fila[2] = campista.getApellidos();
                fila[3] = campista.getNif();
                fila[4] = campista.getDireccion();
                fila[5] = campista.getSip();
                fila[6] = campista.getFechaNacimiento();

                for (int i = 0; i < 3; i++) {
                    if (i < campista.getTelefonos().size()) {
                        fila[i + 7] = campista.getTelefonos().get(i);
                    }
                }

                tablaMascotas.addRow(fila);
            }
            oracleConn.close();
        } catch (Exception e) {
            System.out.println("CampistaDAO::getTabla -- " + e.getMessage());
        } finally {
            return tablaMascotas;
        }
    }

    private void prepareWriteStatement(PreparedStatement insert, Campista campista, int idPos, int startPos) throws SQLException {
        insert.setInt(idPos, campista.getId());
        insert.setString(startPos + 0, campista.getNombre());
        insert.setString(startPos + 1, campista.getApellidos());
        if (campista.getDni() > 0) {
            insert.setInt(startPos + 2, campista.getDni());
        } else {
            insert.setNull(startPos + 2, java.sql.Types.NUMERIC);
        }
        insert.setString(startPos + 3, campista.getDireccion());
        insert.setInt(startPos + 4, campista.getSip());
        
        java.util.Date nacimientoUtil = campista.getFechaNacimiento();
        java.sql.Date nacimientoSql;
        if (nacimientoUtil instanceof java.sql.Date) {
            nacimientoSql = (java.sql.Date) nacimientoUtil;
        } else {
            nacimientoSql = new java.sql.Date(nacimientoUtil.getTime());
        }
        insert.setDate(startPos + 5, nacimientoSql);

        List<String> telefonos = campista.getTelefonos();
        for (int i = 0; i < 3; i++) {
            if (telefonos != null && i < telefonos.size()) {
                insert.setString(startPos + 6 + i, telefonos.get(i));
            } else {
                insert.setString(startPos + 6 + i, null);
            }
        }
    }

    public Campista readResultSet(ResultSet rs, int idPos, int startPos) throws SQLException {
        Campista campista = new Campista();
        if (idPos > 0) {
            campista.setId(rs.getInt(idPos));
        }

        campista.setNombre(rs.getString(startPos + 0));
        campista.setApellidos(rs.getString(startPos + 1));
        campista.setDni(rs.getInt(startPos + 2));
        campista.setDireccion(rs.getString(startPos + 3));
        campista.setSip(rs.getInt(startPos + 4));
        campista.setFechaNacimiento(rs.getDate(startPos + 5));

        List<String> telefonos = new ArrayList<String>();
        for (int i = 0; i < 3; i++) {
            String telefono = rs.getString(startPos + 6 + i);
            if (telefono != null) {
                telefonos.add(telefono);
            }
        }

        campista.setTelefonos(telefonos);
        return campista;
    }
}
