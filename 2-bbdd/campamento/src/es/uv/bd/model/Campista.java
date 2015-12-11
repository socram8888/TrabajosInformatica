package es.uv.bd.model;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
/**
 *
 * @author diaz
 */
public class Campista {
    private int id;
    private String nombre;
    private String apellidos;
    private int dni;
    private String direccion;
    private int sip;
    private Date fechaNacimiento;
    private List<String> telefonos;

    public Campista() {}

    public Campista(int id, String nombre, String apellidos, int dni, String direccion, int sip, Date fechaNacimiento, List<String> telefonos) {
        this.id = id;
        this.nombre = nombre;
        this.apellidos = apellidos;
        this.dni = dni;
        this.direccion = direccion;
        this.sip = sip;
        this.fechaNacimiento = fechaNacimiento;
        this.telefonos = telefonos;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public String getApellidos() {
        return apellidos;
    }

    public void setApellidos(String apellidos) {
        this.apellidos = apellidos;
    }

    public int getDni() {
        return dni;
    }

    public void setDni(int dni) {
        this.dni = dni;
    }

    private static final String LETRAS_NIF = "TRWAGMYFPDXBNJZSQVHLCKE";
    private char letraDNI(int dni) {
        return LETRAS_NIF.charAt(dni % LETRAS_NIF.length());
    }
    
    private static final Pattern NIF_PATTERN = Pattern.compile("^([0-9]{1,8})([A-Za-z])$");
    public void setNif(String nif) {
        if (nif == null || nif.length() == 0) {
            dni = 0;
            return;
        }

        Matcher mtc = NIF_PATTERN.matcher(nif);
        if (!mtc.matches()) {
            throw new IllegalArgumentException("Formato de NIF no valido");
        }
        int dni = Integer.parseInt(mtc.group(1));
        char letra = mtc.group(2).charAt(0);
        if (letraDNI(dni) != letra) {
            throw new IllegalArgumentException("Letra del DNI no valida");
        }
    }

    public String getNif() {
        if (dni <= 0) {
            return null;
        }
        return String.format("%08d%c", dni, letraDNI(dni));
    }

    public String getDireccion() {
        return direccion;
    }

    public void setDireccion(String direccion) {
        this.direccion = direccion;
    }

    public int getSip() {
        return sip;
    }

    public void setSip(int sip) {
        this.sip = sip;
    }

    public Date getFechaNacimiento() {
        return fechaNacimiento;
    }

    public void setFechaNacimiento(Date fechaNacimiento) {
        this.fechaNacimiento = fechaNacimiento;
    }

    public List<String> getTelefonos() {
        return telefonos;
    }

    public void setTelefonos(List<String> telefonos) {
        this.telefonos = telefonos;
    }

    @Override
    public String toString() {
        return "Campista{" + "id=" + id + ", nombre=" + nombre + ", apellidos=" + apellidos + ", dni=" + dni + ", direccion=" + direccion + ", sip=" + sip + ", fechaNacimiento=" + fechaNacimiento + ", telefonos=" + telefonos + '}';
    }
}
